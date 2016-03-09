import yarp
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

PI = np.pi
d = 70+37.5
h = 0
def RightFoot():
    # Big semicircle
    ang = np.linspace(2*PI,PI,180)
    x0 = d + 70*np.cos(ang)
    y0 = h + 70*np.sin(ang)

    # Straightline
    x1 = np.ones(121) * (d-70)
    y1 = h + np.linspace(1,121,121) -1

    # Little circle
    ang2 = np.linspace(PI,14.25*PI/180,180)
    x2 = d - 15 + 55*np.cos(ang2)
    y2 = h + 120 + 55*np.sin(ang2)

    # Inclined line
    x3 = np.linspace(d - 15 + 55*np.cos(14.25*PI/180), d + 70*np.cos(2*PI), 100)
    y3 = np.linspace(h + 120 + 55*np.sin(14.25*PI/180), h + 70*np.sin(2*PI), 100)

    x_sole = np.concatenate([x0,x1,x2,x3])
    y_sole = np.concatenate([y0,y1,y2,y3])
    plt.plot(x_sole,y_sole,'k')

    return;

def LeftFoot():
    # Big semicircle
    ang = np.linspace(2*PI,PI,180)
    x0 = d + 70*np.cos(ang)
    y0 = h + 70*np.sin(ang)

    # Straightline
    x1 = np.ones(121) * (d-70)
    y1 = h + np.linspace(1,121,121) -1

    # Little circle
    ang2 = np.linspace(PI,14.25*PI/180,180)
    x2 = d - 15 + 55*np.cos(ang2)
    y2 = h + 120 + 55*np.sin(ang2)

    # Inclined line
    x3 = np.linspace(d - 15 + 55*np.cos(14.25*PI/180), d + 70*np.cos(2*PI), 100)
    y3 = np.linspace(h + 120 + 55*np.sin(14.25*PI/180), h + 70*np.sin(2*PI), 100)

    x_sole = np.concatenate([-x0,-x1,-x2,-x3])
    y_sole = np.concatenate([y0,y1,y2,y3])
    plt.plot(x_sole,y_sole,'k')

    return;

# Initialise YARP
yarp.Network.init()
# Create a port
p = yarp.Port()
# Open the port
p.open("/gui:i")
# Connect output and input ports
yarp.Network.connect("/jr3:o", "/gui:i")
# Read the data from de port
data = yarp.Bottle()


fig = plt.figure()
#fig.hold(True)

while 1:
    ax = fig.add_subplot(111)
    ax.grid()
    #ax.axis('equal')
    plt.xlim(300,-300)
    plt.ylim(-300,300)
    ax.set_title('ZMP REPRESENTATION IN DOUBLE SUPPORT', fontsize=12, fontweight='bold')
    ax.set_xlabel('y [mm]') # changed because of robot axes
    ax.set_ylabel('x [mm]') # changed because of robot axes

    # Plotting ZMP Areas
    RightFoot()
    LeftFoot()

    # Reading YARP port
    print "Reading..."
    p.read(data)

    x = data.get(0).asDouble() * 1000 # in mm
    y = data.get(1).asDouble() * 1000 # in mm

    #Printing ZMP point
    print "zmp = [" + repr(x) + "," + repr(y) + "]"

    plt.plot(y,x,'ko') # axes are changed because of robot axes
    fig.show()
    #Sample time 1ms
    plt.pause(0.001) #delay in seconds
    fig.clf()

p.close()


