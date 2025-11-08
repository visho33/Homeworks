x = 1e-9:1e-9:1e-7;
y=1+x;
f1 = log(1+x)./x;
f2=log(y)./(y-1);
plot(x, f1, '-k', x, f2, '-r')
title('Resultado de la expresión')
xlabel('x') 
ylabel('y')
legend({'f1', 'f2'}, 'Location', 'northeast')