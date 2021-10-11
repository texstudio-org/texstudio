# kvoptions package
# Matthew Bertucci 10/5/2021 for v3.14

#include:keyval
#include:ltxcmds
#include:kvsetkeys

\ProcessKeyvalOptions{family}#*
\ProcessKeyvalOptions*#*
\ProcessLocalKeyvalOptions{family}#*
\ProcessLocalKeyvalOptions*#*
\SetupKeyvalOptions{options%keyvals}#*
#keyvals:\SetupKeyvalOptions
family=
prefix=
setkeys=
#endkeyvals
\DeclareStringOption{key%plain}#*
\DeclareStringOption[init]{key%plain}[default]#*
\DeclareBoolOption{key%plain}#*
\DeclareBoolOption[init]{key%plain}#*
\DeclareComplementaryOption{key%plain}{parent}#*
\DeclareVoidOption{key%plain}{code}#*
\DeclareDefaultOption{code}#*
\DeclareLocalOption{option}#*
\DeclareLocalOptions{options}#*
\DisableKeyvalOption{family}{key%plain}#*
\DisableKeyvalOption[options%keyvals]{family}{key%plain}#*
#keyvals:\DisableKeyvalOption
action=#undef,warning,error,ignore
global
local
package=
class=
#endkeyvals
\AddToKeyvalOption{family}{key%plain}{code}#*
\AddToKeyvalOption*{key%plain}{code}#*