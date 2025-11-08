function [x,w] = mychebpts(n)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% mychebpts.m - Fast Clenshaw Curtis Quadrature
%
% Compute the n nodes and weights for Clenshaw-Curtis
% Quadrature on the interval [-1,1]. Unlike Gauss 
% quadratures, Clenshaw-Curtis is only exact for 
% polynomials up to order n, however, using the FFT
% algorithm, the weights and nodes are computed in linear
% time. This script will calculate for n=2^20+1 (1048577
% points) in about 5 seconds on a normal laptop computer.
%
% Written originally by: Greg von Winckel - 02/12/2005
% Contact: gregvw(at)chtm(dot)unm(dot)edu
%
% Modified by: Federico Fuentes - 10/2018
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ns=n-1;
c=zeros(n,2);
c(1:2:n,1)=(2./[1 1-(2:2:Ns).^2 ])'; c(2,2)=1;
f=real(ifft([c(1:n,:);c(Ns:-1:2,:)]));
w=[f(1,1); 2*f(2:Ns,1); f(n,1)]';
x=flip(Ns*f(1:n,2));