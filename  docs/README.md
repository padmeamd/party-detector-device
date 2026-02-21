# 📡 Party Detector Device (ESP32)

ESP32 firmware for **Party Detector / Party Patrol** — detects loud noise during quiet hours and sends alerts to a Spring Boot backend via HTTP.

## Hardware
- ESP32 DevKit
- Big Sound sensor module (microphone)

## Wiring (matches firmware defaults)
| Sensor Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| OUT / AO | GPIO34 |

> Use 3.3V (recommended) to keep the signal safe for ESP32 ADC.

## Configuration
Copy:
- `firmware/config.example.h` → `firmware/config.h`

Update:
- WiFi SSID/password
- `SERVER_URL`
- `DEVICE_ID`
- `LOCATION`

## Flashing
1. Open `firmware/party_detector_esp32.ino` in Arduino IDE
2. Select Board: **ESP32 Dev Module**
3. Select the correct port
4. Upload

Open Serial Monitor at **115200 baud** to see readings and alerts.

## Backend
This device sends alerts to:
`POST /api/alerts`

Backend repo:
https://github.com/padmeamd/party-detector-backend