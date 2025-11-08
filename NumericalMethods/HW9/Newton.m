function [x, past, iter] = Newton(x0, f, fprima, tol)
    x = x0 - f(x0)/fprima(x0);
    iter = 0;
    past = [x0, x];
    while abs(x - x0) >= tol && iter < 10000
        x0 = x;
        x = x0 - f(x0)/fprima(x0);
        past = [past, x];
        iter = iter + 1;
    end
    return
end