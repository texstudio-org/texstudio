# captcont package
# Matthew Bertucci 2022/05/03 for v2.0

#keyvals:\usepackage/captcont#c
figbotcap
figtopcap
tabbotcap
tabtopcap
#endkeyvals

\caption*{text}
\caption*[short text%text]{text}
\captcont*{text}
\captcont*[short text%text]{text}
\captcont{text}
\captcont[short text%text]{text}
\iffiguretopcap#S
\figuretopcaptrue#S
\figuretopcapfalse#S
\iftabletopcap#S
\tabletopcaptrue#S
\tabletopcapfalse#S