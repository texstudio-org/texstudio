# fixjfm package
# Matthew Bertucci 2022/07/22 for v0.8

#include:platex

\fixjfmspacing
\UseStandardCJKTextFontCommands
\UseFixJFMCJKTextFontCommands

\SetFixJFMSpacingShrink{length}#*
\SetFixJFMSpacingStretch{length}#*
\DeclareFixJFMCJKTextFontCommand{cmd}{font cmds}#*d
\DeclareStandardCJKTextFontCommand{cmd}{font cmds}#*d
\AppendToUseXCJKTextFontCommands{cmd}{font cmds}#*d
\FixJFMSpacing
\fixjfmparindent
\FixJFMParindent
\EveryparPreHook
\EveryparPostHook
\ifUseFixJFMCJKTextFontCommands#*
\UseFixJFMCJKTextFontCommandstrue#S
\UseFixJFMCJKTextFontCommandsfalse#S
\ifUseStandardCJKTextFontCommands#*
\UseStandardCJKTextFontCommandstrue#S
\UseStandardCJKTextFontCommandsfalse#S

\CATCODE#S
\ENDGROUP#S
\ENDINPUTFIXJFMDOTSTY#S
\FIXJFMDOTSTYRESTORECATCODE#S
\GDEF#S
\RELAX#S