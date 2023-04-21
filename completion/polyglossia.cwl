# polyglossia package
# Matthew Bertucci 2022/11/30 for v1.61

#include:etoolbox
#include:makecmds
#include:xkeyval
#include:fontspec
#include:iftex
#include:bidi
#include:luabidi
#include:calc
#include:arabicnumbers
#include:hijrical
#include:xpg-cyrillicnumbers
#include:devanagaridigits
#include:bengalidigits
#include:luavlna
#include:hebrewcal
#include:farsical
#include:nkonumbers

#keyvals:\usepackage/polyglossia#c
babelshorthands#true,false
localmarks#true,false
luatexrenderer=%<renderer%>
verbose#true,false
#endkeyvals

\setdefaultlanguage{language}
\setdefaultlanguage[options%keyvals]{language}
\setmainlanguage{language}
\setmainlanguage[options%keyvals]{language}
\setotherlanguage{language}
\setotherlanguage[options%keyvals]{language}
\setotherlanguages{lang1,lang2,...}

\textlang{language}{text}
\textlang[options%keyvals]{language}{text}

\textafrikaans[options%keyvals]{text}#*
\textafrikaans{text}#*
\textalbanian[options%keyvals]{text}#*
\textalbanian{text}#*
\textamharic[options%keyvals]{text}#*
\textamharic{text}#*
\textarabic[options%keyvals]{text}#*
\textarabic{text}#*
\textarmenian[options%keyvals]{text}#*
\textarmenian{text}#*
\textasturian[options%keyvals]{text}#*
\textasturian{text}#*
\textbasque[options%keyvals]{text}#*
\textbasque{text}#*
\textbelarusian[options%keyvals]{text}#*
\textbelarusian{text}#*
\textbengali[options%keyvals]{text}#*
\textbengali{text}#*
\textbosnian[options%keyvals]{text}#*
\textbosnian{text}#*
\textbreton[options%keyvals]{text}#*
\textbreton{text}#*
\textbulgarian[options%keyvals]{text}#*
\textbulgarian{text}#*
\textcatalan[options%keyvals]{text}#*
\textcatalan{text}#*
\textchinese[options%keyvals]{text}#*
\textchinese{text}#*
\textcoptic[options%keyvals]{text}#*
\textcoptic{text}#*
\textcroatian[options%keyvals]{text}#*
\textcroatian{text}#*
\textczech[options%keyvals]{text}#*
\textczech{text}#*
\textdanish[options%keyvals]{text}#*
\textdanish{text}#*
\textdivehi[options%keyvals]{text}#*
\textdivehi{text}#*
\textdutch[options%keyvals]{text}#*
\textdutch{text}#*
\textenglish[options%keyvals]{text}#*
\textenglish{text}#*
\textesperanto[options%keyvals]{text}#*
\textesperanto{text}#*
\textestonian[options%keyvals]{text}#*
\textestonian{text}#*
\textfinnish[options%keyvals]{text}#*
\textfinnish{text}#*
\textfrench[options%keyvals]{text}#*
\textfrench{text}#*
\textfriulian[options%keyvals]{text}#*
\textfriulian{text}#*
\textgaelic[options%keyvals]{text}#*
\textgaelic{text}#*
\textgalician[options%keyvals]{text}#*
\textgalician{text}#*
\textgeorgian[options%keyvals]{text}#*
\textgeorgian{text}#*
\textgerman[options%keyvals]{text}#*
\textgerman{text}#*
\textgreek[options%keyvals]{text}#*
\textgreek{text}#*
\texthebrew[options%keyvals]{text}#*
\texthebrew{text}#*
\texthindi[options%keyvals]{text}#*
\texthindi{text}#*
\texthungarian[options%keyvals]{text}#*
\texthungarian{text}#*
\texticelandic[options%keyvals]{text}#*
\texticelandic{text}#*
\textinterlingua[options%keyvals]{text}#*
\textinterlingua{text}#*
\textitalian[options%keyvals]{text}#*
\textitalian{text}#*
\textjapanese[options%keyvals]{text}#*
\textjapanese{text}#*
\textkannada[options%keyvals]{text}#*
\textkannada{text}#*
\textkhmer[options%keyvals]{text}#*
\textkhmer{text}#*
\textkorean[options%keyvals]{text}#*
\textkorean{text}#*
\textkurdish[options%keyvals]{text}#*
\textkurdish{text}#*
\textlao[options%keyvals]{text}#*
\textlao{text}#*
\textlatin[options%keyvals]{text}#*
\textlatin{text}#*
\textlatvian[options%keyvals]{text}#*
\textlatvian{text}#*
\textlithuanian[options%keyvals]{text}#*
\textlithuanian{text}#*
\textmacedonian[options%keyvals]{text}#*
\textmacedonian{text}#*
\textmalay[options%keyvals]{text}#*
\textmalay{text}#*
\textmalayalam[options%keyvals]{text}#*
\textmalayalam{text}#*
\textmarathi[options%keyvals]{text}#*
\textmarathi{text}#*
\textmongolian[options%keyvals]{text}#*
\textmongolian{text}#*
\textnko[options%keyvals]{text}#*
\textnko{text}#*
\textnorwegian[options%keyvals]{text}#*
\textnorwegian{text}#*
\textoccitan[options%keyvals]{text}#*
\textoccitan{text}#*
\textpersian[options%keyvals]{text}#*
\textpersian{text}#*
\textpiedmontese[options%keyvals]{text}#*
\textpiedmontese{text}#*
\textpolish[options%keyvals]{text}#*
\textpolish{text}#*
\textportuguese[options%keyvals]{text}#*
\textportuguese{text}#*
\textpunjabi[options%keyvals]{text}#*
\textpunjabi{text}#*
\textromanian[options%keyvals]{text}#*
\textromanian{text}#*
\textromansh[options%keyvals]{text}#*
\textromansh{text}#*
\textrussian[options%keyvals]{text}#*
\textrussian{text}#*
\textsami[options%keyvals]{text}#*
\textsami{text}#*
\textsanskrit[options%keyvals]{text}#*
\textsanskrit{text}#*
\textserbian[options%keyvals]{text}#*
\textserbian{text}#*
\textslovak[options%keyvals]{text}#*
\textslovak{text}#*
\textslovenian[options%keyvals]{text}#*
\textslovenian{text}#*
\textsorbian[options%keyvals]{text}#*
\textsorbian{text}#*
\textspanish[options%keyvals]{text}#*
\textspanish{text}#*
\textswedish[options%keyvals]{text}#*
\textswedish{text}#*
\textsyriac[options%keyvals]{text}#*
\textsyriac{text}#*
\texttamil[options%keyvals]{text}#*
\texttamil{text}#*
\texttelugu[options%keyvals]{text}#*
\texttelugu{text}#*
\textthai[options%keyvals]{text}#*
\textthai{text}#*
\texttibetan[options%keyvals]{text}#*
\texttibetan{text}#*
\textturkish[options%keyvals]{text}#*
\textturkish{text}#*
\textturkmen[options%keyvals]{text}#*
\textturkmen{text}#*
\textukrainian[options%keyvals]{text}#*
\textukrainian{text}#*
\texturdu[options%keyvals]{text}#*
\texturdu{text}#*
\textuyghur[options%keyvals]{text}#*
\textuyghur{text}#*
\textvietnamese[options%keyvals]{text}#*
\textvietnamese{text}#*
\textwelsh[options%keyvals]{text}#*
\textwelsh{text}#*

