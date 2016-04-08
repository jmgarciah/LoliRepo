data = csvread('../lectura/data.csv');
n = data(:,1);
t = data(:,2);
u_ref = data(:,3);
theta_out = data(:,4);
x1 = data(:,5);

hold on
plot(t,u_ref,'b')
plot(t,theta_out,'r')
plot(t,x1,'g')

title('o')
ylabel('t')
xlabel('t [s]');
legend('Uref','y{out}','x1')