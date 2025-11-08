n = 6;
x = zeros(1, n);
fx = zeros(1, n);
for i = 1:n
    x(i) = -1 + (2*(i-1))/(n-1);
    fx(i) = 1/(1+25*x(i)*x(i));
end

xplot=-1:0.01:1;
fplot = 1./(1+25*xplot.*xplot);

Scf = SplineConstruction(x,fx);
S = EvaluateSpline(x, Scf, xplot);

plot(xplot, S, '-k', xplot, fplot, '-r')
title('Aproximación de la curva de Runge usando spline cúbicas')
xlabel('x') 
ylabel('y')
legend({'Aproximación','f(x)'},'Location','south')