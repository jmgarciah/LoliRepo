data = csvread('../lectura/data.csv');
n = data(:,1);
t = data(:,2);
ref = data(:,3);
y = data(:,4);
x1 = data(:,5);
Ud = data(:,6);

hold on
plot(t,ref,'b')
plot(t,y,'r')
plot(t,x1,'g')
plot(t,Ud,'k')

title('K=[12.55, 4.91], Ki=0.01, Kp=-1.5, Ku=-2.5')
xlabel('t [s]');
legend('Uref','y{out}','x1','Ud(rad)')