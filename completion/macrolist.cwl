# macrolist package
# Matthew Bertucci 7/22/2021

\newlist{listname}
\listelement{listname}{position}
\listadd{listname}[position]{element}
\listremove{listname}{position}
\listremovelast{listname}
\listclear{listname}
\listsize{listname}
\listforeach{listname}{cmd}[begin][end]{action}#d
\listjoin{listname}{joiner}