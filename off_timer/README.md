# ESP32 Firmware

This directory contains the firmware used by **Off Timer**.

The ESP32 exposes a lightweight HTTP server on the local network and waits for commands from the Android application. When a valid request is received, it controls a relay connected to one of its GPIO pins.

---

## Features

- Wi-Fi connectivity
- Automatic discovery using mDNS
- Embedded HTTP server
- Relay control
- Simple REST API
- Designed for local network communication

---

## Hardware Requirements

- ESP32 Development Board
- Relay Module (5V or 3.3V compatible)
- Device to be controlled
- Wi-Fi network

---

## Pin Configuration

| Component | GPIO   |
| --------- | ------ |
| Relay     | GPIO 2 |

> Change `RELAY_PIN` in the source code if your relay is connected to a different GPIO.

---

## Wi-Fi Configuration

Update the following variables before uploading the firmware.

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

## mDNS Service

After connecting to Wi-Fi, the ESP32 advertises itself using **mDNS**.

**Hostname**

```
esp32-device.local
```

**Service**

```
_http._tcp
```

**TXT Records**

| Key    | Value    |
| ------ | -------- |
| device | esp32    |
| type   | presence |

This allows the Android application to automatically discover compatible ESP32 devices on the local network without requiring manual IP configuration.

---

# REST API

## Test Connection

Tests communication between the Android application and the ESP32.

### Request

```
GET /test
```

### Response

```
200 OK
```

### Behavior

- Toggles the relay for approximately one second.
- Used to verify connectivity.

---

## Turn Off Device

Triggers the relay to perform the configured shutdown action.

### Request

```
GET /turn-off
```

### Response

```
200 OK
```

### Behavior

Activates the relay connected to GPIO 2.

---

# Communication Flow

```
Android App
      │
      ▼
mDNS Discovery
      │
      ▼
ESP32 Web Server
      │
      ▼
HTTP GET Request
      │
      ▼
Relay Activation
      │
      ▼
Connected Device
```

---

# Serial Output

During startup the ESP32 reports:

- Wi-Fi connection status
- Assigned IP address
- mDNS initialization
- HTTP server status
- Incoming API requests

Example:

```
Connecting to Wi-Fi...
Connected! IP Address: 192.168.1.10

mDNS Started

Web server started successfully.

API Called: /test received!
API Called: /turn-off received!
```

---

# Upload Instructions

1. Install the ESP32 board package in the Arduino IDE.
2. Install the required libraries:
   - ESPAsyncWebServer
   - ESPmDNS
3. Configure your Wi-Fi credentials.
4. Select your ESP32 board.
5. Upload the firmware.
6. Connect the relay module to the configured GPIO pin.

---

# Notes

- The ESP32 and Android device must be connected to the same local network.
- No cloud services are used.
- All communication happens locally using HTTP.
- Device discovery is performed automatically through mDNS.

---

# License

This firmware is provided for educational and personal use.
