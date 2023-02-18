# ResolSysteme package
# Matthew Bertucci 2023/02/13 for v0.1.4

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
\ProduitMatricesPY(matriceA)(matriceB)
\ProduitMatricesPY<opts nicematrix>(matriceA)(matriceB)
\ProduitMatricesPY[opt de formatage%keyvals](matriceA)(matriceB)
\ProduitMatricesPY[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\ProduitMatricesPY*(matriceA)(matriceB)
\ProduitMatricesPY*<opts nicematrix>(matriceA)(matriceB)
\ProduitMatricesPY*[opt de formatage%keyvals](matriceA)(matriceB)
\ProduitMatricesPY*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\MatricePuissancePY(matrice)(puissance)
\MatricePuissancePY<options nicematrix>(matrice)(puissance)
\MatricePuissancePY[option de formatage%keyvals](matrice)(puissance)
\MatricePuissancePY[option de formatage%keyvals]<options nicematrix>(matrice)(puissance)
\MatricePuissancePY*(matrice)(puissance)
\MatricePuissancePY*<options nicematrix>(matrice)(puissance)
\MatricePuissancePY*[option de formatage%keyvals](matrice)(puissance)
\MatricePuissancePY*[option de formatage%keyvals]<options nicematrix>(matrice)(puissance)
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
\EtatProbPY(état init)(mat de trans)(étape)
\EtatProbPY<options nicematrix>(état init)(mat de trans)(étape)
\EtatProbPY[option de formatage%keyvals](état init)(mat de trans)(étape)
\EtatProbPY[option de formatage%keyvals]<options nicematrix>(état init)(mat de trans)(étape)
\SolutionSystemePY(matriceA)(matriceB)
\SolutionSystemePY<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSystemePY[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY*(matriceA)(matriceB)
\SolutionSystemePY*<opts nicematrix>(matriceA)(matriceB)
\SolutionSystemePY*[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSystemePY*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\EtatStablePY(matrice)
\EtatStablePY<opts nicematrix>(matrice)
\EtatStablePY[opt de formatage%keyvals](matrice)
\EtatStablePY[opt de formatage%keyvals]<opts nicematrix>(matrice)
#endif

\ConvVersFrac{calcul}
\ConvVersFrac[option de formatage%keyvals]{calcul}
\ConvVersFrac*{calcul}
\ConvVersFrac*[option de formatage%keyvals]{calcul}

\AffMatrice(matrice)
\AffMatrice[option de formatage%keyvals](matrice)
\AffMatrice*(matrice)
\AffMatrice*[option de formatage%keyvals](matrice)

\ProduitMatrices(matriceA)(matriceB)
\ProduitMatrices<opts nicematrix>(matriceA)(matriceB)
\ProduitMatrices[opt de formatage%keyvals](matriceA)(matriceB)
\ProduitMatrices[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\ProduitMatrices*(matriceA)(matriceB)
\ProduitMatrices*<opts nicematrix>(matriceA)(matriceB)
\ProduitMatrices*[opt de formatage%keyvals](matriceA)(matriceB)
\ProduitMatrices*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)

\CarreMatrice(matrice)
\CarreMatrice<options nicematrix>(matrice)
\CarreMatrice[option de formatage%keyvals](matrice)
\CarreMatrice[option de formatage%keyvals]<options nicematrix>(matrice)
\CarreMatrice*(matrice)
\CarreMatrice*<options nicematrix>(matrice)
\CarreMatrice*[option de formatage%keyvals](matrice)
\CarreMatrice*[option de formatage%keyvals]<options nicematrix>(matrice)

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

\AffEtatProb(matrice ligne)
\AffEtatProb<options nicematrix>(matrice ligne)
\AffEtatProb[option de formatage%keyvals](matrice ligne)
\AffEtatProb[option de formatage%keyvals]<options nicematrix>(matrice ligne)

\SolutionSysteme(matriceA)(matriceB)
\SolutionSysteme<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSysteme[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme*(matriceA)(matriceB)
\SolutionSysteme*<opts nicematrix>(matriceA)(matriceB)
\SolutionSysteme*[opt de formatage%keyvals](matriceA)(matriceB)
\SolutionSysteme*[opt de formatage%keyvals]<opts nicematrix>(matriceA)(matriceB)

\EtatStable(matrice)
\EtatStable<opts nicematrix>(matrice)
\EtatStable[opt de formatage%keyvals](matrice)
\EtatStable[opt de formatage%keyvals]<opts nicematrix>(matrice)

#keyvals:\ConvVersFrac,\ConvVersFrac*,\AffMatrice,\AffMatrice*,\ProduitMatrices,\ProduitMatrices*,\ProduitMatricesPY,\ProduitMatricesPY*,\CarreMatrice,\CarreMatrice*,\MatricePuissancePY,\MatricePuissancePY*,\DetMatrice,\DetMatrice*,\DetMatricePY,\DetMatricePY*,\MatriceInverse,\MatriceInverse*,\MatriceInversePY,\MatriceInversePY*,\AffEtatProb,\EtatProbPY,\SolutionSysteme,\SolutionSysteme*,\SolutionSystemePY,\SolutionSystemePY*,\EtatStable,\EtatStablePY
t
d
n
dec
dec=%<k%>
#endkeyvals
