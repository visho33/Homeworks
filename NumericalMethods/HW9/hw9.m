f = @(x) x^3-2*x+2;
fprima = @(x) 3*x^2-2;
[raiz1, past1, iter1] = Newton(0.5, f, fprima, 0.00000001);
[raiz2, past2, iter2] = Newton(0.1, f, fprima, 0.00000001);
[raiz3, past3, iter3] = Newton(1+i, f, fprima, 0.00000001);

c = -1:0.1:1;
converge = [];
for i = 1:21
    x = PuntoFijo(0.1, c(i), 0.000001);
    if abs(f(x)) <= 0.1
        converge = [converge, c(i)];
    end
end

n = 20;
[x, w] = legendrepts(n);