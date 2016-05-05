data = csvread('/home/teo/Documentos/data.csv');
n = data(:,1);
t = data(:,2);
zmp = data(:,3);
y = data(:,4);
x1 = data(:,5);
Uref = data(:,6);
u = data(:,7);
angle = data(:,8);


%Sole borders
front = (120+55)/1000*ones(size(n));
back = -70/1000*ones(size(n));
left = (140+37.5)/1000*ones(size(n));
right = -(140+37.5)/1000*ones(size(n));


hold on
plot(t,zmp,'g')
plot(t,y,'r')
plot(t,x1,'b')
plot(t,Uref,'k')
plot(t,u,'m')
plot(t,angle,'y')
plot(t,front,'k--',t,back,'k--');

title('K=[12.55, 4.91], Ki=10, Kp=-0.5, Ku=-2.05')
xlabel('t [s]');
legend('zmp','y{out}','x1','Ud(rad)','u(rad)','angle(deg)')