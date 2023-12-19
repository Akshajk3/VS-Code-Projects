import serial
import serial.tools.list_ports
import pygame

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

pygame.display.set_mode((800, 600))
pygame.display.set_caption("Servo Control with Arrow Keys")

# Initial servo position
servo_position = 90  # You can adjust this based on your servo's center position

movement = [False, False]

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            ArduinoSerial.close()
            exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                movement[0] = True
            elif event.key == pygame.K_RIGHT:
                movement[1] = True
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                movement[0] = False
            if event.key == pygame.K_RIGHT:
                movement[1] = False

    if movement[0] == True:
        servo_position -= 10
        if servo_position < 0:
            servo_position = 0
    if movement[1] == True:
        servo_position += 10
        if servo_position > 180:
            servo_position = 180

    # Send servo position to Arduino
    message = str(servo_position)
    ArduinoSerial.write(message.encode('utf-8'))
    
    # Read data from Arduino (non-blocking)
    if ArduinoSerial.in_waiting > 0:
        input_data = ArduinoSerial.readline().decode('utf-8').rstrip()
        print(f"Received data from Arduino: {input_data}")

    pygame.time.delay(20) # Add a small delay to avoid flooding the serial port
    # command = input("Servo Degrees: ")
    # if(int(command) > 360 or int(command) < 0):
    #     print("Please enter a number between 0 and 360")

    # ArduinoSerial.write(command.encode('utf-8'))

    # if command == "exit":
    #     exit()