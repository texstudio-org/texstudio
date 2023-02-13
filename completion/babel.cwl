# babel.sty
# available from ctan
# tbraun 4.11.2008; Matthew Bertucci 2023/02/13 for v3.86

#keyvals:\usepackage/babel#c
%<language%>
KeepShorthandsActive
activeacute
activegrave
shorthands=#%<chars%>,off
safe=#none,ref,bib
math=#active,normal
config=%<file%>
main=%<language%>
headfoot=%<language%>
noconfigs
showlanguages
nocase
silent
strings=#generic,unicode,encoded,%<label%>,%<font encoding%>
hyphenmap=#off,first,select,other,other*
bidi=#default,basic,basic-r,bidi-l,bidi-r
layout=#sectioning,counters,counters*,contents,footnotes,captions,columns,graphics,extras
provide=*
provide+=*
provide*=*
base
ensureinfo=off
#endkeyvals

\selectlanguage{language}
\begin{selectlanguage}{language}#*
\end{selectlanguage}#*
\foreignlanguage{language}{text}
\foreignlanguage[options%keyvals]{language}{text}
\begin{otherlanguage}{language}
\end{otherlanguage}
\begin{otherlanguage*}{language}
\begin{otherlanguage*}[options%keyvals]{language}
\end{otherlanguage*}

#keyvals:\foreignlanguage,\begin{otherlanguage*}
date
captions
#endkeyvals

\babeltags{tag1=lang1,tag2=lang2,...}
\babelensure{language}
\babelensure[options%keyvals]{language}

#keyvals:\babelensure
include=%<commands%>
exclude=%<commands%>
fontenc=%<encoding%>
#endkeyvals

\shorthandon{characters}
\shorthandoff{characters}
\shorthandoff*{characters}
\useshorthands{char}
\useshorthands*{char}
\defineshorthand{shorthand}{code}
\defineshorthand[lang1,lang2,...]{shorthand}{code}
\languageshorthands{language}
\babelshorthand{shorthand}
\ifbabelshorthand{character}{true}{false}
\aliasshorthand{original}{alias}
\textormath{text code}{math code%formula}#*

#ifOption:base
\AfterBabelLanguage{option_name}{code}
#endif

\babelfont{font_family}{font_name}
\babelfont{font_family}[font_options%keyvals]{font_name}
\babelfont[lang1,lang2,...]{font_family}{font_name}
\babelfont[lang1,lang2,...]{font_family}[font_options%keyvals]{font_name}

#keyvals:\babelfont#c
Alternate=%<feature%>
Annotation=
AutoFakeBold=%<number%>
AutoFakeSlant=%<number%>
BoldFeatures={%<features%>}
BoldFont=%<font name%>
BoldItalicFeatures={%<features%>}
BoldItalicFont=%<font name%>
BoldSlantedFeatures={%<features%>}
BoldSlantedFont=%<font name%>
BoldSwashFeatures={%<features%>}
BoldSwashFont=%<font name%>
CJKShape=#Traditional,Simplified,JIS1978,JIS1983,JIS1990,Expert,NLC
CharacterVariant={%<glyph num list%>:%<variety num%>}
CharacterWidth=#Proportional,Full,Half,Thurd,Quarter,AlternateProportional,AlternateHalf,ResetAll
Color=#%color
Colour=#%color
Contextuals=#Swash,SwashOff,Alternate,AlternateOff,WordInitial,WordInitialOff,WordFinal,WordFinalOff,LineFinal,LineFinalOff,Inner,InnerOff,ResetAll
Diacritics=#MarkToBase,MarkToMark,AboveBase,BelowBase,ResetAll
Extension=%<extension%>
FakeBold=%<number%>
FakeSlant=%<number%>
FakeStretch=%<number%>
Font=%<font name%>
FontFace={%<series%>}{%<shape%>}{%<font name%>}
Fractions=#On,Off,Reset,Alternate,ResetAll
HyphenChar=%<character%>
IgnoreFontspecFile
ItalicFeatures={%<features%>}
ItalicFont=%<font name%>
Kerning=#On,Off,Reset,Uppercase,ResetAll
Language=%<language%>
LetterSpace=%<number%>
Letters=#SmallCaps,PetiteCaps,UppercaseSmallCaps,UppercasePetiteCaps,Unicase,ResetAll
Ligatures=#Required,Common,Contextual,Rare,Discretionary,Historic,TeX
LocalForms=#On,Off,Reset
NFSSFamily=%<font family%>
Numbers=#Uppercase,UppercaseOff,Lowercase,LowercaseOff,Lining,LiningOff,OldStyle,OldStyleOff,Proportional,ProportionalOff,Monospaced,MonospacedOff,SlashedZero,SlashedZeroOff,Arabic,ArabicOff,ResetAll
Opacity=%<factor%>
OpticalSize=%<size%>
Ornament=
Path=%<file path%>
PunctuationSpace=%<number%>
RawFeature=%<feature tag%>
Scale=%<number%>
ScaleAgain=%<number%>
Script=%<name%>
Size=%<number%>
SizeFeatures={%<features%>}
SlantedFeatures={%<features%>}
SlantedFont=%<font name%>
SmallCapsFeatures={%<features%>}
SmallCapsFont=%<font name%>
Style=#Alternate,Italic,Ruby,Swash,Cursive,Historic,Titling,Uppercase,HorizontalKana,VerticalKana,ResetAll
StylisticAlternates=%<feature%>
StylisticSet=%<set number%>
SwashFeatures={%<features%>}
SwashFont=%<font name%>
UprightFeatures={%<features%>}
UprightFont=%<font name%>
Variant=%<integer%>
Vertical=#RotatedGlyphs,AlternatesForRotation,Alternates,KanaAlternates,Kerning,AlternateMetrics,HalfMetrics,ProportionalMetrics,ResetAll
VerticalPosition=#Superior,Inferior,Numerator,Denominator,ScientificInferior,Ordinal,ResetAll
WordSpace=%<number%>
Mapping=%<xetex-only feature%>
Renderer=%<renderer%>
#endkeyvals

\setlocalecaption{language}{caption_name}{string}#*
\babelprovide[options%keyvals]{language}

#keyvals:\babelprovide#c
import
import=%<language tag%>
captions=%<language tag%>
hyphenrules=%<language list%>
main
script=%<script name%>
language=%<language name%>
alph=%<counter%>
Alph=%<counter%>
onchar=#ids,fonts,letters
intraspace=%<base shrink stretch%>
intrapenalty=%<penalty%>
transforms=#transliteration.dad,digraphs.ligatures,hyphen.repeat,oneletter.nobreak,prehyphen.nobreak,diaeresis.hyphen,transliteration.omega,sigma.final,transliteration.hk,punctuation.space,digraphs.hyphen,danda.nobreak,letters.noj,letters.uv,transliteration.iast,transliteration.gajica,kashida.plain
justification=#kashida,elongated,unhyphenated,padding
linebreaking=#kashida,elongated,unhyphenated,padding
mapfont=
maparabic
mapdigits
calendar=%<calendar%>
calendar=%<calendar%>.%<variant%>
#endkeyvals

\localenumeral{style}{number}
\localecounter{style}{counter}
\localedate{year}{month}{day}
\localedate[options%keyvals]{year}{month}{day}

#keyvals:\localedate
calendar=%<calendar%>
variant=%<variant%>
convert
#endkeyvals

\babelcalendar{calendar}{year-macro%cmd}{month-macro%cmd}{day-macro%cmd}#d
\babelcalendar[YYYY-MM-DD]{calendar}{year-macro%cmd}{month-macro%cmd}{day-macro%cmd}#d

\languagename
\iflanguage{language}{true}{false}
\localeinfo{field%keyvals}
\localeinfo*{field%keyvals}

#keyvals:\localeinfo#c,\localeinfo*#c
name.english
tag.ini
tag.bcp47
language.tag.bcp47
tag.opentype
script.name
script.tag.bcp47
script.tag.opentype
region.tag.bcp47
variant.tag.bcp47
extension.x.tag.bcp47
extension.t.tag.bcp47
extension.u.tag.bcp47
#endkeyvals

\getlocaleproperty{cmd}{locale}{property}#*d
\getlocaleproperty*{cmd}{locale}{property}#*d
\LocaleForEach{code}#*
\BabelEnsureInfo#*
\localeid#*

\babelhyphen{text}
\babelhyphen*{text}
\babelnullhyphen#*
\babelhyphenation{exceptions}#*
\babelhyphenation[lang1,lang2,...]{exceptions}#*
\begin{hyphenrules}{language}
\end{hyphenrules}
\babelpatterns{patterns}#*
\babelpatterns[lang1,lang2,...]{patterns}#*

\babelposthyphenation{hypenrules-name}{lua-pattern}{replacement}#*
\babelposthyphenation[options%keyvals]{hypenrules-name}{lua-pattern}{replacement}#*
\babelprehyphenation{locale-name}{lua-pattern}{replacement}#*
\babelprehyphenation[options%keyvals]{locale-name}{lua-pattern}{replacement}#*

#keyvals:\babelposthyphenation#c,\babelprehyphenation#c
label=#transliteration.dad,digraphs.ligatures,hyphen.repeat,oneletter.nobreak,prehyphen.nobreak,diaeresis.hyphen,transliteration.omega,sigma.final,transliteration.hk,punctuation.space,digraphs.hyphen,danda.nobreak,letters.noj,letters.uv,transliteration.iast,transliteration.gajica,kashida.plain
fonts=%<tag1 tag2 ...%>
attribute=%<attribute%>
#endkeyvals

\enablelocaletransform{transform%keyvals}
\disablelocaletransform{transform%keyvals}

#keyvals:\enablelocaletransform,\disablelocaletransform
transliteration.dad
digraphs.ligatures
hyphen.repeat
oneletter.nobreak
prehyphen.nobreak
diaeresis.hyphen
transliteration.omega
sigma.final
transliteration.hk
punctuation.space
digraphs.hyphen
danda.nobreak
letters.noj
letters.uv
transliteration.iast
transliteration.gajica
kashida.plain
#endkeyvals

