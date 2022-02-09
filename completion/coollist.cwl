# coollist package
# Matthew Bertucci 2/8/2022 for v1.4

#include:ifthen
#include:amsmath
#include:amssymb
#include:coolstr
#include:forloop

\setlistStop{string}
\setlistEnd{string}
\listval{list}{index}
\liststore{list}{macro base name}
\listlen{list}
\listlenstore{counter}{list}
\listcopy{list1}{list2}
\listsum{list}{macro%cmd}#d
\listsum[stored list]{list}{macro%cmd}#d