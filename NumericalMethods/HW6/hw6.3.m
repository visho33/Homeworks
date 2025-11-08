[xi2DQ, w2DQ] = GaussLeg2DQuad(5);
rojox = [];
rojoy = [];
negrox = [];
negroy = [];

for n = 1:30
    for m = 1:30
        f = @(xi, eta) (xi.^n).*(eta.^m);
        numInt=w2DQ*f(xi2DQ(:,1), xi2DQ(:,2));
        exactInt=(1/(n+1))*(1^(n+1)-(-1)^(n+1))*(1/(m+1))*(1^(m+1)-(-1)^(m+1));
        error = abs(numInt - exactInt);
        if error < 5*eps
            negrox = [negrox, n];
            negroy = [negroy, m];
        else
            rojox = [rojox, n];
            rojoy = [rojoy, m];
        end
    end
end


%plot(negrox, negroy, '.k', rojox, rojoy, '.r')
%title('Valores de n y m que hacen la cuadratura exacta')
%xlabel('n') 
%ylabel('m')
%legend({'Exacto', 'No exacto'},'Location','southeast')

[xi2D, w2D] = GaussLeg2DTri(3);
rojox = [];
rojoy = [];
negrox = [];
negroy = [];

for n = 1:30
    for m = 1:30
        f = @(xi,eta) (xi.^n).*(eta.^m);
        numInt = w2D*f(xi2D(:,1),xi2D(:,2));
        exactInt=factorial(n)*factorial(m)/factorial(n+m+2);
        error = abs(numInt - exactInt)/abs(exactInt);
        if error < 5*eps
            negrox = [negrox, n];
            negroy = [negroy, m];
        else
            rojox = [rojox, n];
            rojoy = [rojoy, m];
        end
    end
end

plot(negrox, negroy, '.k', rojox, rojoy, '.r')
title('Valores de n y m que hacen la cuadratura exacta')
xlabel('n') 
ylabel('m')
legend({'Exacto', 'No exacto'},'Location','southeast')

