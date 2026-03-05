# cwpuzzle package
# Matthew Bertucci 2026/02/14 for v1.15

#include:amssymb

#keyvals:\usepackage/cwpuzzle#c
numbered
nocenter
unboxed
normalsize
small
large
huge
Huge
german
ngerman
french
#endkeyvals

\begin{Puzzle}{columns}{rows}
\end{Puzzle}

\PuzzleDefineCell{key%plain}{definition}
\PuzzleDefineColorCell{key%plain}{color}

\Frame{llx}{lly}{width%plain}{height%plain}{text}

\begin{PuzzleClues}{text}
\end{PuzzleClues}
\Clue{number}{word%text}{clue%text}#/PuzzleClues

\PuzzleLetters{letters}
\PuzzleNumbers{numbers}

\begin{PuzzleWords}{word length}
\end{PuzzleWords}
\Word{word%text}#/PuzzleWords

\begin{Sudoku}
\end{Sudoku}

\PuzzleSolution
\PuzzleSolution[true or false]

\begin{Kakuro}{columns}{rows}
\end{Kakuro}

\PuzzleUnitlength#*
\PuzzleBlackBox#*
\PuzzleFont#*
\PuzzleNumberFont#*
\PuzzleClueFont#*
\PuzzleWordsText#*
\PuzzleLettersText#*
\PuzzleUnsolved#*
\PuzzlePutNumber{x}{y}{number}#*
\PuzzleHook#*
\PuzzleLineThickness#*
\PuzzleThickline#*
\PuzzlePre#*
\PuzzlePost#*
\PuzzleCluePre #*
\PuzzleCluePost#*
\PuzzleClueWidth#*
\PuzzleContent#*
\PuzzleSolutionContent#*
\SudokuLinethickness#*
\KakuroNumberFont#*
\KakuroHintType#*
\KakuroNumberFont#*
\PPa#S