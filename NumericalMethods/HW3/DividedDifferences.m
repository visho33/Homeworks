function dd = DividedDifferences(x, fx)
    n = length(x);
    dd = zeros(n, n);
    for i = 1:n
        dd(i, i) = fx(i);
    end
    for j = 1:n
        for i = 1:(n-j)
            dd(i, i+j) = (dd(i+1, i+j) - dd(i, i+j-1))/(x(i+j) - x(i));
        end
    end
end