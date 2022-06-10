# imsart class
# Matthew Bertucci 2022/06/06 for release 2022/04/21

#include:imsart

#keyvals:\documentclass/imsart#c
printbiddoi
keywordsasfootnote
historyasfootnote
addressasfootnote
addressatend
autosecdot
noautosecdot
noundefthanksref
frontback
amsmath
amsthm
seceqn
natbib
linksfromyear
numbers
nameyear
authoryear
rotating
ba
ps
ss
ejs
aap
aop
aos
aoas
sts
bj
aihp
bjps
doublespacing
singlespacing
noinfoline
infoline
linenumbers
nolinenumbers
showframe
noshowframe
submission
preedit
preprint
#endkeyvals

#ifOption:amsmath
#include:amsmath
#endif

#ifOption:amsthm
#include:amsthm
\begin{proof}[heading%text]
#endif

#ifOption:natbib
#include:natbib
#endif

#ifOption:rotating
#include:rotating
#endif

#ifOption:ba
#include:lmodern
#endif

#ifOption:ps
#include:lmodern
#endif

#ifOption:ss
#include:lmodern
#endif

#ifOption:ejs
#include:lmodern
#endif

#ifOption:aap
#include:times
#include:helvet
#include:textcomp
#include:textcase
#endif

#ifOption:aop
#include:times
#include:helvet
#include:textcomp
#include:textcase
#endif

#ifOption:aos
#include:times
#include:helvet
#include:textcomp
#include:textcase
#endif

#ifOption:aoas
#include:times
#include:helvet
#include:textcomp
#include:textcase
#endif

#ifOption:sts
\savehline#S
\thline#*
#endif

#ifOption:bj
#include:textcomp
#include:helvet
#include:newtxmath
#include:graphicx
#include:letterspace
#include:enumitem
#include:hyperref
#include:amsmath
#include:amssymb
#include:mathrsfs
#include:bm
#include:amsthm
#include:natbib
#include:color
\savehline#S
\thline#*
\setlstracking{value}
\texttracking{value}{text}
#endif

#ifOption:aihp
#include:times
#include:helvet
#include:textcomp
#endif

#ifOption:bjps
#include:times
#include:helvet
#include:textcomp
\savehline#S
\thline#*
#endif

#ifOption:showframe
#include:color
imsgray#B
#endif