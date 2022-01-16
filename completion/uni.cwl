# uni package
# Matthew Bertucci 11/13/2021 for v1.1

#keyvals:\usepackage/uni#c
strict
default
medium
bold
#endkeyvals

\textuni{text}
\uni
\textunirm{text}
\unirm
\textunisl{text}
\unisl
\textunisc{text}
\unisc
\textunist{text}
\unist
\textunibf{text}
\unibf
\textunibsl{text}
\unibsl
\textunibsc{text}
\unibsc
\textunibst{text}
\unibst

\bausquare
\baucircle
\bautriangle
\bauhead
\bauforms
\dh
\dj
\ng
\th
\varQ
\DH
\DJ
\NG 
\TH
\guilsinglleft
\guilsinglright
\guillemoleft
\guillemoright
\quotesinglbase
\quotedblbase
\textogonek

#ifOption:default
\textcmr{text}
\cmr
\cmrdefault#*
\cmrenc#*
\cmrfamily#*
#endif

\unifamily#*
\unifamilydefault#*
\uniseries#*
\uniseriesdefault#*
\unishape#*
\unishapedefault#*
\stshape#*
\stdefault#*

\k{arg}

\DeclareUniChar{command}{slot}#*d
\DeclareUniCommand{command}{definition}#*d
\DeclareUniCommand{command}[args]{definition}#*d

\UniError{message%text}#S
\unifiledate#S
\unifileversion#S