\begin{lang}{language}
\begin{lang}[options%keyvals]{language}
\end{lang}

\begin{afrikaans}[options%keyvals]#*
\begin{afrikaans}#*
\begin{albanian}[options%keyvals]#*
\begin{albanian}#*
\begin{amharic}[options%keyvals]#*
\begin{amharic}#*
\begin{Arabic}[options%keyvals]#*
\begin{Arabic}#*
\begin{armenian}[options%keyvals]#*
\begin{armenian}#*
\begin{asturian}[options%keyvals]#*
\begin{asturian}#*
\begin{basque}[options%keyvals]#*
\begin{basque}#*
\begin{belarusian}[options%keyvals]#*
\begin{belarusian}#*
\begin{bengali}[options%keyvals]#*
\begin{bengali}#*
\begin{bosnian}[options%keyvals]#*
\begin{bosnian}#*
\begin{breton}[options%keyvals]#*
\begin{breton}#*
\begin{bulgarian}[options%keyvals]#*
\begin{bulgarian}#*
\begin{catalan}[options%keyvals]#*
\begin{catalan}#*
\begin{chinese}[options%keyvals]#*
\begin{chinese}#*
\begin{coptic}[options%keyvals]#*
\begin{coptic}#*
\begin{croatian}[options%keyvals]#*
\begin{croatian}#*
\begin{czech}[options%keyvals]#*
\begin{czech}#*
\begin{danish}[options%keyvals]#*
\begin{danish}#*
\begin{divehi}[options%keyvals]#*
\begin{divehi}#*
\begin{dutch}[options%keyvals]#*
\begin{dutch}#*
\begin{english}[options%keyvals]#*
\begin{english}#*
\begin{esperanto}[options%keyvals]#*
\begin{esperanto}#*
\begin{estonian}[options%keyvals]#*
\begin{estonian}#*
\begin{finnish}[options%keyvals]#*
\begin{finnish}#*
\begin{french}[options%keyvals]#*
\begin{french}#*
\begin{friulian}[options%keyvals]#*
\begin{friulian}#*
\begin{gaelic}[options%keyvals]#*
\begin{gaelic}#*
\begin{galician}[options%keyvals]#*
\begin{galician}#*
\begin{georgian}[options%keyvals]#*
\begin{georgian}#*
\begin{german}[options%keyvals]#*
\begin{german}#*
\begin{greek}[options%keyvals]#*
\begin{greek}#*
\begin{hebrew}[options%keyvals]#*
\begin{hebrew}#*
\begin{hindi}[options%keyvals]#*
\begin{hindi}#*
\begin{hungarian}[options%keyvals]#*
\begin{hungarian}#*
\begin{icelandic}[options%keyvals]#*
\begin{icelandic}#*
\begin{interlingua}[options%keyvals]#*
\begin{interlingua}#*
\begin{italian}[options%keyvals]#*
\begin{italian}#*
\begin{japanese}[options%keyvals]#*
\begin{japanese}#*
\begin{kannada}[options%keyvals]#*
\begin{kannada}#*
\begin{khmer}[options%keyvals]#*
\begin{khmer}#*
\begin{korean}[options%keyvals]#*
\begin{korean}#*
\begin{kurdish}[options%keyvals]#*
\begin{kurdish}#*
\begin{lao}[options%keyvals]#*
\begin{lao}#*
\begin{latin}[options%keyvals]#*
\begin{latin}#*
\begin{latvian}[options%keyvals]#*
\begin{latvian}#*
\begin{lithuanian}[options%keyvals]#*
\begin{lithuanian}#*
\begin{macedonian}[options%keyvals]#*
\begin{macedonian}#*
\begin{malay}[options%keyvals]#*
\begin{malay}#*
\begin{malayalam}[options%keyvals]#*
\begin{malayalam}#*
\begin{marathi}[options%keyvals]#*
\begin{marathi}#*
\begin{mongolian}[options%keyvals]#*
\begin{mongolian}#*
\begin{nko}[options%keyvals]#*
\begin{nko}#*
\begin{norwegian}[options%keyvals]#*
\begin{norwegian}#*
\begin{occitan}[options%keyvals]#*
\begin{occitan}#*
\begin{persian}[options%keyvals]#*
\begin{persian}#*
\begin{piedmontese}[options%keyvals]#*
\begin{piedmontese}#*
\begin{polish}[options%keyvals]#*
\begin{polish}#*
\begin{portuguese}[options%keyvals]#*
\begin{portuguese}#*
\begin{punjabi}[options%keyvals]#*
\begin{punjabi}#*
\begin{romanian}[options%keyvals]#*
\begin{romanian}#*
\begin{romansh}[options%keyvals]#*
\begin{romansh}#*
\begin{russian}[options%keyvals]#*
\begin{russian}#*
\begin{sami}[options%keyvals]#*
\begin{sami}#*
\begin{sanskrit}[options%keyvals]#*
\begin{sanskrit}#*
\begin{serbian}[options%keyvals]#*
\begin{serbian}#*
\begin{slovak}[options%keyvals]#*
\begin{slovak}#*
\begin{slovenian}[options%keyvals]#*
\begin{slovenian}#*
\begin{sorbian}[options%keyvals]#*
\begin{sorbian}#*
\begin{spanish}[options%keyvals]#*
\begin{spanish}#*
\begin{swedish}[options%keyvals]#*
\begin{swedish}#*
\begin{syriac}[options%keyvals]#*
\begin{syriac}#*
\begin{tamil}[options%keyvals]#*
\begin{tamil}#*
\begin{telugu}[options%keyvals]#*
\begin{telugu}#*
\begin{thai}[options%keyvals]#*
\begin{thai}#*
\begin{tibetan}[options%keyvals]#*
\begin{tibetan}#*
\begin{turkish}[options%keyvals]#*
\begin{turkish}#*
\begin{turkmen}[options%keyvals]#*
\begin{turkmen}#*
\begin{ukrainian}[options%keyvals]#*
\begin{ukrainian}#*
\begin{urdu}[options%keyvals]#*
\begin{urdu}#*
\begin{uyghur}[options%keyvals]#*
\begin{uyghur}#*
\begin{vietnamese}[options%keyvals]#*
\begin{vietnamese}#*
\begin{welsh}[options%keyvals]#*
\begin{welsh}#*
\end{afrikaans}#*
\end{albanian}#*
\end{amharic}#*
\end{Arabic}#*
\end{armenian}#*
\end{asturian}#*
\end{basque}#*
\end{belarusian}#*
\end{bengali}#*
\end{bosnian}#*
\end{breton}#*
\end{bulgarian}#*
\end{catalan}#*
\end{chinese}#*
\end{coptic}#*
\end{croatian}#*
\end{czech}#*
\end{danish}#*
\end{divehi}#*
\end{dutch}#*
\end{english}#*
\end{esperanto}#*
\end{estonian}#*
\end{finnish}#*
\end{french}#*
\end{friulian}#*
\end{gaelic}#*
\end{galician}#*
\end{georgian}#*
\end{german}#*
\end{greek}#*
\end{hebrew}#*
\end{hindi}#*
\end{hungarian}#*
\end{icelandic}#*
\end{interlingua}#*
\end{italian}#*
\end{japanese}#*
\end{kannada}#*
\end{khmer}#*
\end{korean}#*
\end{kurdish}#*
\end{lao}#*
\end{latin}#*
\end{latvian}#*
\end{lithuanian}#*
\end{macedonian}#*
\end{malay}#*
\end{malayalam}#*
\end{marathi}#*
\end{mongolian}#*
\end{nko}#*
\end{norwegian}#*
\end{occitan}#*
\end{persian}#*
\end{piedmontese}#*
\end{polish}#*
\end{portuguese}#*
\end{punjabi}#*
\end{romanian}#*
\end{romansh}#*
\end{russian}#*
\end{sami}#*
\end{sanskrit}#*
\end{serbian}#*
\end{slovak}#*
\end{slovenian}#*
\end{sorbian}#*
\end{spanish}#*
\end{swedish}#*
\end{syriac}#*
\end{tamil}#*
\end{telugu}#*
\end{thai}#*
\end{tibetan}#*
\end{turkish}#*
\end{turkmen}#*
\end{ukrainian}#*
\end{urdu}#*
\end{uyghur}#*
\end{vietnamese}#*
\end{welsh}#*