\ensureascii{text}#*

#ifOption:layout=footnotes
\localfootnote{text}
\mainfootnote{text}
\localfootnotetext#*
\mainfootnotetext#*
#endif

\babelsublr{text}#*
\localerestoredirs#*
\BabelPatchSection{section-name}#*
\BabelFootnote{cmd}{language}{before}{after}#*d

#ifOption:bidi=default
#include:fontspec
#endif
#ifOption:bidi=basic
#include:fontspec
#endif
#ifOption:bidi=basic-r
#include:fontspec
#endif
#ifOption:bidi=bidi-l
#include:fontspec
#include:bidi
#endif
#ifOption:bidi=bidi-r
#include:fontspec
#include:bidi
#endif

\languageattribute{language}{list of attributes}
\AddBabelHook{name}{event}{code}#*
\AddBabelHook[language]{name}{event}{code}#*
\EnableBabelHook{name}#*
\DisableBabelHook{name}#*
\BabelContentsFiles#*

\babelcharproperty{char-code}{property}{value}#*
\babelcharproperty{char-code}[to-char-code]{property}{value}#*
\babeladjust{keyvals}

#keyvals:\babeladjust
bidi.mapdigits=#on,off
bidi.mirroring=#on,off
bidi.text=#on,off
bidi.math=#on,off
linebreak.sea=#on,off
linebreak.cjk=#on,off
justify.arabic=#on,off
layout.tabular=#on,off
layout.lists=#on,off
autoload.bcp47=#on,off
bcp47.toname=#on,off
autoload.options=
autoload.bcp47.prefix=
autoload.bcp47.options=
prehyphenation.disable=#nohyphenation,off
select.write=#shift,keep,omit
select.encoding=#off
#endkeyvals

\fmtname#*

\glqq
\grqq
\glq
\grq
\flqq
\frqq
\flq
\frq
\quotedblbase
\quotesinglbase
\guillemetleft
\guillemetright
\guillemotleft#*
\guillemotright#*
\guilsinglleft
\guilsinglright
\dj
\DJ
\umlauthigh#*
\umlautlow#*
\umlautelow#S
\latinencoding#*
\latintext
\textlatin{text}

# miscellaneous (not for standard use)
\adddialect#S
\addlanguage#S
\AfterBabelCommands{code}#S
\allowhyphens#S
\BabelDated{arg}#S
\BabelDatedd{arg}#S
\BabelDateDot#S
\BabelDateM{arg}#S
\BabelDateMM{arg}#S
\BabelDateMMMM{arg}#S
\BabelDateSpace#S
\BabelDatey{arg}#S
\BabelDateyy{arg}#S
\BabelDateyyyy{arg}#S
\BabelLanguages#S
\BabelLower{uccode}{lccode}#S
\BabelLowerMM{uccode-from}{uccode-to}{step}{lccode}#S
\BabelLowerMO{uccode-from}{uccode-to}{step}{lccode}#S
\BabelModifiers#S
\BabelNonASCII#S
\BabelNonText#S
\BabelString#S
\BabelStringsDefault#S
\BabelText{arg}#S
\BCPdata{arg}#S
\EndBabelCommands#S
\IfBabelLayout{layout}{true}{false}#S
\IfBabelSelectorTF{selectors}{true}{false}#S
\LdfInit{language}{captionslanguage}#S
\loadlocalcfg{file}#Si
\localename#S
\ProvidesLanguage{language}#S
\ProvidesLanguage{language}[release info]#S
\SetCase[map-list]{to-upper-code}{to-lower-code}#S
\SetCase{toupper-code}{tolower-code}#S
\SetHyphenMap{to-lower-macros}#S
\SetString{macro-name}{string}#S
\SetStringLoop{macro-name}{string-list}#S
\StartBabelCommands*{language-list}{category}#S
\StartBabelCommands*{language-list}{category}[selector]#S
\StartBabelCommands{language-list}{category}#S
\StartBabelCommands{language-list}{category}[selector]#S

### albanian.ldf v1.0d ###
#ifOption:albanian
\captionsalbanian
\datealbanian
\extrasalbanian
\noextrasalbanian
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
\glossaryname#*
\sh#m
\ch#m
\th#m
\cth#m
\arsh#m
\arch#m
\arth#m
\arcth#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\Prob#m
\Expect#m
\Variance#m
#endif

### azerbaijani.ldf v1.0a ###
#ifOption:azerbaijani
\captionsazerbaijani
\dateazerbaijani
\extrasazerbaijani
\noextrasazerbaijani
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
\glossaryname#*
\azerbaijanischwa
\Azerbaijanischwa
#endif

### basque.ldf v1.0f ###
#ifOption:basque
\captionsbasque
\datebasque
\extrasbasque
\noextrasbasque
\basquehyphenmins#*
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
\glossaryname#*
\dieresia{arg}
\texttilde{arg}
#repl:"|
#repl:"- -
#repl:"< «
#repl:"> »
#repl:~n ñ
#repl:~N Ñ
#endif

### belarusian.ldf v1.5 ###
#ifOption:belarusian
\captionsbelarusian
\datebelarusian
\extrasbelarusian
\noextrasbelarusian
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Belarusian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
\NAD#m
\nad#m
\NAK#m
\nak#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\prefacename#*
\bibname#*
\chaptername#*
\tocname#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
#endif

### bosnian.ldf v1.1 ###
#ifOption:bosnian
\captionsbosnian
\datebosnian
\extrasbosnian
\noextrasbosnian
\th#m
\ctg#m
\arctg#m
\atcctg#m
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
\glossaryname#*
#endif

### breton.ldf v1.0f ###
#ifOption:breton
\captionsbreton
\datebreton
\extrasbreton
\noextrasbreton
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
\glossaryname#*
\at
\boi
\circonflexe
\tild
\degre
\kentan
\eil
\re
\trede
\pevare
\vet
\pempvet
#endif

### bulgarian.ldf v1.2g ###
#ifOption:bulgarian
\captionsbulgarian
\datebulgarian
\extrasbulgarian
\noextrasbulgarian
\Bulgarian
\English
\Bul#*
\Bg#*
\cyrillictext#*
\cyr#*
\selectbglanguage#*
\Eng#*
\selectenglanguage#*
\textcyrillic{text}
\cyrillicencoding#*
\lat#*
\dq
\cyrdash
\cdash#*
\todayRoman
\weekdaynamebulgarian{number}
\abvon
\abvoff
\tg#m
\ctg#m
\cosec#m
\arctg#m
\arcctg#m
\sh#m
\ch#m
\cth#m
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cyrxtounicode#*
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
\glossaryname#*
\Romannumeral{number}
\lastJulianDatebulgarian{number}#*
\firstGregorianDatebulgarian{number}#*
\abbgyear#*
\No
#repl:"< «
#repl:"> »
#repl:"` „
#repl:"' “
#repl:"- -
#repl:"~ 
#repl:"= 
#repl:"| 
#endif

### catalan.ldf v2.2p ###
#ifOption:catalan
\captionscatalan
\datecatalan
\extrascatalan
\noextrascatalan
\catalanhyphenmins#*
\lgem
\Lgem
\up{arg}
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
\glossaryname#*
\dieresis{arg}
#repl:"< «
#repl:"> »
#repl:"- -
#repl:"i ï
#repl:"I Ï
#repl:"c ç
#repl:"C Ç
#repl:"l l
#repl:"L L
#repl:"| 
#endif

### croatian.ldf v1.3l ###
#ifOption:croatian
\captionscroatian
\datecroatian
\extrascroatian
\noextrascroatian
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
\glossaryname#*
#endif

### czech.ldf v3.1a ###
#ifOption:czech
\captionsczech
\dateczech
\extrasczech
\noextrasczech
\q{arg}
\w{arg}
\uv{arg}
\csprimeson
\csprimesoff
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
\glossaryname#*
\sq
\dq
\lcaron
\Lcaron
\clqq
\crqq
\clq
\crq
#endif

### danish.ldf v1.3s ###
#ifOption:danish
\captionsdanish
\datedanish
\extrasdanish
\noextrasdanish
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
\glossaryname#*
#repl:"|
#repl:"- -
#repl:""
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

### dutch.ldf v3.8l (and associated afrikaans.ldf) ###
#ifOption:dutch
\captionsdutch
\datedutch
\extrasdutch
\noextrasdutch
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
\glossaryname#*
\dutchhyphenmins#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"y ij
#repl:"Y IJ
#repl:"|
#repl:"- -
#repl:"~ -
#repl:""
#repl:"` „
#repl:"' “
#endif

#ifOption:afrikaans
\captionsafrikaans
\dateafrikaans
\extrasafrikaans
\noextrasafrikaans
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
\glossaryname#*
\afrikaanshyphenmins#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"y ij
#repl:"Y IJ
#repl:"|
#repl:"- -
#repl:"~ -
#repl:""
#repl:"` „
#repl:"' “
#endif

### english.ldf v3.3r (and variants american, australian, british, canadian, newzealand, UKenglish, USenglish) ###
#ifOption:english
\captionsenglish
\dateenglish
\extrasenglish
\noextrasenglish
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:american
\captionsamerican
\dateamerican
\extrasamerican
\noextrasamerican
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:australian
\captionsaustralian
\dateaustralian
\extrasaustralian
\noextrasaustralian
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\australianhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:british
\captionsbritish
\datebritish
\extrasbritish
\noextrasbritish
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:canadian
\captionscanadian
\datecanadian
\extrascanadian
\noextrascanadian
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\canadianhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:newzealand
\captionsnewzealand
\datenewzealand
\extrasnewzealand
\noextrasnewzealand
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\newzealandhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:UKenglish
\captionsUKenglish
\dateUKenglish
\extrasUKenglish
\noextrasUKenglish
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:USenglish
\captionsUSenglish
\dateUSenglish
\extrasUSenglish
\noextrasUSenglish
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
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
\glossaryname#*
#endif

