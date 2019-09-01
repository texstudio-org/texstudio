# menukeys package
# sdm
# muzimuzhi/28 Aug 2019 for menukeys v1.5

#include:adjustbox
#include:catoptions
#include:etoolbox
#include:kvoptions
#include:relsize
#include:tikz
#include:xcolor
#include:xparse
#include:xstring

# basic 
\menu{text}
\menu[separator]{text}
\directory{path}
\directory[separator]{path}
\keys{keys}
\keys[separator]{keys}

# menukeys styles
\newmenustylesimple{name}[pre]{style}[sep][post]{theme}#*
\newmenustylesimple*{name}[pre]{style}[sep][post]{theme}#*
\renewmenustylesimple{name}[pre]{style%keyvals}[sep][post]{theme}#*
\renewmenustylesimple*{name}[pre]{style%keyvals}[sep][post]{theme}#*
\providemenustylesimple{name}[pre]{style}[sep][post]{theme}#*
\providemenustylesimple*{name}[pre]{style}[sep][post]{theme}#*

\newmenustyle{name}[pre]{first}[sep]{mid}{last}{single}[post]{theme}#*
\newmenustyle*{name}[pre]{first}[sep]{mid}{last}{single}[post]{theme}#*
\renewmenustyle{name}[pre]{first}[sep]{mid}{last}{single%keyvals}[post]{theme}#*
\renewmenustyle*{name}[pre]{first}[sep]{mid}{last}{single%keyvals}[post]{theme}#*
\providemenustyle{name}[pre]{first}[sep]{mid}{last}{single}[post]{theme}#*
\providemenustyle*{name}[pre]{first}[sep]{mid}{last}{single}[post]{theme}#*
\CurrentMenuElement#*
\usemenucolor{element}#*
\drawtikzfolder#*
\drawtikzfolder[front fill color%color]#*
\drawtikzfolder[front fill color%color][draw color%color]#*

# config existing styles
\copymenustyle{copy}{original}#*
\changemenuelement{name}{element%keyvals}{definition}#*
\changemenuelement*{name}{element%keyvals}{definition}#*
\changemenucolortheme{name}{color theme}
#keyvals:\changemenuelement
single
first
middle
last
pre
post
set
single
#endkeyvals

# color themes
\newmenucolortheme{name}{model}{bg}{br}{txt}[a][b][c]#*
\copymenucolortheme{copy}{original}#*
\changemenucolor{name}{element%keyvals}{model}{color definition}#*
\renewmenucolortheme{name}{model}{bg}{br}{txt}[a][b][c]#*
#keyvals:\changemenucolor
bg
br
txt
#endkeyvals

# menu macros
\newmenumacro{macro}[input sep]{style%keyvals}#*
\renewmenumacro{macro}[input sep]{style%keyvals}#*
\providemenumacro{macro}[input sep]{style%keyvals}#*
## keys
\shift
\capslock
\tab
\esc
\oldesc
\ctrl
\Alt
\AltGr
\cmd
\Space
\SPACE
\return
\enter
\winmenu
\backspace
\del
\backdel
\arrowkeyup
\arrowkeydown
\arrowkeyright
\arrowkeyleft
\arrowkey{direction#keyvals}
\ctrlname#*
\delname#*
\spacename#*
#keyvals:\arrowkey
^
v
>
<
#endkeyvals

# predefined menukeys styles
#keyvals:\renewmenustylesimple,\renewmenustyle,\newmenumacro,\renewmenumacro,\providemenumacro
menus
roundedmenus
angularmenus
roundedkeys
shadowedroundedkeys
angularkeys
shadowedangularkeys
typewriterkeys
paths
pathswithfolder
pathswithblackfolder
hyphenatepaths
hyphenatepathswithfolder
hyphenatepathswithblackfolder
#endkeyvals

## predefined color themes ("gray" and "blackwhite") are not listed
## since txs supports only one "%keyvals" for each cwl line
