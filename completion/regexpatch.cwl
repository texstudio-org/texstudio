# regexpatch package
# muzimuzhi 18 Jan 2020, add cwl for regexpatch v0.2d

# common lines shared with "xpatch.cwl"
#include:patch-common

\xpatchcmd*{command}{search}{replace all}{success}{failure}
\xpatchbibmacro*{name}{search}{replace all}{success}{failure}
\xpatchbibdriver*{name}{search}{replace all}{success}{failure}
\xpatchfieldformat*[entry type]{name}{search}{replace all}{success}{failure}
\xpatchnameformat*[entry type]{name}{search}{replace all}{success}{failure}
\xpatchlistformat*[entry type]{name}{search}{replace all}{success}{failure}
\xpatchindexfieldformat*[entry type]{name}{search}{replace all}{success}{failure}
\xpatchindexnameformat*[entry type]{name}{search}{replace all}{success}{failure}
\xpatchindexlistformat*[entry type]{name}{search}{replace all}{success}{failure}

\regexpatchcmd{command}{search}{replace once}{success}{failure}
\regexpatchcmd*{command}{search}{replace all}{success}{failure}
\regexpatchbibmacro{name}{search}{replace once}{success}{failure}
\regexpatchbibmacro*{name}{search}{replace all}{success}{failure}

\xshowcmd*{command}
\xpatchoptarg{name}{replace}
\xpatchparametertext{name}{search}{replace}{success}{failure}
\checkpatchable{name}
\tracingxpatches
\tracingxpatches[0 or 1]
