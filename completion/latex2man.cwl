# latex2man package
# Matthew Bertucci 2/4/2022 for v1.29

#include:ifthen
#include:fancyhdr

#keyvals:\usepackage/latex2man#c
fancy
fancyhdr
nofancy
#endkeyvals

\begin{Name}{chapter}{name}{author}{info}{title%text}
\end{Name}
\begin{Table}{columns}#\tabular
\begin{Table}[width]{columns}#\tabular
\end{Table}
\COLUMNS#*
\EMPTY#*
\LASTCOL#*
\OPTARG#*
\begin{Description}\item
\begin{Description}[label]\item
\end{Description}

\Opt{option}
\Arg{argument}
\OptArg{option}{argument}
\OptoArg{option}{argument}
\oOpt{option}
\oArg{option}
\oOptArg{option}{argument}
\oOptoArg{option}{argument}
\File{file%file}
\Prog{program}
\Cmd{command%plain}{chapter}
\Bar
\Bs
\Tilde
\Dots
\Bullet
\setVersion{version}
\setVersionWord{word%text}
\Version
\setDate
\Date
\Email{email%URL}#U
\URL{URL}#U
\LatexManEnd
\Lbr
\Rbr
\LBr
\RBr
\Dollar
\Circum
\Percent
\TEXbr
\TEXIbr
\MANbr
\HTMLbr
\SP
