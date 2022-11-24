# perspective tikzlibrary
# 2022/11/21 for v3.1.9a

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
3d view
isometric view
perspective
perspective={%<vanishing points%>}
#endkeyvals

\pgfpointperspectivexyz{x}{y}{z}#S