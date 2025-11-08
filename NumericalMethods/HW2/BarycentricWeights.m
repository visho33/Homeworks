function w = BarycentricWeights(xnod)
    n = length(xnod);
    w = zeros(1, n);
    for i = 1:n
        c = 1;
        for j = 1:n
            if i ~= j
                c = c*(xnod(i) - xnod(j));
            end
        end
        w(i) = 1/c;
    end
end