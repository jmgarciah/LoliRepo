% Box 
box on 

% X-Y Grids
grid on
ax = gca;
ax.GridLineStyle = ':';

% LabelTicks font size
set(gca,'FontSize',14);

% Figure title
title('title','FontSize', 14);

% X-Y Labels font size
xlabel('t [s]','FontSize',14);
ylabel('ylabel','FontSize',14);

% Resize Figure window
hFig = gcf;
set(hFig,'windowstyle','normal');
set(hFig,'units','centimeters','Position',[0 0 20 10]);

% Save Figure to eps 
print('00_single_inverted_pendulum_control_with_non_zero_reference','-deps','-r0')