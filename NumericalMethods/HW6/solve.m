function solve(f, a, b, exact)
    x = zeros(33, 1);
    for i = 1:33
        x(i) = i+1;
    end
    I1 = zeros(33, 1);
    I2 = zeros(33, 1);
    for n = 2:34
        [x1, w1] = mylegpts(n);
        [x2, w2] = mychebpts(n);
        for i = 1:n
            I1(n-1) = I1(n-1) + w1(i)*(b-a)/2*f((a+b)/2 + x1(i)*(b-a)/2);
            I2(n-1) = I2(n-1) + w2(i)*(b-a)/2*f((a+b)/2 + x2(i)*(b-a)/2);
        end
        I1(n-1) = abs(I1(n-1) - exact);
        I2(n-1) = abs(I2(n-1) - exact);
    end

    semilogy(x, I1, 'k', x, I2, 'r');
    title('Error de la integral numérica usando una cuadratura')
    xlabel('n') 
    ylabel('Error')
    legend({'Legendre','Chebyshev'},'Location','northeast')
    
end