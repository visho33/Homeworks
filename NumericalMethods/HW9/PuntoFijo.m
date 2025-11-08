function x = PuntoFijo(x0, c, tol)
    g = @(x) x - c*(x^3-2*x+2);
    x = g(x0);
    iter = 0;
    while abs(x - x0) >= tol && iter < 10000
        x0 = x;
        x = g(x0);
        iter = iter + 1;
    end
    return
end