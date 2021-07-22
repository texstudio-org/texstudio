# xkeyval package
# Matthew Bertucci 7/22/2021

\XKV@documentclass
\XKV@classoptionslist

\define@key{family}{key%plain}[default]{function}#d

\define@cmdkey[prefix]{family}[macro prefix]{key%plain}[default]{function}#d
\define@cmdkeys[prefix]{family}[macro prefix]{keys%plain}[default]#d

\define@choicekey[prefix]{family}{key%plain}[bin]{keylist}[default]{function}#d
\define@choicekey*[prefix]{family}{key%plain}[bin]{keylist}[default]{function}#d

\define@choicekey+[prefix]{family}{key%plain}[bin]{keylist}[default]{function1}{function2}#d
\define@choicekey*+[prefix]{family}{key%plain}[bin]{keylist}[default]{function1}{function2}#d

\XKV@cc[bin]{input}{keylist}{function}
\XKV@cc*[bin]{input}{keylist}{function}
\XKV@cc+[bin]{input}{keylist}{function1}{function2}
\XKV@cc*+[bin]{input}{keylist}{function1}{function2}

\define@boolkey[prefix]{family}[macro prefix]{key%plain}[default]{macro}#d
\define@boolkey+[prefix]{family}[macro prefix]{key%plain}[default]{function1}{function2}#d
\define@boolkeys[prefix]{family}[macro prefix]{keylist}[default]#d

\key@ifundefined[prefix]{families}{key%plain}{undefined}{defined}

\disable@keys[prefix]{family}{keylist}

\setkeys[prefix]{families}[ignored keys]{keylist}
\setkeys*[prefix]{families}[ignored keys]{keylist}
\setrmkeys[prefix]{families}[ignored keys]
\setrmkeys*[prefix]{families}[ignored keys]
\setkeys+[prefix]{families}[ignored keys]{keylist}
\setkeys*+[prefix]{families}[ignored keys]{keylist}
\setrmkeys+[prefix]{families}[ignored keys]
\setrmkeys*+[prefix]{families}[ignored keys]

\XKV@prefix
\XKV@fams
\XKV@tfam
\XKV@header
\XKV@tkey
\XKV@na

\savevalue
\gsavevalue

\savekeys[prefix]{family}{keylist}
\gsavekeys[prefix]{family}{keylist}
\delsavekeys[prefix]{family}{keylist}
\gdelsavekeys[prefix]{family}{keylist}
\unsavekeys[prefix]{family}
\gunsavekeys[prefix]{family}

\global
\usevalue

\presetkeys[prefix]{family}{head keys}{tail keys}
\gpresetkeys[prefix]{family}{head keys}{tail keys}
\delpresetkeys[prefix]{family}{head keys}{tail keys}
\gdelpresetkeys[prefix]{family}{head keys}{tail keys}
\unpresetkeys[prefix]{family}
\gunpresetkeys[prefix]{family}

\DeclareOptionX[prefix]<family>{key%plain}[default]{function}
\DeclareOptionX*{function}
\ExecuteOptionsX[prefix]<families>[ignored keys]{keylist}
\ProcessOptionsX[prefix]<families>[ignored keys]
\ProcessOptionsX*[prefix]<families>[ignored keys]

\pre@fam@key#*
\cmd@fam@key#*
\ifpre@fam@key#*
\pre@fam@keytrue#*
\pre@fam@keyfalse#*
\pre@fam@key@default#*
\XKV@pre@fam@key@value#*
\XKV@pre@fam@save#*
\XKV@pre@fam@preseth#*
\XKV@pre@fam@presett#*