function [xi2D, w2D] = GaussLeg2DTri(np)

    [xi2DQ, w2DQ] = GaussLeg2DQuad(np);
    xi2D = zeros(np*np, 2);
    w2D = zeros(1, np*np);
    for i = 1:np*np
        w2D(i) = w2DQ(i)*1/4*(1-1/2*(xi2DQ(i, 2)+1));
        xi2D(i, 1) = (1/2*(xi2DQ(i, 1)+ 1))*(1 - 1/2*(xi2DQ(i, 2)+1));
        xi2D(i, 2) = 1/2*(xi2DQ(i, 2)+1);
    end

end