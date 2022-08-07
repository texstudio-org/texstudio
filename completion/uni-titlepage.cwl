# uni-titlepage package
# Matthew Bertucci 2022/08/06 for v1.1

#include:scrbase
#include:graphicx

\TitlePageStyle[option=value,...%keyvals]{style}

# keys for every style
#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/TU-DD,\TitlePageStyle/TU-HH,\TitlePageStyle/KIT,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography,\TitlePageStyle/WWUM,\TitlePageStyle/UKoLa
author={%<author names%>}
pagenumber=%<number%>
pagestyle=%<style%>
student=%<student name%>
subject=%<subject%>
subjectfont=%<font commands%>
title={%<title text%>}
titlefont=%<font commands%>
titlepagefont=%<font commands%>
#endkeyvals

# keys specific to styles
#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-HH,\TitlePageStyle/WWUM,\TitlePageStyle/UKoLa
academicgrade=%<grade%>
#endkeyvals

#keyvals:\TitlePageStyle/TU-DD,\TitlePageStyle/UKoLa
advisor=%<advisor name%>
#endkeyvals

#keyvals:\TitlePageStyle/TU-DD
blackborder#true,false
#endkeyvals

#keyvals:\TitlePageStyle/TU-DD,\TitlePageStyle/KIT,\TitlePageStyle/WWUM,\TitlePageStyle/UKoLa
chair=%<chair name%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW
company=%<company%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW
course=%<course%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/KIT,\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/TU-HH,\TitlePageStyle/TU-DD,\TitlePageStyle/JT-Typography,\TitlePageStyle/WWUM
date=%<date%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer
dedication={%<dedication text%>}
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-DD,\TitlePageStyle/WWUM
discipline=%<discipline%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW
duration=%<duration%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography
extratitle={%<extra title text%>}
#endkeyvals

#keyvals:\TitlePageStyle/TU-DD,\TitlePageStyle/KIT,\TitlePageStyle/WWUM
faculty=%<faculty name%>
#endkeyvals

#keyvals:\TitlePageStyle/TU-HH
final#true,false
#endkeyvals

#keyvals:\TitlePageStyle/KIT
homepage=%<URL%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography
lowertitleback={%<text%>}
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/KIT,\TitlePageStyle/UKoLa
mainlogo={%<logo code%>}
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-DD
matriculationnumber=%<number%>
#endkeyvals

#keyvals:\TitlePageStyle/TU-HH,\TitlePageStyle/WWUM
oralexaminationdate=%<date%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-HH,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography,\TitlePageStyle/WWUM,\TitlePageStyle/UKoLa
place=%<location%>
#endkeyvals

#keyvals:\TitlePageStyle/TU-DD,\TitlePageStyle/WWUM
professor=%<professor name%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography
publisher=%<publisher name%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-HH,\TitlePageStyle/UKoLa,\TitlePageStyle/KIT,\TitlePageStyle/WWUM
referee={%<referee names%>}
#endkeyvals

#keyvals:\TitlePageStyle/Markus-2,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/Spacer
rulesep=##L
rulewidth=##L
rulecolor=#%color
#endkeyvals

#keyvals:\TitlePageStyle/UKoLa
secondlogo={%<logo code%>}
#endkeyvals

#keyvals:\TitlePageStyle/WWUM
sience=%<sience%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/TU-HH
subtitle={%<subtitle text%>}
subtitlefont=%<font commands%>
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/KIT
titlehead={%<titlehead code%>}
#endkeyvals

#keyvals:\TitlePageStyle/DHBW,\TitlePageStyle/TU-DD,\TitlePageStyle/TU-HH,\TitlePageStyle/KIT,\TitlePageStyle/WWUM
university=%<university%>
#endkeyvals

#keyvals:\TitlePageStyle/KOMAScript,\TitlePageStyle/Markus-1,\TitlePageStyle/Markus-2,\TitlePageStyle/Spacer,\TitlePageStyle/JT-Aufsaetze,\TitlePageStyle/JT-Geschichte,\TitlePageStyle/JT-Typography
uppertitleback={%<text%>}
#endkeyvals

\TitleOption{option%keyvals}{value}

#keyvals:\TitleOption
academicgrade
advisor
author
blackborder
chair
company
course
date
dedication
discipline
duration
extratitle
faculty
final
homepage
lowertitleback
mainlogo
matriculationnumber
oralexaminationdate
pagenumber
pagestyle
place
professor
publisher
referee
rulesep
rulewidth
secondlogo
sience
student
subject
subjectfont
subtitle
subtitlefont
title
titlefont
titlehead
titlepagefont
university
uppertitleback
#endkeyvals

