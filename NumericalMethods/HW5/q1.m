x1 = -1:0.02:1;
x2 = cos((2*(0:100)+1)*pi/202);
x3 = cos((0:100)*pi/100);

Am1 = zeros(101, 101);
Am2 = zeros(101, 101);
Am3 = zeros(101, 101);
Ac1 = zeros(101, 101);
Ac2 = zeros(101, 101);
Ac3 = zeros(101, 101);

for i = 1:101
    for j = 1:101
        Am1(i, j) = monico(j-1, x1(i));
        Am2(i, j) = monico(j-1, x2(i));
        Am3(i, j) = monico(j-1, x3(i));
        Ac1(i, j) = chebyshev(j-1, x1(i));
        Ac2(i, j) = chebyshev(j-1, x2(i));
        Ac3(i, j) = chebyshev(j-1, x3(i));
    end
end

display(cond(Am1));
display(cond(Am2));
display(cond(Am3));
display(cond(Ac1));
display(cond(Ac2));
display(cond(Ac3));
