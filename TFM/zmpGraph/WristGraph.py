import yarp
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

PI = np.pi
alpha = np.pi
rp = 22.5 / 2 # plate radius
rp1 = 14/2 # black plate radius
def Plate():
    # Big circle
    ang = np.linspace(0,2*PI,360)
    x0 = rp*np.cos(ang)
    y0 = rp*np.sin(ang)

    # Little circle
    ang1 = np.linspace(0,2*PI,360)
    x1 = rp1*np.cos(ang1)
    y1 = rp1*np.sin(ang1)

    x_big = np.concatenate([x0])
    y_big = np.concatenate([y0])
    plt.plot(x_big,y_big,'k')

    x_little = np.concatenate([x1])
    y_little = np.concatenate([y1])
    plt.plot(x_little,y_little,'k')

#    plt.fill(x_big,y_big,'r')
    plt.fill(x_little,y_little,'k')

    return;

# Initialise YARP
yarp.Network.init()
# Create a port
p = yarp.Port()
# Open the port
p.open("/gui:i")
# Connect output and input ports
yarp.Network.connect("/jr3ch3:o", "/gui:i")
# Read the data from de port
data = yarp.Bottle()

fig = plt.figure()

while 1:
    ax = fig.add_subplot(111)
    ax.grid()
    #ax.axis('equal')
    plt.xlim(15,-15) # changed because of robot axes
    plt.ylim(-15,15)
    ax.set_title('ZMP REPRESENTATION SINGLE WRIST AND PLATE', fontsize=12, fontweight='bold')
    ax.set_xlabel('Y [mm]')  # changed because of robot axes
    ax.set_ylabel('X [mm]')  # changed because of robot axes

    # Plotting Plate Area
    Plate()

    # Reading YARP port
    print "Reading..."
    p.read(data)
    fx = data.get(0).asDouble()
    fy = data.get(1).asDouble()
    fz = data.get(2).asDouble()
    mx = data.get(3).asDouble()
    my = data.get(4).asDouble()
    mz = data.get(5).asDouble()

    # data in the TEO body system reference
    fx_teo = - fz
    fy_teo = - fy
    fz_teo = - fx
    mx_teo = - mz
    my_teo = - my
    mz_teo = - mx
    # ZMP computation
    if fz != 0 :
        x = - my_teo / fz_teo
        y = mx_teo / fz_teo
    else:
        x = 0
        y = 0
    #Printing ZMP point
    print "zmp = [" + repr(x) + "," + repr(y) + "]"

#    print "fx = " + repr(fx)
#    print "fy = " + repr(fy)

    plt.plot(Y, X,'yo') # changed because of robot axes

    fig.show()

    #Sample time 1ms
    plt.pause(0.001) #delay in seconds
    fig.clf()

p.close()


