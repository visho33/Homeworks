xnodi = zeros(1, 11);
xnodii = zeros(1, 11);

for i = 1:11
    xnodi(i) = -1 + (i-1)/5;
    xnodii(i) = -1*cos(pi*(i-1)/10);
end

wi = BarycentricWeights(xnodi);
wii = BarycentricWeights(xnodii);

plot(xnodi, wi, '-k', xnodii, wii, '-r')
title('Nodos de interpolación en el intervalo [-1, 1]')
xlabel('Nodos') 
ylabel('Pesos')
legend({'Uniforme','Chebyshev de segundo tipo'},'Location','southwest')

xeval = zeros(1, 201);

for i = 1:201
   xeval(i) = -1 + (i-1)/100; 
end

fi1 = zeros(1, 11);
fii1 = zeros(1, 11);

for i = 1:11
    fi1(i) = 1/(1 + 25*xnodi(i)*xnodi(i));
    fii1(i) = 1/(1 + 25*xnodii(i)*xnodii(i));
end

Pi1 = BarycentricEvaluation(xnodi, wi, fi1, xeval);
Pii1 = BarycentricEvaluation(xnodii, wii, fii1, xeval);

Ri1 = zeros(1, 201);
Rii1 = zeros(1, 201);

for i = 1:201
    Ri1(i) = 1/(1+25*xeval(i)*xeval(i))-Pi1(i);
    Rii1(i) = 1/(1+25*xeval(i)*xeval(i))-Pii1(i);
end

plot(xeval, Ri1, '-k', xeval, Rii1, '-r')
title('Error de la interpolación')
xlabel('Puntos de evaluación') 
ylabel('Error')
legend({'Uniforme','Chebyshev de segundo tipo'},'Location','north')

fi2 = zeros(1, 11);
fii2 = zeros(1, 11);

for i = 1:11
    fi2(i) = abs(xnodi(i));
    fii2(i) = abs(xnodii(i));
end

Pi2 = BarycentricEvaluation(xnodi, wi, fi2, xeval);
Pii2 = BarycentricEvaluation(xnodii, wii, fii2, xeval);

Ri2 = zeros(1, 201);
Rii2 = zeros(1, 201);

for i = 1:201
    Ri2(i) = abs(xeval(i))-Pi2(i);
    Rii2(i) = abs(xeval(i))-Pii2(i);
end

plot(xeval, Ri2, '-k', xeval, Rii2, '-r')
title('Error de la interpolación')
xlabel('Puntos de evaluación') 
ylabel('Error')
legend({'Uniforme','Chebyshev de segundo tipo'},'Location','north')

