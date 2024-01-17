import cv2
import mediapipe as mp
import serial
import serial.tools.list_ports

# ports = serial.tools.list_ports.comports()

# ArduinoSerial = serial.Serial()

# portsList = []

# for onePort in ports:
#     portsList.append(str(onePort))
#     print(str(onePort))

# val = input("Select Port: ")

# if val == "exit()":
#     exit()

# ArduinoSerial.baudrate = 9600
# ArduinoSerial.port = val
# ArduinoSerial.open()

mp_drawings = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mphands = mp.solutions.hands

cap = cv2.VideoCapture(0)
hands = mphands.Hands()

previous_closed = False

while True:
    data, image = cap.read()

    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(image)
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            
            lm_data1 = hand_landmarks.landmark[5]
            lm_data2 = hand_landmarks.landmark[8]
            
            y1 = int(lm_data1.y * image.shape[0])
            y2 = int(lm_data2.y * image.shape[0])

            if y2 > y1:
                #print("Hand closed")
                current_closed = True
                
            else:
                #print("Hand open")
                current_closed = False
                

            if current_closed != previous_closed:
                print("hello world")
                if current_closed:
                    pass
                    #ArduinoSerial.write(str(0).encode("utf-8"))
                else:
                    pass
                    #ArduinoSerial.write(str(1).encode("utf-8"))

                previous_closed = current_closed

            #print(f"Landmark 5: ({y1}), Landmark 8: ({y2})")

            mp_drawings.draw_landmarks(image, hand_landmarks, mphands.HAND_CONNECTIONS)
            
    cv2.imshow("Handtracker", image)
    key = cv2.waitKey(10)

    if key == 27:  # Press 'Esc' to exit
        break

cap.release()
#ArduinoSerial.close()
cv2.destroyAllWindows()