# zhnumber package
# Darcy Hu <hot123tea123@gmail.com> 2016
#modified zepinglee 30 Jan 2021
# edited for v3.0

\zhnumber{number}
\zhnumber[options%keyvals]{number}

\zhdigits{number}
\zhdigits[options%keyvals]{number}
\zhdigits*{number}
\zhdigits*[options%keyvals]{number}

\zhnum{counter}
\zhnum[options%keyvals]{counter}

\zhdig{counter}
\zhdig[options%keyvals]{counter}

\zhweekday{yyyy/mm/dd}

\zhdate{yyyy/mm/dd}
\zhdate*{yyyy/mm/dd}

\zhtoday
\zhtime{hh:mm}
\zhcurrtime

\zhtiangan{number}#*
\zhdizhi{number}#*
\zhganzhi{number}#*
\zhganzhinian{year}#*

\zhnumExtendScaleMap{character1, character2, ..., charactern}#*
\zhnumExtendScaleMap[character]{character1, character2, ..., charactern}#*

\zhnumsetup{options%keyvals}

#keyvals:\zhnumsetup,\zhnumber,\zhdigits,\zhdigits*,\zhnum,\zhdig
encoding=#GBK,Big5,UTF8
#
time=#Arabic,Chinese
arabicsep={%<separator%>}
style=#Simplified,Traditional,Normal,Financial,Ancient
null#true,false
ganzhi-cyclic#true,false
reset
activechar#true,false
#
-=
-0=
0=
1=
2=
3=
4=
5=
6=
7=
8=
9=
10=
20=
30=
40=
100=
200=
1000=
#
E2=
E3=
E4=
E8=
E12=
E16=
E20=
E24=
E28=
E32=
E36=
E40=
E44=
#
F0=
F1=
F2=
F3=
F4=
F5=
F6=
F7=
F8=
F9=
F10=
F100=
F1000=
FE2=
FE3=
#
# T1-T10, D1-D12, GZ1-GZ60 omitted
#
dot=
and=
parts=
#
year=
month=
day=
hour=
minute=
weekday=
mon=
tue=
wed=
thu=
fri=
sat=
sun=
#endkeyvals

# not documented
\zhnumClearWrapper#*
\zhnumResetWrapper#*
\zhnumberwithoptions{options}{number}#S
\zhdigitswithoptions{options}{number}#S
\zhnumwithoptions{options}{counter}#S
\zhdigwithoptions{options}{counter}#S