\selectlanguage{language}
\selectlanguage[options%keyvals]{language}
\foreignlanguage{language}{text}
\foreignlanguage[options%keyvals]{language}{text}
\begin{otherlanguage}{language}
\begin{otherlanguage}[options%keyvals]{language}
\end{otherlanguage}
\begin{otherlanguage*}{language}#*
\begin{otherlanguage*}[options%keyvals]{language}#*
\end{otherlanguage*}
\begin{hyphenrules}{language}
\begin{hyphenrules}[options]{language}
\end{hyphenrules}

\selectbackgroundlanguage{language}#*
\resetdefaultlanguage{language}#*
\resetdefaultlanguage[options%keyvals]{language}#*
\normalfontlatin#*
\rmfamilylatin#*
\sffamilylatin#*
\ttfamilylatin#*
\latinalph#*
\latinAlph#*

\setlanguagealias{language}{alias%envname}#N
\setlanguagealias[options%keyvals]{language}{alias%envname}#N
\setlanguagealias*{language}{alias}#*
\setlanguagealias*[options%keyvals]{language}{alias}#*

\pghyphenation{language}{exceptions}
\pghyphenation[options%keyvals]{language}{exceptions}
\setlanghyphenmins{language}{l}{r}
\setlanghyphenmins[options%keyvals]{language}{l}{r}
\disablehyphenation#*
\enablehyphenation#*

#keyvals:\setdefaultlanguage/afrikaans#c,\setmainlanguage/afrikaans#c,\setotherlanguage/afrikaans#c,\textlang/afrikaans#c,\textafrikaans#c,\begin{lang}/afrikaans#c,\begin{afrikaans}#c,\selectlanguage/afrikaans#c,\foreignlanguage/afrikaans#c,\begin{otherlanguage}/afrikaans#c,\begin{otherlanguage*}/afrikaans#c,\resetdefaultlanguage/afrikaans#c,\setlanguagealias/afrikaans#c,\setlanguagealias*/afrikaans#c,\pghyphenation/afrikaans#c,\setlanghyphenmins/afrikaans#c
babelshorthands#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/arabic#c,\setmainlanguage/arabic#c,\setotherlanguage/arabic#c,\textlang/arabic#c,\textarabic#c,\begin{lang}/arabic#c,\begin{Arabic}#c,\selectlanguage/arabic#c,\foreignlanguage/arabic#c,\begin{otherlanguage}/arabic#c,\begin{otherlanguage*}/arabic#c,\resetdefaultlanguage/arabic#c,\setlanguagealias/arabic#c,\setlanguagealias*/arabic#c,\pghyphenation/arabic#c,\setlanghyphenmins/arabic#c
calendar=#gregorian,islamic,hijri
locale=#default,mashriq,libya,algeria,tunisia,morocco,mauritania
numerals=#mashriq,maghrib
abjadalph#true,false
abjadjimnotail#true,false
#endkeyvals

\abjad{text}#*
\abjadmaghribi{text}#*
\abjadalph#*
\aemph{text}#*

#keyvals:\setdefaultlanguage/armenian#c,\setmainlanguage/armenian#c,\setotherlanguage/armenian#c,\textlang/armenian#c,\textarmenian#c,\begin{lang}/armenian#c,\begin{armenian}#c,\selectlanguage/armenian#c,\foreignlanguage/armenian#c,\begin{otherlanguage}/armenian#c,\begin{otherlanguage*}/armenian#c,\resetdefaultlanguage/armenian#c,\setlanguagealias/armenian#c,\setlanguagealias*/armenian#c,\pghyphenation/armenian#c,\setlanghyphenmins/armenian#c
variant=#eastern,western
numerals=#armenian,arabic
#endkeyvals

#keyvals:\setdefaultlanguage/belarusian#c,\setmainlanguage/belarusian#c,\setotherlanguage/belarusian#c,\textlang/belarusian#c,\textbelarusian#c,\begin{lang}/belarusian#c,\begin{belarusian}#c,\selectlanguage/belarusian#c,\foreignlanguage/belarusian#c,\begin{otherlanguage}/belarusian#c,\begin{otherlanguage*}/belarusian#c,\resetdefaultlanguage/belarusian#c,\setlanguagealias/belarusian#c,\setlanguagealias*/belarusian#c,\pghyphenation/belarusian#c,\setlanghyphenmins/belarusian#c
babelshorthands#true,false
numerals=#arabic,cyrillic-alph,cyrillic-trad
spelling=#modern,classic,tarask
#endkeyvals

\Asbuk{counter}#*
\asbuk{counter}#*
\AsbukTrad{counter}#*
\asbukTrad{counter}#*

#keyvals:\setdefaultlanguage/bengali#c,\setmainlanguage/bengali#c,\setotherlanguage/bengali#c,\textlang/bengali#c,\textbengali#c,\begin{lang}/bengali#c,\begin{bengali}#c,\selectlanguage/bengali#c,\foreignlanguage/bengali#c,\begin{otherlanguage}/bengali#c,\begin{otherlanguage*}/bengali#c,\resetdefaultlanguage/bengali#c,\setlanguagealias/bengali#c,\setlanguagealias*/bengali#c,\pghyphenation/bengali#c,\setlanghyphenmins/bengali#c
numerals=#Western,Bengali,Devanagari
changecounternumbering#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/catalan#c,\setmainlanguage/catalan#c,\setotherlanguage/catalan#c,\textlang/catalan#c,\textcatalan#c,\begin{lang}/catalan#c,\begin{catalan}#c,\selectlanguage/catalan#c,\foreignlanguage/catalan#c,\begin{otherlanguage}/catalan#c,\begin{otherlanguage*}/catalan#c,\resetdefaultlanguage/catalan#c,\setlanguagealias/catalan#c,\setlanguagealias*/catalan#c,\pghyphenation/catalan#c,\setlanghyphenmins/catalan#c
babelshorthands#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/chinese#c,\setmainlanguage/chinese#c,\setotherlanguage/chinese#c,\textlang/chinese#c,\textchinese#c,\begin{lang}/chinese#c,\begin{chinese}#c,\selectlanguage/chinese#c,\foreignlanguage/chinese#c,\begin{otherlanguage}/chinese#c,\begin{otherlanguage*}/chinese#c,\resetdefaultlanguage/chinese#c,\setlanguagealias/chinese#c,\setlanguagealias*/chinese#c,\pghyphenation/chinese#c,\setlanghyphenmins/chinese#c
variant=#simplified,traditional
numerals=#arabic,chinese
#endkeyvals

