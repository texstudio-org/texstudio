# democodetools package
# Matthew Bertucci 2022/09/05 for v1.0beta

#include:democodelisting

\begin{Macros}{macrolist}
\end{Macros}
\begin{Envs}{envlist}
\end{Envs}
\begin{Syntax}
\end{Syntax}

\begin{Args}
\end{Args}
\begin{Args+}
\end{Args+}
\begin{Keys}
\end{Keys}
\begin{Keys+}
\end{Keys+}
\begin{Values}
\end{Values}
\begin{Values+}
\end{Values+}
\begin{Options}
\end{Options}
\begin{Options+}
\end{Options+}

\DescribeMacro{macro%cmd}{marglist}
\DescribeMacro{macro%cmd}[oarglist]{marglist}
\DescribeMacro*{macro%cmd}{marglist}
\DescribeMacro*{macro%cmd}[oarglist]{marglist}
\DescribeMacro!{macro%cmd}{marglist}
\DescribeMacro!{macro%cmd}[oarglist]{marglist}
\DescribeMacro+{macro%cmd}{marglist}
\DescribeMacro+{macro%cmd}[oarglist]{marglist}

\DescribeArg{arg}
\DescribeArg[type]{arg}
\DescribeArg*{arg}
\DescribeArg*[type]{arg}
\DescribeArg+{arg}
\DescribeArg+[type]{arg}

\DescribeKey{key%plain}
\DescribeKey[type]{key%plain}
\DescribeKey*{key%plain}
\DescribeKey*[type]{key%plain}
\DescribeKey+{key%plain}
\DescribeKey+[type]{key%plain}

\DescribeValue{value}
\DescribeValue[type]{value}
\DescribeValue*{value}
\DescribeValue*[type]{value}
\DescribeValue+{value}
\DescribeValue+[type]{value}

\DescribeOption{option}
\DescribeOption[type]{option}
\DescribeOption*{option}
\DescribeOption*[type]{option}
\DescribeOption+{option}
\DescribeOption+[type]{option}

\DescribePackage{package}
\DescribePackage[type]{package}
\DescribePackage*{package}
\DescribePackage*[type]{package}
\DescribePackage+{package}
\DescribePackage+[type]{package}

\Macro{macro%cmd}{marglist}
\Macro{macro%cmd}[oarglist]{marglist}
\Macro{macro%cmd}<embellishments>{marglist}
\Macro{macro%cmd}<embellishments>[oarglist]{marglist}
\Macro!{macro%cmd}{parameter description}
\Macro!{macro%cmd}<embellishments>{parameter description}

\oarg{arg}
\oarg[type]{arg}
\marg{arg}
\marg[type]{arg}
\parg{arg}
\parg[type]{arg}
\xarg{arg}
\xarg[type]{arg}
\Arg{arg}
\Arg[type]{arg}
\Meta{arg}

\Key{key%plain}
\Key[pre]{key%plain}
\Keylst{key1,key2,...}
\Keylst[default]{key1,key2,...}
\KeyUse{key%plain}{value}

\Env{envname}
\Env[pre]{envname}
\Envlst{env1,env2,...}
\Envlst[pre]{env1,env2,...}

\Option{option}
\Option[pre]{option}
\Optionlst{opt1,opt2,...}
\Optionlst[pre]{opt1,opt2,...}

\Pack{package}
\Pack[pre]{package}
\Packlst{package1,package2,...}
\Packlst[pre]{package1,package2,...}

\Value{value}
\Value[pre]{value}
\Valuelst{val1,val2,...}
\Valuelst[pre]{val1,val2,...}

\MetaFmt
\MetaFmt[type]
\MetaFmt*
\MetaFmt*[type]

\MarginNote{text}

\dcAuthor{name}
\dcDate{date}
\dcTitle{title%text}
\dcMakeTitle

\begin{dcAbstract}
\end{dcAbstract}

# not documented
\bigtab#S
\colunit#S
\convertto{arg1}{arg2}#S
\rowunit#S