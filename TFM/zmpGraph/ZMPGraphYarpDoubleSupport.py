import yarp
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def zmpStabilityAreasLeftFoot():
    #No-stability area vertex
    p11=[-5,-3]
    p12=[5,-3]
    p13=[5,3]
    p14=[-5,3]

    #Unknown stability area vertex
    p21=[-4,-2]
    p22=[4,-2]
    p23=[4,2]
    p24=[-4,2]

    #Stability area vertex
    p31=[-2,-1]
    p32=[2,-1]
    p33=[2,1]
    p34=[-2,1]

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
p0 = yarp.Port()
p1 = yarp.Port()
# Open the port
p0.open("/gui0:i")
p1.open("/gui1:i")
# Connect output and input ports
yarp.Network.connect("/jr3_0:o", "/gui0:i")
yarp.Network.connect("/jr3_1:o", "/gui1:i")
# Read the data from de port
data0 = yarp.Bottle()
data1 = yarp.Bottle()

fig = plt.figure()
#fig.hold(True)

while 1:
    #plt.hold(True)
    # Plotting ZMP Areas
    zmpStabilityAreasLeftFoot()

    # Reading YARP port
    print "Reading..."
    p0.read(data0)
    p1.read(data1)

    Fx0 = data0.get(0).asDouble()/100
    Fy0 = data0.get(1).asDouble()/100
    Fz0 = data0.get(2).asDouble()/100
    Mx0 = data0.get(3).asDouble()/10
    My0 = data0.get(4).asDouble()/10
    Mz0 = data0.get(5).asDouble()/10
    Fx1 = data1.get(0).asDouble()/100
    Fy1 = data1.get(1).asDouble()/100
    Fz1 = data1.get(2).asDouble()/100
    Mx1 = data1.get(3).asDouble()/10
    My1 = data1.get(4).asDouble()/10
    Mz1 = data1.get(5).asDouble()/10
	
    print "F0 = [" + repr(Fx0) + "," + repr(Fy0) + "," + repr(Fz0) +"]"
    print "M0 = [" + repr(Mx0) + "," + repr(My0) + "," + repr(Mz0) +"]"
    print "F1 = [" + repr(Fx1) + "," + repr(Fy1) + "," + repr(Fz1) +"]"
    print "M1 = [" + repr(Mx1) + "," + repr(My1) + "," + repr(Mz1) +"]"

    #ZMP equations
    #Right foot
    if Fz0 != 0 :
        x0 = -My0 / Fz0
        y0 = Mx0 / Fz0
    else:
        x0 = 0
        y0 = 0

    #Left foot
    if Fz1 != 0 :
        x1 = -My1 / Fz1
        y1 = Mx1 / Fz1
    else:
        x1 = 0
        y1 = 0

    if (Fz0 + Fz1) == 0 :
        x=0
        y=0
    else:
        x = (x0 * Fz0 + x1 * Fz1) / (Fz0 + Fz1)
        y = (y0 * Fz0 + y1 * Fz1) / (Fz0 + Fz1)

#    x_ = (-My0 - My1) / (Fz0 + Fz1)
#    y_ = (Mx0 + Mx1) / (Fz0 + Fz1)

#    ex = x - x_
#    ey = y - y_

    #Printing ZMP point
    zmp = [x,y]

    print "zmp = [" + repr(x) + "," + repr(y) + "]"
#    print "Error en x = " + repr(ex)
#    print "Error en y = " + repr(ey)

    plt.plot(x,y,'ko')
    fig.show()
    plt.pause(0.001)
    fig.clf()

p0.close()
p1.close()