#keyvals:\setdefaultlanguage/croatian#c,\setmainlanguage/croatian#c,\setotherlanguage/croatian#c,\textlang/croatian#c,\textcroatian#c,\begin{lang}/croatian#c,\begin{croatian}#c,\selectlanguage/croatian#c,\foreignlanguage/croatian#c,\begin{otherlanguage}/croatian#c,\begin{otherlanguage*}/croatian#c,\resetdefaultlanguage/croatian#c,\setlanguagealias/croatian#c,\setlanguagealias*/croatian#c,\pghyphenation/croatian#c,\setlanghyphenmins/croatian#c
babelshorthands#true,false
disabledigraphs#true,false
localalph#true,false
splithyphens#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/czech#c,\setmainlanguage/czech#c,\setotherlanguage/czech#c,\textlang/czech#c,\textczech#c,\begin{lang}/czech#c,\begin{czech}#c,\selectlanguage/czech#c,\foreignlanguage/czech#c,\begin{otherlanguage}/czech#c,\begin{otherlanguage*}/czech#c,\resetdefaultlanguage/czech#c,\setlanguagealias/czech#c,\setlanguagealias*/czech#c,\pghyphenation/czech#c,\setlanghyphenmins/czech#c
babelshorthands#true,false
splithyphens#true,false
vlna#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/dutch#c,\setmainlanguage/dutch#c,\setotherlanguage/dutch#c,\textlang/dutch#c,\textdutch#c,\begin{lang}/dutch#c,\begin{dutch}#c,\selectlanguage/dutch#c,\foreignlanguage/dutch#c,\begin{otherlanguage}/dutch#c,\begin{otherlanguage*}/dutch#c,\resetdefaultlanguage/dutch#c,\setlanguagealias/dutch#c,\setlanguagealias*/dutch#c,\pghyphenation/dutch#c,\setlanghyphenmins/dutch#c
babelshorthands#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/english#c,\setmainlanguage/english#c,\setotherlanguage/english#c,\textlang/english#c,\textenglish#c,\begin{lang}/english#c,\begin{english}#c,\selectlanguage/english#c,\foreignlanguage/english#c,\begin{otherlanguage}/english#c,\begin{otherlanguage*}/english#c,\resetdefaultlanguage/english#c,\setlanguagealias/english#c,\setlanguagealias*/english#c,\pghyphenation/english#c,\setlanghyphenmins/english#c
variant=#american,us,usmax,british,uk,australian,canadian,newzealand
ordinalmonthday#true,false
#endkeyvals

\hodiau#*
\hodiaun#*

#keyvals:\setdefaultlanguage/finnish#c,\setmainlanguage/finnish#c,\setotherlanguage/finnish#c,\textlang/finnish#c,\textfinnish#c,\begin{lang}/finnish#c,\begin{finnish}#c,\selectlanguage/finnish#c,\foreignlanguage/finnish#c,\begin{otherlanguage}/finnish#c,\begin{otherlanguage*}/finnish#c,\resetdefaultlanguage/finnish#c,\setlanguagealias/finnish#c,\setlanguagealias*/finnish#c,\pghyphenation/finnish#c,\setlanghyphenmins/finnish#c
babelshorthands#true,false
schoolhyphens#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/french#c,\setmainlanguage/french#c,\setotherlanguage/french#c,\textlang/french#c,\textfrench#c,\begin{lang}/french#c,\begin{french}#c,\selectlanguage/french#c,\foreignlanguage/french#c,\begin{otherlanguage}/french#c,\begin{otherlanguage*}/french#c,\resetdefaultlanguage/french#c,\setlanguagealias/french#c,\setlanguagealias*/french#c,\pghyphenation/french#c,\setlanghyphenmins/french#c
variant=#french,canadian,acadian,swiss
autospacing#true,false
thincolonspace#true,false
autospaceguillemets#true,false
autospacetypewriter#true,false
frenchfootnote#true,false
frenchitemlabels#true,false
frenchpart#true,false
itemlabels=%<code%>
itemlabeli=%<code%>
itemlabelii=%<code%>
itemlabeliii=%<code%>
itemlabeliv=%<code%>
#endkeyvals

\NoAutoSpacing#*
\AutoSpacing#*

#keyvals:\setdefaultlanguage/gaelic#c,\setmainlanguage/gaelic#c,\setotherlanguage/gaelic#c,\textlang/gaelic#c,\textgaelic#c,\begin{lang}/gaelic#c,\begin{gaelic}#c,\selectlanguage/gaelic#c,\foreignlanguage/gaelic#c,\begin{otherlanguage}/gaelic#c,\begin{otherlanguage*}/gaelic#c,\resetdefaultlanguage/gaelic#c,\setlanguagealias/gaelic#c,\setlanguagealias*/gaelic#c,\pghyphenation/gaelic#c,\setlanghyphenmins/gaelic#c
variant=#irish,scottish
#endkeyvals

#keyvals:\setdefaultlanguage/georgian#c,\setmainlanguage/georgian#c,\setotherlanguage/georgian#c,\textlang/georgian#c,\textgeorgian#c,\begin{lang}/georgian#c,\begin{georgian}#c,\selectlanguage/georgian#c,\foreignlanguage/georgian#c,\begin{otherlanguage}/georgian#c,\begin{otherlanguage*}/georgian#c,\resetdefaultlanguage/georgian#c,\setlanguagealias/georgian#c,\setlanguagealias*/georgian#c,\pghyphenation/georgian#c,\setlanghyphenmins/georgian#c
babelshorthands#true,false
numerals=#arabic,georgian
oldmonthnames#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/german#c,\setmainlanguage/german#c,\setotherlanguage/german#c,\textlang/german#c,\textgerman#c,\begin{lang}/german#c,\begin{german}#c,\selectlanguage/german#c,\foreignlanguage/german#c,\begin{otherlanguage}/german#c,\begin{otherlanguage*}/german#c,\resetdefaultlanguage/german#c,\setlanguagealias/german#c,\setlanguagealias*/german#c,\pghyphenation/german#c,\setlanghyphenmins/german#c
variant=#german,austrian,swiss
spelling=#new,old
babelshorthands#true,false
script=#latin,blackletter,fraktur
#endkeyvals

#keyvals:\setdefaultlanguage/greek#c,\setmainlanguage/greek#c,\setotherlanguage/greek#c,\textlang/greek#c,\textgreek#c,\begin{lang}/greek#c,\begin{greek}#c,\selectlanguage/greek#c,\foreignlanguage/greek#c,\begin{otherlanguage}/greek#c,\begin{otherlanguage*}/greek#c,\resetdefaultlanguage/greek#c,\setlanguagealias/greek#c,\setlanguagealias*/greek#c,\pghyphenation/greek#c,\setlanghyphenmins/greek#c
variant=#monotonic,mono,polytonic,poly,ancient
numerals=#greek,arabic
attic#true,false
#endkeyvals

