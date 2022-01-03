# turabian-formatting package
# Matthew Bertucci 12/30/2021

#include:etoolbox
#include:setspace
#include:nowidow
#include:footmisc

# from marginal option of footmisc
\footnotemargin

#ifOption:endnotes
#include:endnotes
#endif

#keyvals:\usepackage/turabian-formatting#c
noraggedright
authordate
noadjustbib
endnotes
#endkeyvals

\listillustrationname#*
\listofillustrations