v0 = [0; 0];
v1 = [1; 0];
c0 = [2; 1];
c1 = [-1; 1];
t=0:0.01:1;
f = BezierCurve(v0, c0, c1, v1, t);

x = [0; 1];
fx = [v0(1); v1(1)];
fy = [v0(2); v1(2)];
dfx = [3*(c0(1) - v0(1)); 3*(v1(1) - c1(1))];
dfy = [3*(c0(2) - v0(2)); 3*(v1(2) - c1(2))];

hddx = HermiteDividedDifferences(x, fx, dfx);
hddy = HermiteDividedDifferences(x, fy, dfy);
hdx = hddx(1, :);
hdy = hddy(1, :);
f1 = zeros(1, 101);
f1(:) = hdx(4);
f2 = zeros(1, 101);
f2(:) = hdy(4);

for i = (3):-1:1
    f1 = f1.*(t - x(floor((i+1)/2))) + hdx(i);
end

for i = (3):-1:1
    f2 = f2.*(t - x(floor((i+1)/2))) + hdy(i);
end

%plot(f(1, :), f(2, :))
%title('Curva de Bezier')
%xlabel('x') 
%ylabel('y')

plot(f1, f2)
title('Interpolación de Hermite')
xlabel('x') 
ylabel('y')