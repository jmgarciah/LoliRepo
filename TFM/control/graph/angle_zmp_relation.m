%% Data (measures in mm) - 19/05/2016
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


%% Data (measures in mm) - 2/06/2016
% Offset deleted at the beginning
% angles in deg and zmp in metres
angle = [0 -0.5 -1 -1.5 -2 -2.5 -3 -3.5 -4 -4.5 -5];
test1 = [0 0.005 0.012 0.0175 0.024 0.0305 0.037 0.043 0.051 0.06 0.0665];
test2 = [0 0.005 0.01 0.018 0.023 0.034 0.04 0.049 0.052 0.065 0.071];
test3 = [0 0.004 0.008 0.014 0.021 0.026 0.036 0.04 0.047 0.055 0.060];
p = polyfit(angle, test1, 1);
line = p(1)*angle + p(2);
p2 = polyfit(angle, test2, 1);
line2 = p2(1)*angle + p2(2);
p3 = polyfit(angle, test3, 1);
line3 = p3(1)*angle + p3(2);

figure; hold on; box on;
plot(angle, test1, 'bo');
plot(angle, test2, 'go');
plot(angle, test3, 'mo');
plot(angle, line,'r');
plot(angle, line2,'r');
plot(angle, line3,'r');
xlabel('angle [deg]');
ylabel('ZMP [mm]');
gtext(['Test 1: zmp = ',num2str(p(1)),'*angle +',num2str(p(2))])
gtext(['Test 2: zmp = ',num2str(p2(1)),'*angle +',num2str(p2(2))])
gtext(['Test 3: zmp = ',num2str(p3(1)),'*angle +',num2str(p3(2))])
legend('ZMP F/T Test1','ZMP F/T Test2', 'ZMP F/T Test3');


%% Data (measures in mm) - 24/06/2016
% sensor height is 0.0358 m
% Offset deleted at the beginning
% angles in deg and zmp in metres


angle = [0 -0.5 -1 -1.5 -2 -2.5 -3 -3.5 -4 -4.5 -5 -5.5];
ZMP1 = [0 0.0068 0.0169 0.0243 0.0336 0.0438 0.0544 0.0639 0.0731 0.0875 0.0952 0.1046];
angleRL1 = [-0.15 -0.51 -1.03 -1.47 -2.09 -2.53 -2.97 -3.58 -4.02 -4.46 -5.07 -5.51];
angleLL1 = [0.15 -0.35 -0.87 -1.31 -1.75 -2.28 -2.81 -3.33 -3.77 -4.39 -4.83 -5.36];
FxR1 = [3.5 1.5 1.5 0 -2 -6 -7 -11 -13 -17 -20 -22];
FxL1 = [-35 -37.5 -36.5 -39.5 -41 -39 -37 -33.5 -31 -28 -24.5 -22];
TyR1 = [5.3 8.6 12.8 15.5 19 22.1 25.1 27.5 29.5 32 33 34.9];
TyL1 = [-14.7 -13.9 -12.8 -11.4 -10.2 -8 -6.3 -4.1 -2.2 -0.1 -3.5 -6.7];

ZMP2 = [0 0.006 0.0134 0.0205 0.028 0.0365 0.0461 0.0545 0.0622 0.0712 0.079 0.086];
angleRL2 = [-0.15 -0.59 -1.12 -1.56 -2.09 -2.61 -3.23 -3.58 -4.11 -4.63 -5.16 -5.6];
angleLL2 = [0.15 -0.35 -0.87 -1.31 -1.84 -2.37 -2.81 -3.33 -3.86 -4.39 -4.92 -5.44];
FxR2 = [8.3 6 10 9 7.5 3.5 2 0 -4 -5 -9 -11];
FxL2 = [-12.7 -22 -21 -23 -24 -21 -20 -16 -13 -11 -9 -8];
TyR2 = [8 11.1 14 17.3 20.5 23.3 26.6 29 31 33.5 34.5 37];
TyL2 = [-19 -11.9 -10 -9.3 -8.1 -5.9 -3.8 -1.4 0 3.3 6.2 7.9];

