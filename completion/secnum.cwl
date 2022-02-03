# secnum package
# Matthew Bertucci 2/1/2022

#include:expl3
#include:xparse
#include:l3keys2e

#keyvals:\usepackage/secnum#c
tocdep=%<integer%>
breaking=%<token%>
#endkeyvals

\setsecnum{num format}