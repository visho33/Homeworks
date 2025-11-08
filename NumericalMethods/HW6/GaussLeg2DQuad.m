function [xi2DQ, w2DQ] = GaussLeg2DQuad(n1D)
    
    xi2DQ = zeros(n1D*n1D, 2);
    w2DQ = zeros(1, n1D*n1D);
    [x, w] = mylegpts(n1D);
    t = 1;
    for i = 1:n1D
        for j = 1:n1D
            xi2DQ(t, 1) = x(i);
            xi2DQ(t, 2) = x(j);
            w2DQ(t) = w(i)*w(j);
            t = t + 1;
        end
    end

end