# filemod package
# Matthew Bertucci 10/31/2021 for v1.2

#include:filemod-expmin

\filemodprint{file}#*
\filemodprintdate{file}#*
\filemodprinttime{file}#*
\thefilemod#*
\thefilemoddate#*
\thefilemodtime#*
\thefilemod#*
\filemodsep#*
\Filemodtoday{file}#*
\FilemodToday{file}#*
\filemodnumdate{file}#*
\filemodnumtime{file}#*
\Filemodgetnum{file}#*
\filemodcmp{file1%file}{file2%file}{clause1}{clause2}#*
\filemodcmp[num]{file1%file}{file2%file}{clause1}{clause2}{clause3}#*
\Filemodcmp{file1%file}{file2%file}{clause1}{clause2}#*
\Filemodcmp[num]{file1%file}{file2%file}{clause1}{clause2}{clause3}#*
\FilemodCmp{file1%file}{file2%file}#*
\FilemodCmp[num]{file1%file}{file2%file}#*
\filemodoptdefault#*
\filemodnewest{file1%file}{file2%file}#*
\filemodnewest[num]{file1%file}{file2%file}#*
\filemodoldest{file1%file}{file2%file}#*
\filemodoldest[num]{file1%file}{file2%file}#*
\filemodNewest{%<{file1}{file2}...{fileN}%>}#*
\filemodNewest[%<num%>]{%<{file1}{file2}...{fileN}%>}#*
\filemodOldest{%<{file1}{file2}...{fileN}%>}#*
\filemodOldest[%<num%>]{%<{file1}{file2}...{fileN}%>}#*
\Filemodnewest{file1%file}{file2%file}#*
\Filemodnewest[num]{file1%file}{file2%file}#*
\Filemodoldest{file1%file}{file2%file}#*
\Filemodoldest[num]{file1%file}{file2%file}#*
\FilemodNewest{%<{file1}{file2}...{fileN}%>}#*
\FilemodNewest[%<num%>]{%<{file1}{file2}...{fileN}%>}#*
\FilemodOldest{%<{file1}{file2}...{fileN}%>}#*
\FilemodOldest[%<num%>]{%<{file1}{file2}...{fileN}%>}#*
\filemodparse{macro}{file}#*
\filemodnotexists{macro}#*
\filemodZ#*
\filemodz#*
