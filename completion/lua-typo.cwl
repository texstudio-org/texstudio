# lua-typo package
# Matthew Bertucci 9/28/2021 for v0.50

#include:luatexbase
#include:luacode
#include:luacolor
#include:kvoptions
#include:atveryend

#keyvals:\usepackage/lua-typo#c
ShowOptions#true,false
None#true,false
All#true,false
BackParindent#true,false
ShortLines#true,false
ShortPages#true,false
OverfullLines#true,false
UnderfullLines#true,false
Widows#true,false
Orphans#true,false
EOPHyphens#true,false
RepeatedHyphens#true,false
ParLastHyphen#true,false
EOLShortWords#true,false
FirstWordMatch#true,false
LastWordMatch#true,false
FootnoteSplit#true,false
#endkeyvals

\luatypoLLminWD#*
\luatypoBackPI#*
\luatypoBackFuzz#*
\luatypoStretchMax#*
\luatypoHyphMax#*
\luatypoPageMin#*
\luatypoMinFull#*
\luatypoMinPart#*

\luatypoOneChar{language}{string}
\luatypoTwoChars{language}{string}
\luatypoSetColor{number}{color}
