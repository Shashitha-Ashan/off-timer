# Off Timer

> **A context-aware inactivity detection system for Android powered by ESP32.**

Off Timer is an Android application that intelligently detects when a user becomes inactive by combining multiple behavioral signals instead of relying on a simple countdown timer.

Once the configured inactivity conditions are satisfied, the app communicates with an ESP32 over the local network to perform automation tasks such as turning off connected devices.

> **Note**
>
> This repository contains only the application APK for testing purposes. The source code is not publicly available.

---

## Demo

https://github.com/user-attachments/assets/b2d6ed3f-175e-4c6a-9329-fd56b7e5476f


---

## Download

Download the latest APK from the **Releases** section.

> **Requirements**
>
> - Android 8.0 (API 26) or later
> - ESP32 running the compatible firmware
> - Both devices connected to the same local network

---

# Features

## Context-Aware Inactivity Detection

Instead of using a fixed timer, Off Timer evaluates multiple activity signals to determine whether the user is genuinely inactive.

Current monitoring modules include:

- Screen state
- Network upload/download activity
- Accelerometer motion detection
- Presence confirmation notifications
- Configurable inactivity timer

---

## Custom Presets

Create multiple automation presets by combining different monitoring modules.

Each preset supports configurable:

- Monitoring frequency
- Timeout values
- Grace period
- Enabled monitoring modules

---

## Automatic Device Discovery

No manual IP configuration.

Compatible ESP32 devices are automatically discovered using **mDNS (Multicast DNS)** on the local network.

---

## Local Communication

Once the inactivity conditions are satisfied:

```
Android App
      │
      ▼
Context Engine
      │
      ▼
Grace Period
      │
      ▼
REST API Request
      │
      ▼
ESP32 Web Server
      │
      ▼
Relay / Connected Device
```

Communication happens entirely over the local network.

No cloud services are required.

---

# Architecture

```
                ┌─────────────────────┐
                │    Foreground       │
                │      Service        │
                └──────────┬──────────┘
                           │
                           ▼
                ┌─────────────────────┐
                │   Context Engine    │
                └──────────┬──────────┘
                           │
      ┌────────────────────┼────────────────────┐
      ▼                    ▼                    ▼
 Screen Monitor      Motion Monitor      Network Monitor
      │                    │                    │
      └──────────────┬─────┴─────────────┬──────┘
                     ▼                   ▼
             Presence Monitor      Timer Monitor
                     │
                     ▼
          Inactivity Conditions Met?
                     │
             Grace Period Countdown
                     │
                     ▼
           REST API Request to ESP32
                     │
                     ▼
            Device Automation Action
```

---

# Tech Stack

### Android

- Kotlin
- Jetpack Compose
- Android Foreground Service
- Android Sensor APIs
- Notifications
- mDNS (NSD)
- REST API

### Embedded

- ESP32
- Embedded Web Server
- HTTP REST API

---

# Use Cases

- Automatically turn off devices after falling asleep
- Power down equipment after late-night study sessions
- Automate devices when leaving a room
- Stop unnecessary power consumption
- Home automation projects
- DIY IoT automation

---

# Project Goals

- Context-aware automation
- Local-first communication
- No cloud dependency
- Flexible rule-based monitoring
- Modular architecture for future monitoring modules

---

# Future Ideas

- Bluetooth activity monitoring
- Geofencing
- Charging state monitoring
- Wi-Fi connection state
- Device orientation
- Ambient light sensor
- Machine learning-based inactivity detection
- Multiple ESP32 device management
- Scheduled automation
- Usage analytics

---

# APK

The latest APK can be found in the **Releases** section of this repository.

---

# License

This repository is provided for demonstration purposes only.

The application source code is currently private.
