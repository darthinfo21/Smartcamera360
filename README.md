# ESP32 Pan-Tilt Camera Control with Face Detection

This project utilizes ESP32 microcontroller along with pan-tilt servo motors for achieving 360-degree movement of a camera module. The project also integrates Wi-Fi connectivity for streaming and implements a Python-based face detection algorithm using OpenCV with Haar cascade classifiers for accurate facial recognition.

## Features

- Incorporates pan-tilt servo motors for achieving 360-degree movement.
- Enables precise camera control using ESP32 microcontroller.
- Establishes Wi-Fi connectivity for streaming video feed.
- Implements Python-based face detection algorithm using OpenCV.
- Utilizes Haar cascade classifiers for accurate facial recognition.

## Requirements

- ESP32 microcontroller board
- Pan-tilt servo motors
- Camera module compatible with ESP32
- Python environment with OpenCV library installed

## Installation

1. Clone this repository to your local machine:

```bash
git clone https://github.com/your_username/esp32-pan-tilt-camera.git
```

2. Connect the ESP32 microcontroller to the pan-tilt servo motors and camera module following the provided schematics.

3. Upload the ESP32 code provided in the `esp32_code` directory to your ESP32 board using the Arduino IDE or any compatible IDE.

4. Install the required Python packages by running:

```bash
pip install -r requirements.txt
```

5. Run the Python script for face detection and camera control:

```bash
python face_detection.py
```

## Usage

1. Ensure that the ESP32 board is powered and connected to a Wi-Fi network.

2. Run the Python script `face_detection.py` on your computer.

3. Access the video feed through the provided IP address and port in a web browser.

4. The camera module will start streaming video, and face detection will be performed in real-time.

## Configuration

- Modify the `config.h` file in the ESP32 code directory to adjust settings such as Wi-Fi credentials, servo motor pins, and camera module configuration.

## Contributions

Contributions are welcome! If you want to contribute to this project, feel free to submit a pull request.


## Acknowledgments

- The need for a simple yet effective pan-tilt camera control system with facial detection capabilities inspired this project.
- We thank the contributors to the OpenCV library for providing robust tools for computer vision tasks.
- Special thanks to the ESP32 community for their continuous support and development of versatile microcontroller platforms.
