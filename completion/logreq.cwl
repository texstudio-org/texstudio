# logreq package
# Matthew Bertucci 2022/05/30 for v1.0

#include:etoolbox
#include:keyval

\binary{package}#*
\cmdline{specs}#*
\DeclareLogreqAttribute{element}[default]{attribute}{dtd specs}#*
\DeclareLogreqAttribute{element}{attribute}{dtd specs}#*
\DeclareLogreqContainer{element}{dtd specs}#*
\DeclareLogreqElement{element}{dtd specs}#*
\external[keyvals]{specs}#*
\file{file}#*
\generic{package}#*
\infile{file}#*
\internal[keyvals]{specs}#*
\LogreqDTDVersion#S
\logrequest[options%keyvals]{request}#*
\logrequest{request}#*
\ltxrequest{package}{active}{request}#*
\option{option}#*
\outfile{file}#*
\provides[keyvals]{file specs}#*
\requests[keyvals]{specs}#*
\requires[keyvals]{file specs}#*

#keyvals:\external,\internal,\logrequest
package=%<package%>
priority=%<priority%>
active=#0,1
#endkeyvals

#keyvals:\provides,\requires
type=#static,dynamic,editable
#endkeyvals