### esperanto.ldf v1.4t ###
#ifOption:esperanto
\captionsesperanto
\dateesperanto
\extrasesperanto
\noextrasesperanto
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
\glossaryname#*
\Esper{counter}
\esper{counter}
\hodiau
\hodiaun
#repl:^c ĉ
#repl:^C Ĉ
#repl:^g ĝ
#repl:^G Ĝ
#repl:^H Ĥ
#repl:^J Ĵ
#repl:^s ŝ
#repl:^S Ŝ
#repl:^h ĥ
#repl:^j ĵ
#repl:^u ŭ
#repl:^U Ŭ
#repl:^| 
#endif

### estonian.ldf v1.1a ###
#ifOption:estonian
\captionsestonian
\dateestonian
\extrasestonian
\noextrasestonian
\estonianhyphenmins#*
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
\glossaryname#*
\dq
#repl:~o õ
#repl:~O Õ
#repl:"a ä
#repl:"A Ä
#repl:"o ö
#repl:"O Ö
#repl:"u ü
#repl:"U Ü
#repl:~s š
#repl:~S Š
#repl:~z ž
#repl:~Z Ž
#repl:"|
#repl:"- -
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

### finnish.ldf v1.3s ###
#ifOption:finnish
\captionsfinnish
\datefinnish
\extrasfinnish
\noextrasfinnish
\finnishhyphenmins#*
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
\glossaryname#*
#repl:"|
#repl:"- -
#repl:"= -
#repl:"" 
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

### frenchb.ldf v3.5m (and associated acadian.ldf) ###
#ifOption:french
\frenchsetup{options%keyvals}
\frenchbsetup{options%keyvals}#S
#keyvals:\frenchsetup,\frenchbsetup
ShowOptions#true,false
StandardLayout#true,false
GlobalLayoutFrench#true,false
IndentFirst#true,false
PartNameFull#true,false
ListItemsAsPar#true,false
StandardListSpacing#true,false
StandardItemizeEnv#true,false
StandardEnumerateEnv#true,false
StandardItemLabels#true,false
ItemLabels=
ItemLabeli=
ItemLabelii=
ItemLabeliii=
ItemLabeliv=
StandardLists#true,false
ListOldLayout#true,false
FrenchFootnotes#true,false
AutoSpaceFootnotes#true,false
AutoSpacePunctuation#true,false
ThinColonSpace#true,false
OriginalTypewriter#true,false
UnicodeNoBreakSpaces#true,false
og=
fg=
INGuillSpace#true,false
EveryParGuill=#open,close,none
EveryLineGuill=#open,close,none
InnerGuillSingle#true,false
ThinSpaceInFrenchNumbers#true,false
SmallCapsFigTabCaptions#true,false
CustomiseFigTabCaptions#true,false
OldFigTabCaptions#true,false
FrenchSuperscripts#true,false
LowercaseSuperscripts#true,false
SuppressWarning#true,false
#endkeyvals
\AddThinSpaceBeforeFootnotes#*
\alsoname#*
\at
\bibname#*
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
\bname{text}
\bsc{text}
\CaptionSeparator#*
\captionsfrench
\ccname#*
\chaptername#*
\circonflexe
\dateacadian#*
\datefrench
\DecimalMathComma
\degre#*
\degres
\descindentFB#*
\dotFFN#*
\enclname#*
\end{descriptionFB}
\end{enumerateFB}
\end{itemizeFB}
\end{listFB}
\end{listORI}#*
\extrasfrench
\FBcolonspace
\FBdatebox#*
\FBdatespace#*
\FBeverylineguill#*
\FBfigtabshape#*
\FBfnindent#*
\FBFrenchFootnotesfalse#*
\FBFrenchFootnotestrue#*
\FBFrenchSuperscriptstrue#*
\FBGlobalLayoutFrenchtrue#*
\FBgspchar#*
\FBguillopen#*
\FBguillspace
\FBInnerGuillSinglefalse#*
\FBInnerGuillSingletrue#*
\FBListItemsAsParfalse#*
\FBListItemsAsPartrue#*
\FBLowercaseSuperscriptstrue#*
\FBmedkern#*
\FBPartNameFulltrue#*
\FBsetspaces[language]{type}{width}{stretch}{shrink}#*
\FBsetspaces{type}{width}{stretch}{shrink}#*
\FBSmallCapsFigTabCaptionstrue#*
\FBStandardEnumerateEnvtrue#*
\FBStandardItemizeEnvtrue#*
\FBStandardItemLabelstrue#*
\FBStandardLayouttrue#*
\FBStandardListSpacingtrue#*
\FBStandardListstrue#*
\FBsupR#*
\FBsupS#*
\FBtextellipsis#*
\FBthickkern#*
\FBthinspace
\FBthousandsep#*
\FBWarning{message%text}#*
\fg
\fgi#*
\fgii#*
\fprimo)
\frenchdate{day}{month}{year}
\FrenchEnumerate{arg}#*
\FrenchFootnotes#*
\FrenchLabelItem#*
\frenchpartfirst#*
\frenchpartsecond#*
\FrenchPopularEnumerate{arg}#*
\frenchtoday
\Frlabelitemi#*
\Frlabelitemi#*
\Frlabelitemii#*
\Frlabelitemii#*
\Frlabelitemiii#*
\Frlabelitemiii#*
\Frlabelitemiv#*
\Frlabelitemiv#*
\frquote{text}
\fup{text}
\glossaryname#*
\headtoname#*
\ieme
\iemes
\ier
\iere
\ieres
\iers
\ifFBAutoSpaceFootnotes#*
\ifFBCompactItemize#*
\ifFBCustomiseFigTabCaptions#*
\ifFBfrench#*
\ifFBFrenchFootnotes#*
\ifFBFrenchSuperscripts#*
\ifFBGlobalLayoutFrench#*
\ifFBIndentFirst#*
\ifFBINGuillSpace#*
\ifFBListItemsAsPar#*
\ifFBListOldLayout#*
\ifFBLowercaseSuperscripts#*
\ifFBLuaTeX#*
\ifFBOldFigTabCaptions#*
\ifFBOriginalTypewriter#*
\ifFBPartNameFull#*
\ifFBReduceListSpacing#*
\ifFBShowOptions#*
\ifFBSmallCapsFigTabCaptions#*
\ifFBStandardEnumerateEnv#*
\ifFBStandardItemizeEnv#*
\ifFBStandardItemLabels#*
\ifFBStandardLayout#*
\ifFBStandardLists#*
\ifFBStandardListSpacing#*
\ifFBSuppressWarning#*
\ifFBThinColonSpace#*
\ifFBThinSpaceInFrenchNumbers#*
\ifFBunicode#*
\ifFBXeTeX#*
\ifLaTeXe#*
\kernFFN#*
\labelindentFB#*
\labelwidthFB#*
\leftmarginFB#*
\listfigurename#*
\listindentFB#*
\No
\no
\NoAutoSpaceBeforeFDP#*
\NoAutoSpacing
\NoEveryParQuote#*
\noextrasfrench
\nombre{arg}#*
\nos
\Nos
\og
\ogi#*
\ogii#*
\pagename#*
\parindentFFN#*
\partfirst#*
\partfirst#*
\partnameord#*
\partsecond#*
\partsecond#*
\prefacename#*
\primo
\proofname#*
\quarto
\rmfamilyFB#*
\secundo
\seename#*
\sffamilyFB#*
\StandardFootnotes#*
\StandardMathComma
\tertio
\tild
\ttfamilyFB#*
\up{text}
\xspace
#endif

