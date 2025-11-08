%Load coordinates V0, C0, C1 and V1 where a given column has the (x,y)
%coordinates of a given Bezier curve. The number of columns is the number
%of Bezier curves.
load('GlyphData.mat')
t=0:0.01:1;
figure
hold on
a = 51;
b = 72;
for j=a:b%size(V0,2) %loop over all Bezier curves
    %Get coordinates of Bezier curve for all values in t
    v=BezierCurve(V0(:,j),C0(:,j),C1(:,j),V1(:,j),t);
    plot(v(1,:),v(2,:),'b') %plot Bezier curve
    text(v(1, 51), v(2, 51), ("$\mbox{ }$" + (j-a+1)),'Interpreter','latex')
    axis equal %to visualize in scale
end
% %Plot initial and final vertices as red asterisks
% plot(V0(1,:),V0(2,:),'r*',V1(1,:),V1(2,:),'r*')
% %Plot control points as green squares.
% plot(C0(1,:),C0(2,:),'gs',C1(1,:),C1(2,:),'gs')