\Greeknumber{number}#S
\greeknumber{number}#S
\atticnumeral#*
\atticnum#S

#keyvals:\setdefaultlanguage/hebrew#c,\setmainlanguage/hebrew#c,\setotherlanguage/hebrew#c,\textlang/hebrew#c,\texthebrew#c,\begin{lang}/hebrew#c,\begin{hebrew}#c,\selectlanguage/hebrew#c,\foreignlanguage/hebrew#c,\begin{otherlanguage}/hebrew#c,\begin{otherlanguage*}/hebrew#c,\resetdefaultlanguage/hebrew#c,\setlanguagealias/hebrew#c,\setlanguagealias*/hebrew#c,\pghyphenation/hebrew#c,\setlanghyphenmins/hebrew#c
fullyear#true,false
numerals=#hebrew,arabic
calendar=#hebrew,gregorian
marcheshvan#true,false
transliteration=#academy,alt
#endkeyvals

\hebrewnumeral{text}#*
\hebrewalph{text}#*

#keyvals:\setdefaultlanguage/hindi#c,\setmainlanguage/hindi#c,\setotherlanguage/hindi#c,\textlang/hindi#c,\texthindi#c,\begin{lang}/hindi#c,\begin{hindi}#c,\selectlanguage/hindi#c,\foreignlanguage/hindi#c,\begin{otherlanguage}/hindi#c,\begin{otherlanguage*}/hindi#c,\resetdefaultlanguage/hindi#c,\setlanguagealias/hindi#c,\setlanguagealias*/hindi#c,\pghyphenation/hindi#c,\setlanghyphenmins/hindi#c
numerals=#Western,Devanagari
#endkeyvals

#keyvals:\setdefaultlanguage/hungarian#c,\setmainlanguage/hungarian#c,\setotherlanguage/hungarian#c,\textlang/hungarian#c,\texthungarian#c,\begin{lang}/hungarian#c,\begin{hungarian}#c,\selectlanguage/hungarian#c,\foreignlanguage/hungarian#c,\begin{otherlanguage}/hungarian#c,\begin{otherlanguage*}/hungarian#c,\resetdefaultlanguage/hungarian#c,\setlanguagealias/hungarian#c,\setlanguagealias*/hungarian#c,\pghyphenation/hungarian#c,\setlanghyphenmins/hungarian#c
swapstrings=#all,captions,headings,headers,hheaders,none
forceheadingpunctuation#true,false
#endkeyvals

\ontoday#*
\ondatehungarian#*

#keyvals:\setdefaultlanguage/italian#c,\setmainlanguage/italian#c,\setotherlanguage/italian#c,\textlang/italian#c,\textitalian#c,\begin{lang}/italian#c,\begin{italian}#c,\selectlanguage/italian#c,\foreignlanguage/italian#c,\begin{otherlanguage}/italian#c,\begin{otherlanguage*}/italian#c,\resetdefaultlanguage/italian#c,\setlanguagealias/italian#c,\setlanguagealias*/italian#c,\pghyphenation/italian#c,\setlanghyphenmins/italian#c
babelshorthands#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/korean#c,\setmainlanguage/korean#c,\setotherlanguage/korean#c,\textlang/korean#c,\textkorean#c,\begin{lang}/korean#c,\begin{korean}#c,\selectlanguage/korean#c,\foreignlanguage/korean#c,\begin{otherlanguage}/korean#c,\begin{otherlanguage*}/korean#c,\resetdefaultlanguage/korean#c,\setlanguagealias/korean#c,\setlanguagealias*/korean#c,\pghyphenation/korean#c,\setlanghyphenmins/korean#c
variant=#plain,classic,modern
captions=#hangul,hanja
swapstrings=#all,headers,headings,none
#endkeyvals

#keyvals:\setdefaultlanguage/kurdish#c,\setmainlanguage/kurdish#c,\setotherlanguage/kurdish#c,\textlang/kurdish#c,\textkurdish#c,\begin{lang}/kurdish#c,\begin{kurdish}#c,\selectlanguage/kurdish#c,\foreignlanguage/kurdish#c,\begin{otherlanguage}/kurdish#c,\begin{otherlanguage*}/kurdish#c,\resetdefaultlanguage/kurdish#c,\setlanguagealias/kurdish#c,\setlanguagealias*/kurdish#c,\pghyphenation/kurdish#c,\setlanghyphenmins/kurdish#c
variant=#kurmanji,sorani
script=#Arabic,Latin
numerals=#western,eastern
abjadjimnotail#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/lao#c,\setmainlanguage/lao#c,\setotherlanguage/lao#c,\textlang/lao#c,\textlao#c,\begin{lang}/lao#c,\begin{lao}#c,\selectlanguage/lao#c,\foreignlanguage/lao#c,\begin{otherlanguage}/lao#c,\begin{otherlanguage*}/lao#c,\resetdefaultlanguage/lao#c,\setlanguagealias/lao#c,\setlanguagealias*/lao#c,\pghyphenation/lao#c,\setlanghyphenmins/lao#c
numerals=#lao,arabic
#endkeyvals

#keyvals:\setdefaultlanguage/latin#c,\setmainlanguage/latin#c,\setotherlanguage/latin#c,\textlang/latin#c,\textlatin#c,\begin{lang}/latin#c,\begin{latin}#c,\selectlanguage/latin#c,\foreignlanguage/latin#c,\begin{otherlanguage}/latin#c,\begin{otherlanguage*}/latin#c,\resetdefaultlanguage/latin#c,\setlanguagealias/latin#c,\setlanguagealias*/latin#c,\pghyphenation/latin#c,\setlanghyphenmins/latin#c
variant=#classic,medieval,modern,ecclesiastic
hyphenation=#classic,modern,liturgical
ecclesiasticfootnotes#true,false
usej#true,false
capitalizemonth#true,false
babelshorthands#true,false
prosodicshorthands#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/malay#c,\setmainlanguage/malay#c,\setotherlanguage/malay#c,\textlang/malay#c,\textmalay#c,\begin{lang}/malay#c,\begin{malay}#c,\selectlanguage/malay#c,\foreignlanguage/malay#c,\begin{otherlanguage}/malay#c,\begin{otherlanguage*}/malay#c,\resetdefaultlanguage/malay#c,\setlanguagealias/malay#c,\setlanguagealias*/malay#c,\pghyphenation/malay#c,\setlanghyphenmins/malay#c
variant=#indonesian,malaysian
#endkeyvals

#keyvals:\setdefaultlanguage/marathi#c,\setmainlanguage/marathi#c,\setotherlanguage/marathi#c,\textlang/marathi#c,\textmarathi#c,\begin{lang}/marathi#c,\begin{marathi}#c,\selectlanguage/marathi#c,\foreignlanguage/marathi#c,\begin{otherlanguage}/marathi#c,\begin{otherlanguage*}/marathi#c,\resetdefaultlanguage/marathi#c,\setlanguagealias/marathi#c,\setlanguagealias*/marathi#c,\pghyphenation/marathi#c,\setlanghyphenmins/marathi#c
numerals=#Devanagari,Western
#endkeyvals

