function hdd = HermiteDividedDifferences(x, fx, dfx)
    n = length(x);
    hdd = zeros(2*n, 2*n);
    for i = 1:2*n
        hdd(i, i) = fx(floor((i+1)/2));
    end
    for i = 1:(2*n-1)
        if mod(i, 2) == 1
            hdd(i, i+1) = dfx(floor((i+1)/2));
        else
            hdd(i, i+1) = (hdd(i+1, i+1) - hdd(i, i))/(x(floor((i+3)/2)) - x(floor((i+1)/2)));
        end
    end
    for j = 2:2*n
        for i = 1:(2*n-j)
            hdd(i, i+j) = (hdd(i+1, i+j) - hdd(i, i+j-1))/(x(floor((i+j+1)/2)) - x(floor((i+1)/2)));
        end
    end
end