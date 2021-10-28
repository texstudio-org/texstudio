# pgfparser package
# Matthew Bertucci 10/24/2021

#include:pgfrcs
#include:pgfkeys

\pgfparserparse{parser name}#*
\pgfparserdef{parser name}{state}{symbol meaning}{action}#*
\pgfparserdef{parser name}{state}{symbol meaning}[args]{action}#*
\pgfparserlet{parser1}{state1}{meaning1}{meaning2}#*
\pgfparserlet{parser1}{state1}{meaning1}[opt1][opt2]{meaning2}#*
\pgfparserdefunknown{parser name}{state}{action}#*
\pgfparserdeffinal{parser name}{action}#*
\pgfparserswitch{state}#*
\pgfparserifmark{arg}{true}{false}#*
\pgfparserreinsert#*
\pgfparserstate#*
\pgfparsertoken#*
\pgfparserletter#*

\pgfparserset{options%keyvals}#*

#keyvals:\pgfparserset#c
silent#true,false
status#true,false
#endkeyvals