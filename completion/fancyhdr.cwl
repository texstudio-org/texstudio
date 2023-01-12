# mode: fancyhdr.sty
# dani/2006-02-18
# modified Edson 30-12-2010
# modified T. Hoffmann 15-05-2014
# modified Matthew Bertucci 2022/11/09 for v4.1

#keyvals:\usepackage/fancyhdr#c
nocheck
compatV3
twoside
myheadings
headings
#endkeyvals

\fancyfoot[places]{footer%text}
\fancyfoot{footer%text}

\fancyhead[places]{header%text}
\fancyhead{header%text}

\fancyhf[places]{output%text}
\fancyhf{output%text}

\fancyfootoffset[places]{length}
\fancyfootoffset{length}
\fancyheadoffset[places]{length}
\fancyheadoffset{length}
\fancyhfoffset[places]{length}
\fancyhfoffset{length}

\fancypagestyle{style name}[base style]{definitions%text}
\fancypagestyle{style name%specialDef}{definitions%text}#s#%fancypagestyle

#keyvals:\pagestyle#c,\thispagestyle#c
fancy
%fancypagestyle
#endkeyvals

\iftopfloat{float page%text}{other%text}
\ifbotfloat{float page%text}{other%text}
\iffloatpage{float page%text}{other%text}
\iffootnote{float page%text}{other%text}

\headrulewidth
\footrulewidth
\headruleskip
\footruleskip
\headrule
\footrule
\headwidth

\fancyheadinit{code}
\fancyfootinit{code}
\fancyhfinit{code}

\fancycenter[distance%l][stretch]{left-mark%text}{center-mark%text}{right-mark%text}
\fancycenter[distance%l]{left-mark%text}{center-mark%text}{right-mark%text}
\fancycenter{left-mark%text}{center-mark%text}{right-mark%text}

# deprecated
\chead[CH-even%text]{CH-odd%text}#*
\chead{header%text}#*
\cfoot[CF-even%text]{CF-odd%text}#*
\cfoot{footer%text}#*
\lhead[LH-even%text]{LH-odd%text}#*
\lhead{header%text}#*
\lfoot[LF-even%text]{LF-odd%text}#*
\lfoot{footer%text}#*
\rhead[RH-even%text]{RH-odd%text}#*
\rhead{header%text}#*
\rfoot[RF-even%text]{RF-odd%text}#*
\rfoot{footer%text}#*
