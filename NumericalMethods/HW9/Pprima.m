function y = Pprima(n, x)
    
    y = (n/(1-x^2))*(P(n-1, x) - x*P(n, x));
    
    return
end