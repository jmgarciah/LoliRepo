
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
n = VarName1;
x_ref = VarName2;
x_real = VarName3;
x1 = VarName4;
x_out = VarName5;

plot(n,x_ref,'b');
plot(n,x_real,'g');
%plot(n,x1,'y');
plot(n,x_out,'r');
legend('x_{ref}','x_{real}','x_{out}');
%title({'Experimento control'; '[K Ki]=[23.17, 6.80, 0.1]'});
%legend('x_{ref}','x_{out}');
title({'Experimento simulacion '; '[K Ki]=[22.8283, 6.7, 5000]'});

