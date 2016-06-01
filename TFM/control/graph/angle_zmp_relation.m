% Data (measures in mm)
angle = [0 -0.5 -1 -1.5 -2 -2.5 -3 -3.5 -4 -4.5 -5];
test1 = [-14.5; -9; -3.5; 0; 8.5; 17.5; 25; 33.5; 47.5; 53; 60]/1000;
test2 = [-14.5; -8.6; -3.7; -2.5; 8.6; 17; 24.5; 32.5; 42.5; 51; 56.5]/1000;
test3 = [-16.5; -12; -6.5; 0.5; 8; 16.5; 24.5; 33; 41; 50.5; 57.5]/1000;
test4 = [-15.5; -10.7; -4.5; 1.5; 8.2; 15.5; 23.5; 33; 40.5; 47.8; 54.5]/1000;
test5 = [-13.5; -8.4; -2.8; 3.9; 10.2; 17.6; 26.1; 34.8; 42.6; 52.1; 60.5]/1000;
test = [test1 test2 test3 test4 test5];

%Valor medio para cada angulo
Vm = mean (test,2);

hold on;
plot(angle, test1, 'bx');
plot(angle, test2, 'rx');
plot(angle, test3, 'gx');
plot(angle, test4, 'yx');
plot(angle, test5, 'mx');
plot(angle, Vm, 'ko')
plot(angle, Vm, 'k-')

title ('Angle - ZMP relation');
xlabel('angle [deg]');
ylabel('ZMP [m]');
legend('test1','test2','test3','test4','test5', 'Average');
