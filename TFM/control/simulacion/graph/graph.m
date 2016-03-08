
%hold on;
% n = VarName1;
% x_real = VarName2;
% y_real = VarName3;
% x_model = VarName4;
% y_model = VarName5;
% u = VarName6;
% par = VarName7;
% 
% 
% plot(n,x_real,'b');
% plot(n,y_real,'g');
% plot(n,x_model,'c');
% plot(n,y_model,'y');
% plot(n,u,'r');
% plot(n,par,'k');
% 
% legend('x_{real}','y_{real}','x_{model}','y_{model}','u','y');
% title({'Experimento simulacion'; 'K=[23.17, 6.80]'});
%%
hold on;
data = csvread('../lectura/data.csv');
n = data(:,1);
x_ref = data(:,2);
x_real = data(:,3);
x1 = data(:,4);
x_out = data(:,5);
angle = data(:,6);

plot(n,x_ref,'b');
plot(n,x_real,'g');
%plot(n,x1,'y');
plot(n,x_out,'r');
%plot(n,angle,'y');
legend('x_{ref}','x_{real}','x_{out}');
title({'Experimento control'; '[K Kp Ki Kd]=[23.18, 6.8, -5000, 10, 10]'});
%legend('x_{ref}','x_{out}');
%title({'Experimento simulacion '; '[K Ki]=[22.8283, 6.7, 5000]'});

