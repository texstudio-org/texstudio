# cooltooltips package
# Matthew Bertucci 11/10/2021 for v1.1

#include:iftex

\cooltooltip{subject%text}{message%text}{URL}{tooltip}{text}#U
\cooltooltip[popup color]{subject%text}{message%text}{URL}{tooltip}{text}#U
\cooltooltip[popup color][link color]{subject%text}{message%text}{URL}{tooltip}{text}#U

\cooltooltiptoggle{text}

\ifcoolpdf#*
\coolpdftrue#*
\coolpdffalse#*