x = cos((2*(0:499)+1)*pi/1000);
A = zeros(500, 500);
f = zeros(500);
g = zeros(500);
h = zeros(500);

for i = 1:500
    for j = 1:500
        A(i, j) = chebyshev(j-1, x(i));
    end
    f(i) = abs(x(i));
    g(i) = abs(x(i))^7;
    h(i) = 1/(1+25*x(i)*x(i));
end

f = f(:, 1);
g = g(:, 1);
h = h(:, 1);

cf = A\f;
cg = A\g;
ch = A\h;

xx = 0:1:499;

semilogy(xx, abs(cf), '.k', xx, abs(cg), '.r', xx, abs(ch), '.b');
title('Aproximación de cos(2x) usando Diferencias Divididas de Hermite')
xlabel('Número del coeficiente') 
ylabel('Valor absoluto del coeficiente')
legend({'|x|','|x|^7', 'Función de Runge'},'Location','southwest')



