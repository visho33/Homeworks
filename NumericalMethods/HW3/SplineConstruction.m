function Scf = SplineConstruction(x,fx)
    n = length(x);
    Scf = zeros(n, 4);
    h = zeros(n-1, 1);
    for i = 1:(n-1)
       h(i) = x(i+1) - x(i);
    end
    for i = 1:n
        Scf(i, 1) = fx(i);
    end
    A = zeros(n, n);
    b = zeros(n, 1);
    A(1, 1) = 1;
    A(n, n) = 1;
    for i = 2:(n-1)
        A(i, i-1) = h(i-1);
        A(i, i) = 2*(h(i-1) + h(i));
        A(i, i+1) = h(i);
        b(i) = 3*(fx(i+1) - fx(i))/h(i) - 3*(fx(i) - fx(i-1))/h(i-1);
    end
    Ai = inv(A);
    Scf(:, 3) = Ai*b;
    
    for i = 1:(n-1)
        Scf(i, 2) = (Scf(i+1, 1) - Scf(i, 1))/(h(i)) - (h(i)*(2*Scf(i, 3) + Scf(i+1, 3)))/3;
        Scf(i, 4) = (Scf(i+1, 3) - Scf(i, 3))/(3*h(i));
    end
    
end