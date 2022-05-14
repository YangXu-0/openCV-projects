import cv2 as cv
import numpy as np

# Loading image
img = cv.imread("20210902_193128.jpg")
grey = cv.cvtColor(img, cv.COLOR_RGB2GRAY)

# Detecting faces
haar_cascade = cv.CascadeClassifier('haarcascade.xml')
faces_rect = haar_cascade.detectMultiScale(grey, scaleFactor=1.1, minNeighbors=10)
print(faces_rect)

# Displaying faces/removing duplicates
target_idx = -1
while True:
    temp = img.copy()
    for i, (x,y,w,h) in enumerate(faces_rect): 
        cv.rectangle(temp, (x,y), (x+w,y+h), (0, 255, 0), thickness=2)
        cv.putText(temp, str(i), (x, y-20), cv.FONT_HERSHEY_PLAIN, 2, (0, 255, 0), 2)

    cv.imshow("test", temp)
    cv.waitKey(0)

    delete_idx = int(input("Remove a duplicate? (-1 for no) "))

    if len(faces_rect) == 0 or delete_idx == -1:
        target_idx = int(input("Which one is the target? "))   # Getting Simon's face
        break
    else:
        faces_rect = np.delete(faces_rect, delete_idx, 0)

# Remove target from all faces
if target_idx == -1:
    print("No target")
    exit()
else:
    target_face = faces_rect[target_idx]
    #cv.imshow("target", img[target_face[1]:target_face[1]+target_face[3], target_face[0]:target_face[0]+target_face[2]])
    faces_rect = np.delete(faces_rect, target_idx, 0)

# Displaying all faces with target removed
temp = img.copy()
for i, (x,y,w,h) in enumerate(faces_rect):
    cv.rectangle(temp, (x,y), (x+w, y+h), (0, 255, 0), thickness=2)
    cv.putText(temp, str(i), (x, y-20), cv.FONT_HERSHEY_PLAIN, 2, (0, 255, 0), 2)

# Make everyone else's faces larger
new = img.copy()
for i, (x,y,w,h) in enumerate(faces_rect):
    adjusted_y = int(y - (y*0.07))
    face = img[adjusted_y:y+h, x:x+w]
    if (target_face[1]-(target_face[1]*0.3)) < adjusted_y:
        dim = (w, (y+h)-int(target_face[1]-(target_face[1]*0.3)))
        print(dim)
        face = cv.resize(face, dim, interpolation=cv.INTER_CUBIC)
        new[int(target_face[1]-(target_face[1]*0.3)):y+h, x:x+w] = face

cv.imshow("new", new)
cv.waitKey(0)

# Delete duplicates
# Choose target face
# Make everyone else's faces larger than target by some margin