# J. Sundermeyer 12/2019
\DeclareInputMath{slot}{text}#*
\DeclareInputText{slot}{math}#*
\DeclareUnicodeCharacter{slot}{text}#*
\inputencodingname#*
\inputencoding{encoding name%keyvals}#*
\IeC{arg}#S

#keyvals:\usepackage/inputenc#c,\inputencoding#c
ascii
latin1
latin2
latin3
latin4
latin5
latin9
latin10
decmulti
cp850
cp852
cp858
cp437
cp437de
cp865
applemac
macce
next
cp1250
cp1252
cp1257
ansinew
utf8
utf8x
armscii8
#endkeyvals

#ifOption:utf8x
#include:ucs
#endif

#ifOption:armscii8
\definearmew{character}
#endif
