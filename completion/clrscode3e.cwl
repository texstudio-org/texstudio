# clrscode3e package
# Matthew Bertucci 2922/07/16

#include:graphics

## Typesetting names
\id{identifier%formula}
\proc{procedure}
\const{constant}
\func{function%formula}

## Typesetting object attributes
\attrib{object%formula}{attribute%formula}
\attribxi{object%formula}{attribute%formula}
\attribxx{object%formula}{attribute%formula}
\attribii{object%formula}{attribute%formula}
\attribix{object%formula}{attribute%formula}
\attribb{object%formula}{attribute1%formula}{attribute2%formula}
\attribbb{object%formula}{attribute1%formula}{attribute2%formula}{attribute3%formula}
\attribbbb{object%formula}{attribute1%formula}{attribute2%formula}{attribute3%formula}{attribute4%formula}
\attribbxxi{object%formula}{attribute1%formula}{attribute2%formula}
\attribe{vertex1%formula}{vertex2%formula}{attribute%formula}
\attribex{vertex1%formula}{vertex2%formula}{attribute%formula}

## Miscellaneous commands
\twodots#m
\gets#m
\isequal#m

## The codebox environment
\begin{codebox}#\tabbing
\end{codebox}
\Procname{procedure}
\li
\zi
\kw{keyword}
\For
\To
\Downto
\By
\While
\If
\Return
\Goto
\Error
\Spawn
\Sync
\Parfor
\Comment
\CommentSymbol
\Do
\End
\Repeat
\Until
\If
\Then
\Else
\ElseIf
\ElseNoIf
\Indentmore
\RComment
\setlinenumber{label}#r
\setlinenumberplus{label}{integer}#r
\Startalign{content}
\Stopalign

## not documented
\codeboxwidth#*
\codeindent#*
\digitwidth#*
\EndTest#*
\FakeIndent#*
\firstcodelinefalse#*
\firstcodelinetrue#*
\iffirstcodeline#*
\ifnumberedline#*
\ifprocname#*
\Indent#*
\liprint#*
\lispace{length}#*
\numberedlinefalse#*
\numberedlinetrue#*
\numref{label}#*r
\procnamefalse#*
\procnametrue#*
\putfakeindents#*
\putindents#*
\savecode#*
\saveprocname#*
\thecodelinenumber#*
\theindent#*
\thethisindent#*
\useregularv#*
\zeroli#*