# SmartMedicine Ball — Smart Training Performance Tracker

## Project Overview

**SmartMedicine Ball** is a smart medicine ball prototype developed as part of the CM2024 Technology and Health Project Course at KTH Royal Institute of Technology.

The project aims to improve performance tracking during medicine ball exercises by automatically detecting and counting repetitions.

The system uses a Seeed Studio XIAO nRF52840 microcontroller with a built-in Inertial Measurement Unit (IMU) to measure acceleration and angular velocity. The sensor data is processed using Arduino/C++ algorithms to identify different motion states and detect completed throws.

The collected data is transmitted via Bluetooth Low Energy (BLE) to a web application, allowing users to monitor their training performance.

---

## Repository Structure

### `Arduino Scripts/`
Contains the Arduino/C++ source code for sensor data acquisition, motion detection, repetition counting, and Bluetooth communication.

---


### `Prototype Sensor Case/`
Contains CAD models and 3D-printing files for the sensor enclosure designed in Autodesk Inventor.

---

### `Explanation Video/`
Contains a video demonstrating the prototype and explaining its functionality.

---

### `Presentation/`
Contains presentation materials describing the project's development, implementation, and results.

---

### `Scientific Paper/`
Contains the final scientific report, including the methodology, experimental results, discussion, and conclusions.

---

### `Legacy/`
Contains previous code versions, experiments, and earlier prototype implementations retained for reference.

---

## Summary

The SmartMedicine Ball project demonstrates how motion sensor technology can be integrated into sports equipment to automatically track exercise repetitions.

By processing acceleration and angular velocity measurements, the prototype identifies medicine ball movements and detects completed throws. The collected information is transmitted wirelessly to a web application, providing users with training feedback.

---

## Purpose

The purpose of this project is to develop a smart medicine ball that simplifies performance tracking during exercise.

The main objectives are to:

- Detect medicine ball throws using IMU sensor data.
- Automatically count completed repetitions.
- Identify different motion states through sensor data processing.
- Transmit training data using Bluetooth Low Energy.
- Display training information through a web application.

---

## License

This project was developed for educational purposes as part of the CM2024 Technology and Health Project Course at KTH Royal Institute of Technology.

No specific open-source license has been assigned.

If you use, modify, or build upon this project, please acknowledge the original developers and provide a link to this repository.

---

## 👥 Credits

- **SmartMedicine Ball Project Group — CM2024, KTH Royal Institute of Technology** — Development, implementation, testing, and documentation of the project.
- **SmartServeBall (2025)** — The structure of this README was inspired by their project.

### Attribution

If you use, modify, or build upon any part of this project, including its source code, hardware design, algorithms, or documentation, please give appropriate credit to the **SmartMedicine Ball Project Group** and include a link to this GitHub repository.
