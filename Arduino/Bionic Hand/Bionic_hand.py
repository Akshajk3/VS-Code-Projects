import serial
import serial.tools.list_ports
import cv2
import mediapipe as mp

ports = serial.tools.list_ports.comports()

ArduinoSerial = serial.Serial()

portsList = []

for onePort in ports:
    portsList.append(str(onePort))
    print(str(onePort))

val = input("Select Port: ")

if val == "exit":
    exit()

ArduinoSerial.baudrate = 9600
ArduinoSerial.port = val
ArduinoSerial.open()

while True:
    value = input("What is the angle: ")
    ArduinoSerial.write(value.encode('utf-8'))