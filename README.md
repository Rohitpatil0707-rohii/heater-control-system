# 🔥 Heater Control System (Arduino-based)

This project simulates a **smart heater control system** using an **Arduino Uno**, **DHT22 temperature sensor**, **I2C LCD**, **buzzer**, and **relay**. The system dynamically adjusts heater states like Idle, Heating, Stabilizing, Target Reached, Too Hot, and Overheat using real-time sensor input and Timer Interrupts for periodic temperature reading.

---

## 🧰 Features

- Temperature Monitoring using **DHT22 Sensor**
- Real-time **state display** on I2C LCD
- "Heater control" using relay module
- "Buzzer alerts" for Overheat & Target Reached
- Efficient **timer interrupt** using `TimerOne` library
- Fully tested on **Wokwi simulator**

---

## 📟 System States

| State Name        | Condition                                    | Action                            |
|-------------------|----------------------------------------------|-----------------------------------|
| **IDLE**          | Default state (fallback case)                | Heater OFF, Buzzer OFF            |
| **HEATING**       | Temp < Target - 1                            | Heater ON, Buzzer OFF             |
| **STABILIZING**   | Temp between Target - 1 and Target           | Heater ON, Buzzer OFF             |
| **TARGET_REACHED**| Temp between Target and Target+2             | Heater OFF, Single beep from buzzer |
| **TOO_HOT**       | Temp > Target+2 and < Overheat               | Heater OFF, Warning Beep          |
| **OVERHEAT**      | Temp ≥ Overheat                              | Heater OFF, Continuous Buzzer     |

---

## 🖼️ System Images

### 🔌 System Overview
![System Overview](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic1.png)

---

### 🪛 Circuit Diagram
![Circuit Diagram](images/image2.png)

---

### 🔥 Heating State Active
![Heating State](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic2.png)

---

### ⚖️ Stabilizing State
![Stabilizing State](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic3.png)

---

### 🎯 Target Reached Display
![Target Reached](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic4.png)

---

### 🚨 Too Hot State (Buzzer Beep)
![Too Hot](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic5.png)

---

### 🔥🔥 Overheat Warning (Continuous Tone)
![Overheat Warning](https://github.com/Rohitpatil0707-rohii/heater-control-system/blob/main/assets/pic6.png)

---

## 🚀 Getting Started

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/your-username/heater-control-system.git
cd heater-control-system
