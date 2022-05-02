# upmethodology-document class
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:class-report
#include:upmethodology-p-common
#include:a4wide
#include:upmethodology-document
#include:upmethodology-extension
#include:upmethodology-frontpage
#include:upmethodology-backpage
#include:url
#include:hyperref

#keyvals:\documentclass/upmethodology-document#c
twoside
oneside
french
francais
english
standardlists
nodocumentinfo
documentinfo
nopubpage
pubpage
nofrontmatter
frontmatter
nofrontcover
frontcover
nobackcover
backcover
taskpackage
specpackage
codepackage
book
report
article
# options passed to underlying class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:book
#include:class-book
#endif

#ifOption:taskpackage
#include:upmethodology-task
#endif

#ifOption:specpackage
#include:upmethodology-spec
#endif

#ifOption:codepackage
#include:upmethodology-code
#endif

\frontmatter
\mainmatter
\backmatter