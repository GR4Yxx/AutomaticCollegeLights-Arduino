# AutomaticCollegeLights-Arduino

This Arduino-based project controls college lights using a set of sensors and a Bluetooth-controlled master-slave architecture. The lights are turned on only when necessary, optimizing energy usage and ensuring lights are on only when needed.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

The **AutomaticCollegeLights-Arduino** project is designed to manage the lighting system in a college environment. Using a series of sensors and a Bluetooth module, this system ensures that lights are activated only when people are present and the lighting conditions require it. The master-slave architecture allows for scalable and efficient control over multiple lights across different areas of the college.

## Features

- **Bluetooth Control**: The system uses Bluetooth for communication between the master and slave devices, ensuring reliable and wireless control.
- **Energy Efficiency**: Lights are automatically turned on and off based on sensor data, reducing unnecessary energy consumption.
- **Scalable Architecture**: The master-slave setup allows for easy expansion of the system to cover additional areas or lights.
- **Easy Installation**: Designed with simplicity in mind, the system can be set up and configured with minimal effort.

## Components

- **Arduino Boards (Master and Slaves)**
- **HC-05 Bluetooth Modules**
- **PIR Motion Sensors**
- **Light Dependent Resistors (LDR)**
- **Relays**
- **LEDs or Bulbs**
- **Wires and Breadboards**

## Circuit Diagram

![Circuit Diagram](link_to_your_circuit_diagram_image)

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/AutomaticCollegeLights-Arduino.git
