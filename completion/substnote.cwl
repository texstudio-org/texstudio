# substnote package
# Matthew Bertucci 2026/08/04 for v0.1.0

\subst{expr}{vars}{terms}#m
\subst[options%keyvals]{expr}{vars}{terms}#m
\subst*{expr}{vars}{terms}#m
\subst*[options%keyvals]{expr}{vars}{terms}#m
\substmark{vars}{terms}#m
\substmark[options%keyvals]{vars}{terms}#m
\substmark*{vars}{terms}#m
\substmark*[options%keyvals]{vars}{terms}#m

#keyvals:\subst,\subst*,\substmark,\substmark*,\usepackage/substnote#c
style=#slash,slashrev,assign,arrow,mapsto,updown,updownrev
fences=#brackets,parens,braces,none
pairsep=%<code%>
synonym=%<csname%>
#endkeyvals

#keyvals:\usepackage/substnote#c
synonym=%<csname%>
#endkeyvals

\substnoteSubst#S
\substnoteSubstMark#S

