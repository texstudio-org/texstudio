# algxpar package
# Matthew Bertucci 2023/06/27 for v0.99

#include:algorithmicx
#include:algpseudocode
#include:ragged2e
#include:xcolor
#include:fancyvrb
#include:pgfopts
#include:amssymb
#include:pgfmath
#include:varwidth
#include:ifthen

#keyvals:\usepackage/algxpar#c
brazilian
language=#english,brazilian
noend
#endkeyvals

\begin{algorithmic}<options%keyvals>
\begin{algorithmic}[lines]<options%keyvals>
\Statep{text}#/algorithmic
\Statep{text}[comment%text]#/algorithmic
\Statep{text}<options%keyvals>#/algorithmic
\Statep{text}[comment%text]<options%keyvals>#/algorithmic
\If{text}[comment%text]#/algorithmic
\If{text}<options%keyvals>#/algorithmic
\If{text}[comment%text]<options%keyvals>#/algorithmic
\EndIf[comment%text]#/algorithmic
\EndIf<options%keyvals>#/algorithmic
\EndIf[comment%text]<options%keyvals>#/algorithmic
\Else[comment%text]#/algorithmic
\Else<options%keyvals>#/algorithmic
\Else[comment%text]<options%keyvals>#/algorithmic
\Elsif{text}#/algorithmic
\Elsif{text}[comment%text]#/algorithmic
\Elsif{text}<options%keyvals>#/algorithmic
\Elsif{text}[comment%text]<options%keyvals>#/algorithmic
\Switch{expression}#/algorithmic
\Switch{expression}[comment%text]#/algorithmic
\Switch{expression}<options%keyvals>#/algorithmic
\Switch{expression}[comment%text]<options%keyvals>#/algorithmic
\EndSwitch#/algorithmic
\EndSwitch[comment%text]#/algorithmic
\EndSwitch<options%keyvals>#/algorithmic
\EndSwitch[comment%text]<options%keyvals>#/algorithmic
\Case{constant-list}#/algorithmic
\Case{constant-list}[comment%text]#/algorithmic
\Case{constant-list}<options%keyvals>#/algorithmic
\Case{constant-list}[comment%text]<options%keyvals>#/algorithmic
\EndCase#/algorithmic
\EndCase[comment%text]#/algorithmic
\EndCase<options%keyvals>#/algorithmic
\EndCase[comment%text]<options%keyvals>#/algorithmic
\Otherwise#/algorithmic
\Otherwise[comment%text]#/algorithmic
\Otherwise<options%keyvals>#/algorithmic
\Otherwise[comment%text]<options%keyvals>#/algorithmic
\EndOtherwise#/algorithmic
\EndOtherwise[comment%text]#/algorithmic
\EndOtherwise<options%keyvals>#/algorithmic
\EndOtherwise[comment%text]<options%keyvals>#/algorithmic
\For{text}[comment%text]#/algorithmic
\For{text}<options%keyvals>#/algorithmic
\For{text}[comment%text]<options%keyvals>#/algorithmic
\EndFor[comment%text]#/algorithmic
\EndFor<options%keyvals>#/algorithmic
\EndFor[comment%text]<options%keyvals>#/algorithmic
\ForEach{text}#/algorithmic
\ForEach{text}[comment%text]#/algorithmic
\ForEach{text}<options%keyvals>#/algorithmic
\ForEach{text}[comment%text]<options%keyvals>#/algorithmic
\ForAll{text}[comment%text]#/algorithmic
\ForAll{text}<options%keyvals>#/algorithmic
\ForAll{text}[comment%text]<options%keyvals>#/algorithmic
\While{text}[comment%text]#/algorithmic
\While{text}<options%keyvals>#/algorithmic
\While{text}[comment%text]<options%keyvals>#/algorithmic
\EndWhile[comment%text]#/algorithmic
\EndWhile<options%keyvals>#/algorithmic
\EndWhile[comment%text]<options%keyvals>#/algorithmic
\Repeat[comment%text]#/algorithmic
\Repeat<options%keyvals>#/algorithmic
\Repeat[comment%text]<options%keyvals>#/algorithmic
\Until{text}[comment%text]#/algorithmic
\Until{text}<options%keyvals>#/algorithmic
\Until{text}[comment%text]<options%keyvals>#/algorithmic
\Loop[comment%text]#/algorithmic
\Loop<options%keyvals>#/algorithmic
\Loop[comment%text]<options%keyvals>#/algorithmic
\EndLoop[comment%text]#/algorithmic
\EndLoop<options%keyvals>#/algorithmic
\EndLoop[comment%text]<options%keyvals>#/algorithmic
\To
\DownTo
\Step
\Continue
\Break
\True
\False
\Nil
\Id{identifier}
\Read
\Write
\Procedure{name}{params}[comment%text]#/algorithmic
\Procedure{name}{params}<options%keyvals>#/algorithmic
\Procedure{name}{params}[comment%text]<options%keyvals>#/algorithmic
\EndProcedure[comment%text]#/algorithmic
\EndProcedure<options%keyvals>#/algorithmic
\EndProcedure[comment%text]<options%keyvals>#/algorithmic
\Function{name}{params}[comment%text]#/algorithmic
\Function{name}{params}<options%keyvals>#/algorithmic
\Function{name}{params}[comment%text]<options%keyvals>#/algorithmic
\Call{name}{params}<options%keyvals>#/algorithmic
\Comment{text}<options%keyvals>#/algorithmic
\Comment{text}<options%keyvals>#/algorithmic
\Commentl{text}#/algorithmic
\Commentl{text}<options%keyvals>#/algorithmic
\CommentIn{text}#/algorithmic
\CommentIn{text}<options%keyvals>#/algorithmic
\Description %<⟨description text⟩%>#/algorithmic
\Input %<⟨inputs⟩%>#/algorithmic
\Output %<⟨outputs⟩%>#/algorithmic
\AlgSet{options%keyvals}

#keyvals:\begin{algorithmic},\Statep,\If,\EndIf,\Else,\Elsif,\Switch,\EndSwitch,\Case,\EndCase,\Otherwise,\EndOtherwise,\For,\EndFor,\ForEach,\ForAll,\While,\EndWhile,\Repeat,\Until,\Loop,\EndLoop,\Procedure,\EndProcedure,\Function,\Call,\Comment,\Commentl,\CommentIn,\AlgSet
language=#english,brazilian
noend
end
keywords={%<assignments%>}
algorithmic indent=##L
comment symbol=%<symbol%>
comment symbol right=%<symbol%>
text font=%<font commands%>
comment font=%<font commands%>
keyword font=%<font commands%>
constant font=%<font commands%>
module font=%<font commands%>
text color=#%color
comment color=#%color
keyword color=#%color
constant color=#%color
module color=#%color
text style=%<style%>
comment style=%<style%>
comment separator width=##L
statement indent=##L
parameter indent=##L
comment width=%<auto|nice|⟨width⟩%>
show boxes
#endkeyvals

\CommentSymbol#*
\CommentSymbolRight#*

\AlgLanguageSet{language}{keyword assignments}
\SetKeyword{keyword}{value}
\SetKeyword[language]{keyword}{value}
\Keyword{keyword}
\Keyword[language]{keyword}
\Constant{name}
\Module{name}

# deprecated
\Set{id}{value}#S

# not documented
\AlgDate#S
\AlgVersion#S
\NewLine#S
\RenewFullyExpandedDocumentCommand{cmd}{def}#S
