# regulatory-sources package
# Matthew Bertucci 2026/09/12 for v1.0.0

#include:regulatory-struct

\ifsourceexists{key%plain}{true code}{false code}
\loadsources{file}
\newsourcedeterminer{register}{kind}{article}
\newsourcefieldalias{alias}{field}
\newsourceregister{name}{full}{short}
\newsourcetypealias{alias}{type}
\newsourcetype{type}{fields}{register}
\newsource{key%plain}{type}{fields}
\sourcedate{YYYY-MM-DD}
\srcfield{key%plain}{field}
\srcref*[options%keyvals]{key%plain}
\srcref*{key%plain}
\srcref[options%keyvals]{key%plain}
\srcref{key%plain}
\srcregister{key%plain}#*
\srctype{key%plain}