# qstest package
# Matthew Bertucci 10/29/2021 for v1.7896

#include:makematch
#include:verbatim

\IncludeTests{pattern list}
\TestErrors{pattern list}
\LogTests{file ext}{keywordlist1}{keywordlist2}
\LogClose{file ext}
\begin{qstest}{test name}{keywordlist}
\end{qstest}
\Expect{arg1}{arg2}
\Expect*{arg1}{arg2}
\Expect*{arg1}*{arg2}
\ExpectIfThen{condition}
\InRange{dimen1%l}{dimen2%l}
\NearTo{dimen%l}
\NearTo[opt dimen%l]{dimen%l}
\SaveValueFile{file name%file}
\CloseValueFile
\SaveValue{cmd}{arg}#d
\SaveValue{cmd}*{arg}#d
\InternalSetValue
\SavedValue
\begin{ExpectCallSequence}{call sequence}
\end{ExpectCallSequence}
\CalledName
