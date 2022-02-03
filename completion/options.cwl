# options package
# Matthew Bertucci 2/2/2022 for v1.0

#include:etoolbox
#include:xcolor

#keyvals:\usepackage/options#c
debug
#endkeyvals

\options{options}#*
\optionsalso{options}#*
\optionswithremaining{options}#*
\option{option}#*
\letoption{option}{macro%cmd}#*d
\edefoption{option}{macro%cmd}#*d
\ifoptiondefined{option}{true}{false}#*
\ifoptionvoid{option}{true}{false}#*
\ifoptionblank{option}{true}{false}#*
\ifoptionequal{option}{value}{true}{false}#*
\ifoptionanyof{option}{list}{true}{false}#*
\ifoptiontype{option}{type}{true}{false}#*
\ifoptionnil{list option}{true}{false}#*
\ifoptioniscode{option}{true}{false}#*
\optionlistdo{list option}{action}#*
\letoptionlist{list option}{macro%cmd}#*d
\ifoptioncontains{list option}{true}{false}#*
\optionshow{option}#*
\optionshowall#*
\optionshowall[bool]#*
\optionshowpath{option}#*
\optionerror{option}{message%text}#*
\optionwarning{option}{message%text}#*
\letoptiontype{option}{type}#*
\optionname{option}#*
\optionprependcode{option}{code}#*
\optionnewcode{option}{code}#*
\optionnewcode*{option}{code}#*
\optionnewhandler{option}{code}#*
\optionnewhandler*{option}{code}#*
\optionvalue#*
\optionnovalue#*

# not documented
\eifblank{string}{true}{false}#*
\eifstrequal{string}{true}{false}#*
\expandnextcmds{arg1}{arg2}#*
\expandnextsingle{arg1}{arg2}#*
\expandnext{arg1}{arg2}#*
\ifoptioncmd{option}{true}{false}#*
\ifoptioncolortransparent{color}{true}{false}#*
\ifoptionisabsolute{option}{true}{false}#*
\letoptionchoices{option}{macro%cmd}#*d
\ontoggle{toggle name}{true}#*
\optioncolorbox{color}{code}#*
\optioncolor{color}#*
\optionlist{list option}#*
\optionparamcount{option}#*
\optionshowtype{option}#*
\optiontextcolor{color}{code}#*
\optiontypeout{option}#*
\optionunit{option}#*