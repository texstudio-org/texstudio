# pgfrcs package
# muzimuzhi, 7 Jul 2020, tikz-pgf 3.1.5b

#include:everyshi

# from pgfutil-common.tex
\pgferror{error text}#*
\pgfwarning{warning text}#*
\usepgflibrary{list of libraries}#*
\usepgfmodule{}#*
\pgfutilensuremath{formula}#*
\pgfutilpreparefilename{file name}#*
\pgfutilifcontainsmacro{token list}#*
\pgfutilifstartswith{start with pattern}{token list}{true}{false}#*
\pgfutilstrreplace{search}{replacement}{string}#*
\pgfutilsolvetwotwoleq{2x2 matrix entries}{2x1 matrix entries}#*
\pgfutilsolvetwotwoleqfloat{2x2 matrix entries}{2x1 matrix entries}#*

# from pgfutil-common-lists.tex
\pgfapplistnewempty{applist name}#*
\pgfapplistpushback %<item to append%>\to %<applist name%>#*
\pgfapplistlet{cmd}=%<applist name%>#*
\pgfprependlistnewempty{prelist name}#*
\pgfprependlistpushfront %<item to prepend%>\to %<prelist name%>#*
\pgfprependlistlet{cmd}=%<prelist name%>#*

# from pgfrcs.code.tex
\pgfrevision#*
\pgfversion#*
\pgfversiondatetime#*
\pgfrevisiondatetime#*
\pgfversiondate#*
\pgfrevisiondate#*
\pgftypesetversion#*
\ProvidesFileRCS{file name}#*
\ProvidesPackageRCS{pkg name}#*
\ProvidesClassRCS{class name}#*
