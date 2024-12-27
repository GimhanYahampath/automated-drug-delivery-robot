# Automated Drug Delivery Robot

![GitHub repo size](https://img.shields.io/github/repo-size/yourusername/automated-drug-delivery-robot)
![GitHub stars](https://img.shields.io/github/stars/yourusername/automated-drug-delivery-robot?style=social)
![GitHub forks](https://img.shields.io/github/forks/yourusername/automated-drug-delivery-robot?style=social)
![GitHub issues](https://img.shields.io/github/issues/yourusername/automated-drug-delivery-robot)
![GitHub license](https://img.shields.io/github/license/yourusername/automated-drug-delivery-robot)
![GitHub top language](https://img.shields.io/github/languages/top/yourusername/automated-drug-delivery-robot)
![GitHub languages count](https://img.shields.io/github/languages/count/yourusername/automated-drug-delivery-robot)

## Overview
The **Automated Drug Delivery Robot** is an innovative solution designed to autonomously administer medicine to a sick child at home. This robot ensures timely medication delivery, detects the patient’s presence, and notifies caregivers if necessary.

### Features
- **Scheduled Medicine Dispensing**: Dispenses medicine from three separate wells at predefined times.
- **Autonomous Navigation**: Moves to the patient’s bedside.
- **Patient Detection**: Uses sensors to verify the patient’s presence.
- **Notification System**: Sends alerts if the patient is not in bed or after successful medication delivery.
- **Return to Base**: Returns to its original position after completing the task.

---

## Getting Started

### Prerequisites
Ensure you have the following hardware and software:

#### Hardware:
- ESP32 Microcontroller
- Servo Motor
- Ultrasonic Sensor (HC-SR04)
- L298N Motor Driver
- 4-Wheel Chassis Kit

#### Software:
- [Arduino IDE](https://www.arduino.cc/en/software)
- Required Libraries:
  - NewPing
  - ESP32Servo
  - Other necessary dependencies

---

### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/automated-drug-delivery-robot.git
   cd automated-drug-delivery-robot
   ```

2. Open the Arduino IDE and install the required libraries via the Library Manager.

3. Connect the ESP32 board and upload the `final.ino` file.

4. Assemble the robot according to the hardware setup provided in the documentation.

---

## Usage

1. Power on the robot and ensure all connections are secure.
2. The robot will:
   - Dispense medicine as per schedule.
   - Navigate to the patient’s bedside.
   - Sound an alarm to alert the patient.
   - Return to its base position after task completion.

3. Monitor notifications sent to the caregiver for patient status updates.

---

## Contributing
We welcome contributions from the community to improve this project. Please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature/bug fix.
3. Submit a pull request with detailed descriptions of your changes.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments
- Open-source libraries and contributors.
- Mentors and colleagues for guidance and support.
- [ThingSpeak](https://thingspeak.com) for IoT data visualization.

---

## Contact
For inquiries or feedback, please contact [your email/contact info].
