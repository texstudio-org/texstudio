# titles package
# Matthew Bertucci 2022/06/20 for v1.2

#include:moredefs
#include:slemph

#keyvals:\usepackage/titles#c
british
american
#endkeyvals

\word{word%text}
\phrase{phrase%text}
\foreign{foreign text}
\foreignword{foreign word}
\term{technical term}
\defn{definition%text}
\book{book title%text}
\journal{journal title%text}
\music{music title%text}
\article{article title%text}
\storytitle{story title%text}
\poemtitle{poem title%text}
\play{play title%text}
\craft{craft title%text}
\species{species}

\Wrapquotes{text}#*
\WrapquotesNS{text}#*
\WrapquotesIS{text}#*
\WrapquotesNN{text}#*
\WrapquotesIN{text}#*
\WrapquotesSN{text}#*
\WrapquotesDN{text}#*
\WrapquotesSK{text}#*
\IfQuestionOrExclamation{text}{true}{false}#*

# from titles.cfg
\longpoem{poem title%text}#*
\film{film title%text}#*
\essaytitle{essay title%text}#*
\chaptertitle{chapter title%text}#*