# regexpatch package
# muzimuzhi 18 Jan 2020, add cwl for regexpatch v0.2d

#include:expl3
#include:xparse

# common lines shared with "xpatch.cwl"
#include:patch-common

\xshowcmd*{command}
\xpatchoptarg{name}{replace}
\xpatchparametertext{name}{search}{replace}{success}{failure}
\checkpatchable{name}
\tracingxpatches
\tracingxpatches[0 or 1]
