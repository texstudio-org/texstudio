# tree-dvips package
# Matthew Bertucci 2022/05/25 for v.91

\node{nodename}{object%text}
\nodepoint{nodename}
\nodepoint{nodename}[hshift%l]
\nodepoint{nodename}[hshift%l][vshift%l]
\nodeconnect{fromnodename}{tonodename}
\nodeconnect{fromnodename}[toloc]{tonodename}
\nodeconnect[fromloc]{fromnodename}{tonodename}
\nodeconnect[fromloc]{fromnodename}[toloc]{tonodename}
\anodeconnect{fromnodename}{tonodename}
\anodeconnect{fromnodename}[toloc]{tonodename}
\anodeconnect[fromloc]{fromnodename}{tonodename}
\anodeconnect[fromloc]{fromnodename}[toloc]{tonodename}
\aanodeconnect{fromnodename}{tonodename}
\aanodeconnect{fromnodename}[toloc]{tonodename}
\aanodeconnect[fromloc]{fromnodename}{tonodename}
\aanodeconnect[fromloc]{fromnodename}[toloc]{tonodename}
\barnodeconnect{fromnodename}{tonodename}
\barnodeconnect[depth%l]{fromnodename}{tonodename}
\abarnodeconnect{fromnodename}{tonodename}
\abarnodeconnect[depth%l]{fromnodename}{tonodename}
\nodecurve{fromnodename}{tonodename}{fdepth%l}
\nodecurve[fromloc]{fromnodename}[toloc]{tonodename}{fdepth%l}
\nodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}
\nodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}[tdepth%l]
\anodecurve{fromnodename}{tonodename}{fdepth%l}
\anodecurve[fromloc]{fromnodename}[toloc]{tonodename}{fdepth%l}
\anodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}
\anodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}[tdepth%l]
\aanodecurve{fromnodename}{tonodename}{fdepth%l}
\aanodecurve[fromloc]{fromnodename}[toloc]{tonodename}{fdepth%l}
\aanodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}
\aanodecurve[fromloc][fromang]{fromnodename}[toloc][toang]{tonodename}{fdepth%l}[tdepth%l]
\nodetriangle{fromnodename}{tonodename}
\delink{fromnodename}{tonodename}{length}
\delink{fromnodename}[toloc]{tonodename}{length}
\delink[fromloc]{fromnodename}{tonodename}{length}
\delink[fromloc]{fromnodename}[toloc]{tonodename}{length}
\nodebox{nodename}
\nodecircle{nodename}
\nodecircle[depth%l]{nodename}
\nodeoval{nodename}
\nodemargin#*
\treelinewidth#*
\dashlength#*
\arrowwidth#*
\arrowlength#*
\arrowinset#*
\arrowhead{width}{length}{inset%l}
\makedash{length}

# not documented
\delinkcurve{arg}#*
\iftransparent#*
\pscmd{PS code}#*
\thinline#*
\transparentfalse#*
\transparenttrue#*
\wnum#*