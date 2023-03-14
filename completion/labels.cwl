# labels package
# Matthew Bertucci 2023/03/14 for v.13

#keyvals:\usepackage/labels#c
newdimens
#endkeyvals

#ifOption:newdimens
\BottomLabelBorder
\BottomPageMargin
\InterLabelColumn
\InterLabelRow
\LeftLabelBorder
\LeftPageMargin
\RightLabelBorder
\RightPageMargin
\TopLabelBorder
\TopPageMargin
#endif

\begin{labels}
\end{labels}

\addresslabel[font commands]{text}
\addresslabel{text}
\BottomBorder
\boxedaddresslabel[font commands]{text}
\boxedaddresslabel{text}
\genericlabel{text}
\ifLabelGrid#*
\ifLabelInfo#*
\LabelCols
\labelfile{file}
\LabelGridfalse
\LabelGridtrue
\LabelInfofalse
\LabelInfotrue
\LabelRows
\LabelSetup
\LeftBorder
\numberoflabels
\promptlabels
\RightBorder
\skiplabels{integer}
\TopBorder

# not documented
\isitapar#S
\LabelTotal#*
\LabTmp#S
\PkgBlurb{arg1}{arg2}#S
\ToMilli{arg}#S
\TypeoutBlurb{arg1}{arg2}#S