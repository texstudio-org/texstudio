# grayhints package
# Matthew Bertucci 2022/05/10 for v1.2

#include:eforms

#keyvals:\usepackage/grayhints#c
usehyforms
nocalcs
nodljs
# options passed to insdljs
dvipsone
dvips
textures
pdftex
luatex
dvipdfm
dvipdfmx
xetex
nodljs
debug
execJS
nopro
reqjs
!reqjs
#endkeyvals

\BlurToBlack
\CalcToGray
\CommitSuccessEvent{actions}
\DateFmt(JS specs%definition);
\DateFmtEx(JS specs%definition);
\DateKey(JS specs%definition);
\DateKeyEx(JS specs%definition);
\EnterCommitFailEvent{actions}
\FmtToGray{text}
\FocusToBlack
\KeyToGray
\matchGray
\MergeChange(JS specs%definition);
\normalGrayColors{normalcolor}{graycolor}
\NumFmt(JS specs%definition);
\NumKey(JS specs%definition);
\PercentFmt(JS specs%definition);
\PercentKey(JS specs%definition);
\RangeValidate(JS specs%definition);
\SimpleCalc(JS specs%definition);
\SpecialFmt(JS specs%definition);
\SpecialKey(JS specs%definition);
\SpecialKeyEx(JS specs%definition);
\TimeFmtEx(JS specs%definition);
\TimeKey(JS specs%definition);

# not documented
\EnterCommitFailDef#*
\FailStringDef#*
\FormsRequirement#S
\nocalcs#S
\nodljsend#S