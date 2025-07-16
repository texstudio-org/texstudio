# nfssext-cfr package
# Matthew Bertucci 2025/07/16 for v1.3

#include:svn-prov
#include:etoolbox

\nfssextset{keyvals}#*

#keyvals:\usepackage/nfssext-cfr#c,\nfssextset
compat#true,false
debug#true,false
force#true,false
#endkeyvals

# The font commands in the package don't guarantee the font used has the corresponding
# shapes, weights, etc., so the font commands here are given with #S.
# Packages that use nfssext-cfr like baskervald, electrum, etc. have the
# available font commands in their own cwl.

\altstyle#S
\bdweight#S
\bfweight#S
\cdwidth#S
\dbweight#S
\dfshape#S
\ebweight#S
\ecwidth#S
\elweight#S
\embossstyle#S
\emboss{text}#S
\epwidth#S
\etwidth#S
\exwidth#S
\infstyle#S
\instyle#S
\lgweight#S
\lnstyle#S
\lstyle#S
\ltstyle#S
\mbweight#S
\mdweight#S
\mdwidth#S
\nwwidth#S
\ofstyle#S
\olshape#S
\ornamentalstyle#S
\ornament{arg}#S
\osstyle#S
\ostyle#S
\plstyle#S
\postyle#S
\pstyle#S
\qtstyle#S
\regstyle#S
\regwidth#S
\rishape#S
\sbweight#S
\scolshape#S
\scushape#S
\shstyle#S
\sishape#S
\sustyle#S
\swashstyle#S
\swstyle#S
\textalt{text}#S
\textbd{text}#S
\textcd{text}#S
\textdb{text}#S
\textdf{text}#S
\texteb{text}#S
\textec{text}#S
\textel{text}#S
\textep{text}#S
\textet{text}#S
\textex{text}#S
\textinf{text}#S
\textin{text}#S
\textlg{text}#S
\textln{text}#S
\textlt{text}#S
\textl{text}#S
\textmb{text}#S
\textnw{text}#S
\textof{text}#S
\textol{text}#S
\textorn{text}#S
\textos{text}#S
\texto{text}#S
\textpl{text}#S
\textpo{text}#S
\textp{text}#S
\textqt{text}#S
\textreg{text}#S
\textri{text}#S
\textrw{text}#S
\textsb{text}#S
\textscu{text}#S
\textsh{text}#S
\textsi{text}#S
\textsu{text}#S
\textswash{text}#S
\textti{text}#S
\texttl{text}#S
\texttm{text}#S
\textto{text}#S
\texttv{text}#S
\textt{text}#S
\textub{text}#S
\textuc{text}#S
\textui{text}#S
\textul{text}#S
\textux{text}#S
\textu{text}#S
\tistyle#S
\tlstyle#S
\tmstyle#S
\tostyle#S
\tstyle#S
\tvstyle#S
\ubweight#S
\ucwidth#S
\uishape#S
\ulweight#S
\ushape#S
\uxwidth#S

# not really documented
\DeclareTextOrnament{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#S