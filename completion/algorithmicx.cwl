# algorithmicx package
# updated Matthew Bertucci 10/12/2021 for v1.2

#include:ifthen

\begin{algorithmic}#\algorithm
\begin{algorithmic}[lines]#\algorithm
\end{algorithmic}

\State#/algorithmic
\Statex#/algorithmic
\BState#/algorithmic

\Comment{text}#/algorithmic

\algref{algorithm%ref}{line%ref}#r

\algstore{savename}#/algorithmic
\algstore*{savename}#/algorithmic
\algrestore{savename}#/algorithmic
\algrestore*{savename}#/algorithmic

\alglanguage{layoutname}

\algnewcommand{cmd}[args][default]{def}#*d
\algnewcommand{cmd}[args]{def}#*d
\algnewcommand{cmd}{def}#*d
\algrenewcommand{cmd}[args][default]{def}#*
\algrenewcommand{cmd}[args]{def}#*
\algrenewcommand{cmd}{def}#*
\algrenewcommand[block]{cmd}[args][default]{def}#*

\algorithmiccomment{text}#*
\algorithmicindent#*
\alglinenumber{num}#*
\algsetlanguage{layoutname}#*
\algdeflanguage{layoutname}#*
\algnewlanguage{layoutname}#*
\algrenewcomment{definition}#*
\algbreak#*

\algblock[block]{start}{end}#*
\algblockdefx[block]{start}{end}[start args]{start text}[end args]{end text}#*
\algblockdefx[block]{start}{end}[start args][default]{start text}[end args][default]{end text}#*
\algdefx[block]{start}{end}[start args]{start text}[end args]{end text}#*
\algdefx[block]{start}{end}[start args][default]{start text}[end args][default]{end text}#*

\algloop[loop]{start}#*
\algloopdefx[loop]{start}[start args][default]{start text}#*

\algcblock[new block]{old block}{continue}{end}#*
\algcblockdefx[new block]{old block}{continue}{end}[continue args]{continue text}[end args]{end text}#*
\algcblockdefx[new block]{old block}{continue}{end}[continue args][default]{continue text}[end args][default]{end text}#*
\algcblockx[new block]{old block}{continue}{end}[continue args][default]{continue text}[end args][default]{end text}#*
\algcblockx[new block]{old block}{continue}{end}[continue args]{continue text}[end args]{end text}#*

\algcloop[new loop]{old loop}{continue}#*
\algcloopdefx[new loop]{old loop}{continue}[continue args]{continue text}#*
\algcloopdefx[new loop]{old loop}{continue}[continue args][default]{continue text}#*
\algcloopx[new loop]{old loop}{continue}[continue args]{continue text}#*
\algcloopx[new loop]{old loop}{continue}[continue args][default]{continue text}#*

\algsetblock[block]{start}{end}{lifetime}{indent}#*
\algsetblockdefx[block]{start}{end}{lifetime}{indent}[start args][default]{start text}[end args][default]{end text}#*
\algsetblockdefx[block]{start}{end}{lifetime}{indent}[start args]{start text}[end args]{end text}#*
\algsetblockx[block]{start}{end}{lifetime}{indent}[start args]{start text}[end args]{end text}#*
\algsetblockx[block]{start}{end}{lifetime}{indent}[start args][default]{start text}[end args][default]{end text}#*

\algsetcblock[new block]{old block}{continue}{end}{lifetime}{indent}#*
\algsetcblockdefx[new block]{old block}{continue}{end}{lifetime}{indent}[continue args]{continue text}[end args]{end text}#*
\algsetcblockdefx[new block]{old block}{continue}{end}{lifetime}{indent}[continue args][default]{continue text}[end args][default]{end text}#*
\algsetcblockx[new block]{old block}{continue}{end}{lifetime}{indent}[continue args]{continue text}[end args]{end text}#*
\algsetcblockx[new block]{old block}{continue}{end}{lifetime}{indent}[continue args][default]{continue text}[end args][default]{end text}#*

\algnotext{ending command}#*
\algnotext[block]{ending command}#*
\algdefaulttext{command}#*
\algdefaulttext[block]{command}#*
\algrenewtext{name}{definition}#*
\algrenewtext{name}[args]{definition}#*
\algtext{name}{definition}#*
\algtext{name}[args]{definition}#*