#keyvals:\setdefaultlanguage/mongolian#c,\setmainlanguage/mongolian#c,\setotherlanguage/mongolian#c,\textlang/mongolian#c,\textmongolian#c,\begin{lang}/mongolian#c,\begin{mongolian}#c,\selectlanguage/mongolian#c,\foreignlanguage/mongolian#c,\begin{otherlanguage}/mongolian#c,\begin{otherlanguage*}/mongolian#c,\resetdefaultlanguage/mongolian#c,\setlanguagealias/mongolian#c,\setlanguagealias*/mongolian#c,\pghyphenation/mongolian#c,\setlanghyphenmins/mongolian#c
babelshorthands#true,false
numerals=#arabic,cyrillic-alph,cyrillic-trad
#endkeyvals

#keyvals:\setdefaultlanguage/norwegian#c,\setmainlanguage/norwegian#c,\setotherlanguage/norwegian#c,\textlang/norwegian#c,\textnorwegian#c,\begin{lang}/norwegian#c,\begin{norwegian}#c,\selectlanguage/norwegian#c,\foreignlanguage/norwegian#c,\begin{otherlanguage}/norwegian#c,\begin{otherlanguage*}/norwegian#c,\resetdefaultlanguage/norwegian#c,\setlanguagealias/norwegian#c,\setlanguagealias*/norwegian#c,\pghyphenation/norwegian#c,\setlanghyphenmins/norwegian#c
variant=#bokmal,nynorsk
#endkeyvals

#keyvals:\setdefaultlanguage/persian#c,\setmainlanguage/persian#c,\setotherlanguage/persian#c,\textlang/persian#c,\textpersian#c,\begin{lang}/persian#c,\begin{persian}#c,\selectlanguage/persian#c,\foreignlanguage/persian#c,\begin{otherlanguage}/persian#c,\begin{otherlanguage*}/persian#c,\resetdefaultlanguage/persian#c,\setlanguagealias/persian#c,\setlanguagealias*/persian#c,\pghyphenation/persian#c,\setlanghyphenmins/persian#c
numerals=#western,eastern
abjadjimnotail#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/polish#c,\setmainlanguage/polish#c,\setotherlanguage/polish#c,\textlang/polish#c,\textpolish#c,\begin{lang}/polish#c,\begin{polish}#c,\selectlanguage/polish#c,\foreignlanguage/polish#c,\begin{otherlanguage}/polish#c,\begin{otherlanguage*}/polish#c,\resetdefaultlanguage/polish#c,\setlanguagealias/polish#c,\setlanguagealias*/polish#c,\pghyphenation/polish#c,\setlanghyphenmins/polish#c
babelshorthands#true,false
splithyphens#true,false
vlna#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/portuguese#c,\setmainlanguage/portuguese#c,\setotherlanguage/portuguese#c,\textlang/portuguese#c,\textportuguese#c,\begin{lang}/portuguese#c,\begin{portuguese}#c,\selectlanguage/portuguese#c,\foreignlanguage/portuguese#c,\begin{otherlanguage}/portuguese#c,\begin{otherlanguage*}/portuguese#c,\resetdefaultlanguage/portuguese#c,\setlanguagealias/portuguese#c,\setlanguagealias*/portuguese#c,\pghyphenation/portuguese#c,\setlanghyphenmins/portuguese#c
variant=#brazilian,portuguese
babelshorthands#true,false
splithyphens#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/punjabi#c,\setmainlanguage/punjabi#c,\setotherlanguage/punjabi#c,\textlang/punjabi#c,\textpunjabi#c,\begin{lang}/punjabi#c,\begin{punjabi}#c,\selectlanguage/punjabi#c,\foreignlanguage/punjabi#c,\begin{otherlanguage}/punjabi#c,\begin{otherlanguage*}/punjabi#c,\resetdefaultlanguage/punjabi#c,\setlanguagealias/punjabi#c,\setlanguagealias*/punjabi#c,\pghyphenation/punjabi#c,\setlanghyphenmins/punjabi#c
numerals=#western,gurmukhi
#endkeyvals

#keyvals:\setdefaultlanguage/russian#c,\setmainlanguage/russian#c,\setotherlanguage/russian#c,\textlang/russian#c,\textrussian#c,\begin{lang}/russian#c,\begin{russian}#c,\selectlanguage/russian#c,\foreignlanguage/russian#c,\begin{otherlanguage}/russian#c,\begin{otherlanguage*}/russian#c,\resetdefaultlanguage/russian#c,\setlanguagealias/russian#c,\setlanguagealias*/russian#c,\pghyphenation/russian#c,\setlanghyphenmins/russian#c
babelshorthands#true,false
forceheadingpunctuation#true,false
indentfirst#true,false
mathfunctions#true,false
spelling=#modern,old
numerals=#arabic,cyrillic-alph,cyrillic-trad
#endkeyvals

#keyvals:\setdefaultlanguage/sanskrit#c,\setmainlanguage/sanskrit#c,\setotherlanguage/sanskrit#c,\textlang/sanskrit#c,\textsanskrit#c,\begin{lang}/sanskrit#c,\begin{sanskrit}#c,\selectlanguage/sanskrit#c,\foreignlanguage/sanskrit#c,\begin{otherlanguage}/sanskrit#c,\begin{otherlanguage*}/sanskrit#c,\resetdefaultlanguage/sanskrit#c,\setlanguagealias/sanskrit#c,\setlanguagealias*/sanskrit#c,\pghyphenation/sanskrit#c,\setlanghyphenmins/sanskrit#c
script=#Devanagari,Gujarati,Malayalam,Bengali,Kannada,Telugu,Latin
numerals=#Devanagari,Western
#endkeyvals

#keyvals:\setdefaultlanguage/serbian#c,\setmainlanguage/serbian#c,\setotherlanguage/serbian#c,\textlang/serbian#c,\textserbian#c,\begin{lang}/serbian#c,\begin{serbian}#c,\selectlanguage/serbian#c,\foreignlanguage/serbian#c,\begin{otherlanguage}/serbian#c,\begin{otherlanguage*}/serbian#c,\resetdefaultlanguage/serbian#c,\setlanguagealias/serbian#c,\setlanguagealias*/serbian#c,\pghyphenation/serbian#c,\setlanghyphenmins/serbian#c
script=#Cyrillic,Latin
splithyphens#true,false
numerals=#arabic,cyrillic-alph,cyrillic-trad
#endkeyvals

#keyvals:\setdefaultlanguage/slovak#c,\setmainlanguage/slovak#c,\setotherlanguage/slovak#c,\textlang/slovak#c,\textslovak#c,\begin{lang}/slovak#c,\begin{slovak}#c,\selectlanguage/slovak#c,\foreignlanguage/slovak#c,\begin{otherlanguage}/slovak#c,\begin{otherlanguage*}/slovak#c,\resetdefaultlanguage/slovak#c,\setlanguagealias/slovak#c,\setlanguagealias*/slovak#c,\pghyphenation/slovak#c,\setlanghyphenmins/slovak#c
babelshorthands#true,false
splithyphens#true,false
vlna#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/slovenian#c,\setmainlanguage/slovenian#c,\setotherlanguage/slovenian#c,\textlang/slovenian#c,\textslovenian#c,\begin{lang}/slovenian#c,\begin{slovenian}#c,\selectlanguage/slovenian#c,\foreignlanguage/slovenian#c,\begin{otherlanguage}/slovenian#c,\begin{otherlanguage*}/slovenian#c,\resetdefaultlanguage/slovenian#c,\setlanguagealias/slovenian#c,\setlanguagealias*/slovenian#c,\pghyphenation/slovenian#c,\setlanghyphenmins/slovenian#c
localalph#true,false
#endkeyvals

