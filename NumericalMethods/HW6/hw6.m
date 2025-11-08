exact1 = 0;
exact2 = 0;
n = 200;
f1 = @(x) exp(-x^2);
f2 = @(x) exp(-1/x^2);
[x, w] = mychebpts(n);
for i = 1:n
    exact1 = exact1 + w(i)*f1(x(i));
    exact2 = exact2 + w(i)*3/2*f2(9/2 + 3/2*x(i));
end

%solve(@(x) x^20, -1, 1, 2/21); %1
%solve(@(x) exp(-x^2), -1, 1, exact1); %2
%solve(@(x) 1/(1+4*x^2), -1, 1, atan(2)); %3
%solve(@(x) abs(x)^3, -1, 1, 0.5); %4
%solve(@(x) abs(x), -1, 1, 1); %5
%solve(@(x) exp(x), 2, 3, exp(3) - exp(2)); %6
solve(@(x) exp(-1/x^2), 3, 6, exact2); %7