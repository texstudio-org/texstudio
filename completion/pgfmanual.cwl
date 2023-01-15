# pgfmanual package
# Matthew Bertucci 2023/01/15 for v2023

# must load pgf or tikz separately

# NOTE: this package does not load pgfmanual-en-macros.tex (that file loads this package)
# but for completion purposes the commands from pgfmanual-en-macros are listed here

# pgfmanual.sty
# └── pgfmanual.code.tex
#     ├── pgfmanual.prettyprinter.code.tex
#     └── pgfmanual.pdflinks.code.tex
# pgfmanual-en-macros.tex

# from pgfmanual.prettyprinter.code.tex
\ifpgfmanualprettyenabled#*
\pgfmanualprettyenabledtrue#S
\pgfmanualprettyenabledfalse#S
\pgfmanualclosebrace#*
\pgfmanualprettyprintcode{tokens}#*
\pgfmanualprettyprintstyles#*
\ifpgfmanualprettycommentactive#*
\pgfmanualprettycommentactivetrue#S
\pgfmanualprettycommentactivefalse#S
\pgfmanualprettyprinterhandlecollectedargs{arg}#*
\pgfmanualprettyprinterhandlecollectedargsVtwo{result}{found terminator: 0|1}#*
\ifpgfmanualprettyprinterarghasunmatchedbraces#*
\pgfmanualprettyprinterarghasunmatchedbracestrue#S
\pgfmanualprettyprinterarghasunmatchedbracesfalse#S
\pgfmanualprettyprintercollectargcount{numargs}{code}#*
\ifpgfmanualprettyprinterfoundterminator#*
\pgfmanualprettyprinterfoundterminatortrue#S
\pgfmanualprettyprinterfoundterminatorfalse#S
\pgfmanualprettyprintercollectupto{arg1}{arg2}#*
\pgfmanualprettyprinterterminator#*
\pgfmanualprettyprintpgfkeys{pgfkeys}#*

# from pgfmanual.pdflinks.code.tex
\ifpgfmanualpdfwarnings#*
\pgfmanualpdfwarningstrue#S
\pgfmanualpdfwarningsfalse#S
\ifpgfmanualshowlabels#*
\pgfmanualshowlabelstrue#S
\pgfmanualshowlabelsfalse#S
\pgfmanualpdflabel{label}{text}
\pgfmanualpdflabel[catcode changes]{label}{text}
\pgfmanualpdfref{label}{text}
\declareandlabel{\controlsequence}
\verbpdfref{\controlsequence more stuff}

