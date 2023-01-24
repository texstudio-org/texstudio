# expkv package
# Matthew Bertucci 2023/01/23 for v2.0

#keyvals:\usepackage/expkv#c
all
#endkeyvals

#ifOption:all
#include:expkv-pop
#include:expkv-cs
#include:expkv-def
#include:expkv-opt
#endif

## Setting up Keys ##
\ekvdef{set}{key%plain}{code}#*
\ekvdefNoVal{set}{key%plain}{code}#*
\ekvlet{set}{key%plain}{cmd}#*d
\ekvletNoVal{set}{key%plain}{cmd}#*d
\ekvletkv{set1}{key1}{set2}{key2}#*
\ekvletkvNoVal{set1}{key1}{set2}{key2}#*
\ekvdefunknown{set}{code}#*
\ekvdefunknownNoVal{set}{code}#*
\ekvredirectunknown{set}{set-list}#*
\ekvredirectunknownNoVal{set}{set-list}#*
\ekvletunknown{set}{cmd}#*d
\ekvletunknownNoVal{set}{cmd}#*d

## Helpers in Actions ##
\ekvifdefined{set}{key%plain}{true}{false}#*
\ekvifdefinedNoVal{set}{key%plain}{true}{false}#*
\ekvifdefinedset{set}{true}{false}#*
\ekvsneak{after}#*
\ekvsneakPre{after}#*
\ekvbreak{after}#*
\ekvbreakPreSneak{after}#*
\ekvbreakPostSneak{after}#*
\ekvmorekv{keyvals}#*
\ekvchangeset{new-set}#*

## Parsing Keys in Sets ##
\ekvset{set}{keyvals}#*
\ekvsetSneaked{set}{sneak}{keyvals}#*
\ekvsetdef{cmd}{set}#*d
\ekvsetSneakeddef{cmd}{set}#*d
\ekvsetdefSneaked{cmd}{set}{sneaked}#*d
\ekvcompile{cmd}{set}{keyvals}#*d
\ekvcompile*{cmd}{set}{keyvals}#*d

## Generic Key Parsing ##
\ekvparse{code1}{code2}{keyvals}#*

## Other Useful Macros ##
\ekvoptarg{next}{default}#*
\ekvoptargTF{true}{false}#*
\ekvcsvloop{code}{csv-list}#*
\ekverr{package}{message%text}#*

## Other Macros ##
\ekvDate#S
\ekvVersion#S
