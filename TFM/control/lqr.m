m  = 62.416; %System mass
g = 9.81; %Gravity constant
l = (92+330+299.897+123.005)/1000; %Pendulum longitude
k = 0.1; %Stiffness
T = 0.001; %Sample Time

a = (k - m*g*l) / (m*l^2);
b = k / (m*l^2);

% Space state matrices
A = [0 1; -a 0]; 
B = [0; 1];
C = [k*b 0];
D = -k;


%% CONTINUOUS TO DISCRETE SPACE STATE EQUATIONS 
% x' = Ax(t) + Bu(t) 
% y = Cx(t) + Du(t)
% ||||
% vvvv
% x[k+1] = Gx[k] + Hu[k]
% y[k] = Cx[k] + Du[k]
% 
% G = e^(A*T) where T is time sample
% H = (e^(A*T)-I)*A^-1

AT = A*T;
G = expm(AT);
H = (expm(AT)-eye(2,2))*(A^-1)*B;


%% LQR calculus
% Q and R : Ricatti equation parameters
Q = C'*C;
R = eye(size(H,2)); %R=1

% LINEAR QUADRATIC REGULATOR  (DISCRETE CASE)
% Kopt = (R+B'PB)^-1B'PA
% P -> A'PA -C P+A'PB(R+B'PB)^-1B'PA + Q = 0

[K] = dlqr(G,H,Q,R);

%% System response (??????????????????)

% Ac = (G-H*K);
% Bc = H;
% Cc = C;
% Dc = D;
% 
% sys_cl = ss(Ac,Bc,Cc,Dc,T);
% 
% t = 0:T:100;
% r = 0*ones(size(t));
% [y,t,x] = lsim(sys_cl,r,t);
% plot(t,y,'b',t,r,'r');
