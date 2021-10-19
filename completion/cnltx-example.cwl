# cnltx-example package
# Matthew Bertucci 10/18/2021 for v0.15

#include:cnltx-listings
#include:cnltx-translations
#include:mdframed
#include:idxcmds
#include:textcomp
#include:adjustbox
#include:ifxetex
#include:ulem

\code{arg}
\verbcode|%<text%>|
\verbcode{verbatimSymbol}#S
\cs{name}
\cs*{name}
\csidx{name}
\env{name}
\env*{name}
\envidx{name}
\beginend{text}#*
\beginenv
\beginenv*
\endenv
\endenv*
\meta{meta}
\marg{arg}
\Marg{arg}
\oarg{arg}
\Oarg{arg}
\darg{arg}
\Darg{arg}
\sarg

\newarg{cmd}{left delim}{right delim}#d
\newarg[formatting]{cmd}{left delim}{right delim}#d

\option{name}
\option*{name}
\optionidx{name}
\module{name}
\module*{name}
\moduleidx{name}
\key{name}{value}
\key*{name}{value}
\key-{name}{value}
\keyis{name}{value}
\keyis*{name}{value}
\keyis-{name}{value}
\choices{list of choices}
\choicekey{name}{list of choices}
\boolkey{name}
\default{value}

\pkg{package}
\pkg*{package}
\pkgidx{package}
\cls{class}
\cls*{class}
\clsidx{class}

\inputexample{file}
\inputexample[options%keyvals]{file}
\inputsidebyside{file}
\inputsidebyside[options%keyvals]{file}
\inputsourcecode{file}
\inputsourcecode[options%keyvals]{file}
\implementation{file}
\implementation[options%keyvals]{file}

\newinputsourcefilecmd{cmd}
\newinputsourcefilecmd[options%keyvals]{cmd}

\begin{example}
\begin{example}[options%keyvals]
\end{example}
\begin{sidebyside}
\begin{sidebyside}[options%keyvals]
\end{sidebyside}
\begin{sourcecode}#V
\begin{sourcecode}[options%keyvals]#V
\end{sourcecode}
\begin{bash}#V
\begin{bash}[options%keyvals]#V
\end{bash}

\newsourcecodeenv{envname}#N
\newsourcecodeenv[options%keyvals]{envname}#N

#keyvals:\setcnltx,\inputexample,\inputsidebyside,\inputsourcecode,\implementation,\newinputsourcefilecmd,\begin{example},\begin{sidebyside},\begin{sourcecode},\newsourcecodeenv
side-by-side#true,false
code-only#true,false
code-left#true,false
compile#true,false
code-sep={%<definitions%>}
pre-code={%<definitions%>}
after-code={%<definitions%>}
pre-output={%<definitions%>}
after-output={%<definitions%>}
add-frame-options={%<mdframed options%>}
frame-options={%<mdframed options%>}
add-local-frame={%<mdframed options%>}
local-frame={%<mdframed options%>}
gobble=%<integer%>
add-cmds={%<list of csnames%>}
add-silent-cmds={%<list of csnames%>}
add-listings-options={%<listings options%>}
add-sourcecode-options={%<listings options%>}
sourcecode-options={%<listings options%>}
add-envs={%<list of envnames%>}
add-silent-envs={%<list of envnames%>}
max-pages=%<number%>
max-height=##L
pages={%<specs%>}
runs=%<number%>
program=#pdflatex,lualatex,xelatex,arara
file-ext=%<extension%>
exe-with={%<options%>}
graphics={%<options%>}
float#true,false
float-env=%<envname%>
caption={%<text%>}
float-pos={%<float parameters%>}
outside#true,false
add-frame#true,false
before-skip=##L
after-skip=##L
#endkeyvals

\codefont#*
\sourceformat#*
\exampleformat#*
\versionnoteformat#*
\packageformat#*
\classformat#*
\argumentformat#*

#keyvals:\setcnltx
title-format={%<definitions%>}
abstract-width=##L
abstract-format={%<definitions%>}
caption-font={%<definitions%>}
caption-label-font={%<definitions%>}
code-font={%<definitions%>}
source-format={%<definitions%>}
expl-format={%<definitions%>}
module-sep={%<definitions%>}
version-note-format={%<definitions%>}
pkg-format={%<definitions%>}
cls-format={%<definitions%>}
arg-format={%<definitions%>}
deafult-format={%<definitions%>}
#endkeyvals

\indexcs{name}#*
\indexenv{name}#*
\MakePercentComment#*