# from pgfmanual-en-macros.tex
\pgfmanualtargetcount#*
examplefill#B
graphicbackground#B
codebackground#B
animationgraphicbackground#B
\begin{pgfmanualentry}
\end{pgfmanualentry}
\thepgfmanualentry#*
\pgfmanualentryheadline{text}
\pgfmanualbody
\origtexttt{text}#S
\exclamationmarktext#*
\atmarktext#*
\pgfmanualnormalbar#*
\begin{pgflayout}{layout}
\end{pgflayout}
\begin{sysanimateattribute}{attribute}
\end{sysanimateattribute}
\begin{animateattribute}{attribute}
\end{animateattribute}
\begin{tikzanimateattribute}{attribute}
\end{tikzanimateattribute}
\begin{command}{command%plain}
\end{command}
\includeluadocumentationof{lua class}
\begin{luageneric}{arg1}{arg2}{arg3}{arg4}
\end{luageneric}
\begin{luatable}{arg1}{arg2}{arg3}
\end{luatable}
\begin{luafield}{field}
\end{luafield}
\begin{lualibrary}{library}
\end{lualibrary}
\begin{luadeclare}{arg1}{arg2}{arg3}{arg4}
\end{luadeclare}
\begin{luadeclarestyle}{arg1}{arg2}{arg3}{arg4}
\end{luadeclarestyle}
\begin{luanamespace}{prefix}{name}
\end{luanamespace}
\begin{luafiledescription}{arg}#*
\end{luafiledescription}#*
\begin{luacommand}{arg1}{arg2}{arg3}{arg4}
\end{luacommand}
\begin{luaparameters}
\end{luaparameters}
\begin{luareturns}
\end{luareturns}
\parametercount#*
\begin{parameterdescription}
\end{parameterdescription}
\saveditemcommand#S
\savedlistcommand#S
\denselist{label}{spacing}#S
\restorelist#S
\parameteritem#S
\parameteritem[label]#S
\begin{commandlist}{cmd1,cmd2,...}
\end{commandlist}
\begin{internallist}{cmd1,cmd2,...}
\begin{internallist}[type]{cmd1,cmd2,...}
\end{internallist}
\extractinternalcommand{arg1}{arg2}#S
\mvar{arg}
\extractmathfunctionname{arg}#S
\begin{math-function}{function}
\end{math-function}
\mathdefaultname#S
\mathurl#S
\pgfmanualemptytext#*
\pgfmanualvbarvbar#*
\begin{math-operator}{operator}{type}{name}
\begin{math-operator}[no index]{operator}{type}{name}
\end{math-operator}
\mathtest#S
\mathtype#S
\begin{math-operators}{left}{right}{type}{name}
\begin{math-operators}[no index]{left}{right}{type}{name}
\end{math-operators}
\mathinfixoperator{operator}{text}
\mathprefixoperator{operator}{text}
\mathpostfixoperator{operator}{text}
\mathgroupoperator{operator}{text}
\mathconditionaloperator{operator}{text}
\mathcommand
\mathcommand[expr]
\makemathcommand{arg1}(arg2){arg3}\stop#*
\calcname
\begin{math-keyword}{{%<name%>} %<other text%>}
\end{math-keyword}
\extracttikzmathkeyword{arg1}{arg2}#S
\extractcommand{arg1}{arg2}#S
\luaextractcommand{arg1}{arg2}#S
\extractenvironement{arg1}{arg2}#S
\begin{environment}{{%<envname%>}%<arguments%>}
\begin{plainenvironment}{{%<envname%>}%<arguments%>}
\end{plainenvironment}
\extractplainenvironement{arg1}{arg2}#S
\begin{contextenvironment}{{%<envname%>}%<arguments%>}
\end{contextenvironment}
\extractcontextenvironement{arg1}{arg2}#S
\begin{shape}{shape}
\end{shape}
\begin{pictype}{pictype}{arguments}
\end{pictype}
\begin{shading}{shading}
\end{shading}
\begin{graph}{graph}
\end{graph}
\begin{gdalgorithm}{name}{employs}
\end{gdalgorithm}
\begin{dataformat}{format}
\end{dataformat}
\begin{stylesheet}{stylesheet}
\end{stylesheet}
\begin{handler}{handler}
\end{handler}
\gobble{arg}#*
\extracthandler{arg1}{arg2}#S
\begin{stylekey}{path/key=value}
\end{stylekey}
\choicesep#*
\choicearg{text}#*
\iffirstchoice#*
\firstchoicetrue#S
\firstchoicefalse#S
\mchoice{choice1,choice2,...}
\begin{key}{path/key=value}
\end{key}
\insertpathifneeded{path/key}{default path}
\begin{keylist}{path1/key1=value1,path2/key2=value2,...}
\begin{keylist}[default path]{path1/key1=value1,path2/key2=value2,...}
\end{keylist}
\extractkey{arg}#S
\extractkeyequal{arg}#S
\extractdefault{arg1}{arg2}#S
\extractinitial{arg1}{arg2}#S
\extractequalinitial{arg}#S
\keyalias{path}
\iffirsttime#*
\firsttimetrue#S
\firsttimefalse#S
\pgfmanualdecomposecount#S
\decompose#S
\decomposetoodeep#S
\decomposefindlast#S
\indexkey{/path/key}
\begin{predefinedmethod}{}
\end{predefinedmethod}
\extractpredefinedmethod{arg1}(arg2)#S
\begin{ooclass}{}
\end{ooclass}
\begin{method}{}
\end{method}
\extractmethod{arg1}(arg2)#S
\begin{classattribute}{attribute}
\end{classattribute}
\extractattribute{arg}#S
\begin{predefinednode}{method}
\end{predefinednode}
\begin{coordinatesystem}{system}
\end{coordinatesystem}
\begin{snake}{name}#*
\end{snake}#*
\begin{decoration}{decoration}
\end{decoration}
\pgfmanualbar
\begin{pathoperation}{operation}{other text}
\begin{pathoperation}[noindex]{operation}{other text}
\end{pathoperation}
\pgfmanualtest#S
\begin{datavisualizationoperation}{operation}{other text}
\begin{datavisualizationoperation}[noindex]{operation}{other text}
\end{datavisualizationoperation}
\doublebs#*
\begin{package}{package}
\end{package}
\begin{pgfmodule}{module}
\end{pgfmodule}
\begin{pgflibrary}{library}
\end{pgflibrary}
\begin{purepgflibrary}{library}
\end{purepgflibrary}
\begin{tikzlibrary}{library}
\end{tikzlibrary}
\begin{pgfkeyslibrary}{library}
\end{pgfkeyslibrary}
\begin{filedescription}{file}
\end{filedescription}
\begin{packageoption}{option}
\end{packageoption}
\opt{text%plain}
\ooarg{arg}
\pgfmanualopt#S
\beamer
\pdf
\eps
\pgfname
\tikzname
\pstricks
\prosper
\seminar
\texpower
\foils
\getridofats{arg}#S
\getridtest#S
\removeats{arg}#S
\strippedat#S
\strippedtext#S
\stripcommand{arg}#S
\printanat#*
\declare{entry}
\pgfmanualdeclare#*
\begin{textoken}{token}
\end{textoken}
\myprintocmmand{arg}#S
\example
\themeauthor
\indexoption{option}
\itemcalendaroption{option}
\begin{class}{class}
\end{class}
\extractclass{arg1}(arg2)#S
\noindexing#*
\begin{arrowtipsimple}{name}
\end{arrowtipsimple}
\begin{arrowtip}{name}{description%text}{draw options}{option labels}
\end{arrowtip}
\begin{arrowcap}{name}{description%text}{draw options}{option labels}{shift}
\end{arrowcap}
\begin{pattern}{pattern}
\end{pattern}
\processaction{arg}#S
\begin{arrowexamples}
\end{arrowexamples}
\begin{arrowcapexamples}
\end{arrowcapexamples}
\arrowcapexample[%<options%>]
\arrowcapexample %<type%>[%<options%>]
\arrowexample[%<options%>]
\arrowexample %<type%>[%<options%>]
\arrowexampledup[%<options%>]
\arrowexampledupdot[%<options%>]
\arrowexampledouble[%<options%>]
\arrowexampledouble %<type%>[%<options%>]
\symarrow{arrow tip}
\symarrowdouble{arrow tip}
\sarrow{tip1}{tip2}
\sarrowdouble{tip1}{tip2}
\carrow{arrow tip}
\myvbar
\plotmarkentry{mark}
\plotmarkentrytikz{mark}
\returntospace#S
\showreturn#S
\commenthandler#S
\typesetcomment#S
\ifpgfmanualtikzsyntaxhilighting#*
\pgfmanualtikzsyntaxhilightingtrue#S
\pgfmanualtikzsyntaxhilightingfalse#S
\pgfmanualanimscale#*
\examplesource#S
\opensource{file}#*
\examplelines#S
\exampleline#S
\readexamplelines#S
\ifcodeexamplefromfile#*
\codeexamplefromfiletrue#S
\codeexamplefromfilefalse#S
\codeexamplewidth#*
\codeexamplebox#*
\begin{codeexample}[options%keyvals]#V
\end{codeexample}
#keyvals:\begin{codeexample}#c
width=##L
graphic=#%color
code=#%color
execute code
hidden
code only
setup code
multipage
pre={%<code%>
post={%<code%>
typeset listing=
render instead={%<code%>}
vbox
ignorespaces
leave comments
from file=%<file%>
tikz syntax#true,false
animation list={%<num1,num2,...%>}
animation pre={%<code%>}
animation post={%<code%>}
animation scale=%<factor%>
animation bb={(%<x1,y1%>) %<type%> (%<x2,y2%>)}
preamble={%<code%>}
#endkeyvals
\codeexampleboxanim#*
\pgfmanualdolisting{arg}#*
\pgfmanualcslinkpreskip#*
keycolor#B
cscolor#B
pointcolor#B
basecolor#B
linkcolor#B
\pgfmanualswitchoncolors#*
\pgfmanualwordstartup{text}#*
\noligs{text}#*
\pgfmanualnoligs{arg}#S
