import cv2
import numpy as np

# empty canvas with size 512 by 512
canvas = np.zeros(shape=[512, 512, 3], dtype=np.uint8)


while True:
    cv2.imshow("Window", canvas)
    if cv2.waitKey(1) == ord('q'):
        break

cv2.destroyAllWindows()