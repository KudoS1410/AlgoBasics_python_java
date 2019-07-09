import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np
import colorsys
import threading

class Point(object):
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y
        pass

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __eq__(self, other):
        if self.x == other.x and self.y == other.y:
            return True
        else:
            return False
    pass


def onMouse(event, x, y, flags, params):

    global col, start, end, point_count
    s = 2
    if event == cv.EVENT_LBUTTONUP:
        if point_count == 0:
            col = cv.rectangle(col, (x-s, y-s), (x+s, y+s), color=(0, 0, 255), thickness= -1)
            start = Point(x, y)
            print(f'start: {start.x}, {start.y}')
            point_count += 1
            pass
        elif point_count == 1:
            col = cv.rectangle(col, (x - s, y - s), (x + s, y + s), color=(255, 255, 0), thickness=-1)
            end = Point(x, y)
            print(f'end: {end.x}, {end.y}')
            point_count += 1
            pass


def bfs(st, en):
    global col, h, w, directions
    col_const = 200
    count = 0

    found = False
    queue = []
    visited = [[0 for j in range(w)]for i in range(h)]
    parent = [[Point() for j in range(w)]for i in range(h)]

    queue.append(st)
    visited[st.y][st.x] = 1

    while len(queue) > 0:
        parent_point = queue.pop(0)
        count +=1
        # print('in queue')
        if count%20 == 0:
            display_image = col.copy()
            display_image = cv.resize(display_image, (512, 512))
            cv.imshow('image', display_image)
            cv.waitKey(1)

        for direction in directions:

            daughter_cell = parent_point + direction
            x = daughter_cell.x
            y = daughter_cell.y
            if daughter_cell.x>0 and daughter_cell.y>0 and daughter_cell.y<h and daughter_cell.x<w:
                if visited[daughter_cell.y][daughter_cell.x] == 0 and (col[daughter_cell.y][daughter_cell.x][0] != 255 or
                    col[daughter_cell.y][daughter_cell.x][1] != 255 or
                    col[daughter_cell.y][daughter_cell.x][2] != 255):

                # print('visiting')
                    queue.append(daughter_cell)
                    visited[y][x] = visited[parent_point.y][parent_point.x] + 1

                    col[y][x] = list(reversed([255 * i for i in
                        colorsys.hsv_to_rgb(
                            visited[y][x] / col_const, 100, 100)]))
                    # col[y][x] = (0, 255, 255)
                    parent[y][x] = parent_point

                    if daughter_cell == en:
                        print('end')
                        found = True
                        del queue[:]
    path = []
    if found:
        point = en
        while point!=st:
            path.append(point)
            point = parent[point.y][point.x]
        path.append(point)
        # path.reverse()
        for p in path:
            # col[p.y][p.x] = [255, 255, 0]
            cv.rectangle(col, (p.x-1, p.y-1), (p.x+1, p.y+1), (255, 255, 0), -1)
            display_image = col.copy()
            display_image = cv.resize(display_image, (512, 512))
            cv.imshow('image', display_image)
            cv.waitKey(1)
        print('found')
        display_image = col.copy()
        display_image = cv.resize(display_image, (512, 512))
        cv.imshow('image', display_image)
        cv.waitKey(0)

    else:
        print('not found')


point_count = 0
start  = Point()
end = Point()

directions = [Point(0, -1), Point(0, 1), Point(1, 0), Point(-1, 0)]
# up , down, right, left

img = cv.imread('maze81(1).jpg', 0)
img = cv.resize(img, (512, 512))
ret, thresh = cv.threshold(img, 150, 255, cv.THRESH_BINARY)
thresh = cv.resize(thresh, (256, 256))

col = cv.cvtColor(thresh, cv.COLOR_GRAY2BGR)
h, w, d = col.shape

cv.namedWindow('image')
cv.setMouseCallback('image', onMouse)
while True:
    cv.imshow('original', img)
    cv.imshow('image', col)
    cv.imshow('thresh', thresh)
    # cv.imshow('difference', diff)
    k = cv.waitKey(100)
    if point_count == 2:
        break
pass


# now we have the start and end points
bfs(start, end)



cv.destroyAllWindows()