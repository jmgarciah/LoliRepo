
hold on;
n = VarName1;
x_real = VarName2;
y_real = VarName3;
x_model = VarName4;
y_model = VarName5;
u = VarName6;
par = VarName7;


plot(n,x_real,'b');
plot(n,y_real,'g');
plot(n,x_model,'c');
plot(n,y_model,'y');
plot(n,u,'r');
plot(n,par,'k');

legend('x_{real}','y_{real}','x_{model}','y_{model}','u','y');
title('Experimento 2 control');