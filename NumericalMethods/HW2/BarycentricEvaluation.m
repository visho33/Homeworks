function P = BarycentricEvaluation(xnod, w, f, xeval)
    n = length(xnod);
    m = length(xeval);
    P = zeros(1, m);
    for i = 1:m
        flag = -1;
        for j = 1:n
            if xnod(j) == xeval(i)
                flag = j;
            end
        end
        if flag ~= -1
            P(i) = f(flag);
        else
            num = 0;
            den = 0;
            for j = 1:n
                num = num + (w(j)/(xeval(i) - xnod(j)))*f(j);
                den = den + (w(j)/(xeval(i) - xnod(j)));
            end
            P(i) = num/den;
        end 
    end
end