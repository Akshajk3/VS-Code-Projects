import cv2
import serial, time

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(1)

ArduinoSerial=serial.Serial('com7',9600,timeout=0.1)
time.sleep(1)

while cap.isOpened():
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1) #mirror the image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMulitScale(gray, 1.1, 6)
    
    for x, y, w, h in faces:
        #sending coordinates to the Arduino
        string = 'X{0:d}Y{1:d}'.format((x+w//2), (y+h//2))
        print(string)
        ArduinoSerial.write(string.encode('utf-8'))
        #plot the center of the face
        cv2.circle(frame, (x+w//2, y+h//2),2, (0, 255, 0), 2)
        #plot the roi
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0, 255, 0), 3)

        cv2.imshow('img', frame)
        if cv2.waitKey(10)&0xFF==ord('q'):
            break
cap.release()
cv2.destroyAllWindows()
