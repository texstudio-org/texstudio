# underoverlap package
# Matthew Bertucci 10/6/2021 for v0.0.1-r1

#include:etoolbox
#include:mathtools

\UOLoverbrace{arg}#m
\UOLoverbrace{arg}[overlap arg]#m
\UOLunderbrace{arg}#m
\UOLunderbrace{arg}[overlap arg]#m
\UOLoverline{arg}#m
\UOLoverline{arg}[overlap arg]#m
\UOLunderline{arg}#m
\UOLunderline{arg}[overlap arg]#m
\newUOLdecorator{cmd}{definition}#d
\UOLaugment{cmd}
\UOLunaugment{cmd}#*