function S = EvaluateSpline(x, Scf, xplot)
    
    n = length(x);
    m = length(xplot);
    S = zeros(m, 1);
    for i = 1:m
        for j = 1:(n-1)
            if xplot(i) >= x(j) && xplot(i) < x(j+1)
                S(i) = Scf(j, 1) + Scf(j, 2)*(xplot(i) - x(j)) + Scf(j, 3)*(xplot(i) - x(j))^2 + Scf(j, 4)*(xplot(i) - x(j))^3;
            end
        end
    end

end