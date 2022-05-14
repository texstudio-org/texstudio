# opacity-pro package
# Matthew Bertucci 2022/05/13 for v1.1.1

#keyvals:\usepackage/opacity-pro#c
dvips
dvipsone
#endkeyvals

\settransparency{ca}{CA}{content%text}
\settransparency{ca}{CA}[PDF KVs]{content%text}
\settransparency[blend mode%keyvals]{ca}{CA}{content%text}
\settransparency[blend mode%keyvals]{ca}{CA}[PDF KVs]{content%text}
\settransparency*{ca}{CA}{content%text}
\settransparency*{ca}{CA}[PDF KVs]{content%text}
\settransparency*[blend mode%keyvals]{ca}{CA}{content%text}
\settransparency*[blend mode%keyvals]{ca}{CA}[PDF KVs]{content%text}

\begin{settransparency}{ca}{CA}
\begin{settransparency}{ca}{CA}[PDF KVs]
\begin{settransparency}[blend mode%keyvals]{ca}{CA}
\begin{settransparency}[blend mode%keyvals]{ca}{CA}[PDF KVs]
\end{settransparency}
\begin{settransparency*}{ca}{CA}
\begin{settransparency*}{ca}{CA}[PDF KVs]
\begin{settransparency*}[blend mode%keyvals]{ca}{CA}
\begin{settransparency*}[blend mode%keyvals]{ca}{CA}[PDF KVs]
\end{settransparency*}

#keyvals:\settransparency#c,\settransparency*#c,\begin{settransparency}#c,\begin{settransparency*}#c
Normal
Multiply
Screen
Overlay
Darken
Lighten
ColorDodge
ColorBurn
HardLight
SoftLight
Difference
Exclusion
Hue
Color
Saturation
Luminosity
#endkeyvals

# not documented
\settransparencyii{arg1}{arg2}{arg3}{arg4}{arg5}#S
\settransparencyi{arg1}{arg2}{arg3}#S