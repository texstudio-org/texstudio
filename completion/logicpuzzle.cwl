# logicpuzzle package
# Matthew Bertucci 9/29/2021 for v2.5

#include:xkeyval
#include:ifthen
#include:ragged2e
#include:marginnote
#include:tikz
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarycalc
#include:tikzlibraryshapes.geometric

\begin{logicpuzzle}
\begin{logicpuzzle}[options%keyvals]
\end{logicpuzzle}

\logicpuzzlesetup{options%keyvals}

\begin{puzzlebackground}
\end{puzzlebackground}
\begin{puzzleforeground}
\end{puzzleforeground}

\setcell{column}{row}{element}
\setcells{col1/row1,col2/row2,...}{element}
\setbigcell{column}{row}{element}
\setbigcell[fontsize]{column}{row}{element}
\setrow{row}{element list}
\setcolorrow{row}{element list}
\setcolumn{column}{element list}
\setcolorcolumn{column}{element list}
\setrule{column}{row}{rule%formula}
\fillcell{column}{row}
\fillrow{row}{csv list of 0 and 1}
\fillcolumn{column}{csv list of 0 and 1}
\filldiagonals
\filldiagonals[color]
\framearea{color}{TikZ path}
\fillarea{color}{TikZ path}
\colorarea{color}{TikZ path}
\framepuzzle
\framepuzzle[color]
\tikzpath{column}{row}{direction list}
\xtikzpath{column}{row}{dir1/len1,dir2/len2,...}
\titleformat{format}
\puzzlecounter
\setpuzzlecounter{number}
\definecounterstyle{name}{definition}
\setgridlinestyle{style}
\setnormallinewidth{width}
\setthicklinewidth{width}

### 2D-Sudoku ###
\begin{ddsudoku}
\begin{ddsudoku}[options%keyvals]
\end{ddsudoku}
\ddsudokucell{column}{row}{number}
\ddsudokusetup{options%keyvals}

### Battleship ###
\begin{battleship}
\begin{battleship}[options%keyvals]
\end{battleship}
\placeship{direction%keyvals}{column}{row}{length}
#keyvals:\placeship
H
V
#endkeyvals
\placesegment{column}{row}{ship segment}
\Ship
\ShipC
\ShipL
\ShipR
\ShipB
\ShipT
\Island
\Water
\ship{column}{row}{ship segment}#S
\placewater{column}{row}
\placeisland{column}{row}
\shipH{number list}
\shipV{number list}
\shipbox{number list}
\battleshipsetup{options%keyvals}
\classicgame{csv list}

### Bokkusu ###
\begin{bokkusu}
\begin{bokkusu}[options%keyvals]
\end{bokkusu}
\valueH{number list}
\valueV{number list}
\sumH{number list}
\sumV{number list}
\bokkususetup{options%keyvals}

### Bridges ###
\begin{bridges}
\begin{bridges}[options%keyvals]
\end{bridges}
\bridgesrow{row}{number list}
\bridgescolumn{column}{number list}
\bridge{TikZ path}
\bridge[options]{TikZ path}
\bridgessetup{options%keyvals}

### Chaos Sudoku ###
\begin{chaossudoku}
\begin{chaossudoku}[options%keyvals]
\end{chaossudoku}
\chaossudokucell{column}{row}{number}
\chaossudokusetup{options%keyvals}

### Four Winds ###
\begin{fourwinds}
\begin{fourwinds}[options%keyvals]
\end{fourwinds}
\fourwindscell{column}{row}{number}
\fourwindssetup{options%keyvals}

### Hakyuu ###
\begin{hakyuu}
\begin{hakyuu}[options%keyvals]
\end{hakyuu}
\hakyuucell{column}{row}{number}
\hakyuusetup{options%keyvals}

### Hitori ###
\begin{hitori}
\begin{hitori}[options%keyvals]
\end{hitori}
\hitorisetup{options%keyvals}

### Kakuro ###
\begin{kakuro}
\begin{kakuro}[options%keyvals]
\end{kakuro}
\kakurorow{row}{csv list}
\kakurocolumn{column}{csv list}
\KKR{sumV}{sumH}
\Black
\kakurosetup{options%keyvals}

### Kendoku ###
\begin{kendoku}
\begin{kendoku}[options%keyvals]
\end{kendoku}
\kendokucell{column}{row}{number}
\kendokusetup{options%keyvals}

