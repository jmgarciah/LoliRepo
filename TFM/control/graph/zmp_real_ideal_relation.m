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
figure;
error =  ref - (0.78*ref-0.0029);
plot(ref, error)
xlabel('ZMP ref')
ylabel('error')
% Error to angle

% Relation between angle commanded (ZMP/L)*180/pi and ZMP read
figure; hold on;
%plot(angle_ref, ref, 'r');
plot(angle_ref, zmp, 'b')


%Comparation angle-ZMP
figure; hold on;
plot(angle_ref, zmp,'bo');
zmp1 = -0.01558 * angle_ref;
plot(angle_ref, zmp1,'r')
xlabel('angle(deg)');
ylabel('ZMP (m)');
legend('no offset', 'with offset');
