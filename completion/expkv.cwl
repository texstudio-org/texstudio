# expkv package
# Matthew Bertucci 11/3/2021 for v1.9a

## 1.1 Setting up Keys ##
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

## 1.2 Parsing Keys ##
\ekvset{set}{keyvals}#*
\ekvsetSneaked{set}{sneak}{keyvals}#*
\ekvsetdef{cmd}{set}#*d
\ekvsetSneakeddef{cmd}{set}#*d
\ekvsetdefSneaked{cmd}{set}{sneaked}#*d
\ekvparse{code1}{code2}{keyvals}#*

## 1.3 Other Macros ##
\ekvDate#S
\ekvVersion#S
\ekvifdefined{set}{key%plain}{true}{false}#*
\ekvifdefinedNoVal{set}{key%plain}{true}{false}#*
\ekvifdefinedset{set}{true}{false}#*
\ekvbreak{after}#*
\ekvbreakPreSneak{after}#*
\ekvbreakPostSneak{after}#*
\ekvsneak{after}#*
\ekvsneakPre{after}#*
\ekvchangeset{new-set}#*
\ekvoptarg{next}{default}#*
\ekvoptargTF{true}{false}#*
\ekvcsvloop{code}{csv-list}#*
\ekverr{package}{message%text}#*
\ekvtmpa#S
\ekvtmpb#S