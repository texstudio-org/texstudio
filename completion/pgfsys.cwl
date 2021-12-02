# pgfsys package
# Matthew Bertucci 11/14/2021 for v3.19a

# pgfsys.sty
# ├── pgfrcs.sty (see pgfrcs.cwl for its dependencies)
# ├── pgfsys.code.tex
# │   └── pgfkeys.code.tex
# ├── pgfsyssoftpath.code.tex
# └── pgfsysprotocol.code.tex

#include:pgffrcs

#keyvals:\usepackage/pgfsys#c
dvisvgm
#endkeyvals

## from pgfsys.code.tex
\pgfset{keyvals}#*
\ifpgfpicture#*
\pgfpicturetrue#*
\pgfpicturefalse#*
\ifpgfsysanimationsupported#*
\pgfsysanimationsupportedtrue#*
\pgfsysanimationsupportedfalse#*
\pgfsysdriver#*

# from pgfkeys.code.tex (this is all pgfkeys.sty inputs)
#include:pgfkeys

## from pgfsyssoftpath.code.tex
\ifpgfsyssoftpathmovetorelevant#*
\pgfsyssoftpathmovetorelevanttrue#*
\pgfsyssoftpathmovetorelevantfalse#*

## from pgfsysprotocol.code.tex
# no user commands
