#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>

WebServer server(80);
WiFiClientSecure client;
String configFile = "/config.json";

// Список сайтов
std::vector<String> urls;
int checkInterval = 30 * 1000; // Интервал проверки (30 сек)
unsigned long lastCheckTime = 0;

// ================== Чтение/сохранение в config.json ==================
void loadConfig() {
    if (!SPIFFS.exists(configFile)) return;
    File file = SPIFFS.open(configFile, "r");
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, file);
    file.close();

    urls.clear();
    for (JsonVariant v : doc["urls"].as<JsonArray>()) {
        urls.push_back(v.as<String>());
    }
    checkInterval = doc["interval"].as<int>() * 1000;
}

void saveConfig() {
    File file = SPIFFS.open(configFile, "w");
    StaticJsonDocument<1024> doc;
    JsonArray arr = doc.createNestedArray("urls");
    for (String url : urls) arr.add(url);
    doc["interval"] = checkInterval / 1000;
    serializeJson(doc, file);
    file.close();
}

// ================== Проверка сайтов ==================
struct SiteStatus {
    String url;
    String status;
    int responseTime;
};
std::vector<SiteStatus> siteResults;

void checkSites() {
    siteResults.clear();
    client.setInsecure(); // Без проверки сертификата

    for (auto &url : urls) {
        HTTPClient http;
        http.begin(client, url);
        unsigned long start = millis();
        int httpCode = http.GET();
        unsigned long end = millis();
        
        SiteStatus result;
        result.url = url;
        if (httpCode > 0) {
            result.status = "Up";
            result.responseTime = end - start;
        } else {
            result.status = "Down";
            result.responseTime = -1;
        }
        
        siteResults.push_back(result);
        http.end();
    }
}

// ================== Обработчики (синхронные) ==================
void handleRoot() {
    // Отдаем index.html из SPIFFS
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
        server.send(500, "text/plain", "Cannot open index.html");
        return;
    }
    server.streamFile(file, "text/html");
    file.close();
}

void handleStatusJson() {
    // Возвращаем JSON со статусами
    DynamicJsonDocument doc(2048);
    JsonArray arr = doc.to<JsonArray>();

    for (auto &site : siteResults) {
        JsonObject obj = arr.createNestedObject();
        obj["url"] = site.url;
        obj["status"] = site.status;
        obj["response_time"] = site.responseTime;
    }

    String json;
    serializeJson(arr, json);
    server.send(200, "application/json", json);
}

void handleAddSite() {
    if (!server.hasArg("url")) {
        server.send(400, "text/plain", "Missing url");
        return;
    }
    String newUrl = server.arg("url");
    urls.push_back(newUrl);
    saveConfig();
    server.send(200, "text/plain", "OK");
}

void handleDeleteSite() {
    if (!server.hasArg("index")) {
        server.send(400, "text/plain", "Missing index");
        return;
    }
    int index = server.arg("index").toInt();
    if (index >= 0 && index < (int)urls.size()) {
        urls.erase(urls.begin() + index);
        saveConfig();
    }
    server.send(200, "text/plain", "OK");
}

void handleSetInterval() {
    if (!server.hasArg("sec")) {
        server.send(400, "text/plain", "Missing sec");
        return;
    }
    checkInterval = server.arg("sec").toInt() * 1000;
    saveConfig();
    server.send(200, "text/plain", "OK");
}

void setup() {
    Serial.begin(115200);
    WiFi.begin("Neutron", "oKx48u93sy@K");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi подключен!");

    SPIFFS.begin(true);
    loadConfig();

    // Регистрируем обработчики
    server.on("/", handleRoot);
    server.on("/status", handleStatusJson);
    server.on("/addSite", HTTP_POST, handleAddSite);
    server.on("/deleteSite", HTTP_POST, handleDeleteSite);
    server.on("/setInterval", HTTP_POST, handleSetInterval);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient(); // Синхронное обслуживание

    unsigned long now = millis();
    if ((now - lastCheckTime) >= checkInterval) {
        lastCheckTime = now;
        checkSites();
    }
}
