n = 6;
x = zeros(1, n);
fx = zeros(1, n);
for i = 1:n
    x(i) = -1 + (2*(i-1))/(n-1);
    fx(i) = cos(2*x(i));
end

dd = DividedDifferences(x, fx);

xplot=-1:0.01:1;
fplot = cos(2*xplot);
fxplot = zeros(1, 201);
d = dd(1, :);

fxplot(:) = d(n);
for i = (n-1):-1:1
    fxplot = fxplot.*(xplot - x(i)) + d(i);
end

plot(xplot, fxplot, '-k', xplot, fplot, '-r')
title('Aproximación de cos(2x) usando Diferencias Divididas')
xlabel('x') 
ylabel('y')
legend({'Aproximación','cos(2x)'},'Location','south')
