#%%

import numpy as np
import math

f = open("input1.txt",'r')

points = []
while True:
        line = f.readline().split()
        if not line :
            break
        line[0] = int(line[0])
        line[1] = int(line[1])
        points.append(line)

f.close()

orig = points[0]
for _, point in enumerate(points):
    if point[1] < orig[1]:
        orig = point
    elif point[1] == orig[1] and point[0] < orig[0]:
        orig = point
#print(anchor_point)

def angle(p0, p1):
    y_span=p0[1]-p1[1]
    x_span=p0[0]-p1[0]
    return math.atan2(y_span,x_span)

# find the angle
points_angles = []
origin = [0,0]
for _, point in enumerate(points):
    points_angles.append([point[0],point[1], angle(orig, point)])

points_angles = np.array(points_angles)    
points_angles = points_angles[points_angles[:,2].argsort()]
sorted_points =  points_angles[:,(0,1)]

convex_hull = [orig, sorted_points[0]]

def ccw(a, b, c):
    return (b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1])
    
for point in sorted_points[1:]:
    while ccw(convex_hull[-2],convex_hull[-1], point)<=0:
        del convex_hull[-1] # backtrack
    convex_hull.append(point)

def ccw(x1, y1, x2, y2, x3, y3):
    return (x1 * y2 + x2 * y3 + x3 * y1) - (y1 * x2 + y2 * x3 + y3 * x1)

x = convex_hull[0][0]
y = convex_hull[0][1]
answer = 0.0
for i in range(1,len(convex_hull)-1):
    answer += ccw(x, y,convex_hull[i][0], convex_hull[i][1],convex_hull[i+1][0], convex_hull[i+1][1])


f = open("전용본_output1.txt",'w')
f.write('%.1f\n' % round(abs(answer)/2, 1))
for i in range(1,len(convex_hull)):
    f.write('{0} {1}\n' .format((int)(convex_hull[i][0]), (int)(convex_hull[i][1])))
print(round(abs(answer)/2, 1))
print(convex_hull)

f.close()

#def point_in_polygon(polygon, point):
#    odd = False
#    i = 1
#    j = len(polygon) - 1
#    print(polygon[j])
#    while i < len(polygon) - 1:
#        i = i + 1

        #if (((polygon[i][1] > point[1]) != (polygon[j][1] > point[1])) and (point[0] < ((polygon[j][0] - polygon[i][0]) * (point[1] - polygon[i][1]) / (polygon[j][1] - polygon[i][1])) +polygon[i][0])):
       # if(polygon[i][1] < )
        #    odd = not odd
        #j = i
    # If the number of crossings was odd, the point is in the polygon
    #return odd
def point_in_polygon(poly,point):

    n = len(poly)
    inside = False
    y = point[1]
    x = point[0]
    p1x,p1y = poly[0]
    for i in range(n+1):
        p2x,p2y = poly[i % n]
        if y > min(p1y,p2y):
            if y <= max(p1y,p2y):
                if x <= max(p1x,p2x):
                    if p1y != p2y:
                        xints = (y-p1y)*(p2x-p1x)/(p2y-p1y)+p1x
                    if p1x == p2x or x <= xints:
                        inside = not inside
        p1x,p1y = p2x,p2y

    return inside

f = open("point_in_polygon_input.txt",'r')
o = open("전용본_point_in_polygon_output1.txt",'w')
testpoints = []
while True:
        line = f.readline().split()
        if not line :
            break
        line[0] = int(line[0])
        line[1] = int(line[1])
        print(line[0],line[1])
        result = point_in_polygon(convex_hull, (line[0], line[1]))
        if result == 1:
            o.write("in\n")
        else:
            o.write("out\n")  


f.close()
o.close()
# %%