ZMP3 = [0.0001 0.0069 0.0135 0.0205 0.0293 0.0376 0.0475 0.0568 0.0647 0.0739 0.0813 0.0895];   
angleRL3 = [-0.15 -0.5 -1.03 -1.56 -2.09 -2.61 -3.05 -3.67 -4.02 -4.63 -5.07 -5.6];
angleLL3 = -[0.08 0.43 0.96 1.40 1.93 2.37 2.89 3.42 3.86 4.48 4.83 5.53];
FxR3 = [2 5 3 2 0 -+5 -7 -9 -12 -15 -16 -18];
FxL3 = [-20 -23 -25 -26 -25.5 -24 -23 -18 -15 -14 -12 -10];
TyR3 = [7 10.4 13 16.4 19.6 22.1 25.4 27.8 29.9 31.9 33 34.5];
TyL3 = [-12 -11.4 -10 -8.9 -7.5 -5.4 -3.3 -0.8 1.2 4 6.6 9.2];


ZMP4 = [0 0.0065 0.0145 0.0226 0.0318 0.0408 0.0475 0.0558 0.0648 0.0743 0.08 0.090];
angleRL4 = [-0.15 -0.68 -1.21 -1.65 -2.17 -2.7 -3.14 -3.67 ];
angleLL4 = [0.15 -0.43 -0.96 -1.49 -1.93 -2.5 -2.89 -3.42];
FxR4 = [6 4 4 2 6 0 2 -1];
FxL4 = [-28 -30 -32 -19 -22 -15 -13];
TyR4 = [11 15.2 18 23 24.4 28.9 30.4];
TyL4 = [-11 -9.9 -8 -7 -4.3 -3.1 0.8];

ZMP5 = [0 0.0064 0.0135 0.0218 0.0312 0.0394 0.0463 0.0578 nan nan nan nan];
FxR5 = [4 4 1 0 -2 -4 -8 -12];
FxL5 = [-22 -24 -26 -24.5 -23.5 -22 -20 -18];
TyR5 = [8.1 11.4 14.6 17.7 21.5 24.1 26 29];
TyL5 = [-12.2 -11.4 -10.3 -8.6 -4.8 -1.9 0];


p1 = polyfit(angle, ZMP1, 1);
line = p1(1)*angle + p1(2);
p2 = polyfit(angle, ZMP2, 1);
line2 = p2(1)*angle + p2(2);
p3 = polyfit(angle, ZMP3, 1);
line3 = p3(1)*angle + p3(2);
p4 = polyfit(angle(1:8), ZMP4(1:8), 1);
line4 = p4(1)*angle + p4(2);
p5 = polyfit(angle(1:8), ZMP5(1:8), 1);
line4 = p5(1)*angle + p5(2);

%Valor medio de ZMP para cada angulo
ZMP = [ZMP1' ZMP2' ZMP3' ZMP4' ZMP5'];
ZMPVm = mean(ZMP,2)

% Graficas relacion angulo-read ZMP
figure; hold on; box on;
plot(angle, ZMP1, 'bo');
plot(angle, ZMP2, 'yo');
plot(angle, ZMP3, 'go');
plot(angle, ZMP4, 'ko');
plot(angle, ZMP5, 'mo')
plot(angle, ZMPVm, 'r');

xlabel('angle [deg]');
ylabel('ZMP [m]');
legend('ZMP F/T Test1','ZMP F/T Test2', 'ZMP F/T Test3', 'ZMP F/T Test4', ...
    'ZMP F/T Test5','Mean ZMP');

% Angle commanded vs encoders measure
figure; hold on; box on;
plot(angle, angle, 'r');
plot(angle, angleRL1, 'bo', angle, angleLL1, 'b*');
plot(angle, angleRL2, 'mo', angle, angleLL2, 'm*');
plot(angle, angleRL3, 'go', angle, angleLL3, 'g*');
plot(angle(1:8), angleRL4, 'ko', angle(1:8), angleLL4, 'k*');
xlabel('Angle sent (deg)');
ylabel('Angle read (deg)');
legend('Commanded angle', 'test1LeftLeg','test1RightLeg', 'test2LeftLeg', ...
    'test2RightLeg','test3RightLeg','test3RightLeg','test4RightLeg','test4RightLeg');
title('ommanded angle - angle read from encoders');


% Joint torques
MaxMotorTorque = 0.108; % RMS torque in Nm
TransRatio = 1.69*160 % belts ratio and motor-gearhead ratio
MaxJointTorque = TransRatio * MaxMotorTorque;

figure; hold on; box on;
plot(0:-0.01:angle(1,12), MaxJointTorque, 'k-');
plot(angle, TyR1,'bo', angle, TyL1,'b*');
plot(angle, TyR2,'go', angle, TyL2,'g*');
plot(angle, TyR3,'mo', angle, TyL3,'m*');
plot(angle(1:7), TyR1,'co', angle(1:7), TyL1,'c*');