import numpy as np
import cv2
import time

# Initializing the face and eye cascade classifiers from xml files
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye_tree_eyeglasses.xml')

# Variable to store execution state
first_read = True
start_time = None
sleep_detected_time = None

# Starting the video capture
cap = cv2.VideoCapture(0)
ret, img = cap.read()

while ret:
    ret, img = cap.read()
    # Converting the recorded image to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Applying filter to remove impurities
    gray = cv2.bilateralFilter(gray, 5, 1, 1)

    # Detecting the face for the region of image to be fed to the eye classifier
    faces = face_cascade.detectMultiScale(gray, 1.3, 5, minSize=(200, 200))
    if len(faces) > 0:
        for (x, y, w, h) in faces:
            img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # roi_face is the face which is input to the eye classifier
            roi_face = gray[y:y + h, x:x + w]
            roi_face_clr = img[y:y + h, x:x + w]
            eyes = eye_cascade.detectMultiScale(roi_face, 1.3, 5, minSize=(50, 50))

            # Examining the length of the eyes object for eyes
            if len(eyes) >= 2:
                # Reset the start time and sleep detected time
                start_time = None
                sleep_detected_time = None
                cv2.putText(img, "Eyes open!", (70, 70), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 2)
            else:
                if start_time is None:
                    # Start the timer
                    start_time = time.time()
                else:
                    elapsed_time = time.time() - start_time
                    if elapsed_time >= 2:
                        if sleep_detected_time is None:
                            # Record the sleep detected time
                            sleep_detected_time = time.time()
                            print("Sleep detected at:", time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(sleep_detected_time)))
                        cv2.putText(img, "Sleep detected!", (70, 70), cv2.FONT_HERSHEY_PLAIN, 2, (0, 0, 255), 2)
                        # Additional action for sleep detected, such as playing a sound or sending a notification

    else:
        cv2.putText(img, "No face detected", (100, 100), cv2.FONT_HERSHEY_PLAIN, 3, (0, 255, 0), 2)

    # Controlling the algorithm with keys
    cv2.imshow('img', img)
    a = cv2.waitKey(1)
    if a == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()