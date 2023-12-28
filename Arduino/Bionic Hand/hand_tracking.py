import cv2
import mediapipe as mp

mp_drawings = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mphands = mp.solutions.hands

cap = cv2.VideoCapture(0)
hands = mphands.Hands()

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
                print("Hand closed")
            else:
                print("Hand open")

            #print(f"Landmark 5: ({y1}), Landmark 8: ({y2})")

            mp_drawings.draw_landmarks(image, hand_landmarks, mphands.HAND_CONNECTIONS)
            
    cv2.imshow("Handtracker", image)
    cv2.waitKey(1)