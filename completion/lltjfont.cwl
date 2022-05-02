# lltjfont package
# Matthew Bertucci 4/9/2022 for v20220311.0

# loads tuenc.def

\Cht#*
\cht#*
\Cdp#*
\cdp#*
\Cwd#*
\cwd#*
\Cvs#*
\cvs#*
\Chs#*
\chs#*
\cHT#*
\ystrutbox#*
\dstrutbox#*
\tstrutbox#*
\zstrutbox#*
\ystrut
\tstrut
\dstrut
\zstrut
\DeclareYokoKanjiEncoding{encoding}{text settings}{math settings}
\DeclareTateKanjiEncoding{encoding}{text settings}{math settings}
\DeclareKanjiEncodingDefaults{text settings}{math settings}
\DeclareKanjiFamily{encoding}{family}{settings}
\DeclareKanjiSubstitution{encoding}{family}{series}{shape}
\DeclareErrorKanjiFont{encoding}{family}{series}{shape}{size}
\reDeclareMathAlphabet{unified cmd}{al cmd}{ja cmd}
\DeclareRelationFont{ja encoding}{ja family}{ja series}{ja shape}{al encoding}{al family}{al series}{al shape}
\SetRelationFont{ja encoding}{ja family}{ja series}{ja shape}{al encoding}{al family}{al series}{al shape}
\userelfont
\KanjiEncodingPair{encoding1}{encoding2}#*
\adjustbaseline
\romanencoding{encoding}
\kanjiencoding{encoding}
\romanfamily{family}
\kanjifamily{family}
\romanseries{series}
\kanjiseries{series}
\romanseriesforce{series}#*
\kanjiseriesforce{series}#*
\romanshape{shape}
\kanjishape{shape}
\romanshapeforce{shape}#*
\kanjishapeforce{shape}#*
\useroman{encoding}{family}{series}{shape}
\usekanji{encoding}{family}{series}{shape}
\mcfamily
\gtfamily
\getjfont#S
\DeclareAlternateKanjiFont{encoding}{family}{series}{shape}{alt encoding}{alt family}{alt series}{alt shape}{range}
\ClearAlternateKanjiFont{encoding}{family}{series}{shape}

# deprecated
\DeclareKanjiEncoding{encoding}{text settings}{math settings}#S

# from tuenc.def
\UnicodeEncodingName#*
\UnicodeFontTeXLigatures#*
\UnicodeFontFile{arg1}{arg2}#*
\UnicodeFontName{arg1}{arg2}#*
\DeclareUnicodeAccent{cmd}{encoding}{char code}#*d
\DeclareUnicodeComposite{cmd}{letter}{definition}#*d
\textquotedbl#n
\guillemetleft#n
\guillemotleft#*n
\guillemetright#n
\guillemotright#*n
\DH#n
\TH#n
\dh#n
\th#n
\DJ#n
\dj#n
\NG#n
\ng#n
\quotesinglbase#n
\quotedblbase#n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#*n
\hwithstroke#*n
\k{arg}#n