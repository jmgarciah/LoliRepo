% Data (measures in metres)
%ZMP = [0 0.005 0.0095 0.012 0.0155 0.019 0.0225 0.0295]
zmp = [0.0015 0.0043 0.0085 0.013 0.017 0.021 0.024 0.027 0.033 0.0365];
ref = [0.005 0.01 0.015 0.02 0.025 0.03 0.035 0.04 0.045 0.05];
angle = -asin(zmp / 0.8927) *180/pi;
angle_ref = -asin(ref / 0.8927) *180/pi;
zmp_ideal =  ref;

% Relation between the ZMP commanded and the ZMP obtained from sensors
figure; hold on;
plot(ref, zmp ,'bo');
plot(ref, zmp_ideal, 'm');
xlabel('ZMP referencia');
ylabel('ZMP F/T');
legend('ZMP real', 'ZMP ideal')

% Lines above have a linear error increment
%figure;
error =  ref - (0.76*ref-0.002);
plot(ref, error)
xlabel('ZMP ref')
ylabel('error')

% Relation between angle commanded (ZMP/L)*180/pi and ZMP read
figure; hold on;
%plot(angle_ref, ref, 'r');
plot(angle_ref, zmp, 'b')
xlabel('angle sent (deg)');
ylabel('zmp read (mm)');


%Comparation angle-ZMP
figure; hold on;
plot(angle_ref, zmp,'bo');
zmp1 = -0.01558 * angle_ref;
plot(angle_ref, zmp1,'r')
xlabel('angle(deg)');
ylabel('ZMP (m)');
legend('no offset', 'with offset');


%Aproximacion a 1/x
cociente = error ./ ref;
y = (0.004 ./ (1.5*ref)) + 0.23 ;
figure; hold on
plot(ref, cociente,'bo');
plot(ref, y,'r-');
legend('cociente', 'ajuste');
gtext('y = (0.004/(1.5*ref)) + 0.23')
xlabel('ref');
ylabel('error/ref');

ref = 0.02;
theta = (ref/0.0156) + (0.004/(1.5*ref)+0.23)*ref/0.0156


%Aproximacion a exponencial y = c*e^ax
cociente = error ./ ref;
p = polyfit(ref,log(cociente),1);
a = p(1);
c = exp(p(2));
fprintf('exponente a= %2.3f\n',a);
fprintf('coeficiente c = %3.3f\n',c);

y =  c * exp(a*ref);

y2 =  c * exp(-100*ref)+0.28;

plot(ref,y,'r',ref,y2,'g',ref, cociente, 'bo')
xlabel('ref');
ylabel('error/ref');
legend('y = 0.51 * e^-14.792*ref', 'y = (0.51 * e^-100*ref )+0.28' )

ref = 0.07;
o = -((ref/0.0135) + ((0.5186*exp(-100*ref))))

ref= 0.01;
o = -(ref/0.0156) - ((0.5186*exp(-14.79*ref)-12*ref))

% Comparation between angle error and zmp error.
error =  ref - (0.76*ref-0.002);
angle_error = +(0.76*ref-0.002)/0.0156;

plot(error, angle_error, 'bo')
xlabel('zmp')
ylabel('|theta|');

