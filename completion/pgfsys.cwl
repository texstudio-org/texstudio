# pgfsys package
# Matthew Bertucci 10/24/2021

#include:pgfrcs
#include:pgfkeys

\pgfsysdriver#*
\ifpgfpicture#*
\pgfpicturetrue#*
\pgfpicturefalse#*
\ifpgfsyssoftpathmovetorelevant#*
\pgfsyssoftpathmovetorelevanttrue#*
\pgfsyssoftpathmovetorelevantfalse#*
\ifpgfsysanimationsupported#*
\pgfsysanimationsupportedtrue#*
\pgfsysanimationsupportedfalse#*