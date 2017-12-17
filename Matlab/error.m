line0=zeros(2,1001);
% line1=zeros(2,1001);
% line2=zeros(2,1001);
% line3=zeros(2,1001);
e=5;
d=200;

line0(1,:)=50;
line0(2,:)=50:-0.1:-50;

% line1(1,:)=50:-0.1:-50;
% line1(2,:)=-50;
% 
% line2(1,:)=-50;
% line2(2,:)=-50:0.1:50;
% 
% line3(1,:)=50:0.1:50;
% line3(2,:)=50;
% line=[line0,line1,line2,line3];
theta=iKine1(line0);
xy = fKine(theta);

plot(xy(1,:),xy(2,:),'LineWidth',1);

axis equal
axis([-60, 60, -60, 60]);
hold on 

theta=iKine0(line0);

error = tan(2*theta(1,:)).*(e+sqrt(d^2+line0(2,:).^2)-d);

plot(xy(1,:)-error,xy(2,:),'LineWidth',1);

xlabel('x')
ylabel('y')
