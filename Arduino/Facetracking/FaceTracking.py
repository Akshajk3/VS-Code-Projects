import cv2
import serial, time

cascade_path = "haarcascade_frontalface_default.xml"
clf = cv2.CascadeClassifier(cascade_path)
cap = cv2.VideoCapture(0)

ArduinoSerial = serial.Serial("com9", 9600, timeout=0.1)

time.sleep(1)

while True:
    _, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = clf.detectMultiScale(gray, scaleFactor = 1.1)

    for x,y,w,h in faces:
        string='X{0:d}Y{1:d}'.format((x+w//2),(y+h//2))
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0, 255, 0), 2)
        print(string)
        ArduinoSerial.write(string.encode("utf-8"))
    
    cv2.imshow("Face Tracking Turret", frame)
    if cv2.waitKey(1) == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()