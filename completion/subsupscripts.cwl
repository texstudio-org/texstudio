# subsupscripts package
# Matthew Bertucci 12/13/2021 for v1.0

\fourscripts{arg}{lsup}{lsub}{rsup}{rsub}#m
\lrsubscripts{arg}{lsub}{rsub}#m
\lrsuperscripts{arg}{lsup}{rsup}#m
\twolscripts{arg}{lsup}{lsub}#m
\twolscripts[skip%l]{arg}{lsup}{lsub}#m
\tworscripts{arg}{rsup}{rsub}#m
\tworscripts[skip%l]{arg}{rsup}{rsub}#m
\lsubscript{arg}{lsub}#m
\lsubscript[skip%l]{arg}{lsub}#m
\lsuperscript{arg}{lsup}#m
\lsuperscript[skip%l]{arg}{lsup}#m
\rsubscript{arg}{rsub}#m
\rsubscript[skip%l]{arg}{rsub}#m
\rsuperscript{arg}{rsup}#m
\rsuperscript[skip%l]{arg}{rsup}#m

\largerSkips
\setDblLSkip{skip%l}
\setDblRSkip{skip%l}
\setSingleLSkip{skip%l}
\setSingleRSkip{skip%l}

\fourscriptsC{arg}{lsup}{lsub}{rsup}{rsub}{lskip%l}{rskip%l}#*m
\lrsubscriptsC{arg}{lsub}{rsub}{lskip%l}{rskip%l}#*m
\lrsuperscriptsC{arg}{lsup}{rsup}{lskip%l}{rskip%l}#*m

\dblleftscriptskip#*
\dblrightscriptskip#*
\singleleftscriptskip#*
\singlerightscriptskip#*