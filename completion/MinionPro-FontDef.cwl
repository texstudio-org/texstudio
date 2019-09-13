# Added as a workaround for a crash in TXS when it tries to autogenerate the CWL for MinionPro fonts.
# For details see https://github.com/texstudio-org/texstudio/issues/716
#include:fltpoint
#include:keyval
#include:otfontdef
\DeclareFontNamingScheme{arg1}#S
\DeclareOption#S
\DeclareSizeFunction{arg1}{arg2}#S
\ExecuteOptions#S
\Mn#S
\NeedsTeXFormat#S
\ProcessOptions#S
\ProvidesPackage#S
\csname#S
\do#S
\expandafter#S
\otf#S
\setkeys{arg1}{arg2}#S
\xbody#S
