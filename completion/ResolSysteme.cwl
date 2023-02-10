# ResolSysteme package
# Matthew Bertucci 2023/02/08 for v0.1.2

#include:nicematrix
#include:ifthen
#include:xintexpr
#include:xinttools
#include:listofitems
#include:siunitx
#include:nicefrac
#include:xstring

#keyvals:\usepackage/ResolSysteme#c
pyluatex
#endkeyvals

#ifOption:pyluatex
\DetMatricePY(matrice)
\DetMatricePY[option de formatage%keyvals](matrice)
\DetMatricePY*(matrice)
\DetMatricePY*[option de formatage%keyvals](matrice)
\MatriceInversePY(matrice)
\MatriceInversePY<options nicematrix>(matrice)
\MatriceInversePY[option de formatage%keyvals](matrice)
\MatriceInversePY[option de formatage%keyvals]<options nicematrix>(matrice)
\MatriceInversePY*(matrice)
\MatriceInversePY*<options nicematrix>(matrice)
\MatriceInversePY*[option de formatage%keyvals](matrice)
\MatriceInversePY*[option de formatage%keyvals]<options nicematrix>(matrice)
\SolutionSystemePY(matriceA)(matriceB)
\SolutionSystemePY<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSystemePY[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY*(matriceA)(matriceB)
\SolutionSystemePY*<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY*[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSystemePY*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
#endif

\ConvVersFrac{calcul}
\ConvVersFrac[option de formatage%keyvals]{calcul}
\ConvVersFrac*{calcul}
\ConvVersFrac*[option de formatage%keyvals]{calcul}

\AffMatrice(matrice)
\AffMatrice[option de formatage%keyvals](matrice)
\AffMatrice*(matrice)
\AffMatrice*[option de formatage%keyvals](matrice)

\DetMatrice(matrice)
\DetMatrice[option de formatage%keyvals](matrice)
\DetMatrice*(matrice)
\DetMatrice*[option de formatage%keyvals](matrice)

\MatriceInverse(matrice)
\MatriceInverse<options nicematrix>(matrice)
\MatriceInverse[option de formatage%keyvals](matrice)
\MatriceInverse[option de formatage%keyvals]<options nicematrix>(matrice)
\MatriceInverse*(matrice)
\MatriceInverse*<options nicematrix>(matrice)
\MatriceInverse*[option de formatage%keyvals](matrice)
\MatriceInverse*[option de formatage%keyvals]<options nicematrix>(matrice)

\SolutionSysteme(matriceA)(matriceB)
\SolutionSysteme<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSysteme[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme*(matriceA)(matriceB)
\SolutionSysteme*<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme*[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSysteme*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)

#keyvals:\ConvVersFrac,\ConvVersFrac*,\AffMatrice,\AffMatrice*,\DetMatrice,\DetMatrice*,\DetMatricePY,\DetMatricePY*,\MatriceInverse,\MatriceInverse*,\MatriceInversePY,\MatriceInversePY*,\SolutionSysteme,\SolutionSysteme*,\SolutionSystemePY,\SolutionSystemePY*
t
d
n
dec
dec=%<k%>
#endkeyvals
