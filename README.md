## 🌍 Языки | Languages  

🇷🇺 [Русский](https://github.com/CyberScopeToday/ESP32-Uptime-Monitor/blob/main/READMERU.md)  
🇬🇧 [English](https://github.com/CyberScopeToday/ESP32-Uptime-Monitor/tree/main)  


# 🌐 ESP32 Uptime Monitor  

📡 ESP32 Uptime Monitor is a web-based uptime monitoring system for ESP32. It periodically checks websites and IPs, measures response times, and displays results in a retro-style web interface with a cool Matrix Rain effect. 💾  

![image](https://github.com/user-attachments/assets/db658d59-ec60-40e3-8169-6f690d37fe7c)

---

## 📖 Table of Contents  

- Features  
- Requirements  
- Dependencies  
- File Structure  
- Installation  
- Configuration  
- Web Interface  
- API Endpoints  
- Contributing  
- License 

---

## ✨ Features  

✔️ Monitors Websites & IPs – Checks availability of defined URLs and IP addresses.  
✔️ Response Time Tracking – Measures and displays response time.  
✔️ Adjustable Check Interval – Interval can be modified via web interface.  
✔️ Web Interface – Manage sites, check statuses, and change settings.  
✔️ Matrix Rain Effect – Retro-style aesthetic for a cool hacker look. 😎  
✔️ SPIFFS Storage – Saves configuration in config.json on ESP32.  
✔️ Runs Independently – No need for external servers.  

---

## 🔧 Requirements  

- ESP32 Development Board  
- Arduino IDE (or PlatformIO)  
- Wi-Fi Connection  
- SPIFFS Filesystem Support  

---

## 📦 Dependencies  

This project uses the following libraries:  

- WiFi.h – Wi-Fi connection  
- WiFiClientSecure.h – Secure HTTP requests  
- HTTPClient.h – HTTP communication  
- WebServer.h – Web interface  
- SPIFFS.h – File storage  
- ArduinoJson – JSON parsing  

---

## 📂 File Structure  

ESP32-Uptime-Monitor/  
│── data/  (Files to upload to SPIFFS)  
│   ├── index.html  (Web interface)  
│   ├── style.css  (Optional - for future styling)  
│   ├── script.js  (Optional - for future enhancements)  
│── src/  (Source code)  
│   ├── main.ino  (Main ESP32 code)  
│   ├── config.json  (Configuration file stored in SPIFFS)  
│── .gitignore  (Ignore unnecessary files)  
│── README.md  (Documentation)  
│── LICENSE  (MIT License)  

---

## 🚀 Installation  

### 1️⃣ Clone the Repository  

git clone https://github.com/CyberScopeToday/ESP32-Uptime-Monitor.git  

### 2️⃣ Open in Arduino IDE / PlatformIO  

- Open main.ino in Arduino IDE.  
- Install required ESP32 board support from the Boards Manager.  

### 3️⃣ Set Up SPIFFS Filesystem  

To upload index.html to SPIFFS:  

- Install the ESP32 Sketch Data Upload Plugin:  
  - Download: ESP32 SPIFFS Tool (https://github.com/me-no-dev/arduino-esp32fs-plugin)  
  - Extract & place it into:  
    - Windows: C:\Users\<YourUser>\Documents\Arduino\tools  
    - Mac/Linux: ~/Arduino/tools/  
  - Restart Arduino IDE.  
  - Go to Tools > ESP32 Sketch Data Upload to upload files.  

### 4️⃣ Modify config.json  

Edit config.json inside the /data/ folder before uploading:  

{  
  "wifi_ssid": "Your_WiFi_Name",  
  "wifi_password": "Your_WiFi_Password",  
  "urls": [  
    "https://example.com",  
    "https://arduino.cc",  
    "https://google.com"  
  ],  
  "interval": 30  
}  

### 5️⃣ Upload the Firmware  

- Select your ESP32 board in Tools > Board  
- Choose the correct COM port  
- Click Upload 🚀  

---

## ⚙️ Configuration  

Modify settings via Web Interface or by editing config.json:  

Parameter | Description  
------------ | -------------  
wifi_ssid | Wi-Fi network name  
wifi_password | Wi-Fi password  
urls | List of websites to monitor  
interval | Check interval (seconds)  

---

## 🖥️ Web Interface  

Once ESP32 is running, open http://[ESP32-IP]/ in a browser.  

### Features:  

✔ Live Site Statuses – View real-time uptime & response times  
✔ Add/Delete Sites – Manage monitored URLs  
✔ Change Interval – Adjust monitoring frequency  

---

## 📡 API Endpoints  

Method | Endpoint | Description  
------------ | ------------- | -------------  
GET | /status | Returns site statuses as JSON  
POST | /addSite | Adds a new site (url param)  
POST | /deleteSite | Deletes site by index  
POST | /setInterval | Changes check interval  

Example JSON response from /status:  

[  
  { "url": "https://example.com", "status": "Up", "response_time": 123 },  
  { "url": "https://arduino.cc", "status": "Down", "response_time": -1 }  
]  

---

## 🤝 Contributing  

Contributions are welcome! 🎉  

1. Fork the repo  
2. Create a new branch  
3. Commit your changes  
4. Open a pull request  

---

## 📜 License  

This project is licensed under the MIT License. See LICENSE for details.  
