# Automatic Barrier System

Robotics Homework 1 project created in **Tinkercad** using an **Arduino Uno**.

The project simulates an automatic barrier that detects an approaching object with an HC-SR04 ultrasonic sensor and opens or closes a servo-controlled barrier automatically. LEDs indicate the current barrier state, while a piezo buzzer provides different sounds when opening and closing.

## Features

- Detects objects using an HC-SR04 ultrasonic distance sensor
- Opens the barrier automatically when an object is within **150 cm**
- Closes the barrier when the object moves beyond **170 cm**
- Closes automatically after **2 seconds** if no object is detected
- Red LED indicates that the barrier is closed
- Green LED indicates that the barrier is open
- Different buzzer frequencies are used for opening and closing
- Distance and barrier state are printed to the Serial Monitor

## Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| HC-SR04 ultrasonic sensor | Measures object distance |
| Micro servo | Controls the barrier |
| Red LED | Indicates closed state |
| Green LED | Indicates open state |
| Piezo buzzer | Audible opening/closing feedback |
| 2 × 200 Ω resistors | Current limiting for LEDs |
| Breadboard | Component interconnection |

## Pin Connections

| Component | Arduino Pin |
|---|---|
| Servo signal | D9 |
| HC-SR04 TRIG | D7 |
| HC-SR04 ECHO | D6 |
| Piezo buzzer | D5 |
| Red LED | D4 |
| Green LED | D3 |

The servo and ultrasonic sensor are powered from the Arduino **5 V** and **GND** connections through the breadboard power rails.

## How It Works

The Arduino continuously measures the distance reported by the ultrasonic sensor.

- If the measured distance is **150 cm or less**, the barrier opens.
- The servo moves from **0° to 90°**.
- The red LED turns off and the green LED turns on.
- A **1200 Hz** tone is played while the barrier opens.

When the object moves to **170 cm or farther**, the barrier closes.

- The servo returns to **0°**.
- The green LED turns off and the red LED turns on.
- A **600 Hz** tone is played while the barrier closes.

Using separate opening and closing distances prevents the barrier from rapidly switching states when an object is close to the detection threshold.

If the ultrasonic sensor stops detecting an object while the barrier is open, the barrier closes after approximately **2 seconds**.

## Running the Project

1. Open the project in Tinkercad Circuits.
2. Make sure the circuit is wired according to the schematic.
3. Copy the code from `main.cpp` into the Arduino code editor.
4. Start the simulation.
5. Change the distance of the object in front of the ultrasonic sensor.
6. Observe the servo, LEDs, buzzer, and Serial Monitor.

## Expected Behaviour

### Barrier Closed

- Servo position: **0°**
- Red LED: **ON**
- Green LED: **OFF**

### Barrier Open

- Servo position: **90°**
- Red LED: **OFF**
- Green LED: **ON**

## Project Files

- `main.cpp` — Arduino source code
- `README.md` — project documentation
- Tinkercad circuit/schematic — hardware design

## Possible Improvements

Possible future improvements include:

- Adding a second sensor to detect when a vehicle has fully passed the barrier
- Adding a display for distance or barrier status
- Making the distance thresholds adjustable
- Adding a manual override button
- Adding additional safety logic before closing the barrier

## Youtube Demo
- https://www.youtube.com/watch?v=oLvtGektMMk
