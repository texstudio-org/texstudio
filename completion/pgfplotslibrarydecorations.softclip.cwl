# decorations.softclip pgfplotslibrary
# 2022/12/11 for v1.18.1

#include:tikzlibraryintersections
# loads fillbetween pgflibrary

\pgfpathcomputesoftclippath{input path}{clip path}#*
\tikzifisnamedpath{path}{true}{false}#S

# from fillbetween pgflibrary
\pgfcomputeintersectionsegments{1 or 2}#*
\pgfgetintersectionsegmentpath{1 or 2}{index}#*
\pgfcomputereversepath{macro}#*
\pgfaddpath{macro}#*
\pgfsetpathandBB{macro}#*
\pgfaddpathandBB{macro}#*
\pgfpathreplacefirstmoveto{macro}#*
\pgfintersectionsegments#*
\pgfpointlastofsetpath#S