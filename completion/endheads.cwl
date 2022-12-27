# endheads package
# Matthew Bertucci 2022/12/26 for v1.6

\setupendnoteheaders
\notesbychapter
\setstyleforchapternotebegin{code}
\setstyleforchapternoteend{code}
\resetendnotes
\changenotesname{text}
\changenotesheader{text}
\changenotescontentsname{text}
\notesincontents
\changesinglepageabbrev{new abbrev}
\changemultiplepageabbrev{new abbrev}
\changechapternotesline{text}

# not documented
\appendtomacro{arg1}{arg2}#S
\chapternoteslinename#S
\checknoteheaders#S
\endnoteheadersonfalse#S
\endnoteheadersontrue#S
\endnotesname#S
\ifendnoteheaderson#S
\ifnotesbychapteron#S
\ifnotesincontentson#S
\ifrefundefined{arg}#S
\iftitleinnotes#S
\literalendnote{arg}#S
\multiplepageabbrev#S
\mymarks#S
\notesbychapteronfalse#S
\notesbychapterontrue#S
\notescontentsname#S
\notesheadername#S
\notesincontentsonfalse#S
\notesincontentsontrue#S
\notesname#*
\oldtheendnotes#S
\setcounterfrompageref{counter}{label}#*
\setcounterfromref{counter}{label}#*
\singlepageabbrev#S
\strip{arg}#S
\styleforchapternotebegin#S
\styleforchapternoteend#S
\theallendnotes#S
\thenotepageholder#S
\titleinnotesfalse#S
\titleinnotestrue#S