function v = BezierCurve(v0, c0, c1, v1, t)
    n = length(t);
    v = zeros(n, 2);
    v = (1-t).^3.*v0 + 3.*(1-t).^2.*t.*c0 + 3.*(1-t).*t.^2.*c1 +t.^3.*v1;
end