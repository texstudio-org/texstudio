# familytree package
# Matthew Bertucci 2022/06/29 for v3.1

#include:relsize

## Individual Box (ft-individual.dtx) ##
\indvdldef{new box name}{individual name}
\indvdldef{new box name}{individual name}[additional info]
\indvdldef{new box name}{individual name}[additional info][maleline xlength]#*
\indvdldef{new box name}[title%text]{individual name}
\indvdldef{new box name}[title%text]{individual name}[additional info]#*
\indvdldef{new box name}[title%text]{individual name}[additional info][maleline xlength]#*
\indvdldef[child mark]{new box name}{individual name}
\indvdldef[child mark]{new box name}{individual name}[additional info]#*
\indvdldef[child mark]{new box name}{individual name}[additional info][maleline xlength]#*
\indvdldef[child mark]{new box name}[title%text]{individual name}#*
\indvdldef[child mark]{new box name}[title%text]{individual name}[additional info]#*
\indvdldef[child mark]{new box name}[title%text]{individual name}[additional info][maleline xlength]
\ftindvdldef{new box name}{individual name}#S
\ftindvdldef{new box name}{individual name}[additional info]#S
\ftindvdldef{new box name}{individual name}[additional info][maleline xlength]#S
\ftindvdldef{new box name}[title%text]{individual name}#S
\ftindvdldef{new box name}[title%text]{individual name}[additional info]#S
\ftindvdldef{new box name}[title%text]{individual name}[additional info][maleline xlength]#S
\ftindvdldef[child mark]{new box name}{individual name}#S
\ftindvdldef[child mark]{new box name}{individual name}[additional info]#S
\ftindvdldef[child mark]{new box name}{individual name}[additional info][maleline xlength]#S
\ftindvdldef[child mark]{new box name}[title%text]{individual name}#S
\ftindvdldef[child mark]{new box name}[title%text]{individual name}[additional info]#S
\ftindvdldef[child mark]{new box name}[title%text]{individual name}[additional info][maleline xlength]#S

\biological
\ftbiological#*
\adopted
\ftadopted#*
\top
\fttop#*
\blank
\ftblank#*
\haschild
\fthaschild#*
\private
\ftprivate#*
\maleline
\ftmaleline#*
\femaleline
\ftfemaleline#*
\patrilineal
\ftpatrilineal#*
\matrilineal
\ftmatrilineal#*

\nameboxcfg{space from child mark}{font}{space to maleline}{maleline length}
\ftnameboxcfg{space from child mark}{font}{space to maleline}{maleline length}#*
\cmarkboxcfg{space between two lines}{line length}
\ftcmarkboxcfg{space between two lines}{line length}#*
\titleboxcfg{indent}{font}{linestretch}{vspace to individual name}
\fttitleboxcfg{indent}{font}{linestretch}{vspace to individual name}
\optboxcfg{vspace to individual name}{indent}{font}{linestretch}
\ftoptboxcfg{vspace to individual name}{indent}{font}{linestretch}#*

## Sibling Box (ft-sibling.dtx) ##
\sblngdef{new box name}{list of individual boxes}
\ftsblngdef{new box name}{list of individual boxes}#*
\ivaldef{new box name}{length}
\ftivaldef{new box name}{length}#*
\ival
\ftival#*
\ivalnameCY#S
\ivalival#S
\ivali
\ftivali#*
\ivalinameCY#S
\ivaliival#S
\ivalii
\ftivalii#*
\ivaliinameCY#S
\ivaliiival#S
\sblngboxcfg{space between siblings}
\ftsblngboxcfg{space between siblings}#*

## Parent-child Relationship Box or Generations Box (ft-gens.dtx) ##
\pcdef{new box name}{parent box name}{child box name}
\ftpcdef{new box name}{parent box name}{child box name}#*
\gensdef{new box name}{parent box name}{list of connection pairs}
\ftgensdef{new box name}{parent box name}{list of connection pairs}#*

## Marriage Box (ft-marriage.dtx) ##
\mrrgdef{new box name}{spouse list A}{oneself}{spouse list B}
\mrrgdef{new box name}{spouse list A}{oneself}{spouse list B}[childline xlength]
\ftmrrgdef{new box name}{spouse list A}{oneself}{spouse list B}#*
\ftmrrgdef{new box name}{spouse list A}{oneself}{spouse list B}[childline xlength]#*
\mrrgboxcfg{space between two lines}{space between name and line}{line length}
\ftmrrgboxcfg{space between two lines}{space between name and line}{line length}#*

## Library (ft-lib.dtx) ##
\ftymd{year}
\ftymd{year}[month]
\ftymd{year}[month][date]
\ftundef{box name}
\ifftdbg#*
\ftdbgtrue#*
\ftdbgfalse#*