import cv2
import numpy as np
import requests
from PIL import Image
from io import BytesIO

# IP address of the ESP32 camera module
ESP32_IP = "192.168.175.188"

# Haar Cascade for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

def capture_frame():
    try:
        # Send request to ESP32 to capture a frame
        response = requests.get(f"http://{ESP32_IP}/capture")
        if response.status_code == 200:
            # Read the response content as an image
            img_data = BytesIO(response.content)
            img = Image.open(img_data)
            # Convert image to OpenCV format (BGR)
            frame = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2BGR)
            return frame
        else:
            print("Error: Unable to capture frame.")
            return None
    except Exception as e:
        print(f"Error: {e}")
        return None

def detect_faces(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5)
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
    return frame

def main():
    while True:
        frame = capture_frame()
        if frame is not None:
            frame = detect_faces(frame)
            cv2.imshow("ESP32 Camera", frame)
        
        # Press 'q' to quit
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