### Killer Sudoku ###
\begin{killersudoku}
\begin{killersudoku}[options%keyvals]
\end{killersudoku}
\killersudokucell{column}{row}{number}
\killersudokusetup{options%keyvals}

###  Laser Beam ###
\begin{laserbeam}
\begin{laserbeam}[options%keyvals]
\end{laserbeam}
\laserH{number list}
\laserV{number list}
\mirrorH{number list}
\mirrorV{number list}
\placearrow{column}{row}{direction%keyvals}
#keyvals:\placearrow
LeftUp
LeftDown
RightUp
RightDown
#endkeyvals
\placecross{column}{row}
\placemirror{column}{row}{direction%keyvals}
#keyvals:\placemirror
H
V
#endkeyvals
\laser{TikZ path}
\laser[color]{TikZ path}
\laserbeamsetup{options%keyvals}

### Magic Labyrinth ###
\begin{magiclabyrinth}
\begin{magiclabyrinth}[options%keyvals]
\end{magiclabyrinth}
\magiclabyrinthcell{column}{row}{number}
\mlline{TikZ path}
\magiclabyrinthsetup{options%keyvals}

### Magnets ###
\begin{magnets}
\begin{magnets}[options%keyvals]
\end{magnets}
\plusH{number list}
\minusH{number list}
\plusV{number list}
\minusV{number list}
\magnetsH{number list}
\magnetsV{number list}
\PMH{col1/row1,col2/row2,...}
\MPH{col1/row1,col2/row2,...}
\PMV{col1/row1,col2/row2,...}
\MPV{col1/row1,col2/row2,...}
\magnetssetup{options%keyvals}

### Masyu ###
\begin{masyu}
\begin{masyu}[options%keyvals]
\end{masyu}
\masyucell{column}{row}{element}
\MasyuW
\MasyuB
\masyuline{TikZ path}
\masyusetup{options%keyvals}

### Minesweeper ###
\begin{minesweeper}
\begin{minesweeper}[options%keyvals]
\end{minesweeper}
\Mine
\minesweepersetup{options%keyvals}

### Nonogram ###
\begin{nonogram}
\begin{nonogram}[options%keyvals]
\end{nonogram}
\nonogramrow{row}{col1/len1,col2/len2,...}
\nonogramcolumn{column}{row1/len1,row2/len2,...}
\nonogramV{csv list}
\nonogramH{csv list}
\puzzlestrut
\nonogramsetup{options%keyvals}

### Number Link ###
\begin{numberlink}
\begin{numberlink}[options%keyvals]
\end{numberlink}
\numberlinkcell{column}{row}{element}
\link{TikZ path}
\numberlinksetup{options%keyvals}

### Resuko ###
\begin{resuko}
\begin{resuko}[options%keyvals]
\end{resuko}
\resukocell{column}{row}{element}
\Straight
\StraightH
\StraightV
\Cross
\CrossH
\CrossV
\CurveTL
\CurveTR
\CurveBL
\CurveBR
\Graveltrap
\pitlane{column}{row}{direction%keyvals}
#keyvals:\pitlane
H
V
#endkeyvals
\parkinglot{column}{row}
\trackH{csv list}
\trackV{csv list}
\track{TikZ path}
\resukosetup{options%keyvals}

### Schatzsuche ###
\begin{schatzsuche}
\begin{schatzsuche}[options%keyvals]
\end{schatzsuche}
\Diamond
\schatzsuchesetup{options%keyvals}

### Skyline ###
\begin{skyline}
\begin{skyline}[options%keyvals]
\end{skyline}
\skylineT{number list}
\skylineB{number list}
\skylineL{number list}
\skylineR{number list}
\skylinecell{column}{row}{height}
\skylinesetup{options%keyvals}

### Slitherlink ###
\begin{slitherlink}
\begin{slitherlink}[options%keyvals]
\end{slitherlink}
\slitherlinkcell{column}{row}{number}
\slitherlinksetup{options%keyvals}

### Star Battle ###
\begin{starbattle}
\begin{starbattle}[options%keyvals]
\end{starbattle}
\starbattlecell{column}{row}{element}
\starbattlesetup{options%keyvals}

###  Stars and Arrows ###
\begin{starsandarrows}
\begin{starsandarrows}[options%keyvals]
\end{starsandarrows}
\starsH{number list}
\starsV{number list}
\Star
\Right
\RightUp
\Up
\LeftUp
\Left
\LeftDown
\Down
\RightDown
\starsandarrowssetup{options%keyvals}