#ifOption:acadian
\frenchsetup{options%keyvals}
\frenchbsetup{options%keyvals}#S
#keyvals:\frenchsetup,\frenchbsetup
ShowOptions#true,false
StandardLayout#true,false
GlobalLayoutFrench#true,false
IndentFirst#true,false
PartNameFull#true,false
ListItemsAsPar#true,false
StandardListSpacing#true,false
StandardItemizeEnv#true,false
StandardEnumerateEnv#true,false
StandardItemLabels#true,false
ItemLabels=
ItemLabeli=
ItemLabelii=
ItemLabeliii=
ItemLabeliv=
StandardLists#true,false
ListOldLayout#true,false
FrenchFootnotes#true,false
AutoSpaceFootnotes#true,false
AutoSpacePunctuation#true,false
ThinColonSpace#true,false
OriginalTypewriter#true,false
UnicodeNoBreakSpaces#true,false
og=
fg=
INGuillSpace#true,false
EveryParGuill=#open,close,none
EveryLineGuill=#open,close,none
InnerGuillSingle#true,false
ThinSpaceInFrenchNumbers#true,false
SmallCapsFigTabCaptions#true,false
CustomiseFigTabCaptions#true,false
OldFigTabCaptions#true,false
FrenchSuperscripts#true,false
LowercaseSuperscripts#true,false
SuppressWarning#true,false
#endkeyvals
\acadiandate{day}{month}{year}
\acadiantoday
\AddThinSpaceBeforeFootnotes#*
\alsoname#*
\at
\bibname#*
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
\bname{text}
\bsc{text}
\CaptionSeparator#*
\captionsfrench#*
\captionsacadian
\ccname#*
\chaptername#*
\circonflexe
\dateacadian
\datefrench#*
\DecimalMathComma
\degre#*
\degres
\descindentFB#*
\dotFFN#*
\enclname#*
\end{descriptionFB}
\end{enumerateFB}
\end{itemizeFB}
\end{listFB}
\end{listORI}#*
\extrasfrench#*
\extrasacadian
\FBcolonspace
\FBdatebox#*
\FBdatespace#*
\FBeverylineguill#*
\FBfigtabshape#*
\FBfnindent#*
\FBFrenchFootnotesfalse#*
\FBFrenchFootnotestrue#*
\FBFrenchSuperscriptstrue#*
\FBGlobalLayoutFrenchtrue#*
\FBgspchar#*
\FBguillopen#*
\FBguillspace
\FBInnerGuillSinglefalse#*
\FBInnerGuillSingletrue#*
\FBListItemsAsParfalse#*
\FBListItemsAsPartrue#*
\FBLowercaseSuperscriptstrue#*
\FBmedkern#*
\FBPartNameFulltrue#*
\FBsetspaces[language]{type}{width}{stretch}{shrink}#*
\FBsetspaces{type}{width}{stretch}{shrink}#*
\FBSmallCapsFigTabCaptionstrue#*
\FBStandardEnumerateEnvtrue#*
\FBStandardItemizeEnvtrue#*
\FBStandardItemLabelstrue#*
\FBStandardLayouttrue#*
\FBStandardListSpacingtrue#*
\FBStandardListstrue#*
\FBsupR#*
\FBsupS#*
\FBtextellipsis#*
\FBthickkern#*
\FBthinspace
\FBthousandsep#*
\FBWarning{message%text}#*
\fg
\fgi#*
\fgii#*
\fprimo)
\frenchdate{day}{month}{year}#*
\FrenchEnumerate{arg}#*
\FrenchFootnotes#*
\FrenchLabelItem#*
\frenchpartfirst#*
\frenchpartsecond#*
\FrenchPopularEnumerate{arg}#*
\frenchtoday
\Frlabelitemi#*
\Frlabelitemi#*
\Frlabelitemii#*
\Frlabelitemii#*
\Frlabelitemiii#*
\Frlabelitemiii#*
\Frlabelitemiv#*
\Frlabelitemiv#*
\frquote{text}
\fup{text}
\glossaryname#*
\headtoname#*
\ieme
\iemes
\ier
\iere
\ieres
\iers
\ifFBAutoSpaceFootnotes#*
\ifFBCompactItemize#*
\ifFBCustomiseFigTabCaptions#*
\ifFBfrench#*
\ifFBFrenchFootnotes#*
\ifFBFrenchSuperscripts#*
\ifFBGlobalLayoutFrench#*
\ifFBIndentFirst#*
\ifFBINGuillSpace#*
\ifFBListItemsAsPar#*
\ifFBListOldLayout#*
\ifFBLowercaseSuperscripts#*
\ifFBLuaTeX#*
\ifFBOldFigTabCaptions#*
\ifFBOriginalTypewriter#*
\ifFBPartNameFull#*
\ifFBReduceListSpacing#*
\ifFBShowOptions#*
\ifFBSmallCapsFigTabCaptions#*
\ifFBStandardEnumerateEnv#*
\ifFBStandardItemizeEnv#*
\ifFBStandardItemLabels#*
\ifFBStandardLayout#*
\ifFBStandardLists#*
\ifFBStandardListSpacing#*
\ifFBSuppressWarning#*
\ifFBThinColonSpace#*
\ifFBThinSpaceInFrenchNumbers#*
\ifFBunicode#*
\ifFBXeTeX#*
\ifLaTeXe#*
\kernFFN#*
\labelindentFB#*
\labelwidthFB#*
\leftmarginFB#*
\listfigurename#*
\listindentFB#*
\No
\no
\NoAutoSpaceBeforeFDP#*
\NoAutoSpacing
\NoEveryParQuote#*
\noextrasfrench#*
\noextrasacadian
\nombre{arg}#*
\nos
\Nos
\og
\ogi#*
\ogii#*
\pagename#*
\parindentFFN#*
\partfirst#*
\partfirst#*
\partnameord#*
\partsecond#*
\partsecond#*
\prefacename#*
\primo
\proofname#*
\quarto
\rmfamilyFB#*
\secundo
\seename#*
\sffamilyFB#*
\StandardFootnotes#*
\StandardMathComma
\tertio
\tild
\ttfamilyFB#*
\up{text}
\xspace
#endif

### friulan.ldf v1.3 ###
#ifOption:friulan
\captionsfriulan
\datefriulan
\extrasfriulan
\noextrasfriulan
\friulanhyphenmins#*
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
\glossaryname#*
#endif

### galician.ldf v4.3c ###
#ifOption:galician
\captionsgalician
\dategalician
\extrasgalician
\noextrasgalician
\selectgalician
\selectgalician*
\layoutgalician#*
\textgalician#*
\shorthandsgalician#*
\mathgalician#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\galiciandatedo
\galiciandatede
\deactivatetilden#*
\galiciandeactivate{characters}#*
\shorthandsgalician#*
\decimalcomma
\decimalpoint
\galiciandecimal{math}
\sptext{arg}
\sptextfont#*
\accentedoperators#*
\unaccentedoperators#*
\spacedoperators#*
\unspacedoperators#*
\begin{quoting}
\end{quoting}
\lquoti
\rquoti
\lquotii
\rquotii
\lquotiii
\rquotiii
\activatequoting#*
\deactivatequoting#*
\lsc{text}
\msc{text}
#repl:~n ñ
#repl:~N Ñ
#repl:"i ï
#repl:"u ü
#repl:"I Ï
#repl:"U Ü
#repl:"r r
#repl:"R R
#repl:"" 
#repl:"|
#repl:"- -
#repl:"= -
#repl:"< «
#repl:"> »
#repl:<< «
#repl:>> »
#repl:?` ¿
#repl:!` ¡
#repl:"? ¿
#repl:"! ¡
#endif

### germanb.ldf v2.13 (and associated austrian.ldf and swissgerman.ldf) ###
#ifOption:german
\captionsgerman
\dategerman
\extrasgerman
\noextrasgerman
\dq
\tosstrue#*
\tossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
\ck#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:austrian
\captionsaustrian
\dateaustrian
\extrasaustrian
\noextrasaustrian
\dq
\tosstrue#*
\tossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
\ck#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:swissgerman
\captionsswissgerman
\dateswissgerman
\extrasswissgerman
\noextrasswissgerman
\dq
\tosstrue#*
\tossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
\ck#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"ck ck
#repl:"ff ff
#repl:"ll ll
#repl:"mm mm
#repl:"nn nn
#repl:"pp pp
#repl:"rr rr
#repl:"tt tt
#repl:"FF FF
#repl:"LL LL
#repl:"MM MM
#repl:"NN NN
#repl:"PP PP
#repl:"RR RR
#repl:"TT TT
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

### ngermanb.ldf v2.13 (and associated naustrian.ldf and nswissgerman.ldf) ###
#ifOption:ngerman
\captionsngerman
\datengerman
\extrasngerman
\noextrasngerman
\dq
\ntosstrue#*
\ntossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:naustrian
\captionsnaustrian
\datenaustrian
\extrasnaustrian
\noextrasnaustrian
\dq
\ntosstrue#*
\ntossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

#ifOption:nswissgerman
\captionsnswissgerman
\datenswissgerman
\extrasnswissgerman
\noextrasnswissgerman
\dq
\ntosstrue#*
\ntossfalse#*
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
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#endif

