# ext.scalepicture tikzlibrary
# 2025/03/19 for v0.6

\tikzextpicturewidth#L
\tikzextpictureheight#L

#keyvals:\begin{tikzpicture}#c
ext/save picture size
ext/picture width=##L
ext/minimum picture width=##L
ext/maximum picture width=##L
ext/picture height=##L
ext/minimum picture height=##L
ext/maximum picture height=##L
ext/minimum picture size={%<width%>}{%<height%>}
ext/maximum picture size={%<width%>}{%<height%>}
ext/picture width*=##L
ext/minimum picture width*=##L
ext/maximum picture width*=##L
ext/picture height*=##L
ext/minimum picture height*=##L
ext/maximum picture height*=##L
ext/picture size*={%<width%>}{%<height%>}
#endkeyvals

# not documented
\tikzextspwrite{arg1}{arg2}{arg3}#S

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
