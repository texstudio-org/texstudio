# exam-zh-symbols package
# Matthew Bertucci 2023/06/02 for v0.1.25

#include:tikz

#keyvals:\examsetup,\ExamPrintAnswerSet
symbols={%<键值列表%>}
symbols/paralleleq-type=#slant,perpendicular
symbols/change-frac-style#true,false
symbols/change-dfrac-style#true,false
symbols/frac-add=%<muskip%>
symbols/dfrac-add=%<muskip%>
# not in documentation
symbols/parallel-angle=%<degrees%>
symbols/parallel-twoline-distance=##L
symbols/parallel-length=##L
symbols/parallel-baseline=##L
symbols/nparallel-slant-angle=%<degrees%>
symbols/nparallel-slant-length=##L
symbols/parallel-type=#slant,perpendicular
symbols/nparallel-type=#slant,perpendicular
symbols/paralleleq-slant-angle=%<degrees%>
symbols/paralleleq-upper-line-length=##L
symbols/paralleleq-lower-line-length=##L
symbols/paralleleq-upper-twoline-distance=##L
symbols/paralleleq-lower-twoline-distance=##L
symbols/paralleleq-lower-xshift=##L
symbols/subset-radius=##L
symbols/subset-upper-linewidth=##L
symbols/subset-lower-linewidth=##L
symbols/subset-upper-lower-distance=##L
symbols/subsetneqq-lower-twoline-distance=##L
symbols/subsetneqq-lower-slant-length=##L
symbols/supsetneqq-lower-slant-length=##L
symbols/subsetneqq-lower-slant-angle=%<degrees%>
symbols/supsetneqq-lower-slant-angle=%<degrees%>
symbols/nsubset-n-slant-angle=%<degrees%>
symbols/nsubseteq-n-slant-angle=%<degrees%>
symbols/nsubsetneqq-n-slant-angle=%<degrees%>
symbols/nsubset-n-slant-length=##L
symbols/nsubseteq-n-slant-length=##L
symbols/nsubsetneqq-n-slant-length=##L
#endkeyvals

\eu#m
\upe#m
\iu#m
\upi#m
\uppi#m

\paralleleq#m
\subset*#m
\nsubset*#m
\subseteq*#m
\nsubseteq*#m
\subsetneqq*#m
\nsubsetneqq#m
\supset*#m
\nsupset*#m
\supseteq*#m
\nsupseteq*#m
\supsetneqq*#m
\nsupsetneqq#m
\cap*#m
\cup*#m
\sim*#m
\cong*#m

\examzhfrac{numerator}{denominator}#*m
\examzhdfrac{numerator}{denominator}#*m
