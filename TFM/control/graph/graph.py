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
yarp.Network.connect("/jr3:o", "/gui:i")
# Read the data from de port
data = yarp.Bottle()


fig = plt.figure()


XZMP = np.zeros(1)
YZMP = np.zeros(1)
XZMP_real = np.zeros(1)
YZMP_real = np.zeros(1)
U = np.zeros(1)
Y = np.zeros(1)
t = np.zeros(1)
n=0

while 1:

    plt.grid()
    plt.title('System Outputs', fontsize=12, fontweight='bold')
    plt.xlabel('t [mm]')


    # Reading YARP port
    print "Reading..."

    p.read(data)
    Fx = data.get(0).asDouble()/100
    Fy = data.get(1).asDouble()/100
    Fz = data.get(2).asDouble()/100
    Mx = data.get(3).asDouble()/100
    My = data.get(4).asDouble()/100
    Mz = data.get(5).asDouble()/100
    print "F = [" + repr(Fx) + "," + repr(Fy) + "," + repr(Fz) +"]"
    print "M = [" + repr(Mx) + "," + repr(My) + "," + repr(Mz) +"]"

    xzmp = data.get(6).asDouble()
    yzmp = data.get(7).asDouble()
    u = data.get(8).asDouble()
    y = data.get(9).asDouble()
    xzmp_real = data.get(10).asDouble()
    yzmp_real = data.get(11).asDouble()

    T=0.001


    print "zmp = [" + repr(xzmp) + "," + repr(yzmp)+ "]"
    print "u = " + repr(u)
    print "y = " + repr(y)
    print "zmp_real = [" + repr(xzmp_real) + "," + repr(yzmp_real)+ "]"

    XZMP = np.append(XZMP,xzmp)
    YZMP = np.append(YZMP,yzmp)
    XZMP_real = np.append(XZMP_real,xzmp_real)
    YZMP_real = np.append(YZMP_real,yzmp_real)
    U = np.append(U,u)
    Y = np.append(Y,y)
    t = np.append(t, T*n)

    print "t = " + repr(t[n])

    plt.plot(t,XZMP,'c', label='x_zmp')
    plt.plot(t,YZMP,'y', label='y_zmp')
    plt.plot(t,XZMP_real,'b', label='x_zmp_real')
    plt.plot(t,YZMP_real,'g', label='y_zmp_real')
    plt.plot(t,U,'g', label='u')
    plt.plot(t,Y,'r', label='T')

    legend = plt.legend(loc='upper right')

    n=n+1

    fig.show()

    #Sample time 1ms
    plt.pause(0.00001) #delay in seconds
    fig.savefig('./graph.png')
    fig.clf()


    p.close()
