import serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

ArduinoSerial = serial.Serial()

portsList = []

for onePort in ports:
    portsList.append(str(onePort))
    print(str(onePort))

val = input("Select Port: COM")

for x in range(0, len(portsList)):
    if portsList[x].startswith("COM" + str(val)):
        portsVar = "COM" + str(val)
        print(portsVar)

ArduinoSerial.baudrate = 9600
ArduinoSerial.port = portsVar
ArduinoSerial.open()

while True:
    command = input("Servo Degrees: ")
    if(command > 360 or command < 0):
        print("Please enter a number between 0 and 360")

    ArduinoSerial.write(command.encode('utf-8'))

    if command == "exit":
        exit()