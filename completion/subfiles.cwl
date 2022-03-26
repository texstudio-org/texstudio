# author: Tim Hoffmann
# last modified: 2015-05-20
# updated Matthew Bertucci 11/13/2021 for v2.2

#include:import

#keyvals:\usepackage/subfiles#c
v1
#endkeyvals

\subfile{file}#i
\subfileinclude{file}#*i
\subfix{file}#*
\ifSubfilesClassLoaded{then}{else}#*
