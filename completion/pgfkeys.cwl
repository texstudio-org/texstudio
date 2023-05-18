# pgfkeys package
# muzimuzhi, 7 Jul 2020, tikz-pgf 3.1.5b
# updated 2023/01/15 for v3.1.10

# from pgfkeys.code.tex
\pgfkeyssetvalue{full key}{token text}#*
\pgfkeyssetevalue{full key}{token text}#*
\pgfkeysaddvalue{full key}{prefix code}{append code}#*
\pgfkeyslet{full key}{macro}#*
\pgfkeysgetvalue{full key}{macro}#*
\pgfkeysvalueof{full key}#*
\pgfkeysifdefined{full key}{true}{false}#*
\pgfkeysifassignable{full key}{true}{false}#*

\pgfkeys{key list%keyvals}
\pgfqkeys{default path}{key list%keyvals}
\pgfkeysalso{key list%keyvals}#*
\pgfqkeysalso{default path}{key list%keyvals}#*

\pgfeov#*
\pgfkeysdef{key%plain}{code}#*
\pgfkeysedef{key%plain}{code}#*
\pgfkeysdefnargs{key%plain}{arg count}{code}#*
\pgfkeysedefnargs{key%plain}{arg count}{code}#*
\pgfkeysdefargs{key%plain}{arg pattern}{code}#*
\pgfkeysedefargs{key%plain}{arg pattern}{code}#*

\pgfkeysdefaultpath#*
\pgfkeyscurrentpath#*
\pgfkeyscurrentname#*
\pgfkeyscurrentkey#*
\pgfkeyscurrentkeyRAW#*
\pgfkeyscurrentvalue#*

\pgfkeysnovalue#*
\pgfkeysvaluerequired#*
\pgfkeysaddhandleonlyexistingexception{handler key}#*

\usepgfkeyslibrary{library%keyvals}#*

#keyvals:\usepgfkeyslibrary#c
filtered
#endkeyvals

# from pgfkeyslibraryfiltered.code.tex
# key filtering - setting filters
\pgfkeysfiltered{key-value list}#*
\pgfqkeysfiltered{default path}{key-value list}#*
\pgfkeysalsofrom{macro}#*
\pgfkeysalsofiltered{key-value list}#*
\pgfkeysalsofilteredfrom{macro}#*

# key filtering - family support
\pgfkeysactivatefamiliesandfilteroptions{family list}{key-value list}#*
\pgfqkeysactivatefamiliesandfilteroptions{family list}{default path}{key-value list}#*
\pgfkeysactivatesinglefamilyandfilteroptions{family name}{key-value list}#*
\pgfqkeysactivatesinglefamilyandfilteroptions{family name}{default path}{key-value list}#*

# key filtering - programmer interface
\pgfkeysinterruptkeyfilter#*
\endpgfkeysinterruptkeyfilter#*
\pgfkeyssavekeyfilterstateto{macro}#*
\pgfkeysinstallkeyfilter{full key}{optional args}#*
\pgfkeysinstallkeyfilterhandler{full key}{optional args}#*
\pgfkeysactivatefamily{family name}#*
\pgfkeysdeactivatefamily{family name}#*
\pgfkeysactivatefamilies{family list}{deactivate macro name%cmd}#*d
\pgfkeysiffamilydefined{family}{true}{false}#*
\pgfkeysisfamilyactive{family}#*
\pgfkeysgetfamily{full key}{result macro}#*
\pgfkeyssetfamily{full key}{family}#*
\pgfkeysevalkeyfilterwith{full key}={filter args}#*

# key filtering - internal macros
\pgfkeyssplitpath#*
\pgfkeyscasenumber#*
\pgfkeyscurrentkeyfilter#*
\pgfkeyscurrentkeyfilterargs#*
\pgfkeyscurrentkeyfilterhandler#*
\pgfkeyscurrentkeyfilterhandlerargs#*

# tex-if
\ifpgfkeysaddeddefaultpath#*
\pgfkeysaddeddefaultpathtrue#*
\pgfkeysaddeddefaultpathfalse#*
\ifpgfkeyssuccess#*
\pgfkeyssuccesstrue#*
\pgfkeyssuccessfalse#*
\ifpgfkeysfilteringisactive#*
\pgfkeysfilteringisactivetrue#*
\pgfkeysfilteringisactivefalse#*
\ifpgfkeysfiltercontinue#*
\pgfkeysfiltercontinuetrue#*
\pgfkeysfiltercontinuefalse#*
