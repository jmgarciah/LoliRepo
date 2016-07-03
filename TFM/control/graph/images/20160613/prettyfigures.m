data = csvread('exp06.csv');

n = data(267:647,1);
t = data(267:647,2)-8.01;
zmp_ft = data(267:647,3);
zmp_model = data(267:647,4);
zmp_error = data(267:647,5);
zmp_ref = data(267:647,6);
u = data(267:647,7);
x1 = data(267:647,8);
x2 = data(267:647,9);
angle = data(267:647,10);

%Sole borders
front = (120+55)/1000*ones(size(n));
back = -70/1000*ones(size(n));
left = (140+37.5)/1000*ones(size(n));
right = -(140+37.5)/1000*ones(size(n));

figure; hold on; grid on; box on
L11 = line(t,zmp_ref,'Color','k','LineWidth',2);
L12 = line(t,zmp_model,'Color','b','LineWidth',2);
L13 = line(t,zmp_ft,'Color','g','LineWidth',2);
L14 = line(t,front,'Color','k','LineStyle','--');
L15 = line(t,back,'Color','k','LineStyle','--');

ax1 = gca; % current axes
ax1.XColor = 'k';
ax1.YColor = 'k';
ax1.YLim = [-0.04 0.12];
ax1.FontSize = 14;

ax1_pos = ax1.Position; % position of first axes
ax2 = axes('Position',ax1_pos,...
    'XAxisLocation','bottom',...
    'YAxisLocation','right',...
    'Color','none',...
    'FontSize', 14);
L21 = line(t,angle,'Parent',ax2,'Color','r','LineWidth',2);


%title('Multiple x-axes and y-axes figure')
xlabel(ax1, 't [s]');
ylabel(ax1, 'ZMP [m]');
ylabel(ax2, 'angle [deg]');
legend([L11, L12, L13, L21],...
    'Reference ZMP','Model ZMP', 'F-T ZMP',...
    'Angular position');

