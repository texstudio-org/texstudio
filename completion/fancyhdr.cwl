# mode: fancyhdr.sty
# dani/2006-02-18
# modified Edson 30-12-2010
# modified T. Hoffmann 15-05-2014
#modified Matthew Bertucci 7/25/2021

\chead[CH-even]{CH-odd}
\chead{header}
\cfoot[CF-even]{CF-odd}
\cfoot{footer}

\lhead[LH-even]{LH-odd}
\lhead{header}
\lfoot[LF-even]{LF-odd}
\lfoot{footer}

\rhead[RH-even]{RH-odd}
\rhead{header}
\rfoot[RF-even]{RF-odd}
\rfoot{footer}

\fancyfoot[places]{footer}
\fancyfoot{footer}

\fancyhead[places]{header}
\fancyhead{header}

\fancyhf[places]{output}
\fancyhf{header}

\fancyfootoffset[places]{length}
\fancyheadoffset[places]{length}
\fancyhfoffset[places]{length}

\fancypagestyle{name}[base style]{definitions}

\iftopfloat{float page}{other}
\ifbotfloat{float page}{other}
\iffloatpage{float page}{other}
\iffootnote{float page}{other}

\headrulewidth
\footrulewidth
\headruleskip
\footruleskip
\headwidth
\thepage
\headrule
\footrule

\fancyheadinit{code}
\fancyfootinit{code}
\fancyhfinit{code}

\fancycenter[distance][stretch]{left-mark}{center-mark}{right-mark}
