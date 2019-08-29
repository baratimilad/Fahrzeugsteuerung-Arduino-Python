import math
import matplotlib.pyplot as plt

def pythagoras(a,b,norm=2):
        return (a**norm+b**norm)**.5

carspeedx=0
carspeedy=0
w=.5

dx=1
dy=1
speed=[]
angle=[]
for x in (dx,-dx):
    for y in (dy,-dy): 
        wheelspeedx=carspeedx-w*y#swap and invert to get perpendicular to radius
        wheelspeedy=carspeedy+w*x#w scales rotation

        plt.plot([0,x],[0,y],'g.-')
        plt.plot([x,x+wheelspeedx],[y,y+wheelspeedy],'b')

        angle+=[math.atan2(wheelspeedx,wheelspeedy)*180/math.pi]
        speed+=[pythagoras(wheelspeedx,wheelspeedy)]
        if angle[-1]<0:
                angle[-1]+=180
                speed[-1]*=-1
print(angle,speed)
plt.pause(10)