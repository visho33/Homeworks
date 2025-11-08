function y = P(n, x)
    
    if n == 0
        y = 1;
        return
    end
    if n == 1
        y = x;
        return
    end
    
    y = (1/n)*((2*n - 1)*x*P(n-1, x) - (n-1)*P(n-2, x));
    
    return
end