### greek.ldf v1.10 (and options greek.polutoniko and greek.ancient) ###
#ifOption:greek
\captionsgreek
\dategreek
\extrasgreek
\noextrasgreek
\greekscript
\greektext
\ensuregreek{text}
\textgreek{text}
\greeknumeral{number}
\Greeknumeral{number}
\greekfontencoding#*
\textol{text}#*
\outlfamily#*
\greekhyphenmins#*
\Grtoday
\anwtonos#n
\katwtonos#n
\qoppa#n
\varqoppa#n
\stigma#n
\sampi#n
\Digamma#n
\ddigamma#n
\euro#n
\permill#n
\textAlpha#*n
\textBeta#*n
\textGamma#*n
\textDelta#*n
\textEpsilon#*n
\textZeta#*n
\textEta#*n
\textTheta#*n
\textIota#*n
\textKappa#*n
\textLambda#*n
\textMu#*n
\textNu#*n
\textXi#*n
\textOmicron#*n
\textPi#*n
\textRho#*n
\textSigma#*n
\textTau#*n
\textUpsilon#*n
\textPhi#*n
\textChi#*n
\textPsi#*n
\textOmega#*n
\textalpha#*n
\textbeta#*n
\textgamma#*n
\textdelta#*n
\textepsilon#*n
\textzeta#*n
\texteta#*n
\texttheta#*n
\textiota#*n
\textkappa#*n
\textlambda#*n
\textmu#*n
\textnu#*n
\textxi#*n
\textomicron#*n
\textpi#*n
\textrho#*n
\textsigma#*n
\textfinalsigma#*n
\textautosigma#*n
\texttau#*n
\textupsilon#*n
\textphi#*n
\textchi#*n
\textpsi#*n
\textomega#*n
\textpentedeka#*n
\textpentehekaton#*n
\textpenteqilioi#*n
\textstigma#*n
\textvarstigma#*n
\textKoppa#*n
\textkoppa#*n
\textqoppa#*n
\textQoppa#*n
\textStigma#*n
\textSampi#*n
\textsampi#*n
\textanoteleia#*n
\texterotimatiko#*n
\textdigamma#*n
\textDigamma#*n
\textdexiakeraia#*n
\textaristerikeraia#*n
\textvarsigma#*n
\textstigmagreek#*n
\textkoppagreek#*n
\textStigmagreek#*n
\textSampigreek#*n
\textsampigreek#*n
\textdigammagreek#*n
\textDigammagreek#*n
\textnumeralsigngreek#*n
\textnumeralsignlowergreek#*n
\textpentemuria#*n
\textpercent#*n
\textmicro#*n
\textschwa#*n
\textampersand#n
\accdialytika{arg}#*n
\acctonos{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accvaria{arg}#*n
\accperispomeni{arg}#*n
\prosgegrammeni#*n
\ypogegrammeni#*n
\accdialytikaperispomeni{arg}#*n
\accdialytikatonos{arg}#*n
\accdialytikavaria{arg}#*n
\accdasiaperispomeni{arg}#*n
\accdasiavaria{arg}#*n
\accdasiaoxia{a}#*n
\accpsiliperispomeni{a}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accinvertedbrevebelow{arg}#*n
\textsubarch{arg}#*n
\accbrevebelow{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accdasiavaria{arg}#*n
\acctonos{arg}#*n
\accdasiaoxia{arg}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accperispomeni{arg}#*n
\accdasiaperispomeni{arg}#*n
\accpsiliperispomeni{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
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
\glossaryname#*
#endif

#ifOption:greek.polutoniko
\captionspolutonikogreek
\datepolutonikogreek
\extraspolutonikogreek
\noextraspolutonikogreek
\captionsgreek
\dategreek
\extrasgreek
\noextrasgreek
\greekscript
\greektext
\ensuregreek{text}
\textgreek{text}
\greeknumeral{number}
\Greeknumeral{number}
\greekfontencoding#*
\textol{text}#*
\outlfamily#*
\greekhyphenmins#*
\Grtoday
\anwtonos#n
\katwtonos#n
\qoppa#n
\varqoppa#n
\stigma#n
\sampi#n
\Digamma#n
\ddigamma#n
\euro#n
\permill#n
\textAlpha#*n
\textBeta#*n
\textGamma#*n
\textDelta#*n
\textEpsilon#*n
\textZeta#*n
\textEta#*n
\textTheta#*n
\textIota#*n
\textKappa#*n
\textLambda#*n
\textMu#*n
\textNu#*n
\textXi#*n
\textOmicron#*n
\textPi#*n
\textRho#*n
\textSigma#*n
\textTau#*n
\textUpsilon#*n
\textPhi#*n
\textChi#*n
\textPsi#*n
\textOmega#*n
\textalpha#*n
\textbeta#*n
\textgamma#*n
\textdelta#*n
\textepsilon#*n
\textzeta#*n
\texteta#*n
\texttheta#*n
\textiota#*n
\textkappa#*n
\textlambda#*n
\textmu#*n
\textnu#*n
\textxi#*n
\textomicron#*n
\textpi#*n
\textrho#*n
\textsigma#*n
\textfinalsigma#*n
\textautosigma#*n
\texttau#*n
\textupsilon#*n
\textphi#*n
\textchi#*n
\textpsi#*n
\textomega#*n
\textpentedeka#*n
\textpentehekaton#*n
\textpenteqilioi#*n
\textstigma#*n
\textvarstigma#*n
\textKoppa#*n
\textkoppa#*n
\textqoppa#*n
\textQoppa#*n
\textStigma#*n
\textSampi#*n
\textsampi#*n
\textanoteleia#*n
\texterotimatiko#*n
\textdigamma#*n
\textDigamma#*n
\textdexiakeraia#*n
\textaristerikeraia#*n
\textvarsigma#*n
\textstigmagreek#*n
\textkoppagreek#*n
\textStigmagreek#*n
\textSampigreek#*n
\textsampigreek#*n
\textdigammagreek#*n
\textDigammagreek#*n
\textnumeralsigngreek#*n
\textnumeralsignlowergreek#*n
\textpentemuria#*n
\textpercent#*n
\textmicro#*n
\textschwa#*n
\textampersand#n
\accdialytika{arg}#*n
\acctonos{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accvaria{arg}#*n
\accperispomeni{arg}#*n
\prosgegrammeni#*n
\ypogegrammeni#*n
\accdialytikaperispomeni{arg}#*n
\accdialytikatonos{arg}#*n
\accdialytikavaria{arg}#*n
\accdasiaperispomeni{arg}#*n
\accdasiavaria{arg}#*n
\accdasiaoxia{a}#*n
\accpsiliperispomeni{a}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accinvertedbrevebelow{arg}#*n
\textsubarch{arg}#*n
\accbrevebelow{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accdasiavaria{arg}#*n
\acctonos{arg}#*n
\accdasiaoxia{arg}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accperispomeni{arg}#*n
\accdasiaperispomeni{arg}#*n
\accpsiliperispomeni{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
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
\glossaryname#*
#endif

#ifOption:greek.ancient
\captionsancientgreek
\extrasancientgreek
\captionsgreek
\dategreek
\extrasgreek
\noextrasgreek
\greekscript
\greektext
\ensuregreek{text}
\textgreek{text}
\greeknumeral{number}
\Greeknumeral{number}
\greekfontencoding#*
\textol{text}#*
\outlfamily#*
\greekhyphenmins#*
\Grtoday
\anwtonos#n
\katwtonos#n
\qoppa#n
\varqoppa#n
\stigma#n
\sampi#n
\Digamma#n
\ddigamma#n
\euro#n
\permill#n
\textAlpha#*n
\textBeta#*n
\textGamma#*n
\textDelta#*n
\textEpsilon#*n
\textZeta#*n
\textEta#*n
\textTheta#*n
\textIota#*n
\textKappa#*n
\textLambda#*n
\textMu#*n
\textNu#*n
\textXi#*n
\textOmicron#*n
\textPi#*n
\textRho#*n
\textSigma#*n
\textTau#*n
\textUpsilon#*n
\textPhi#*n
\textChi#*n
\textPsi#*n
\textOmega#*n
\textalpha#*n
\textbeta#*n
\textgamma#*n
\textdelta#*n
\textepsilon#*n
\textzeta#*n
\texteta#*n
\texttheta#*n
\textiota#*n
\textkappa#*n
\textlambda#*n
\textmu#*n
\textnu#*n
\textxi#*n
\textomicron#*n
\textpi#*n
\textrho#*n
\textsigma#*n
\textfinalsigma#*n
\textautosigma#*n
\texttau#*n
\textupsilon#*n
\textphi#*n
\textchi#*n
\textpsi#*n
\textomega#*n
\textpentedeka#*n
\textpentehekaton#*n
\textpenteqilioi#*n
\textstigma#*n
\textvarstigma#*n
\textKoppa#*n
\textkoppa#*n
\textqoppa#*n
\textQoppa#*n
\textStigma#*n
\textSampi#*n
\textsampi#*n
\textanoteleia#*n
\texterotimatiko#*n
\textdigamma#*n
\textDigamma#*n
\textdexiakeraia#*n
\textaristerikeraia#*n
\textvarsigma#*n
\textstigmagreek#*n
\textkoppagreek#*n
\textStigmagreek#*n
\textSampigreek#*n
\textsampigreek#*n
\textdigammagreek#*n
\textDigammagreek#*n
\textnumeralsigngreek#*n
\textnumeralsignlowergreek#*n
\textpentemuria#*n
\textpercent#*n
\textmicro#*n
\textschwa#*n
\textampersand#n
\accdialytika{arg}#*n
\acctonos{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accvaria{arg}#*n
\accperispomeni{arg}#*n
\prosgegrammeni#*n
\ypogegrammeni#*n
\accdialytikaperispomeni{arg}#*n
\accdialytikatonos{arg}#*n
\accdialytikavaria{arg}#*n
\accdasiaperispomeni{arg}#*n
\accdasiavaria{arg}#*n
\accdasiaoxia{a}#*n
\accpsiliperispomeni{a}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accinvertedbrevebelow{arg}#*n
\textsubarch{arg}#*n
\accbrevebelow{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accdasiavaria{arg}#*n
\acctonos{arg}#*n
\accdasiaoxia{arg}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accperispomeni{arg}#*n
\accdasiaperispomeni{arg}#*n
\accpsiliperispomeni{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
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
\glossaryname#*
#endif

### icelandic.ldf v1.3 ###
#ifOption:icelandic
\captionsicelandic
\dateicelandic
\extrasicelandic
\noextrasicelandic
\tala{arg}
\grada{arg}
\gradur{arg}
\upp{arg}
\ilqq
\irqq
\ilq
\irq
\iflqq
\ifrqq
\ifrq
\iflq
\dq
\oob
\Oob
\ooob
\OOob
\eob
\Eob
\eeob
\EEob
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
\glossaryname#*
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#repl:"| 
#repl:"- -
#repl:"~ -
#repl:"= -
#repl:"o ǫ
#repl:"O Ǫ
#repl:"ó ǫ̇
#repl:"Ó Ǫ́
#repl:"e ę
#repl:"E Ę
#repl:"é ę̇
#repl:"É Ę̇
#endif

### indonesian.ldf v1.0m (and proxies bahasa.ldf, indon.ldf, and bahasai.ldf) ###
#ifOption:indonesian
\captionsindonesian
\dateindonesian
\extrasindonesian
\noextrasindonesian
\indonesianhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:bahasa
\captionsbahasa
\datebahasa
\extrasbahasa
\noextrasbahasa
\bahasahyphenmins#*
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
\glossaryname#*
#endif

#ifOption:indon
\captionsindon
\dateindon
\extrasindon
\noextrasindon
\indonhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:bahasai
\captionsbahasai
\datebahasai
\extrasbahasai
\noextrasbahasai
\bahasaihyphenmins#*
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
\glossaryname#*
#endif

### interlingua.ldf v1.6 ###
#ifOption:interlingua
\captionsinterlingua
\dateinterlingua
\extrasinterlingua
\noextrasinterlingua
\interlinguahyphenmins#*
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
\glossaryname#*
#endif

### irish.ldf v1.0h ###
#ifOption:irish
\captionsirish
\dateirish
\extrasirish
\noextrasirish
\irishhyphenmins#*
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
\glossaryname#*
#endif

### italian.ldf v1.4.04 ###
#ifOption:italian
\captionsitalian
\dateitalian
\extrasitalian
\noextrasitalian
\italianhyphenmins#*
\setactivedoublequote
\setISOcompliance#*
\IntelligentComma
\NoIntelligentComma
\XXIletters
\XXVIletters
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
\glossaryname#*
\ap{text%plain}
\ped{text%plain}
\unit{unit}
\virgola
\virgoladecimale
\LtxSymbCaporali#*
\CaporaliFrom{encoding}{family}{open guill slot}{close guill slot}#*
#endif

### japanese.ldf v3.1 ###
#ifOption:japanese
\captionsjapanese
\datejapanese
\extrasjapanese
\noextrasjapanese
\prefacename#*
\bibname#*
\prechaptername#*
\postchaptername#*
\presectionname#*
\postsectionname#*
\prepartname#*
\postpartname#*
\proofname#*
\glossaryname#*
#endif

### kurmanji.ldf v1.1 ###
#ifOption:kurmanji
\captionskurmanji
\datekurmanji
\extraskurmanji
\noextraskurmanji
\datekurmanjialternate
\kurmanjihyphenmins#*
\ontoday
\datesymd
\datesdmy
\dategdmy
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
\glossaryname#*
\januaryname
\februaryname
\marchname
\aprilname
\mayname
\junename
\julyname
\augustname
\septembername
\octobername
\novembername
\decembername
#endif

### latin.ldf v4.0 (and associated classiclatin, ecclesiasticlatin, medievallatin) ###
#ifOption:latin
\captionslatin
\datelatin
\extraslatin
\noextraslatin
\ProsodicMarksOn
\ProsodicMarksOff
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
\glossaryname#*
#repl:"< «
#repl:"> »
#repl:"| 
#endif

#ifOption:classiclatin
\captionsclassiclatin
\dateclassiclatin
\extrasclassiclatin
\noextrasclassiclatin
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
\glossaryname#*
#repl:"< «
#repl:"> »
#repl:"| 
#endif

#ifOption:ecclesiasticlatin
\captionsecclesiasticlatin
\dateecclesiasticlatin
\extrasecclesiasticlatin
\noextrasecclesiasticlatin
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
\glossaryname#*
#repl:"< «
#repl:"> »
#repl:"| 
#repl:"ae æ
#repl:"oe œ
#repl:"Ae Æ
#repl:"AE Æ
#repl:"Oe Œ
#repl:"OE Œ
#endif

#ifOption:medievallatin
\captionsmedievallatin
\datemedievallatin
\extrasmedievallatin
\noextrasmedievallatin
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
\glossaryname#*
#repl:"< «
#repl:"> »
#repl:"| 
#repl:"ae æ
#repl:"oe œ
#repl:"Ae Æ
#repl:"AE Æ
#repl:"Oe Œ
#repl:"OE Œ
#endif

### latvian.ldf v2.0b ###
#ifOption:latvian
\captionslatvian
\datelatvian
\extraslatvian
\noextraslatvian
\latvianhyphenmins#*
\datumaa
\datums
\latviangada#*
\latviantoday
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
\glossaryname#*
#endif

### lithuanian.ldf v1.0 ###
#ifOption:lithuanian
\captionslithuanian
\datelithuanian
\extraslithuanian
\noextraslithuanian
\lithuanianhyphenmins#*
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
\glossaryname#*
#endif

### macedonian.ldf v1.1 ###
#ifOption:macedonian
\captionsmacedonian
\datemacedonian
\extrasmacedonian
\noextrasmacedonian
\cyrillicencoding#*
\Macedonian
\English
\Romannumeral{number}
\todayRoman
\englishhyphenmins#*
\Mkd#*
\Mk#*
\cyrillictext#*
\cyr#*
\Eng#*
\prefacename#*
\bibname#*
\chaptername#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\theoremname#*
\corollaryname#*
\lemmaname#*
\glossaryname#*
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\dq
\cdash#*
\cyrdash
\overbar{arg}#*m
\textoverline{arg}#*
\overbarshort{arg}#*m
\textoverlineshort{arg}#*
\IfItalic{arg1}{arg2}#*
\tbar{arg}#*
#endif

### magyar.ldf v1.5c (and alias hungarian) ###
#ifOption:magyar
\captionsmagyar
\datemagyar
\extrasmagyar
\noextrasmagyar
\ondatemagyar
\prefacename#*
\bibname#*
\enclname#*
\ccname#*
\headtoname#*
\proofname#*
\glossaryname#*
\chaptername#*
\notesname#*
\pagename#*
\seename#*
\alsoname#*
\acite*{keylist}#c
\Acite*{keylist}#c
\acite{keylist}#c
\Acite{keylist}#c
\apageref*{label}#r
\Apageref*{label}#r
\apageref{label}#r
\Apageref{label}#r
\aref({label})#r
\Aref({label})#r
\aref*{label}#r
\Aref*{label}#r
\aref{label}#r
\Aref{label}#r
\atold%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\Atold%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\az*{szó}
\Az*{szó}
\az{szó}
\Az{szó}
\az+%<\refcmd{label}%>
\Az+%<\refcmd{label}%>
\azc{keylist}#*c
\Azc{keylist}#*c
\azp{label}#*r
\Azp{label}#*r
\azr{label}#*r
\Azr{label}#*r
\captionlabeldelim#S
\dMf#S
\editorfootnote{lábjegyzet-szöveg%text}
\emitdate[toldalék]{formátum}{dátum}
\emitdate{formátum}{dátum}
\factorial#m
\footnotestyle{előírás%keyvals}
#keyvals:\footnotestyle
reset=#none,section,chapter,page,page-resume,page-cont
resume
indent=#article-nosp,article-sp,hulist
ruler=#none,one-line,fourth,choose
marksize=max-normal
mark=#arabic,stars,stars-max
mpmark=#arabic,stars,stars-max
plain
huplain
starplain
editor
#endkeyvals
\hang{bekezdéskezdő jel}
\headingfootnote[szám]{lábjegyzet-szöveg%text}
\headingfootnote{lábjegyzet-szöveg%text}
\HuComma#*
\hunnewlabel#*
\Hunumeral{counter}
\hunumeral{counter}
\huordinal{counter}
\Huordinal{counter}
\magyarDumpHuMin#*
\makeFootnotable{környezet-név}
\MathBrk{szimbólum}#m
\MathBrkAll{szimbólum}#m
\MathReal{képlet tizedestörtekkel%formula}
\mond %<⟨kimondott szöveg⟩%>
\ondatemagyar
\ontoday
\refstruc{label}#r
\refstrucparen{label}#*r
\SafeToday
\textqq{szövegközti idézet%text}
\told%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\told%<⟨szám⟩%>+%<⟨toldalék1⟩%>+%<⟨toldalék2⟩%>{}
#endif

#ifOption:hungarian
\captionshungarian
\datehungarian
\extrashungarian
\noextrashungarian
\prefacename#*
\bibname#*
\enclname#*
\ccname#*
\headtoname#*
\proofname#*
\glossaryname#*
\chaptername#*
\notesname#*
\pagename#*
\seename#*
\alsoname#*
\acite*{keylist}#c
\Acite*{keylist}#c
\acite{keylist}#c
\Acite{keylist}#c
\apageref*{label}#r
\Apageref*{label}#r
\apageref{label}#r
\Apageref{label}#r
\aref({label})#r
\Aref({label})#r
\aref*{label}#r
\Aref*{label}#r
\aref{label}#r
\Aref{label}#r
\atold%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\Atold%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\az*{szó}
\Az*{szó}
\az{szó}
\Az{szó}
\az+%<\refcmd{label}%>
\Az+%<\refcmd{label}%>
\azc{keylist}#*c
\Azc{keylist}#*c
\azp{label}#*r
\Azp{label}#*r
\azr{label}#*r
\Azr{label}#*r
\captionlabeldelim#S
\dMf#S
\editorfootnote{lábjegyzet-szöveg%text}
\emitdate[toldalék]{formátum}{dátum}
\emitdate{formátum}{dátum}
\factorial#m
\footnotestyle{előírás%keyvals}
#keyvals:\footnotestyle
reset=#none,section,chapter,page,page-resume,page-cont
resume
indent=#article-nosp,article-sp,hulist
ruler=#none,one-line,fourth,choose
marksize=max-normal
mark=#arabic,stars,stars-max
mpmark=#arabic,stars,stars-max
plain
huplain
starplain
editor
#endkeyvals
\hang{bekezdéskezdő jel}
\headingfootnote[szám]{lábjegyzet-szöveg%text}
\headingfootnote{lábjegyzet-szöveg%text}
\HuComma#*
\hunnewlabel#*
\Hunumeral{counter}
\hunumeral{counter}
\huordinal{counter}
\Huordinal{counter}
\magyarDumpHuMin#*
\makeFootnotable{környezet-név}
\MathBrk{szimbólum}#m
\MathBrkAll{szimbólum}#m
\MathReal{képlet tizedestörtekkel%formula}
\mond %<⟨kimondott szöveg⟩%>
\ondatehungarian
\ontoday
\refstruc{label}#r
\refstrucparen{label}#*r
\SafeToday
\textqq{szövegközti idézet%text}
\told%<⟨szám⟩%>+%<⟨toldalék⟩%>{}
\told%<⟨szám⟩%>+%<⟨toldalék1⟩%>+%<⟨toldalék2⟩%>{}
#endif

### malay.ldf v1.0m (and proxies bahasam.ldf, melayu.ldf, and meyalu.ldf) ###
#ifOption:malay
\captionsmalay
\datemalay
\extrasmalay
\noextrasmalay
\malayhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:bahasam
\captionsbahasam
\datebahasam
\extrasbahasam
\noextrasbahasam
\bahasamhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:melayu
\captionsmelayu
\datemelayu
\extrasmelayu
\noextrasmelayu
\melayuhyphenmins#*
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
\glossaryname#*
#endif

#ifOption:meyalu
\captionsmeyalu
\datemeyalu
\extrasmeyalu
\noextrasmeyalu
\meyaluhyphenmins#*
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
\glossaryname#*
#endif

### mongolian.ldf v1.2 ###
#ifOption:mongolian
\captionsmongolian
\datemongolian
\extrasmongolian
\noextrasmongolian
\latinencoding#*
\cyrillicencoding#*
\Mongolian
\English
\Mon#*
\Eng#*
\cyrillictext#*
\cyr#*
\lat
\textcyrillic{text}
\prefacename
\bibname
\chaptername
\authorname
\enclname
\ccname
\headtoname
\pagename
\seename
\alsoname
\proofname
\glossaryname
\cdash#*
\mdqon#*
\mdqoff#*
\englishhyphenmins#*
\Useg{counter}
\useg{counter}
\sh#m
\ch#m
\tg#m
\arctg#m
\arcctg#m
\ctg#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\nsd#m
\nsk#m
\NSD#m
\NSK#m
\nod#m
\nok#m
\NOD#m
\NOK#m
\Proj#m
\No
# from T2A encoding
\C{arg}
\CYRA
\cyra
\CYRAE
\cyrae
\CYRB
\cyrb
\CYRC
\cyrc
\CYRCH
\cyrch
\CYRCHRDSC
\cyrchrdsc
\CYRCHVCRS
\cyrchvcrs
\CYRD
\cyrd
\cyrdash
\CYRDJE
\cyrdje
\CYRDZE
\cyrdze
\CYRDZHE
\cyrdzhe
\CYRE
\cyre
\CYREREV
\cyrerev
\CYRERY
\cyrery
\CYRF
\cyrf
\CYRG
\cyrg
\CYRGHCRS
\cyrghcrs
\CYRGUP
\cyrgup
\CYRH
\cyrh
\CYRHDSC
\cyrhdsc
\CYRHRDSN
\cyrhrdsn
\CYRI
\cyri
\CYRIE
\cyrie
\CYRII
\cyrii
\CYRISHRT
\cyrishrt
\CYRJE
\cyrje
\CYRK
\cyrk
\CYRKBEAK
\cyrkbeak
\CYRKDSC
\cyrkdsc
\CYRKVCRS
\cyrkvcrs
\CYRL
\cyrl
\cyrlangle
\CYRLJE
\cyrlje
\CYRM
\cyrm
\CYRN
\cyrn
\CYRNDSC
\cyrndsc
\CYRNG
\cyrng
\CYRNJE
\cyrnje
\CYRO
\cyro
\CYROTLD
\cyrotld
\CYRP
\cyrp
\CYRpalochka
\CYRQ
\cyrq
\CYRR
\cyrr
\cyrrangle
\CYRS
\cyrs
\CYRSCHWA
\cyrschwa
\CYRSDSC
\cyrsdsc
\CYRSFTSN
\cyrsftsn
\CYRSH
\cyrsh
\CYRSHCH
\cyrshch
\CYRSHHA
\cyrshha
\CYRT
\cyrt
\CYRTSHE
\cyrtshe
\CYRU
\cyru
\CYRUSHRT
\cyrushrt
\CYRV
\cyrv
\CYRW
\cyrw
\CYRY
\cyry
\CYRYA
\cyrya
\CYRYHCRS
\cyryhcrs
\CYRYI
\cyryi
\CYRYO
\cyryo
\CYRYU
\cyryu
\CYRZ
\cyrz
\CYRZDSC
\cyrzdsc
\CYRZH
\cyrzh
\CYRZHDSC
\cyrzhdsc
\f{arg}
\guillemotleft
\guillemotright
\k{arg}
\quotedblbase
\textquotedbl
\U{arg}
#endif

### norsk.ldf v2.0i ###
#ifOption:norsk
\captionsnorsk
\datenorsk
\extrasnorsk
\noextrasnorsk
\dq
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
\glossaryname#*
#endif

### piedmontese.ldf v1.0 ###
#ifOption:piedmontese
\captionspiedmontese
\datepiedmontese
\extraspiedmontese
\noextraspiedmontese
\piedmontesehyphenmins#*
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
\glossaryname#*
#endif

### pinyin.ldf v4.8.5 ###
#ifOption:pinyin
\captionspinyin#*
\datepinyin#*
\extraspinyin#*
\noextraspinyin#*
\mdqon#*
\mdqoff#*
#repl:"u ü
#repl:"U Ü
#endif

### polish.ldf v1.2l ###
#ifOption:polish
\captionspolish
\datepolish
\extraspolish
\noextraspolish
\aob
\Aob
\eob
\Eob
\lpb
\Lpb
\zkb
\Zkb
\sob#*
\spb#*
\skb#*
\textpl#*
\telepl#*
\dq
\polishrz#*
\polishzx#*
\mdqon#*
\mdqoff#*
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
\glossaryname#*
#repl:"" 
#repl:"- -
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#repl:"| 
#repl:"a ą
#repl:"A Ą
#repl:"e ę
#repl:"E Ę
#repl:"c ć
#repl:"C Ć
#repl:"l ł
#repl:"L Ł
#repl:"r ż
#repl:"R Ż
#repl:"z ź
#repl:"Z Ź
#endif

### portuges.ldf v1.2t ###
#ifOption:portuges
\captionsportuges
\dateportuges
\extrasportuges
\noextrasportuges
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
\glossaryname#*
\ord
\orda
\ro#*
\ra#*
#endif

#ifOption:portuguese
\captionsportuguese
\dateportuguese
\extrasportuguese
\noextrasportuguese
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
\glossaryname#*
\ord
\orda
\ro#*
\ra#*
#endif

#ifOption:brazil
\captionsbrazil
\datebrazil
\extrasbrazil
\noextrasbrazil
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
\glossaryname#*
\ord
\orda
\ro#*
\ra#*
#endif

#ifOption:brazilian
\captionsbrazilian
\datebrazilian
\extrasbrazilian
\noextrasbrazilian
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
\glossaryname#*
\ord
\orda
\ro#*
\ra#*
#endif

### romanian.ldf v1.2m ###
#ifOption:romanian
\captionsromanian
\dateromanian
\extrasromanian
\noextrasromanian
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
\glossaryname#*
#endif

### romansh.ldf v1.0 ###
#ifOption:romansh
\captionsromansh
\dateromansh
\extrasromansh
\noextrasromansh
\romanshhyphenmins#*
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
\glossaryname#*
#endif

### russianb.ldf v1.3m (and option russian.ancient) ###
#ifOption:russian
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsrussian
\daterussian
\extrasrussian
\noextrasrussian
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\prefacename#*
\bibname#*
\chaptername#*
\tocname#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
#endif

#ifOption:russian.ancient
\cyrdash
\asbuk{counter}
\Asbuk{counter}
\Russian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\NOD#m
\nod#m
\NOK#m
\nok#m
\Proj#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsrussian
\daterussian
\extrasrussian
\noextrasrussian
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\prefacename#*
\bibname#*
\chaptername#*
\tocname#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
#endif

### spanish.ldf v5.0q ###
#ifOption:spanish
#keyvals:\usepackage/babel#c
es-lcroman
es-minimal
es-nodecimaldot
es-noenumerate
es-noindentfirst
es-noitemize
es-nolayout
es-nolists
es-noquoting
es-nosectiondot
es-noshorthands
es-notilde
es-preindex
es-sloppy
es-tabla
es-tilden
es-ucroman
es-uppernames
mexico
mexico-com
#endkeyvals
\captionsspanish
\datespanish
\extrasspanish
\noextrasspanish
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\prefacename#*
\glossaryname#*
\spanishrefname#*
\spanishabstractname#*
\spanishbibname#*
\spanishchaptername#*
\spanishappendixname#*
\spanishcontentsname#*
\spanishlistfigurename#*
\spanishlisttablename#*
\spanishindexname#*
\spanishfigurename#*
\spanishtablename#*
\spanishpartname#*
\spanishenclname#*
\spanishccname#*
\spanishheadtoname#*
\spanishpagename#*
\spanishseename#*
\spanishalsoname#*
\spanishproofname#*
\spanishprefacename#*
\spanishglossaryname#*
\spanishdashitems#*
\spanishsignitems#*
\spanishsymbitems#*
\spanishindexchars{encap}{open}{close}#*
\spanishscroman
\spanishlcroman
\spanishucroman
\Today
\spanishdate{año}{mes}{día}
\spanishDate{año}{mes}{día}
\spanishdatedel
\spanishdatede
\spanishreverseddate
\spanishdatefirst{día-uno}
\spanishdeactivate{caracteres}
\decimalcomma
\decimalpoint
\spanishdecimal{math%formula}
\sptext{text}
\spanishplainpercent
\percentsign#*
\lsc{text}
\begin{quoting}
\end{quoting}
\lquoti
\rquoti
\lquotii
\rquotii
\lquotiii
\rquotiii
\activatequoting
\deactivatequoting
\sen#m
\tg#m
\arcsen#m
\arctg#m
\accentedoperators
\unaccentedoperators
\spacedoperators
\unspacedoperators
\spanishoperators#*
\dotlessi
\selectspanish
\spanishoptions#*
\textspanish#*
\notextspanish#*
\mathspanish#*
\shorthandsspanish#*
#endif

### samin.ldf v1.0c ###
#ifOption:samin
\captionssamin
\datesamin
\extrassamin
\noextrassamin
\saminhyphenmins#*
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
\glossaryname#*
#endif

### scottish.ldf v1.0g ###
#ifOption:scottish
\captionsscottish
\datescottish
\extrasscottish
\noextrasscottish
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
\glossaryname#*
#endif

### serbian.ldf v2.1 ###
#ifOption:serbian
\captionsserbian
\dateserbian
\extrasserbian
\noextrasserbian
\today*
\todayRoman
\todayRoman*
\enumCyr
\enumLat
\enumEng
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\arsh#m
\arch#m
\arth#m
\arcth#m
\cosec#m
\Prob#m
\Expect#m
\Variance#m
\arcsec#m
\arccosec#m
\sech#m
\cosech#m
\arsech#m
\arcosech#m
\NZD#m
\nzd#m
\NZS#m
\nzs#m
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
\glossaryname#*
#repl:"c č
#repl:"C Č
#repl:"s š
#repl:"S Š
#repl:"z ž
#repl:"Z Ž
#repl:"d đ
#repl:"D Đ
#repl:"" 
#repl:"- -
#repl:"~ -
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
#repl:"| 
#endif

### serbianc.ldf v3.1 ###
#ifOption:serbianc
\captionsserbianc
\dateserbianc
\extrasserbianc
\noextrasserbianc
\cyrdash
\Serbianc
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\Prob#m
\Variance#m
\arsh#m
\arch#m
\arth#m
\arcth#m
\arcsec#m
\arccosec#m
\sech#m
\cosech#m
\arsech#m
\arcosech#m
\Expect#m
\nzs#m
\nzd#m
\NZS#m
\NZD#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\todayRoman
\todayRoman*
\enumCyr
\enumLat
\enumEng
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
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
\glossaryname#*
#endif

### slovak.ldf v3.1a ###
#ifOption:slovak
\captionsslovak
\dateslovak
\extrasslovak
\noextrasslovak
\q{arg}
\dq
\sq
\uv{arg}
\lcaron#*
\Lcaron#*
\clqq
\crqq
\clq
\crq
\standardhyphens#*
\splithyphens#*
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
\glossaryname#*
#endif

### slovene.ldf v1.2n ###
#ifOption:slovene
\captionsslovene
\dateslovene
\extrasslovene
\noextrasslovene
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
\glossaryname#*
#endif

### lsorbian.ldf v1.0i (and proxy lowersorbian) ###
#ifOption:lsorbian
\captionslsorbian
\datelsorbian
\extraslsorbian
\noextraslsorbian
\newdatelsorbian
\olddatelsorbian
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
\glossaryname#*
#endif

#ifOption:lowersorbian
\captionslowersorbian
\datelowersorbian
\extraslowersorbian
\noextraslowersorbian
\newdatelowersorbian
\olddatelowersorbian
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
\glossaryname#*
#endif

### usorbian.ldf v1.0i (and proxy uppersorbian) ###
#ifOption:usorbian
\captionsusorbian
\dateusorbian
\extrasusorbian
\noextrasusorbian
\newdateusorbian
\olddateusorbian
\dq
\mdqon#*
\mdqoff#*
\ck#*
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
\glossaryname#*
#endif

#ifOption:uppersorbian
\captionsuppersorbian
\dateuppersorbian
\extrasuppersorbian
\noextrasuppersorbian
\newdateuppersorbian
\olddateuppersorbian
\dq
\mdqon#*
\mdqoff#*
\ck#*
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
\glossaryname#*
#endif

### swedish.ldf v2.3e ###
#ifOption:swedish
\captionsswedish
\dateswedish
\extrasswedish
\noextrasswedish
\swedishhyphenmins#*
\datesymd
\datesdmy
\dq
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
\glossaryname#*
#repl:"a ä
#repl:"o ö
#repl:"A Ä
#repl:"O Ö
#repl:"w å
#repl:"W Å
#repl:"f f
#repl:"b b
#repl:"d d
#repl:"g g
#repl:"l l
#repl:"m m
#repl:"n n
#repl:"p p
#repl:"r r
#repl:"s s
#repl:"t t
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#endif

### thai.ldf v1.8 ###
#ifOption:thai
\captionsthai
\datethai
\extrasthai
\noextrasthai
\thaihyphenmins#*
\thaitext
\textthai{text}
\textpali{text}
\wbr
\thainum{counter}
\thaibracenum{counter}
\thaialph{counter}
\thaiAlph{counter}
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
\textquotedbl#n
\textyamakkan#n
\textfongmun#n
\textangkhankhu#n
\textkhomut#n
\textYoYingPali#n
\textThoThanPali#n
\thaiKoKai
\thaiKhoKhai
\thaiKhoKhuat
\thaiKhoKhwai
\thaiKhoKhon
\thaiKhoRakhang
\thaiNgoNgu
\thaiChoChan
\thaiChoChing
\thaiChoChang
\thaiSoSo
\thaiChoChoe
\thaiYoYing
\thaiDoChada
\thaiToPatak
\thaiThoThan
\thaiThoNangmontho
\thaiThoPhuthao
\thaiNoNen
\thaiDoDek
\thaiToTao
\thaiThoThung
\thaiThoThahan
\thaiThoThong
\thaiNoNu
\thaiBoBaimai
\thaiPoPla
\thaiPhoPhung
\thaiFoFa
\thaiPhoPhan
\thaiFoFan
\thaiPhoSamphao
\thaiMoMa
\thaiYoYak
\thaiRoRua
\thaiRu
\thaiLoLing
\thaiLu
\thaiWoWaen
\thaiSoSala
\thaiSoRusi
\thaiSoSua
\thaiHoHip
\thaiLoChula
\thaiOAng
\thaiHoNokhuk
\thaiPaiyannoi
\thaiSaraA
\thaiMaiHanakat
\thaiSaraAa
\thaiSaraAm
\thaiSaraI
\thaiSaraIi
\thaiSaraUe
\thaiSaraUee
\thaiSaraU
\thaiSaraUu
\thaiPhinthu
\thaiSaraE
\thaiSaraAe
\thaiSaraO
\thaiSaraAiMaimuan
\thaiSaraAiMaimalai
\thaiLakkhangyao
\thaiMaiyamok
\thaiMaitaikhu
\thaiMaiEk
\thaiMaiTho
\thaiMaiTri
\thaiMaiChattawa
\thaiThanthakhat
\thaiNikhahit
\thaiYamakkan
\thaiFongman
\thaizero
\thaione
\thaitwo
\thaithree
\thaifour
\thaifive
\thaisix
\thaiseven
\thaieight
\thainine
\thaiAngkhankhu
\thaiKhomut
#endif

### thaicjk.ldf v4.8.5 ###
#ifOption:thaicjk
\captionsthaicjk
\datethaicjk
\extrasthaicjk
\noextrasthaicjk
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
\textquotedbl
\thaiKoKai
\thaiKhoKhai
\thaiKhoKhuat
\thaiKhoKhwai
\thaiKhoKhon
\thaiKhoRakhang
\thaiNgoNgu
\thaiChoChan
\thaiChoChing
\thaiChoChang
\thaiSoSo
\thaiChoChoe
\thaiYoYing
\thaiDoChada
\thaiToPatak
\thaiThoThan
\thaiThoNangmontho
\thaiThoPhuthao
\thaiNoNen
\thaiDoDek
\thaiToTao
\thaiThoThung
\thaiThoThahan
\thaiThoThong
\thaiNoNu
\thaiBoBaimai
\thaiPoPla
\thaiPhoPhung
\thaiFoFa
\thaiPhoPhan
\thaiFoFan
\thaiPhoSamphao
\thaiMoMa
\thaiYoYak
\thaiRoRua
\thaiRu
\thaiLoLing
\thaiLu
\thaiWoWaen
\thaiSoSala
\thaiSoRusi
\thaiSoSua
\thaiHoHip
\thaiLoChula
\thaiOAng
\thaiHoNokhuk
\thaiPaiyannoi
\thaiSaraA
\thaiMaiHanakat
\thaiSaraAa
\thaiSaraAm
\thaiSaraI
\thaiSaraIi
\thaiSaraUe
\thaiSaraUee
\thaiSaraU
\thaiSaraUu
\thaiPhinthu
\textbaht
\thaiSaraE
\thaiSaraAe
\thaiSaraO
\thaiSaraAiMaimuan
\thaiSaraAiMaimalai
\thaiLakkhangyao
\thaiMaiyamok
\thaiMaitaikhu
\thaiMaiEk
\thaiMaiTho
\thaiMaiTri
\thaiMaiChattawa
\thaiThanthakhat
\thaiNikhahit
\thaiYamakkan
\thaiFongman
\thaizero
\thaione
\thaitwo
\thaithree
\thaifour
\thaifive
\thaisix
\thaiseven
\thaieight
\thainine
\thaiAngkhankhu
\thaiKhomut
#endif

### turkish.ldf v1.4 ###
#ifOption:turkish
\captionsturkish
\dateturkish
\extrasturkish
\noextrasturkish
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\subjectname#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif

### ukraineb.ldf v1.4e ###
#ifOption:ukrainian
\cyrdash
\Ukrainian
\sh#m
\ch#m
\tg#m
\ctg#m
\arctg#m
\arcctg#m
\th#m
\cth#m
\cosec#m
\cyrillicencoding#*
\cyrillictext#*
\cyr#*
\textcyrillic{text}
\dq
\captionsukrainian
\dateukrainian
\extrasukrainian
\noextrasukrainian
\CYRA#*
\CYRB#*
\CYRV#*
\CYRG#*
\CYRGUP#*
\CYRD#*
\CYRE#*
\CYRIE#*
\CYRZH#*
\CYRZ#*
\CYRI#*
\CYRII#*
\CYRYI#*
\CYRISHRT#*
\CYRK#*
\CYRL#*
\CYRM#*
\CYRN#*
\CYRO#*
\CYRP#*
\CYRR#*
\CYRS#*
\CYRT#*
\CYRU#*
\CYRF#*
\CYRH#*
\CYRC#*
\CYRCH#*
\CYRSH#*
\CYRSHCH#*
\CYRYU#*
\CYRYA#*
\CYRSFTSN#*
\CYRERY#*
\cyra#*
\cyrb#*
\cyrv#*
\cyrg#*
\cyrgup#*
\cyrd#*
\cyre#*
\cyrie#*
\cyrzh#*
\cyrz#*
\cyri#*
\cyrii#*
\cyryi#*
\cyrishrt#*
\cyrk#*
\cyrl#*
\cyrm#*
\cyrn#*
\cyro#*
\cyrp#*
\cyrr#*
\cyrs#*
\cyrt#*
\cyru#*
\cyrf#*
\cyrh#*
\cyrc#*
\cyrch#*
\cyrsh#*
\cyrshch#*
\cyryu#*
\cyrya#*
\cyrsftsn#*
\cyrery#*
\cdash#*
\prefacename#*
\bibname#*
\chaptername#*
\tocname#*
\authorname#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\acronymname#*
\lstlistingname#*
\lstlistlistingname#*
\notesname#*
\nomname#*
\abbgyear#*
\No
#endif

### vietnamese.ldf v1.4 ###
#ifOption:vietnamese
\viettext
\viet#*
\textviet{text}
\captionsvietnamese
\datevietnamese
\extrasvietnamese
\noextrasvietnamese
\textquotedbl#n
\OHORN#n
\ohorn#n
\UHORN#n
\uhorn#n
\abreve#n
\Abreve#n
\acircumflex#n
\Acircumflex#n
\ecircumflex#n
\Ecircumflex#n
\ocircumflex#n
\Ocircumflex#n
\ohorn#n
\Ohorn#n
\uhorn#n
\Uhorn#n
\abreve#n
\ABREVE#n
\acircumflex#n
\ACIRCUMFLEX#n
\ecircumflex#n
\ECIRCUMFLEX#n
\ocircumflex#n
\OCIRCUMFLEX#n
\h{arg}#n
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
\glossaryname#*
\headpagename#*
#endif

### welsh.ldf v1.1a ###
#ifOption:welsh
\captionswelsh
\datewelsh
\extraswelsh
\noextraswelsh
\welshhyphenmins#*
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
\glossaryname#*
#endif
