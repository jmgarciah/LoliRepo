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

title('o')
xlabel('t [s]');
legend('Uref','y{out}','x1','Ud')