# chessfss package
# Matthew Bertucci 10/4/2021 for v1.2a

#include:ifthen

\figfont#*
\figsymbol{text}#*
\setfigfontfamily{family}#*

\king
\symking
\queen
\symqueen
\rook
\symrook
\bishop
\symbishop
\knight
\symknight
\pawn
\sympawn

\settextfigchars{king}{queen}{rook}{bishop}{knight}{pawn}#*
\settextfigchars[lang]{king}{queen}{rook}{bishop}{knight}{pawn}#*
\settextfiglanguage{language}#*
\textfigsymbol{piecechar}#*
\textking
\textqueen
\textrook
\textbishop
\textknight
\textpawn
\textsymfigsymbol{piece}#*
\textsymking#*
\textsymqueen#*
\textsymrook#*
\textsymbishop#*
\textsymknight#*
\textsympawn#*
\usetextfig#*
\usesymfig#*

\setfigstyle{font cmds}#*

\boardfont#*
\boardsymbol{text}#*
\setboardfontfamily{family}#*
\setboardfontseries{series}#*
\setboardfontsize{size}#*
\setboardfontencoding{encoding}#*

\WhiteEmptySquare#*
\BlackEmptySquare#*
\WhiteKingOnWhite#*
\BlackKingOnWhite#*
\WhiteKingOnBlack#*
\BlackKingOnBlack#*
\WhiteQueenOnWhite#*
\BlackQueenOnWhite#*
\WhiteQueenOnBlack#*
\BlackQueenOnBlack#*
\WhiteRookOnWhite#*
\BlackRookOnWhite#*
\WhiteRookOnBlack#*
\BlackRookOnBlack#*
\WhiteBishopOnWhite#*
\BlackBishopOnWhite#*
\WhiteBishopOnBlack#*
\BlackBishopOnBlack#*
\WhiteKnightOnWhite#*
\BlackKnightOnWhite#*
\WhiteKnightOnBlack#*
\BlackKnightOnBlack#*
\WhitePawnOnWhite#*
\BlackPawnOnWhite#*
\WhitePawnOnBlack#*
\BlackPawnOnBlack#*

\getsquarewidth{reference piece}#*
\showchessboardencoding{encoding}#*
\showchessboardencoding[font family]{encoding}#*

\setboardfontcolors{keyvals}

#keyvals:\setboardfontcolors
whitefieldmask=#%color
blackfieldmask=#%color
whitefield=#%color
blackfield=#%color
whiteonwhitepiecemask=#%color
whiteonblackpiecemask=#%color
blackonwhitepiecemask=#%color
blackonblackpiecemask=#%color
whitepiece=#%color
blackpiece=#%color
#endkeyvals

\inffont#*
\infsymbol{text}#*
\setinffontfamily{family}#*

\checksymbol
\castlinghyphen,
\withattack
\withinit
\zugzwang
\withidea
\onlymove
\diagonal
\file
\centre
\weakpt
\ending
\qside
\kside
\etc
\morepawns
\timelimit
\moreroom
\counterplay
\capturesymbol
\bishoppair
\betteris
\wupperhand
\doublepawns
\bupperhand
\wbetter
\bbetter
\wdecisive
\bdecisive
\unclear
\chesssee
\mate
\compensation
\opposbishops
\seppawns
\passedpawn
\samebishops
\devadvantage
\unitedpawns
\with
\without
\comment
\markera#*
\markerb#*
\chessetc#*

\sidefont#*
\sidesymbol{text}#*
\setsidefontencoding{encoding}#*
\setsidefontfamily{family}#*
\setsidefontseries{series}#*
\setsidefontshape{shape}#*
\setsidefontsize{size}#*

\setchessfontfamily{family}#*
\setallchessfontfamily{family}#*

\castlingchar
\longcastling
\shortcastling
\novelty
\chesscomment
\various