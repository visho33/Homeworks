A = rand(2, 3);
B = rand(3, 3);
C = rand(3, 2);
D = rand(3, 3);

%a)
2*A + transpose(C);

%b)
%C - 3*B -> Imposible ya que C es de 3x2 y B de 3x3 y deben ser de igual
%tamaño

%c)
3*B - 2*D;

%d)
A*D;

%e)
C*A;

%f)
A*C;

%g)
B*D;

%h)
%C*B -> Imposible ya que C es de 3x2 y B es de 3x3 y la segunda componente
%de C debe ser igual a la primera de B

%i)
transpose(C)*B;

%j)
%det(A) -> Imposible porque A es de 2x3 y el determinante solo existe si
%una matriz es de n x n

%k)
det(D)

%l)
A*transpose(A)

%m)
transpose(A)*A

%n)
det(A*transpose(A))

%o)
det(transpose(A)*A)