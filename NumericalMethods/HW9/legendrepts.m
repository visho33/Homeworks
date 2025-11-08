function [x, w] = legendrepts(n)
    
    x = zeros(n, 1);
    w = zeros(1, n);
    
    for i = 1:n
        x(i) = cos(((2*i-1)/(2*n))*pi); 
        x(i) = Newton2(n, x(i), 0.00000001);
    end
    
    for i = 1:n
        w(i) = (2)/((1-x(i)^2)*(Pprima(n, x(i)))^2);
    end
    
    return
end