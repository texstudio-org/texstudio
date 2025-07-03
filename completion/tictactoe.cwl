# tictactoe package
# Matthew Bertucci 2025/06/28 for v1.0

#include:tikz
#include:xspace

#keyvals:\usepackage/tictactoe#c
ox
#endkeyvals

#ifOption:ox
\ox{grid positions}{winning line}
\ox[scale]{grid positions}{winning line}
\oxscore{grid positions}{winning line}{score}
\oxscore[scale]{grid positions}{winning line}{score}
\oxscorenobox{grid positions}{winning line}{score}
\oxscorenobox[scale]{grid positions}{winning line}{score}
#endif

\tictactoe{grid positions}{winning line}
\tictactoe[scale]{grid positions}{winning line}
\tictactoescore{grid positions}{winning line}{score}
\tictactoescore[scale]{grid positions}{winning line}{score}
\tictactoescorenobox{grid positions}{winning line}{score}
\tictactoescorenobox[scale]{grid positions}{winning line}{score}
\nought
\nought[scale]
\cross
\cross[scale]

\iftictactoeox#*
\tictacO#*
\tictacX#*
\tictaccellmaker{arg1}{arg2}#*
\tictaccellmarker[opt]{arg1}{arg2}{arg3}#*
\tictaccellmarker{arg1}{arg2}{arg3}#*
\tictacfontsize#*
\tictacfontspacing#*
\tictacn#*
\tictaco#*
\tictacrowmaker[opt]{arg1}{arg2}#*
\tictacrowmaker{arg1}{arg2}#*
\tictacscale#*
\tictacscorewidth#*
\tictactoegrid[opt]{arg1}{arg2}#*
\tictactoegrid{arg1}{arg2}#*
\tictacx#*
\tictocfaintcol#*
\tictocfullcol#*
\tictocgridlinescol#*
\tictocwincol#*

# not documented
\thetictaccellcounter#S
\thetictacrowmakercounter#S
\thetictacrowmakermax#S