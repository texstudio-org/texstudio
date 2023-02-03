# scrlfile-hook package
# Matthew Bertucci 11/19/2021 for v3.34

#include:scrlogo

\BeforeFile{file}{commands}#*
\BeforeFile{file}[label]{commands}#*
\AfterFile{file}{commands}#*
\AfterFile{file}[label]{commands}#*
\BeforeClass{class}{commands}#*
\BeforeClass{class}[label]{commands}#*
\BeforePackage{package}{commands}#*
\BeforePackage{package}[label]{commands}#*
\AfterAtEndOfClass{class}{commands}#*
\AfterAtEndOfClass{class}[label]{commands}#*
\AfterAtEndOfClass*{class}{commands}#*
\AfterAtEndOfClass*{class}[label]{commands}#*
\AfterAtEndOfPackage{package}{commands}#*
\AfterAtEndOfPackage{package}[label]{commands}#*
\AfterAtEndOfPackage*{package}{commands}#*
\AfterAtEndOfPackage*{package}[label]{commands}#*
\AfterClass{class}{commands}#*
\AfterClass{class}[label]{commands}#*
\AfterClass*{class}{commands}#*
\AfterClass*{class}[label]{commands}#*
\AfterPackage{package}{commands}#*
\AfterPackage{package}[label]{commands}#*
\AfterPackage*{package}{commands}#*
\AfterPackage*{package}[label]{commands}#*
\ReplaceInput{original file%file}{replacement file%file}#*
\ReplaceClass{original class}{replacement class}#*
\ReplacePackage{original package}{replacement package}#*
\UnReplaceInput{file}#*
\UnReplaceClass{class}#*
\UnReplacePackage{package}#*
\PreventPackageFromLoading{package list}#*
\PreventPackageFromLoading[alternate code]{package list}#*
\PreventPackageFromLoading*{package list}#*
\PreventPackageFromLoading*[alternate code]{package list}#*
\StorePreventPackageFromLoading{command}#*d
\ResetPreventPackageFromLoading#*
\UnPreventPackageFromLoading{package list}#*
\UnPreventPackageFromLoading*{package list}#*
\BeforeClosingMainAux{commands}#*
\AfterReadingMainAux{commands}#*
