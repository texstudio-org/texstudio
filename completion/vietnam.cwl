# vietnam package
# Matthew Bertucci 3/16/2022 for v1.3

#include:ifthen
#include:fontenc
# loads T5 option of fontenc
#include:inputenc

#keyvals:\usepackage/vietnam#c
viscii
tcvn
vps
mviscii
noinputenc
nocaptions
utf8
utf8x
varioref
cmap
#endkeyvals

#ifOption:utf8x
#include:ucs
#endif

#ifOption:cmap
#include:ifpdf
#include:cmap
#endif

#ifOption:varioref
#include:varioref-vi
#endif

# from vncaps.tex
\alsoname#*
\bibname#*
\captionsenglish#*
\captionsvietnam#*
\ccname#*
\chaptername#*
\dateUSenglish#*
\dateenglish#*
\datevietnam#*
\enclname#*
\glossaryname#*
\headpagename#*
\headtoname#*
\pagename#*
\prefacename#*
\proofname#*
\undefined#S

# from T5 option of fontenc
\Abreve#n
\abreve#n
\ABREVE#n
\Acircumflex#n
\acircumflex#n
\ACIRCUMFLEX#n
\DJ#n
\dj#n
\Ecircumflex#n
\ecircumflex#n
\ECIRCUMFLEX#n
\guillemotleft#n
\guillemotright#n
\guilsinglleft#n
\guilsinglright#n
\h{arg}#n
\Ocircumflex#n
\ocircumflex#n
\OCIRCUMFLEX#n
\OHORN#n
\ohorn#n
\Ohorn#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\UHORN#n
\uhorn#n
\Uhorn#n