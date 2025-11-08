function x = Newton2(n, x0, tol)
    x = x0 - P(n, x0)/Pprima(n, x0);
    iter = 0;
    while abs(x - x0) >= tol && iter < 100000
        x0 = x;
        x = x0 - P(n, x0)/Pprima(n, x0);
        iter = iter + 1;
    end
    return
end