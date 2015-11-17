import yarp
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def zmpStabilityAreas():
    #No-stability area vertex
    p11=[-4,-4]
    p12=[2,-4]
    p13=[2,6]
    p14=[-4,6]

    #Unknown stability area vertex
    p21=[-2.5,-2]
    p22=[1,-2]
    p23=[1,4]
    p24=[-2.5,4]

    #Stability area vertex
    p31=[-1.5,-1]
    p32=[0.5,-1]
    p33=[0.5,2.5]
    p34=[-1.5,2.5]

    #No-stability area (RED)
    x1=[p11[0],p12[0],p13[0],p14[0],p11[0]]
    y1=[p11[1],p12[1],p13[1],p14[1],p11[1]]

    #Unknown stability area (YELLOW)
    x2=[p21[0],p22[0],p23[0],p24[0],p21[0]]
    y2=[p21[1],p22[1],p23[1],p24[1],p21[1]]

    #Stability area (GREEN)
    x3=[p31[0],p32[0],p33[0],p34[0],p31[0]]
    y3=[p31[1],p32[1],p33[1],p34[1],p31[1]]

    #Plot configuration
    plt.axis([-10,10,-10,10])
    plt.plot(x1,y1,'k',x2,y2,'k',x3,y3,'k',linewidth=2.0)
    plt.fill(x1,y1,'r')
    plt.fill(x2,y2,'y')
    plt.fill(x3,y3,'g')
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
    # Plotting ZMP Areas
    zmpStabilityAreas()

    # Reading YARP port
    print "Reading..."
    p.read(data)
    Fx = data.get(0).asDouble()/100
    Fy = data.get(1).asDouble()/100
    Fz = data.get(2).asDouble()/100
    Mx = data.get(3).asInt()/10
    My = data.get(4).asInt()/10
    Mz = data.get(5).asInt()/10
    print "F = [" + repr(Fx) + "," + repr(Fy) + "," + repr(Fz) +"]"
    print "M = [" + repr(Mx) + "," + repr(My) + "," + repr(Mz) +"]"
    #ZMP equations
    if Fz != 0 :
        x = My / Fz
        y = Mx / Fz
    else:
        x=0
        y=0
    #Printing ZMP point
    zmp = [x,y]
    print "zmp = [" + repr(x) + "," + repr(y) + "]"

    plt.plot(x,y,'ko')
    fig.show()
    #Sample time 1ms
    plt.pause(0.001) #delay in seconds
    fig.clf()

p.close()
