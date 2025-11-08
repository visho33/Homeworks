k = 1000;
TaylorCoefficient = (-1)^k*factorial(2*k)/(4^k*factorial(k)^2*(2*k+1));

TaylorCoefficient2 = (-1)^k/(2*k+1);
for c = 1:k
    TaylorCoefficient2 = TaylorCoefficient2*(2*c)*(2*c - 1)/(4*c*c);
end
