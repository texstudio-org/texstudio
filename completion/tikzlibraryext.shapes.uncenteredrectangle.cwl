# ext.shapes.uncenteredrectangle tikzlibrary
# 2025/03/19 for v0.6

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
ext_uncentered rectangle
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
ext/uncentered rectangle center=#left,text,right,real
ext/uncentered rectangle use saved center#true,false
ext/uncentered rectangle center yshift=##L
#endkeyvals

\uncrec{left}{center}{right}

#keyvals:\tikzcdset#c,\begin{tikzcd}#c
install uncentered rectangle in columns=%<column%>
#endkeyvals

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
