# pgfkeys package
# muzimuzhi, 7 Jul 2020, tikz-pgf 3.1.5b

# from pgfkeys.code.tex
\pgfkeyssetvalue{full key}{token text}#*
\pgfkeyssetevalue{full key}{token text}#*
\pgfkeysaddvalue{full key}{prefix code}{append code}#*
\pgfkeyslet{full key}{macro}#*
\pgfkeysgetvalue{full key}{macro}#*
\pgfkeysvalueof{full key}#*
\pgfkeysifdefined{full key}{true}{false}#*
\pgfkeysifassignable{full key}{true}{false}#*

\pgfkeys{key list}
\pgfqkeys{default path}{key list}
\pgfkeysalso{key list}#*
\pgfqkeysalso{default path}{key list}#*

\pgfkeysdef{key}{code}#*
\pgfkeysedef{key}{code}#*
\pgfkeysdefnargs{key}{arg count}{code}#*
\pgfkeysedefnargs{key}{arg count}{code}#*
\pgfkeysdefargs{key}{arg pattern}{code}#*
\pgfkeysedefargs{key}{arg pattern}{code}#*

\pgfkeysdefaultpath#*
\pgfkeyscurrentpath#*
\pgfkeyscurrentname#*
\pgfkeyscurrentkey#*
\pgfkeyscurrentkeyRAW#*
\pgfkeyscurrentvalue#*

\pgfkeysnovalue#*
\pgfkeysvaluerequired#*
\pgfkeysaddhandleonlyexistingexception{handler key}#*

# from pgfkeysfiltered.code.tex
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
\pgfkeysactivatefamilies{family list}{deactivate macro name}#*
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
