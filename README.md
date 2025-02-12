# ESP32 Uptime Monitor

ESP32 Uptime Monitor is a project that periodically checks the availability of specified websites and IP addresses, measures response time, and displays the results in a web interface with a retro "Matrix Rain" effect.

## Features

- **Website and IP Monitoring** - Periodically checks the availability of websites and IPs via HTTPS.
- **Response Time Measurement** - Displays the response time for each monitored resource.
- **Configurable Check Interval** - The interval can be set via the configuration file or web interface.
- **Web Interface for Management** - Add/remove sites and adjust settings easily.
- **Matrix Rain Effect** - Retro animation effect for the background.
- **Persistent Configuration Storage** - Saves settings in SPIFFS (`config.json`).

## Requirements

- **Hardware:** ESP32 (e.g., ESP32 DevKit)
- **Development Environment:** Arduino IDE or PlatformIO
- **Wi-Fi:** A working Wi-Fi connection for monitoring

## Dependencies

This project uses the following libraries:

- WiFi.h
- WiFiClientSecure.h
- HTTPClient.h
- WebServer.h
- SPIFFS.h
- ArduinoJson

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/ESP32-Uptime-Monitor.git
   ```

2. **Open the project in Arduino IDE or PlatformIO.**
3. **Configure Wi-Fi settings** in the code or modify `config.json`.
4. **Upload the firmware** to your ESP32.

## Configuration

Configuration is stored in the `config.json` file (SPIFFS). Example:

```json
{
  "wifi_ssid": "YourWiFi",
  "wifi_password": "YourPassword",
  "urls": [
    "https://example.com",
    "https://arduino.cc"
  ],
  "ips": [
    "8.8.8.8",
    "1.1.1.1"
  ],
  "interval": 30
}
```

- **wifi_ssid** - Wi-Fi network name.
- **wifi_password** - Wi-Fi password.
- **urls** - List of URLs to monitor.
- **ips** - List of IP addresses to monitor.
- **interval** - Check interval in seconds.

## Usage

1. **Find the ESP32 IP address** in the serial monitor.
2. **Access the web interface** using the ESP32 IP address in a browser.
3. **Manage monitoring:**
   - Add a new website by entering the URL and clicking "Add".
   - Remove a website using the delete button.
   - Adjust the check interval and save the settings.

## API Endpoints

- **GET /** - Serves the main HTML interface.
- **GET /status** - Returns a JSON array with website statuses.
- **POST /addSite** - Adds a new site to the monitoring list.
- **POST /deleteSite** - Removes a site from the monitoring list.
- **POST /setInterval** - Updates the monitoring interval.

## Contribution

We welcome contributions! If you find a bug or want to add a new feature, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See `LICENSE` for details.

## Contact

For questions or suggestions, feel free to open an issue in the repository.

