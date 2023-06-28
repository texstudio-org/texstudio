# simples-matrices package
# Matthew Bertucci 2022/06/21 for v1.0

#include:l3keys2e
#include:amsmath

\simplesmatricessetup{options%keyvals}

#keyvals:\usepackage/simples-matrices#c,\simplesmatricessetup,\matrice,\declarermatrice,\declarermatrice*,\lamatrice,\matid,\matnulle
envir=%<envname%>
prefix=%<envname prefix%>
typeord=%<type%>
argopt=%<token list%>
#endkeyvals

#keyvals:\simplesmatricessetup
out-of-box
#endkeyvals

\matrice{clist of coefficients}#m
\matrice[type]{clist of coefficients}#m
\matrice<keyvals>{clist of coefficients}#m
\matrice<keyvals>[type]{clist of coefficients}#m
\matrice(prefix){clist of coefficients}#m
\matrice(prefix)[type]{clist of coefficients}#m
\matrice(prefix)<keyvals>{clist of coefficients}#m
\matrice(prefix)<keyvals>[type]{clist of coefficients}#m

\declarermatrice{matrix name}{clist of coefficients%formula}
\declarermatrice{matrix name}[type]{clist of coefficients%formula}
\declarermatrice<keyvals>{matrix name}{clist of coefficients%formula}
\declarermatrice<keyvals>{matrix name}[type]{clist of coefficients%formula}
\declarermatrice(prefix){matrix name}{clist of coefficients%formula}
\declarermatrice(prefix){matrix name}[type]{clist of coefficients%formula}
\declarermatrice(prefix)<keyvals>{matrix name}{clist of coefficients%formula}
\declarermatrice(prefix)<keyvals>{matrix name}[type]{clist of coefficients%formula}
\declarermatrice*{matrix name}{clist of coefficients%formula}
\declarermatrice*{matrix name}[type]{clist of coefficients%formula}
\declarermatrice*<keyvals>{matrix name}{clist of coefficients%formula}
\declarermatrice*<keyvals>{matrix name}[type]{clist of coefficients%formula}
\declarermatrice*(prefix){matrix name}{clist of coefficients%formula}
\declarermatrice*(prefix){matrix name}[type]{clist of coefficients%formula}
\declarermatrice*(prefix)<keyvals>{matrix name}{clist of coefficients%formula}
\declarermatrice*(prefix)<keyvals>{matrix name}[type]{clist of coefficients%formula}

\lamatrice{matrix name}
\lamatrice<keyvals>{matrix name}
\lamatrice(prefix){matrix name}
\lamatrice(prefix)<keyvals>{matrix name}

\MatriceInterieur
\LaMatriceInterieur{matrix name}

\matid{number of columns}#m
\matid[coefficient]{number of columns}#m
\matid<keyvals>{number of columns}#m
\matid<keyvals>[coefficient]{number of columns}#m
\matid(prefix){number of columns}#m
\matid(prefix)[coefficient]{number of columns}#m
\matid(prefix)<keyvals>{number of columns}#m
\matid(prefix)<keyvals>[coefficient]{number of columns}#m

\matnulle{number of columns}#m
\matnulle[coefficient]{number of columns}#m
\matnulle<keyvals>{number of columns}#m
\matnulle<keyvals>[coefficient]{number of columns}#m
\matnulle(prefix){number of columns}#m
\matnulle(prefix)[coefficient]{number of columns}#m
\matnulle(prefix)<keyvals>{number of columns}#m
\matnulle(prefix)<keyvals>[coefficient]{number of columns}#m