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
            
            lm_data = hand_landmarks.landmark[0]

            cx, cy = int(lm_data.x * image.shape[1]) , int(lm_data.y * image.shape[0])

            print(f"Landmark 0: ({cx}, {cy})")

            mp_drawings.draw_landmarks(image, hand_landmarks, mphands.HAND_CONNECTIONS)
            
    cv2.imshow("Handtracker", image)
    cv2.waitKey(1)