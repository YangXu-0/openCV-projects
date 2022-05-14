import cv2 as cv
import numpy as np

maze = cv.imread("./mazes/maze_1.jpg")
grey = cv.cvtColor(maze, cv.COLOR_BGR2GRAY)
maze_inv = cv.bitwise_not(grey)

line_edges = cv.Canny(maze_inv, 150, 255)
lines = cv.HoughLines(line_edges, 1, np.pi/180, 200)


"""
blank = np.zeros(maze.shape[:2], dtype='uint8')

for r_theta in lines:
    r,theta = r_theta[0]
    print(f'(r, theta): ({r}, {theta})')

    a = np.cos(theta)
    b = np.sin(theta)

    x0 = a*r
    y0 = b*r

    x1 = int(x0 + 1000*(-b))
    y1 = int(y0 + 1000*(a))

    x2 = int(x0 - 1000*(-b))
    y2 = int(y0 - 1000*(a))

    print(f"(x0, y0): ({x0}, {y0})")
    print(f"(x1, y1): ({x1}, {y1})")
    print(f"(x2, y2): ({x2}, {y2})\n")

    cv.line(blank, (x1,y1), (x2,y2), (255, 255, 255), 2)
"""

rho = 1  # distance resolution in pixels of the Hough grid
theta = np.pi / 180  # angular resolution in radians of the Hough grid
threshold = 15  # minimum number of votes (intersections in Hough grid cell)
min_line_length = 0  # minimum number of pixels making up a line
max_line_gap = 30  # maximum gap in pixels between connectable line segments
line_image = np.copy(maze) * 0  # creating a blank to draw lines on

# Run Hough on edge detected image
# Output "lines" is an array containing endpoints of detected line segments
lines = cv.HoughLinesP(line_edges, rho, theta, threshold, np.array([]),
                    min_line_length, max_line_gap)

for line in lines:
    for x1,y1,x2,y2 in line:
        cv.line(line_image,(x1,y1),(x2,y2),(255,255,255),2)

cv.imshow("maze", line_edges)
cv.waitKey(0)