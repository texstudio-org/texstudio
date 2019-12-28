# fancyref package
# Michael S. 2010/11/20
#            see https://github.com/LaTeXing/LaTeX-cwl/blob/master/fancyref.cwl
# muzimuzhi/28 Dec 2019 for fancyref 1999/02/03 v0.9c

\fref{label}#r
\Fref{label}#r
\fref[format%keyvals]{label}#r
\Fref[format%keyvals]{label}#r
\fancyrefchangeprefix{prefix macro}{preﬁx}
\fancyrefaddcaptions{language}{string defs}
\frefformat{format%keyvals}{preﬁx macro}{output}
\Frefformat{format%keyvals}{preﬁx macro}{output}
\fancyrefhook{output of format}#*

#keyvals:\fref,\Fref,\frefformat,\Frefformat
vario
plain
margin
main
#endkeyvals

# macros that store strings and have no arguments
\fancyrefchaplabelprefix#*
\fancyrefseclabelprefix#*
\fancyrefeqlabelprefix#*
\fancyreffiglabelprefix#*
\fancyreftablabelprefix#*
\fancyrefenumlabelprefix#*
\fancyreffnlabelprefix#*
\fancyrefargdelim#*
\fancyrefloosespacing#*
\fancyreftightspacing#*
\fancyrefdefaultspacing#*
\Frefchapname#*
\Frefenumname#*
\Frefeqname#*
\Freffigname#*
\Freffnname#*
\Frefonname#*
\Frefpgname#*
\Frefsecname#*
\Frefseename#*
\Freftabname#*
\frefchapname#*
\frefenumname#*
\frefeqname#*
\freffigname#*
\freffnname#*
\frefonname#*
\frefpgname#*
\frefsecname#*
\frefseename#*
\freftabname#*
\Freffigshortname#*
\Frefpgshortname#*
\Freftabshortname#*
\freffigshortname#*
\frefpgshortname#*
\freftabshortname#*
\fancyrefdefaultformat#*