### Sudoku ###
\begin{lpsudoku}
\begin{lpsudoku}[options%keyvals]
\end{lpsudoku}
\lpsudokucell{column}{row}{number}
\lpsudokusetup{options%keyvals}

### Sun and Moon ###
\begin{sunandmoon}
\begin{sunandmoon}[options%keyvals]
\end{sunandmoon}
\Cloud
\Moon
\MoonT
\MoonB
\MoonR
\MoonL
\MoonTR
\MoonTL
\MoonBR
\MoonBL
\sunandmoonsetup{options%keyvals}

### Tents and Trees ###
\begin{tentsandtrees}
\begin{tentsandtrees}[options%keyvals]
\end{tentsandtrees}
\tentH{number list}
\tentV{number list}
\Tree
\Tent
\tentsandtreessetup{options%keyvals}

### Tunnel ###
\begin{tunnel}
\begin{tunnel}[options%keyvals]
\end{tunnel}
\tunnelH{number list}
\tunnelV{number list}
\portal{column}{row}
\tube{TikZ path}
\tunnelsetup{options%keyvals}

### keyval options ###
#keyvals:\begin{logicpuzzle},\logicpuzzlesetup,\begin{ddsudoku},\ddsudokusetup,\begin{battleship},\battleshipsetup,\begin{bokkusu},\bokkususetup,\begin{bridges},\bridgessetup,\begin{chaossudoku},\chaossudokusetup,\begin{fourwinds},\fourwindssetup,\begin{hakyuu},\hakyuusetup,\begin{hitori},\hitorisetup,\begin{kakuro},\kakurosetup,\begin{kendoku},\kendokusetup,\begin{killersudoku},\killersudokusetup,\begin{laserbeam},\laserbeamsetup,\begin{magiclabyrinth},\magiclabyrinthsetup,\begin{magnets},\magnetssetup,\begin{masyu},\masyusetup,\begin{minesweeper},\minesweepersetup,\begin{nonogram},\nonogramsetup,\begin{numberlink},\numberlinksetup,\begin{resuko},\resukosetup,\begin{schatzsuche},\schatzsuchesetup,\begin{skyline},\skylinesetup,\begin{slitherlink},\slitherlinksetup,\begin{starbattle},\starbattlesetup,\begin{starsandarrows},\starsandarrowssetup,\begin{lpsudoku},\lpsudokusetup,\begin{sunandmoon},\sunandmoonsetup,\begin{tentsandtrees},\tentsandtreessetup,\begin{tunnel},\tunnelsetup
rows=%<number%>
columns=%<number%>
width=##L
scale=
fontsize=#tiny,scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge
title=
titleindent=##L
titlewidth=##L
bgcolor=#%color
counterstyle=#none,left,right
cvoffset=##L
#endkeyvals

#keyvals:\begin{logicpuzzle},\logicpuzzlesetup,\begin{bokkusu},\bokkususetup,\begin{bridges},\bridgessetup,\begin{fourwinds},\fourwindssetup,\begin{kakuro},\kakurosetup,\begin{masyu},\masyusetup,\begin{nonogram},\nonogramsetup,\begin{numberlink},\numberlinksetup,\begin{resuko},\resukosetup
color=#%color
#endkeyvals

#keyvals:\begin{battleship},\battleshipsetup
shipcolor=#%color
sbindent=##L
sbwidth=##L
sbshipscale=
#endkeyvals

#keyvals:\begin{bridges},\bridgessetup
grid=#dashed,none,solid
#endkeyvals

#keyvals:\begin{kakuro},\kakurosetup,\begin{nonogram},\nonogramsetup
solution#true,false
#endkeyvals

#keyvals:\begin{nonogram},\nonogramsetup
extracells=%<integer%>
helplines=
#endkeyvals

#keyvals:\begin{skyline},\skylinesetup
sudoku#true,false
#endkeyvals

# not documented
\setTikZpreset{TikZ keys}#*
\logicpuzzlecell{column}{row}{element}#S
\bridgescell{column}{row}{element}#S
\hitoricell{column}{row}{element}#S
\kakurocell{column}{row}{element}#S
\magnetscell{column}{row}{element}#S
\minesweepercell{column}{row}{element}#S
\schatzsuchecell{column}{row}{element}#S
\sunandmooncell{column}{row}{element}#S
