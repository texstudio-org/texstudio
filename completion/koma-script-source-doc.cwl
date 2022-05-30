# koma-script-source-doc class
# Matthew Bertucci 2022/05/18 for v0.91

#include:l3keys2e
#include:class-ltxdoc
#include:class-scrartcl
#include:auxhook
#include:scrlogo

#keyvals:\documentclass/koma-script-source-doc#c
indexlatex#true,false
#endkeyvals

\cls{class}
\cls[CTAN path%URL]{class}
\cls*{class}
\cls*[CTAN path%URL]{class}
\cnt{counter}
\dhook{dohook}
\env{envname}
\file{file}
\fnt{font}
\len{length%plain}
\opt{option}
\optvalue{value}
\pkg{package}
\pkg[CTAN path%URL]{package}
\pkg*{package}
\pkg*[CTAN path%URL]{package}
\plen{pseudolength}
\pstyle{pstyle}
\var{variable}

\DescribeCommand{cmd}
\DescribeCommand[options%keyvals]{cmd}
\begin{command}{cmd}
\begin{command}[options%keyvals]{element}
\end{command}
\PrintDescribeCommand{cmd}
\PrintCommandName{cmd}
\SpecialMainCommandIndex{cmd}
\SpecialCommandIndex{cmd}

\DescribeOption{option}
\DescribeOption[options%keyvals]{option}
\begin{option}{option}
\begin{option}[options%keyvals]{option}
\end{option}
\PrintDescribeOption{option}
\PrintOptionName{option}
\SpecialMainOptionIndex{option}
\SpecialOptionIndex{option}

\DescribeILength{length%plain}
\DescribeILength[options%keyvals]{length%plain}
\begin{ilength}{length%plain}
\begin{ilength}[options%keyvals]{length%plain}
\end{ilength}
\PrintDescribeILength{length%plain}
\PrintILengthName{length%plain}
\SpecialMainILengthIndex{length%plain}
\SpecialILengthIndex{length%plain}

\DescribeCounter{counter}
\DescribeCounter[options%keyvals]{counter}
\begin{counter}{counter}
\begin{counter}[options%keyvals]{counter}
\end{counter}
\PrintDescribeCounter{counter}
\PrintCounterName{counter}
\SpecialMainCounterIndex{counter}
\SpecialCounterIndex{counter}

\DescribeKOMAfont{KOMAfont}
\DescribeKOMAfont[options%keyvals]{KOMAfont}
\begin{fontelement}{KOMAfont}
\begin{fontelement}[options%keyvals]{KOMAfont}
\end{fontelement}
\PrintDescribeKOMAfont{KOMAfont}
\PrintKOMAfontName{KOMAfont}
\SpecialMainKOMAfontIndex{KOMAfont}
\SpecialKOMAfontIndex{KOMAfont}

\DescribeKOMAvar{KOMAvar}
\DescribeKOMAvar[options%keyvals]{KOMAvar}
\begin{variable}{KOMAvar}
\begin{variable}[options%keyvals]{KOMAvar}
\end{variable}
\PrintDescribeKOMAvar{KOMAvar}
\PrintKOMAvarName{KOMAvar}
\SpecialMainKOMAvarIndex{KOMAvar}
\SpecialKOMAvarIndex{KOMAvar}

\DescribePLength{pseudolength}
\DescribePLength[options%keyvals]{pseudolength}
\begin{pseudolength}{pseudolength}
\begin{pseudolength}[options%keyvals]{pseudolength}
\end{pseudolength}
\PrintDescribePLength{pseudolength}
\PrintPLengthName{pseudolength}
\SpecialMainPLengthIndex{pseudolength}
\SpecialPLengthIndex{pseudolength}

\DescribePageStyle{pagestyle}
\DescribePageStyle[options%keyvals]{pagestyle}
\begin{pgstyle}{pagestyle}
\begin{pgstyle}[options%keyvals]{pagestyle}
\end{pgstyle}
\PrintDescribePageStyle{pagestyle}
\PrintPageStyleName{pagestyle}
\SpecialMainPageStyleIndex{pagestyle}
\SpecialPageStyleIndex{pagestyle}

\DescribeDoHook{dohook}
\DescribeDoHook[options%keyvals]{dohook}
\begin{dohook}{dohook}
\begin{dohook}[options%keyvals]{dohook}
\end{dohook}
\PrintDescribeDoHook{dohook}
\PrintDoHookName{dohook}
\SpecialMainDoHookIndex{dohook}
\SpecialDoHookIndex{dohook}

#keyvals:\DescribeCommand#c,\begin{command}#c,\DescribeOption#c,\begin{option}#c,\DescribeILength#c,\begin{ilength}#c,\DescribeCounter#c,\begin{counter}#c,\DescribeKOMAfont#c,\begin{fontelement}#c,\DescribeKOMAvar#c,\begin{variable}#c,\DescribePLength#c,\begin{pseudolength}#c,\DescribePageStyle#c,\begin{pgstyle}#c,\DescribeDoHook#c,\begin{dohook}#c
noindex#true,false
noprint#true,false
#endkeyvals