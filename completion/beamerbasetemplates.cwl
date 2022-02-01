# beamerbasetemplates package
# Matthew Bertucci 1/30/2022 for v3.65

#include:beamerbaseauxtemplates

\usebeamertemplate{element name}
\usebeamertemplate*{element name}
\usebeamertemplate**{element name}
\usebeamertemplate***{element name}

\expandbeamertemplate{beamer template name}
\ifbeamertemplateempty{beamer template name}{executed if empty}{executed otherwise}

\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number][default optional argument]{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}[default optional argument]{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number][default optional argument]{predefined text}
\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number]{predefined text}
\defbeamertemplate<mode specification>*{element name}{predefined option}{predefined text}
\defbeamertemplate{element name}{predefined option}[argument number][default optional argument]{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}[default optional argument]{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}[argument number][default optional argument]{predefined text}
\defbeamertemplate{element name}{predefined option}[argument number]{predefined text}
\defbeamertemplate{element name}{predefined option}{predefined text}

\defbeamertemplatealias{element name}{new predefined option name}{existing predefined option name}

\defbeamertemplateparent{parent template}[predefined option]{child template list}[args][default]{arguments for children}
\defbeamertemplateparent{parent template}{child template list}[args][default]{args for children}
\defbeamertemplateparent{parent template}{child template list}{args for children}

\setbeamertemplate{element name}{arguments}
\setbeamertemplate{element name}[predefined option]
\setbeamertemplate{element name}[predefined option]{arguments}

\addtobeamertemplate{element name}{pre-text%text}{post-text%text}