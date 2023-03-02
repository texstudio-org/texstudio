# xob-font package
# Matthew Bertucci 2022/05/05 for v0.9.7

#include:etoolbox
#include:fontspec
#include:kotex
#include:ob-unfontsdefault

#keyvals:\usepackage/xob-font#c
oldhangul
gremph
itemph
nanum
nanumx
hcr
#endkeyvals

\setkomainfont(Regular)
\setkomainfont(Regular)(Bold)#*
\setkomainfont(Regular)(Bold)(Italic)
\setkomainfont[basename](Regular)
\setkomainfont[basename](Regular)(Bold)#*
\setkomainfont[basename](Regular)(Bold)(Italic)
\setkosansfont(Regular)
\setkosansfont(Regular)(Bold)#*
\setkosansfont(Regular)(Bold)(Italic)
\setkosansfont[basename](Regular)
\setkosansfont[basename](Regular)(Bold)#*
\setkosansfont[basename](Regular)(Bold)(Italic)
\setkomonofont(Regular)
\setkomonofont(Regular)(Bold)#*
\setkomonofont(Regular)(Bold)(Italic)
\setkomonofont[basename](Regular)
\setkomonofont[basename](Regular)(Bold)#*
\setkomonofont[basename](Regular)(Bold)(Italic)

\setobmainfont(Regular)
\setobmainfont(Regular)(Bold)#*
\setobmainfont(Regular)(Bold)(Italic)
\setobmainfont[basename](Regular)
\setobmainfont[basename](Regular)(Bold)#*
\setobmainfont[basename](Regular)(Bold)(Italic)
\setobsansfont(Regular)
\setobsansfont(Regular)(Bold)#*
\setobsansfont(Regular)(Bold)(Italic)
\setobsansfont[basename](Regular)
\setobsansfont[basename](Regular)(Bold)#*
\setobsansfont[basename](Regular)(Bold)(Italic)
\setobmonofont(Regular)
\setobmonofont(Regular)(Bold)#*
\setobmonofont(Regular)(Bold)(Italic)
\setobmonofont[basename](Regular)
\setobmonofont[basename](Regular)(Bold)#*
\setobmonofont[basename](Regular)(Bold)(Italic)

\compressbnms

# not documented
\setmonoscale{factor}#*
\setkorfont{arg1}{arg2}#*
\setkorfontxob{arg}#*
\setxoblatinfont{arg}#*

# deprecated
\setkormainfont{Regular}#S
\setkormainfont(Bold)(Italic){Regular}#S
\setkorsansfont{Regular}#S
\setkorsansfont(Bold)(Italic){Regular}#S
\setkormonofont{Regular}#S
\setkormonofont(Bold)(Italic){Regular}#S
\setkorfontorigmethod{arg1}{arg2}#S
\setkorfontorigstar{arg}#S
\setkorfontorigstar*{arg}#S