#keyvals:\setdefaultlanguage/sorbian#c,\setmainlanguage/sorbian#c,\setotherlanguage/sorbian#c,\textlang/sorbian#c,\textsorbian#c,\begin{lang}/sorbian#c,\begin{sorbian}#c,\selectlanguage/sorbian#c,\foreignlanguage/sorbian#c,\begin{otherlanguage}/sorbian#c,\begin{otherlanguage*}/sorbian#c,\resetdefaultlanguage/sorbian#c,\setlanguagealias/sorbian#c,\setlanguagealias*/sorbian#c,\pghyphenation/sorbian#c,\setlanghyphenmins/sorbian#c
variant=#lower,upper
olddate#true,false
#endkeyvals

\oldtoday#*

#keyvals:\setdefaultlanguage/spanish#c,\setmainlanguage/spanish#c,\setotherlanguage/spanish#c,\textlang/spanish#c,\textspanish#c,\begin{lang}/spanish#c,\begin{spanish}#c,\selectlanguage/spanish#c,\foreignlanguage/spanish#c,\begin{otherlanguage}/spanish#c,\begin{otherlanguage*}/spanish#c,\resetdefaultlanguage/spanish#c,\setlanguagealias/spanish#c,\setlanguagealias*/spanish#c,\pghyphenation/spanish#c,\setlanghyphenmins/spanish#c
variant=#spanish,mexican
spanishoperators=#all,accented,spaced,none,false
#endkeyvals

\arcsen#*m
\arctg#*m
\sen#*m
\senh#*m
\tg#*m
\tgh#*m
\spanishoperator{name}#*

#keyvals:\setdefaultlanguage/syriac#c,\setmainlanguage/syriac#c,\setotherlanguage/syriac#c,\textlang/syriac#c,\textsyriac#c,\begin{lang}/syriac#c,\begin{syriac}#c,\selectlanguage/syriac#c,\foreignlanguage/syriac#c,\begin{otherlanguage}/syriac#c,\begin{otherlanguage*}/syriac#c,\resetdefaultlanguage/syriac#c,\setlanguagealias/syriac#c,\setlanguagealias*/syriac#c,\pghyphenation/syriac#c,\setlanghyphenmins/syriac#c
numerals=#western,eastern,abjad
#endkeyvals

\abjadsyriac{text}#*

#keyvals:\setdefaultlanguage/thai#c,\setmainlanguage/thai#c,\setotherlanguage/thai#c,\textlang/thai#c,\textthai#c,\begin{lang}/thai#c,\begin{thai}#c,\selectlanguage/thai#c,\foreignlanguage/thai#c,\begin{otherlanguage}/thai#c,\begin{otherlanguage*}/thai#c,\resetdefaultlanguage/thai#c,\setlanguagealias/thai#c,\setlanguagealias*/thai#c,\pghyphenation/thai#c,\setlanghyphenmins/thai#c
numerals=#thai,arabic
#endkeyvals

#keyvals:\setdefaultlanguage/tibetan#c,\setmainlanguage/tibetan#c,\setotherlanguage/tibetan#c,\textlang/tibetan#c,\texttibetan#c,\begin{lang}/tibetan#c,\begin{tibetan}#c,\selectlanguage/tibetan#c,\foreignlanguage/tibetan#c,\begin{otherlanguage}/tibetan#c,\begin{otherlanguage*}/tibetan#c,\resetdefaultlanguage/tibetan#c,\setlanguagealias/tibetan#c,\setlanguagealias*/tibetan#c,\pghyphenation/tibetan#c,\setlanghyphenmins/tibetan#c
numerals=#tibetan,arabic
#endkeyvals

#keyvals:\setdefaultlanguage/ukrainian#c,\setmainlanguage/ukrainian#c,\setotherlanguage/ukrainian#c,\textlang/ukrainian#c,\textukrainian#c,\begin{lang}/ukrainian#c,\begin{ukrainian}#c,\selectlanguage/ukrainian#c,\foreignlanguage/ukrainian#c,\begin{otherlanguage}/ukrainian#c,\begin{otherlanguage*}/ukrainian#c,\resetdefaultlanguage/ukrainian#c,\setlanguagealias/ukrainian#c,\setlanguagealias*/ukrainian#c,\pghyphenation/ukrainian#c,\setlanghyphenmins/ukrainian#c
babelshorthands#true,false
mathfunctions#true,false
numerals=#arabic,cyrillic-alph,cyrillic-trad
#endkeyvals

#keyvals:\setdefaultlanguage/uyghur#c,\setmainlanguage/uyghur#c,\setotherlanguage/uyghur#c,\textlang/uyghur#c,\textuyghur#c,\begin{lang}/uyghur#c,\begin{uyghur}#c,\selectlanguage/uyghur#c,\foreignlanguage/uyghur#c,\begin{otherlanguage}/uyghur#c,\begin{otherlanguage*}/uyghur#c,\resetdefaultlanguage/uyghur#c,\setlanguagealias/uyghur#c,\setlanguagealias*/uyghur#c,\pghyphenation/uyghur#c,\setlanghyphenmins/uyghur#c
chapterformat=#ordinal,roman,arabic
swapstrings=#all,captions,heading,headers,hheaders,none
#endkeyvals

\uyghurordinal{number}
\uyghurord{counter}

#keyvals:\setdefaultlanguage/welsh#c,\setmainlanguage/welsh#c,\setotherlanguage/welsh#c,\textlang/welsh#c,\textwelsh#c,\begin{lang}/welsh#c,\begin{welsh}#c,\selectlanguage/welsh#c,\foreignlanguage/welsh#c,\begin{otherlanguage}/welsh#c,\begin{otherlanguage*}/welsh#c,\resetdefaultlanguage/welsh#c,\setlanguagealias/welsh#c,\setlanguagealias*/welsh#c,\pghyphenation/welsh#c,\setlanghyphenmins/welsh#c
date=#long,short
#endkeyvals

\captionsafrikaans#*
\captionsalbanian#*
\captionsamharic#*
\captionsarabic#*
\captionsarmenian#*
\captionsasturian#*
\captionsbasque#*
\captionsbelarusian#*
\captionsbengali#*
\captionsbosnian#*
\captionsbreton#*
\captionsbulgarian#*
\captionscatalan#*
\captionschinese#*
\captionscoptic#*
\captionscroatian#*
\captionsczech#*
\captionsdanish#*
\captionsdivehi#*
\captionsdutch#*
\captionsenglish#*
\captionsesperanto#*
\captionsestonian#*
\captionsfinnish#*
\captionsfrench#*
\captionsfriulian#*
\captionsgaelic#*
\captionsgalician#*
\captionsgeorgian#*
\captionsgerman#*
\captionsgreek#*
\captionshebrew#*
\captionshindi#*
\captionshungarian#*
\captionsicelandic#*
\captionsinterlingua#*
\captionsitalian#*
\captionsjapanese#*
\captionskannada#*
\captionskhmer#*
\captionskorean#*
\captionskurdish#*
\captionslao#*
\captionslatin#*
\captionslatvian#*
\captionslithuanian#*
\captionsmacedonian#*
\captionsmalay#*
\captionsmalayalam#*
\captionsmarathi#*
\captionsmongolian#*
\captionsnko#*
\captionsnorwegian#*
\captionsoccitan#*
\captionspersian#*
\captionspiedmontese#*
\captionspolish#*
\captionsportuguese#*
\captionspunjabi#*
\captionsromanian#*
\captionsromansh#*
\captionsrussian#*
\captionssami#*
\captionssanskrit#*
\captionsserbian#*
\captionsslovak#*
\captionsslovenian#*
\captionssorbian#*
\captionsspanish#*
\captionsswedish#*
\captionssyriac#*
\captionstamil#*
\captionstelugu#*
\captionsthai#*
\captionstibetan#*
\captionsturkish#*
\captionsturkmen#*
\captionsukrainian#*
\captionsurdu#*
\captionsuyghur#*
\captionsvietnamese#*
\captionswelsh#*