\maketitle[option=value,...%keyvals]
\TitleOptions{option=value,...%keyvals}

#keyvals:\maketitle,\TitleOptions
academicgrade=%<grade%>
advisor=%<advisor name%>
author={%<author names%>}
blackborder#true,false
chair=%<chair name%>
company=%<company%>
course=%<course%>
date=%<date%>
dedication={%<dedication text%>}
discipline=%<discipline%>
duration=%<duration%>
extratitle={%<extra title text%>}
faculty=%<faculty name%>
final#true,false
homepage=%<URL%>
lowertitleback={%<text%>}
mainlogo={%<logo code%>}
matriculationnumber=%<number%>
oralexaminationdate=%<date%>
pagenumber=%<number%>
pagestyle=%<style%>
place=%<location%>
professor=%<professor name%>
publisher=%<publisher name%>
referee={%<referee names%>}
rulesep=##L
rulewidth=##L
secondlogo={%<logo code%>}
sience=%<sience%>
student=%<student name%>
subject=%<subject%>
subjectfont=%<font commands%>
subtitle={%<subtitle text%>}
subtitlefont=%<font commands%>
title={%<title text%>}
titlefont=%<font commands%>
titlehead={%<titlehead code%>}
titlepagefont=%<font commands%>
university=%<university%>
uppertitleback={%<text%>}
#endkeyvals

\NowButAfterBeginDocument{code}#*
\begin{titlepage}[options%keyvals]
\end{titlepage}
\begin{fullsizetitle}[options%keyvals]
\end{fullsizetitle}

#keyvals:\begin{titlepage},\begin{fullsizetitle}
pagenumber=%<number%>
pagestyle=%<style%>
#endkeyvals

\usetitleelement{element%keyvals}
\usenonemptytitleelement{element%keyvals}

#keyvals:\usetitleelement,\usenonemptytitleelement
academicgrade
advisor
author
chair
company
course
date
dedication
discipline
duration
faculty
homepage
mainlogo
matriculationnumber
oralexaminationdate
place
professor
publisher
referee
secondlogo
subject
subtitle
title
titlehead
university
#endkeyvals

\advisorname#*
\atthename#*
\bachelorthesisname#*
\blackborderfalse#S
\blackbordertrue#S
\chairmanname#*
\companyname#*
\coursename#*
\dedication#*
\DefineReplaceTitleKey{name}{alias}#*
\DefineSimpleTitleKey{name}#*
\degreethesisname#*
\diplomathesisname#*
\durationname#*
\englishordinal{number}#*
\englishordinalfemalerefereename#*
\englishordinalmalerefereename#*
\englishordinalmalereferename#*
\examinationdatename#*
\examinationname#*
\exittitle#*
\extratitle{text}#*
\femaleordinal{number}#*
\femalerefereename#*
\finalfalse#S
\finaltrue#S
\fromname#*
\fromplacename#*
\germanfemaleordinal{number}#*
\germanmaleordinal{number}#*
\germanordinal{number}#*
\germanordinalfemalecorrectorname#*
\germanordinalfemalerefereename#*
\germanordinalmalecorrectorname#*
\germanordinalmalerefereename#*
\homepage{URL}#*
\ifblackborder#S
\iffinal#S
\indatename#*
\inittitle#*
\inittitlestyle#*
\KITlongname#*
\KITurl#*
\lowertitleback{text}#*
\mainlogo#*
\makemaintitle#*
\makemaintitleback#*
\makeposttitle#*
\makeposttitleback#*
\makepretitle#*
\makepretitleback#*
\maleordinal{number}#*
\malerefereename#*
\masterthesisname#*
\matriculationnumber#*
\matriculationnumbername#*
\ofthename#*
\oralexaminationdatename#*
\ordinal{number}#*
\ordinalfemalecorrectorname#*
\ordinalfemalerefereename#*
\ordinalmalerefereename#*
\PackageNotLoadedError{message}#S
\presentationinformationDHBW#*
\presentationinformationKIT#*
\presentationinformationTUHH#*
\presentationinformationUKoLa#*
\presentationinformationUKoLA#*
\presentationinformationWWUM#*
\presentedbyname#*
\projectpapername#*
\publishers#*
\refereename#*
\seminarpapername#*
\studentresearchname#*
\studentreserchname#*
\thename#*
\thetitlepage#*
\titlebox#*
\titlefont#*
\titlehead{text}#*
\titlepagestyle#*
\uppertitleback{text}#*
