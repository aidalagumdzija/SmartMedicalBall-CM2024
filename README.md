# 🏐 Smart Medicine Ball — Smart Training Performance Tracker

## 📘 Project Overview

The **Smart Medicine Ball** project combines embedded sensor technology, wireless communication, and motion analysis to automatically detect and count repetitions during medicine ball exercises.

The goal is to simplify performance tracking during high-intensity workouts, such as HYROX and CrossFit, where athletes often need to manually count their repetitions.

Using a **Seeed Studio XIAO nRF52840** microcontroller with a built-in 6-axis IMU (LSM6DS3), the system measures acceleration and angular velocity to identify:

- When the medicine ball is stationary.
- When the ball is in motion.
- When a throw has been detected.
- The number of completed repetitions.

The processed data is transmitted via **Bluetooth Low Energy (BLE)** to a web application, allowing users to monitor their training performance.

This project was developed as part of the **CM2024 Technology and Health Project Course at KTH Royal Institute of Technology**.

---

## 📁 Repository Structure

### 💻 `SeeedIMU/`

Contains the Arduino/C++ source code developed for the Smart Medicine Ball, including:

- IMU sensor data acquisition and processing.
- Motion state identification using acceleration measurements.
- Throw detection and repetition counting algorithms.
- Bluetooth Low Energy (BLE) communication.

The code is developed for the Seeed Studio XIAO nRF52840 microcontroller.

---

### 🛠️ `Prototype Design/`

Contains the design files and images of the physical prototype, including:

- Autodesk Inventor CAD files for the sensor enclosure.
- 3D-printing files for the enclosure.
- Images of the assembled prototype.

The enclosure is designed to secure and protect the electronic components inside the medicine ball during exercise.

---

### 🎥 `Explanation Video/`

Contains a demonstration video presenting:

- The Smart Medicine Ball prototype.
- An explanation of the system and its functionality.
- A demonstration of the repetition-counting process.

---

### 📊 `Presentation/`

Contains project presentation materials covering:

- Project background and objectives.
- Hardware and software development.
- System implementation.
- Experimental results and conclusions.

---

### 📄 `Scientific Paper/`

Contains the scientific report documenting:

- Project background and related research.
- Hardware design and methodology.
- Motion detection algorithms.
- Experimental testing and results.
- Discussion, limitations, and conclusions.

---

### 🗃️ `Legacy/`

Contains earlier versions of source code, experiments, and prototype implementations retained for reference and future development.

---

## 🧩 Summary

| Component | Description |
|---|---|
| **Microcontroller** | Seeed Studio XIAO nRF52840 |
| **Motion Sensor** | Built-in 6-axis IMU (LSM6DS3) |
| **Embedded Software** | Arduino/C++ for motion detection and repetition counting |
| **Wireless Communication** | Bluetooth Low Energy (BLE) |
| **Web Application** | Visualization of training data |
| **Mechanical Design** | 3D-printed sensor enclosure designed in Autodesk Inventor |
| **Documentation** | Scientific report and project presentation |
| **Demonstration** | Prototype explanation video |

---

## 🎯 Purpose

The Smart Medicine Ball project demonstrates how embedded sensor technology can be integrated into conventional sports equipment to provide automatic repetition counting and training feedback.

The prototype serves as a foundation for further development of sensor-based performance tracking in sports technology.

---

## 📜 License

This project was developed for educational purposes as part of the **CM2024 Technology and Health Project Course at KTH Royal Institute of Technology**.

No specific open-source license has been assigned.

If you use, modify, or build upon this project, please acknowledge the original developers and provide a link to this repository.

---

## 👥 Credits

- **SmartMedicineBall (2026) — CM2024, KTH Royal Institute of Technology** — Development, implementation, testing, and documentation of the Smart Medicine Ball project.
- **SmartServeBall (2025)** — The structure of this README and the halftime report was inspired by their project.

### Attribution for Future Projects

If you use, modify, or build upon any part of this project, including its source code, hardware design, algorithms, or documentation, please give appropriate credit to the **Smart Medicine Ball Project Group** and include a link to this GitHub repository.

We encourage future students and developers to build upon this work while acknowledging the original contributions.
