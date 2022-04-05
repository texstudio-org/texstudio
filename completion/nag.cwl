# nag package
# Matthew Bertucci 4/2/2022 for v0.7

#keyvals:\usepackage/nag#c
abort
experimental
l2tabu
orthodox
#endkeyvals

\PackageInfoNoLine{package name}{info text%text}#*
\ObsoleteCS{csname}{suggestions%text}#*
\ObsoleteCS[reason%text]{csname}{suggestions%text}#*
\ObsoleteEnv{envname}{suggestions%text}#*
\ObsoleteEnv[reason%text]{envname}{suggestions%text}#*
\ObsoletePackage{package name}{alternative%text}#*
\ObsoletePackage[reason%text]{package name}{alternative%text}#*
\SuggestedPackage{package name}#*
\SuggestedPackage[reason%text]{package name}#*
\IncompatiblePackages{package1}{package2}{hint%text}#*
\IncompatiblePackages[reason%text]{package name}{package2}{hint%text}#*
\ObsoleteClass{class name}{alternative%text}#*
\ObsoleteClass[reason%text]{class name}{alternative%text}#*
\BadFileLoadOrder{file1}{file2}#*
\BadFileLoadOrder[reason%text]{file1}{file2}#*
\NotAnEnvironment{command}#*
\NotASwitch{command}#*
\FBsuboheight#*
\NagDeclareFloat{float name}#*