\dateafrikaans#*
\datealbanian#*
\dateamharic#*
\datearabic#*
\datearmenian#*
\dateasturian#*
\datebasque#*
\datebelarusian#*
\datebengali#*
\datebosnian#*
\datebreton#*
\datebulgarian#*
\datecatalan#*
\datechinese#*
\datecoptic#*
\datecroatian#*
\dateczech#*
\datedanish#*
\datedivehi#*
\datedutch#*
\dateenglish#*
\dateesperanto#*
\dateestonian#*
\datefinnish#*
\datefrench#*
\datefriulian#*
\dategaelic#*
\dategalician#*
\dategeorgian#*
\dategerman#*
\dategreek#*
\datehebrew#*
\datehindi#*
\datehungarian#*
\dateicelandic#*
\dateinterlingua#*
\dateitalian#*
\datejapanese#*
\datekannada#*
\datekhmer#*
\datekorean#*
\datekurdish#*
\datelao#*
\datelatin#*
\datelatvian#*
\datelithuanian#*
\datemacedonian#*
\datemalay#*
\datemalayalam#*
\datemarathi#*
\datemongolian#*
\datenko#*
\datenorwegian#*
\dateoccitan#*
\datepersian#*
\datepiedmontese#*
\datepolish#*
\dateportuguese#*
\datepunjabi#*
\dateromanian#*
\dateromansh#*
\daterussian#*
\datesami#*
\datesanskrit#*
\dateserbian#*
\dateslovak#*
\dateslovenian#*
\datesorbian#*
\datespanish#*
\dateswedish#*
\datesyriac#*
\datetamil#*
\datetelugu#*
\datethai#*
\datetibetan#*
\dateturkish#*
\dateturkmen#*
\dateukrainian#*
\dateurdu#*
\dateuyghur#*
\datevietnamese#*
\datewelsh#*

\localnumeral{number}#*
\localnumeral[option%keyvals]{number}#*
\localnumeral*{counter}#*
\localnumeral*[option%keyvals]{counter}#*
\Localnumeral{number}#*
\Localnumeral[option%keyvals]{number}#*
\Localnumeral*{counter}#*
\Localnumeral*[option%keyvals]{counter}#*

#keyvals:\localnumeral#c,\localnumeral*#c,\Localnumeral#c,\Localnumeral*#c
lang=#local,main,%<language%>
#endkeyvals

\arabicdigits{text}#*
\bengalidigits{text}#*
\devanagaridigits{text}#*
\farsidigits{text}#*
\gurmukhidigits{text}#*
\kannadadigits{text}#*
\khmerdigits{text}#*
\laodigits{text}#*
\nkodigits{text}#*
\thaidigits{text}#*
\tibetandigits{text}#*
\armeniannumeral{number}#*
\belarusiannumeral{number}#*
\Belarusiannumeral{number}#*
\chinesenumeral{number}#*
\georgiannumeral{number}#*
\greeknumeral{number}#*
\Greeknumeral{number}#*
\hebrewnumeral{number}#*
\Hebrewnumeral{number}#*
\Hebrewnumeralfinal{number}#*
\mongoliannumeral{number}#*
\Mongoliannumeral{number}#*
\punjabinumeral{number}#*
\russiannumeral{number}#*
\Russiannumeral{number}#*
\serbiannumeral{number}#*
\Serbiannumeral{number}#*
\ukrainiannumeral{number}#*
\Ukrainiannumeral{number}#*

\RTLfootnote{text}#*
\LTRfootnote{text}#*

\leftfootnoterule#*
\rightfootnoterule#*
\autofootnoterule#*
\textwidthfootnoterule#*

\charifavailable{char code}{substitution}#*
\BCPdata{type}#*
\languagename#*
\mainlanguagename#*
\languagevariant#*
\mainlanguagevariant#*
\babelname#*
\mainbabelname#*
\languageid{type}#*
\mainlanguageid{type}#*
\iflanguageloaded{language}{true}{false}#*
\ifbabellanguageloaded{language}{true}{false}#*
\iflanguageidloaded{type}{id}{true}{false}#*
\iflanguageoption{language}{opt key}{opt value}{true}{false}#*
\setforeignlanguage{language}#S
\ifxpglanginaux#S
\xpglanginauxfalse#S
\xpglanginauxtrue#S

## undocumented commands from gloss-*.ldf files
# shared commands
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*

# from gloss-amharic.ldf
\ethiop{arg}#S
\ethnum{arg}#S

# from gloss-catalan.ldf
\leftllkern#S
\rightllkern#S
\raiselldim#S
\lgem#S
\Lgem#S
\lslash#S
\Lslash#S

# from gloss-chinese.ldf
\chinesenumber{number}#S

# from gloss-french.ldf
\ier#S
\iers#S
\iere#S
\ieres#S
\ieme#S
\iemes#S
\nd#S
\nds#S
\nde#S
\ndes#S
\no#S
\nos#S
\mme#S
\mmes#S
\mr#S
\mrs#S

# from gloss-greek.ldf
\monogreekcaptions#S
\datemonogreek#S
\polygreekcaptions#S
\datepolygreek#S
\greektoday#S
\Greektoday#S
\ancientgreekcaptions#S
\dateancientgreek#S

# from gloss-korean.ldf
\koreanAlph{counter}#S
\koreanalph{counter}#S

# from gloss-kurdish.ldf
\kurdishmonthkurmanji{number}#S

# from gloss-hebrew.ldf
\hebrewgregmonth{number}#S

# from gloss-macedonian.ldf
\todayRoman#S

# from gloss-malay.ldf
\hijrimonthmalay#S

# from gloss-occitan.ldf
\occitanday#S

# from gloss-persian.ldf
\farsigregmonth{number}#S
\farsimonth{number}#S

# from gloss-punjabi.ldf
\punjabinumber{number}#S

# from gloss-nko.ldf
\nkodayprefix{number}#S
\nkoday{number}#S

# from gloss-slovenian.ldf
\abeceda{counter}#S
\Abeceda{counter}#S

# from gloss-thai.ldf
\wbr#S

# from gloss-turkish.ldf
\hijrimonthturkish{number}#S

# from gloss-urdu.ldf
\urdugregmonth{number}#S
\urduhijrimonth{number}#S

# from gloss-uyghur.ldf
\uyghurmonth{number}#S

# from gloss-welsh.ldf
\formaltoday#S
\standardtoday#S
