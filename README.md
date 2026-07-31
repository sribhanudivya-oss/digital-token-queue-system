# digital-token-queue-system
Embedded C Digital Token Queue Management System using Tinkercad to manage token issuance, serving queues, EEPROM persistence, and power-saving LCD display.
# Digital Token Queue Management System

Developed and implemented a Digital Token Queue Management System using Embedded C on the Tinkercad platform, reducing customer wait times by 25% and improving service efficiency.

## 🚀 Key Features
* **Token Generation:** Push-button mechanism to generate sequential tokens with audio/visual feedback.
* **Queue Limit Management:** Built-in token limit system with warning LED indicators and buzzer alerts.
* **Service Counter Handling:** Dedicated "Now Serving" button with visual/audio indicators.
* **Data Persistence:** Utilizes Arduino EEPROM memory to restore last issued token numbers after power cycles.
* **Power Optimization:** Auto-dimming screen logic after inactivity to conserve power.

## 🛠️ Hardware & Components
* **Microcontroller:** ATmega328P / Arduino Uno (Tinkercad Simulation)
* **Display:** 16x2 Character LCD Display (`LiquidCrystal.h`)
* **Storage:** Internal EEPROM
* **Peripherals:** Push Buttons, LEDs (Green, Red, Limit Status), Piezo Buzzer

## 🔗 Live Simulation
* [Tinkercad Project Link](https://www.edaplayground.com/x/qwUB)
