# pst-pdgr package
# Matthew Bertucci 2022/09/01 for v0.4

#include:pstricks
#include:pst-node
#include:pst-tree
#include:pst-xkey

\affectedstyle
\affectedbgcolor
\affectedfgcolor

\pstPerson{id}
\pstPerson[options%keyvals]{id}
\pstAbortion{id}
\pstAbortion[options%keyvals]{id}
\pstChildless{id}
\pstChildless[options%keyvals]{id}
\pstRelationship{nodeA}{nodeB}
\pstRelationship[options%keyvals]{nodeA}{nodeB}
\pstDescent{parent}{child}
\pstDescent[options%keyvals]{parent}{child}
\pstTwins{parent}{twin node}{left twin}{right twin}

\TpstPerson{id}
\TpstPerson[options%keyvals]{id}
\TpstAbortion{id}
\TpstAbortion[options%keyvals]{id}
\TpstChildless{id}
\TpstChildless[options%keyvals]{id}

\ncAngles{arg1}{arg2}#*
\PSTPedigreeLoaded#S