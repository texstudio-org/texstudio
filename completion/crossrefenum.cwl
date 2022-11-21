# crossrefenum package
# Matthew Bertucci 2022/11/14 for v1.0

#include:zref
# loads abspage option of zref
#include:zref-abspage

\crossrefenum{enumeration}
\crossrefenum[type%keyvals]{enumeration}
\crossrefenum[type%keyvals][print prefix?]{enumeration}

#keyvals:\crossrefenum#c
page
note
pagenote
edpage
edline
edpageline
#endkeyvals

\crfnmPage#*
\crfnmPages#*
\crfnmNote#*
\crfnmNotes#*
\crfnmLine#*
\crfnmLines#*
\crfnmEdpage#*
\crfnmEdpages#*
\crfnmEdline#*
\crfnmEdlines#*
\crfnmDefaultEnumDelim#*
\crfnmDefaultBeforeLastInEnum#*
\crfnmDefaultRangeSep#*

\crfnmDefaultCollapsable#*
\crfnmNoteCollapsable#*

\crfnmDefaultSubtypesSep#*
\crfnmDefaultPrintFirstPrefix#*
\crfnmDefaultFormatInSecond{arg}#*
\crfnmEdlineFormatInSecond{arg}#*
\crfnmEdlinePrintPrefixInSecond#*
\crfnmDefaultEnumDelimInSecond#*
\crfnmDefaultBeforeLastInEnumInSecond#*
\crfnmDefaultGroupSubtypes#*
\crfnmDefaultNumberingContinuousAcrossDocument#*
\crfnmDefaultOrder#*

# not documented
\crfnmAuthor#S
\crfnmDate#S
\crfnmDefaultBeforeLastInSecond#S
\crfnmDefaultPrintPrefixInSecond#S
\crfnmName#S
\crfnmOriginalCatcodeAt#S
\crfnmShortDesc#S
\crfnmSubscript#S
\crfnmSuperscript#S
\crfnmVersion#S