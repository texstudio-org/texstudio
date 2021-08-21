# tocloft.sty
# J. Sundermeyer
# Edson 20-12-2010
# Matthew Bertucci 8/15/2021

\addcontentsline{file}{kind}{title}#n
\contentsline{kind}{title}{page}#n
\addtocontents{file}{text}#n

\tocloftpagestyle{style}#n

\addtocontents{file}{text}

\cftmarktoc#n
\cftmarklof#n
\cftmarklot#n

\cftbeforetoctitleskip#n
\cftbeforeloftitleskip#n
\cftbeforelottitleskip#n

\cftaftertoctitleskip#n
\cftafterloftitleskip#n
\cftafterlottitleskip#n

\cfttoctitlefont#n
\cftloftitlefont#n
\cftlottitlefont#n

\cftaftertoctitle#n
\cftafterloftitle#n
\cftafterlottitle#n

\cftdot#n
\cftdotsep#n
\cftnodots#n
\cftdotfill{sep}

\cftsetpnumwidth{length}#n
\cftsetrmarg{length}#n
\cftpnumalign#n
\cftparskip#n

\cftbeforepartskip#n
\cftbeforechapskip#n
\cftbeforesecskip#n
\cftbeforesubsecskip#n
\cftbeforesubsubsecskip#n
\cftbeforeparaskip#n
\cftbeforesubparaskip#n
\cftbeforefigskip#n
\cftbeforesubfigskip#n
\cftbeforetabskip#n
\cftbeforesubtabskip#n

\cftpartindent#n
\cftchapindent#n
\cftsecindent#n
\cftsubsecindent#n
\cftsubsubsecindent#n
\cftparaindent#n
\cftsubparaindent#n
\cftfigindent#n
\cftsubfigindent#n
\cfttabindent#n
\cftsubtabindent#n

\cftpartnumwidth#n
\cftchapnumwidth#n
\cftsecnumwidth#n
\cftsubsecnumwidth#n
\cftsubsubsecnumwidth#n
\cftparanumwidth#n
\cftsubparanumwidth#n
\cftfignumwidth#n
\cftsubfignumwidth#n
\cfttabnumwidth#n
\cftsubtabnumwidth#n

\cftpartfont#n
\cftchapfont#n
\cftsecfont#n
\cftsubsecfont#n
\cftsubsubsecfont#n
\cftparafont#n
\cftsubparafont#n
\cftfigfont#n
\cftsubfigfont#n
\cfttabfont#n
\cftsubtabfont#n

\cftpartpresnum#n
\cftchappresnum#n
\cftsecpresnum#n
\cftsubsecpresnum#n
\cftsubsubsecpresnum#n
\cftparapresnum#n
\cftsubparapresnum#n
\cftfigpresnum#n
\cftsubfigpresnum#n
\cfttabpresnum#n
\cftsubtabpresnum#n

\cftpartaftersnum#n
\cftchapaftersnum#n
\cftsecaftersnum#n
\cftsubsecaftersnum#n
\cftsubsubsecaftersnum#n
\cftparaaftersnum#n
\cftsubparaaftersnum#n
\cftfigaftersnum#n
\cftsubfigaftersnum#n
\cfttabaftersnum#n
\cftsubtabaftersnum#n

\cftpartaftersnumb#n
\cftchapaftersnumb#n
\cftsecaftersnumb#n
\cftsubsecaftersnumb#n
\cftsubsubsecaftersnumb#n
\cftparaaftersnumb#n
\cftsubparaaftersnumb#n
\cftfigaftersnumb#n
\cftsubfigaftersnumb#n
\cfttabaftersnumb#n
\cftsubtabaftersnumb#n

\cftpartleader#n
\cftchapleader#n
\cftsecleader#n
\cftsubsecleader#n
\cftsubsubsecleader#n
\cftparaleader#n
\cftsubparaleader#n
\cftfigleader#n
\cftsubfigleader#n
\cfttableader#n
\cftsubtableader#n

\cftpartdotsep#n
\cftchapdotsep#n
\cftsecdotsep#n
\cftsubsecdotsep#n
\cftsubsubsecdotsep#n
\cftparadotsep#n
\cftsubparadotsep#n
\cftfigdotsep#n
\cftsubfigdotsep#n
\cfttabdotsep#n
\cftsubtabdotsep#n

\cftpartpagefont#n
\cftchappagefont#n
\cftsecpagefont#n
\cftsubsecpagefont#n
\cftsubsubsecpagefont#n
\cftparapagefont#n
\cftsubparapagefont#n
\cftfigpagefont#n
\cftsubfigpagefont#n
\cfttabpagefont#n
\cftsubtabpagefont#n

\cftpartafterpnum#n
\cftchapafterpnum#n
\cftsecafterpnum#n
\cftsubsecafterpnum#n
\cftsubsubsecafterpnum#n
\cftparaafterpnum#n
\cftsubparaafterpnum#n
\cftfigafterpnum#n
\cftsubfigafterpnum#n
\cfttabafterpnum#n
\cftsubtabafterpnum#n

\cftsetindents{entry}{indent}{numwidth}
\cftpagenumbersoff{entry}#n
\cftpagenumberson{entry}#n

\newlistof[within]{entry}{ext}{listofname}#n
\newlistof{entry}{ext}{listofname}#n

\tocdepth#n
\lotdepth#n
\lofdepth#n
\newlistentry[within]{entry}{ext}{level-1}#n

\cftchapterprecis{text}#*n
\cftchapterprecishere{text}#*n
\cftchapterprecistoc{text}#*n

\cftlocalchange{file}{pnumwidth}{tocrmarg}#*n

\cftaddtitleline{file}{kind}{title}{page}#*n
\cftaddnumtitleline{file}{kind}{num}{title}{page}#*n

\cftlofposthook#*n
\cftlofprehook#*n
\cftlotposthook#*n
\cftlotprehook#*n
\cfttocposthook#*n
\cfttocprehook#*n

\cftpartfillnum#*n
\cftchapfillnum#*n
\cftsecfillnum#*n
\cftsubsecfillnum#*n
\cftsubsubsecfillnum#*n
\cftparafillnum#*n
\cftsubparafillnum#*n
\cftfigfillnum#*n
\cftsubfigfillnum#*n
\cfttabfillnum#*n
\cftsubtabfillnum#*n

\cftchapname#*n
\cftsecname#*n
\cftsubsecname#*n
\cftsubsubsecname#*n
\cftparaname#*n
\cftsubparaname#*n
\cftfigname#*n
\cftsubfigname#*n
\cfttabname#*n
\cftsubtabname#*n

\phantomsection#*n
\cftparfillskip#*n
