# filehook package
# Matthew Bertucci 10/6/2021 for v0.8a

\AtBeginOfEveryFile{code}#*
\AtEndOfEveryFile{code}#*
\AtBeginOfFiles{code}#*
\AtEndOfFiles{code}#*
\AtBeginOfFile{file}{code}#*
\AtEndOfFile{file}{code}#*
\AtBeginOfIncludes{code}#*
\AtEndOfIncludes{code}#*
\AfterIncludes{code}#*
\AtBeginOfIncludeFile{file}{code}#*
\AtEndOfIncludeFile{file}{code}#*
\AfterIncludeFile{file}{code}#*
\AtBeginOfInputs{code}#*
\AtEndOfInputs{code}#*
\AtBeginOfInputFile{file}{code}#*
\AtEndOfInputFile{file}{code}#*
\AtBeginOfPackageFile{package}{code}#*
\AtEndOfPackageFile{package}{code}#*
\AtBeginOfPackageFile*{package}{code}#*
\AtEndOfPackageFile*{package}{code}#*
\AtBeginOfClassFile{class}{code}#*
\AtEndOfClassFile{class}{code}#*
\AtBeginOfClassFile*{class}{code}#*
\AtEndOfClassFile*{class}{code}#*
\ClearHook#*