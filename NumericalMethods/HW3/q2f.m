n1 = 6;
x = zeros(1, n1);
fx = zeros(1, n1);
dfx = zeros(1, n1);
for i = 1:n1
    x(i) = -1 + (2*(i-1))/(n1-1);
    fx(i) = 1/(1+25*x(i)*x(i));
    dfx(i) = -(50*x(i))/((1+25*x(i)*x(i))*(1+25*x(i)*x(i)));
end

dd = DividedDifferences(x, fx);

xplot=-1:0.01:1;
fplot = 1./(1+25.*xplot.*xplot);
fxplot = zeros(1, 201);
d = dd(1, :);

hdd = HermiteDividedDifferences(x, fx, dfx);
hfxplot = zeros(1, 201);
hd = hdd(1, :);
hfxplot(:) = hd(2*n1);
fxplot(:) = d(n1);

for i = (n1-1):-1:1
    fxplot = fxplot.*(xplot - x(i)) + d(i);
end

for i = (2*n1-1):-1:1
    hfxplot = hfxplot.*(xplot - x(floor((i+1)/2))) + hd(i);
end

n2 = 12;
x = zeros(1, n2);
fx = zeros(1, n2);
for i = 1:n2
    x(i) = -1 + (2*(i-1))/(n2-1);
    fx(i) = 1/(1+25*x(i)*x(i));
end

dd = DividedDifferences(x, fx);
fxplot2 = zeros(1, 201);
d = dd(1, :);
fxplot2(:) = d(n2);

for i = (n2-1):-1:1
    fxplot2 = fxplot2.*(xplot - x(i)) + d(i);
end

%plot(xplot, hfxplot, '-k', xplot, fplot, '-r')
%title('Aproximación de la curva de Runge usando Diferencias Divididas de Hermite')
%xlabel('x') 
%ylabel('y')
%legend({'Aproximación','Curva de Runge'},'Location','south')

plot(xplot, hfxplot, '-k', xplot, fplot, '-r', xplot, fxplot, '-g', xplot, fxplot2, '-b')
title('Aproximaciones de la curva de Runge con interpolaciones')
xlabel('x')
ylabel('y')
legend({'Hérmite de grado 11','Curva de Runge', 'Simple de grado 5', 'Simple de grado 11'},'Location','south')
