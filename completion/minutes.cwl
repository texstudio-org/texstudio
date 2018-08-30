\minutesstyle{keyvals}
#keyvals:\minutesstyle
vote=#text
header=#text
#endkeyvals
\begin{Minutes}{title}
\foreignMinutes
\end{Minutes}
\subtitle{text}
\moderation{name%text}
\minutetaker{name%text}
\participant{name, name%text}
\guest{name, name%text}
\minutesdate{date}
\starttime{time}
\endtime{time}
\location{location%text}
\cc{name, name%text}
\missing[no excuse name%text]{excused name, excused name%text}
\missingExcused{name, name%text}
\missingNoExcuse{name, name%text}
\topic[short title]{title}#L2
\addtopic[short title]{title}#L2
\subtopic[short title]{title}#L3
\subsubtopic[short title]{title}#L4
\minitopic{title}#L1
\newcols[title][1]
\task[done]{*who}[when]{what}
\listoftasks[file]
\schedule[cal]{when}[time]{what}[long]
\begin{Vote}
\vote{text}{yes}{no}{-}[text]
\end{Vote}
\decisionTheme{ref%labeldef}{title}
\decision{ref%ref}{text}[longText%text]
\listofdecisions
\begin{Argumentation}
\pro
\Pro
\contra
\Contra
\result
\end{Argumentation}
\begin{Opinions}
\end{Opinions}
\opinion{who}{what%text}
\begin{Secret}
\end{Secret}
\secret{text}
\attachment[ref%refkey]{Title}{pages}
\listofattachments
\postscript{text}
\inputminutes{file}#i
