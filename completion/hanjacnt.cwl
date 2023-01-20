# hanjacnt package
# ponte-vecchio 2023-01-17 for v2.8

#keyvals:\usepackage/hanjacnt#c
manspace
20
30
finhanja
fullfinhanja
varfinhanja
#endkeyvals

#include:kotex

## 2.1 Numbers
\NumHanja{%<number%>}
\NumHangul{%<number%>}
\NumHanjaBig{%<number%>}
\NumHangulBig{%<number%>}

## 2.2 Financial Hanja
\FinHanjaMode
\FinHanjaMode{option%keyvals}

#keyvals:\FinHanjaMode
full
var
fullvar
off
on
#endkeyvals

### 2.3 Spaces at 'man' (10,000) positions
\ManSpaceOn
\ManSpaceOff

### 2.4 Digit
\NumHanjaDig{%<number%>}
\HanjaZero{%<char%>}
\HanjaZeroFont{%<font%>}
\TwentyHanjaChar[%<options%>]

#keyvals:\TwentyHanjaChar#c
2
10
20
30
21
31
#endkeyvals

\KRVcom{number}
\KRVverse{book}{verse}
\KRVverse{book}{verse}{number}

### 2.5 Replace Hanja for a given number
\MarkHanja{name%keyvals}{hanja}

#keyvals:\MarkHanja#c
default
one
two
three
four
five
six
seven
eight
nine
ten
hundred
thousand
shi
bae
chu
man
eok
cho
#endkeyvals

## 2.6 Counters
\HANJA{%<counter%>}#*
\HANGUL{%<counter%>}#*
\HANJADIG{%<counter%>}#*

## 2.7 Date-times in Hanja and Hangul
\HanjaYear{%<year%>}
\HanjaMonth{%<month%>}
\HanjaDay{%<day%>}
\HangulYear{%<year%>}
\HangulMonth{%<month%>}
\HangulDay{%<day%>}
\HanjaToday
\HangulToday
\HanjaTodayWithGanji
\HangulTodayWithGanji
\HangulLunarToday
\HangulLunarTodayWithGanji
\HangulLunarDay{%<day%>}
\HangulDangiYear{%<year%>}
\HanjaDangiYear{%<year%>}
\HangulBulgiYear{%<year%>}
\HanjaBulgiYear{%<year%>}
\HangulGanji
\HangulGanji{%<year%>}
\HanjaGanji
\HanjaGanji{%<year%>}

### 2.8 Selecting fonts
\NumHanjaFont{%<font%>}
