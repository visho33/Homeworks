Nmax=100000;
a=zeros(1,Nmax+1);
b=zeros(1,Nmax+1);
n = zeros(1, Nmax + 1);
errora=zeros(1, Nmax + 1);
errorb=zeros(1, Nmax + 1);
for k=0:Nmax
    n(k+1) = k+1;
    if k==0
        a(k+1)= 4;
        b(k+1)= 6/sqrt(3);
        errora(k+1) = abs(a(k+1) - pi)/pi;
        errorb(k+1) = abs(b(k+1) - pi)/pi;
    else
        a(k+1)=a(k)+ 4*(((-1)^k)/(2*k+1));
        b(k+1)=b(k)+ 6*(((-1)^k)*((1/sqrt(3))^(2*k+1))/(2*k+1));
        errora(k+1) = abs(a(k+1) - pi)/pi;
        errorb(k+1) = abs(b(k+1) - pi)/pi;
    end
end

loglog(n(11:Nmax+1), errora(11:Nmax+1), '-k', n(11:Nmax+1), errorb(11:Nmax+1), '-r')
title('Error relativo de las aproximaciones de \pi usando los N términos de la serie')
xlabel('N') 
ylabel('Error relativo')
legend({'Error de la serie para x = 1','Error de la serie para x = 3^{-0.5}'},'Location','northeast')

p = polyfit(log(n(11:Nmax+1)), log(errora(11:Nmax+1)), 1);


