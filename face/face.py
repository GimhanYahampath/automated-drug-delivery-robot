import paho.mqtt.client as mqtt
import pandas as pd
import cv2
import urllib.request
import numpy as np
import os
from datetime import datetime
import face_recognition
 

# Function to handle connection
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

# Create an MQTT client
client = mqtt.Client()

# Attach the on_connect function to the client
client.on_connect = on_connect

# Connect to the Mosquitto broker
broker_address = "test.mosquitto.org"  # e.g., "broker.hivemq.com"
client.connect(broker_address, port=1883)


path = r'image_folder'
url='http://192.168.20.37/cam-hi.jpg'
##'''cam.bmp / cam-lo.jpg /cam-hi.jpg / cam.mjpeg '''
 

images = []
classNames = []
myList = os.listdir(path)
print(myList)
for cl in myList:
    curImg = cv2.imread(f'{path}/{cl}')
    images.append(curImg)
    classNames.append(os.path.splitext(cl)[0])
print(classNames)
 
 
def findEncodings(images):
    encodeList = []
    for img in images:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(img)[0]
        encodeList.append(encode)
    return encodeList
 
 

 
 
encodeListKnown = findEncodings(images)
print('Encoding Complete')
 
#cap = cv2.VideoCapture(0)
 
while True:
    #success, img = cap.read()
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    img=cv2.imdecode(imgnp,-1)
# img = captureScreen()
    imgS = cv2.resize(img, (0, 0), None, 0.25, 0.25)
    imgS = cv2.cvtColor(imgS, cv2.COLOR_BGR2RGB)
 
    facesCurFrame = face_recognition.face_locations(imgS)
    encodesCurFrame = face_recognition.face_encodings(imgS, facesCurFrame)
 
    for encodeFace, faceLoc in zip(encodesCurFrame, facesCurFrame):
        matches = face_recognition.compare_faces(encodeListKnown, encodeFace)
        faceDis = face_recognition.face_distance(encodeListKnown, encodeFace)
# print(faceDis)
        matchIndex = np.argmin(faceDis)
 
        if matches[matchIndex]:
            name = classNames[matchIndex].upper()
            print(name)
            if name == "RAVINDU":
                            # Publish a message
                topic = "home/ravindu"  
                message = "DETECTED"
                client.publish(topic, message)
                print(f"Message '{message}' sent to topic '{topic}'")
            y1, x2, y2, x1 = faceLoc
            y1, x2, y2, x1 = y1 * 4, x2 * 4, y2 * 4, x1 * 4
            cv2.rectangle(img, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.rectangle(img, (x1, y2 - 35), (x2, y2), (0, 255, 0), cv2.FILLED)
            cv2.putText(img, name, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 2)

 
    cv2.imshow('Webcam', img)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break
cv2.destroyAllWindows()
cv2.imread