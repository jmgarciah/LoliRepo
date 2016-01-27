import yarp
import numpy as np
import matplotlib.pyplot as plt


# Initialise YARP
yarp.Network.init()
# Create a port
p = yarp.Port()
# Open the port
p.open("/gui:i")
# Connect output and input ports
yarp.Network.connect("/system:o", "/gui:i")
# Read the data from de port
data = yarp.Bottle()

fig = plt.figure()


XZMP = np.zeros(1)
YZMP = np.zeros(1)
U = np.zeros(1)
Y = np.zeros(1)
t = np.zeros(1)
n=0

while 1:
#    ax = fig.add_subplot(111)
#    ax.grid()
#    ax.axis('equal')
#    ax.set_title('ZMP REPRESENTATION IN SINGLE SUPPORT', fontsize=12, fontweight='bold')
#    ax.set_xlabel('x [mm]')
#    ax.set_ylabel('y [mm]')

    # Reading YARP port
    print "Reading..."
    p.read(data)
    xzmp = data.get(0).asDouble()*100
    yzmp = data.get(1).asDouble()*100
    u = data.get(2).asDouble()*10
    y = data.get(3).asInt()*10


    T=0.001


    print "zmp = [" + repr(xzmp) + "," + repr(yzmp)+ "]"
    print "u = " + repr(u)
    print "y = " + repr(y)

    XZMP = np.append(XZMP,xzmp)
    YZMP = np.append(YZMP,yzmp)
    U = np.append(U,u)
    Y = np.append(Y,y)
    t = np.append(t, T*n)

    plt.plot(t,XZMP,'b.')
    plt.plot(t,YZMP,'r.')
    plt.plot(t,U,'g.')
    plt.plot(t,Y,'m.')

    n=n+1

    fig.show()

    #Sample time 1ms
    plt.pause(0.001) #delay in seconds
    fig.clf()


p.close()
