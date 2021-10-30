# standalone package
# Fran J. Sanchez 30/10/2021 for v1.3a

#include:xkeyval
#include:ifpdf
#include:ifluatex
#include:ifxetex
#include:shellesc

#ifOption:varwidth
#include:varwidth
#endif
#ifOption:preview
#include:preview
#endif
#ifOption:beamer
#include:beamer
#endif
#ifOption:tikz
#include:tikz
#endif
#ifOption:multido
#include:multido
#endif
#ifOption:pstricks
#include:pstricks
#endif

#include:currfile
#include:filehook
#include:gincltex
#include:filemod

## As document class:

#keyvals:\documentclass/standalone,\standaloneconfig
class=
crop=#true,false
preview=#true,false

## can also be multiple lengths
border=##L
## ? border=#\{#L #L\}
## ? border=#\{#L #L #L #L\}

## and multiple environments
multi=#true,false,environments...
multi

ignorerest=#true,false
multido=#true,false
multido
varwidth=##L
varwidth
tikz=#true,false
tikz
pstricks=#true,false
pstricks
beamer=#true,false
beamer
float=#true,false
convert=#true,false,{options}
convert
png=#true,false,{options}
png
#endkeyvals

\standaloneconfig{%<options%>}#*
\standaloneenv{environment}#*
\standaloneignore#*

\begin{standalone}#S

\ifstandalonebeamer#*

## not so sure about this one, has a lot of options
\begin{standaloneframe}{frame title}{frame subtitle}#*
\begin{standaloneframe}{frame title}#*
\begin{standaloneframe}#*


###############################
## As package:

## standaloneconfig has different keyvals if
## used as package or as a document class...
#keyvals:\usepackage/standalone,\standaloneconfig,\includestandalone
subpreambles=#true,false
subpreambles
sort=#true,false
sort
print=#true,false
print
comments=#true,false
nocomments
group=#true,false
mode=#tex,image,image|tex,buildmissing,buildnew
obeyclassoptions=#true,false
extension=
build=#{options}
#endkeyvals

\standaloneconfig{%<options%>}#*

## also any options  in \includegraphics
\includestandalone{file}#i

###############################
## Common:

\ifstandalone#*
\IfStandalone{code for standalone}{code for main document}#*
\onlyifstandalone{code}#*
