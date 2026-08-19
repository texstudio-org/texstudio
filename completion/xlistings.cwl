# xlistings package
# Matthew Bertucci 2026/08/18 for v1.0.0

#include:kvoptions
#include:etoolbox
#include:xcolor
#include:pgfkeys
#include:listingsutf8
#include:accsupp
#include:lstautogobble

#keyvals:\usepackage/xlistings#c
print#true,false
digital
guardspace#true,false
numinpar#true,false
hlnumbers#true,false
upshape#true,false
inlinesize#true,false
highlights#true,false
fakeminted#true,false
extendednums#true,false
debug#true,false
style=%<style%>
#endkeyvals

\begin{minted}{language}#V
\begin{minted}[options%keyvals]{language}#V
\end{minted}

\BadgeNextListing{language}
\LoadLanguages{languages}
\lstcolorlet{type}{color}
\xlstb[options%keyvals]{language}{code%definition}
\xlstblacklistlinenumbers*{integer}
\xlstblacklistlinenumbers{integer}
\xlstb{language}{code%definition}
\xlstc[options%keyvals]{language}{code%definition}
\xlstc{language}{code%definition}
\xlstguard{number}
\xlsthlboxd{TikZ keys}
\xlsthlbox{color}
\xlsthlerror
\xlsthlinfo
\xlsthlwarning
\xlsti[options%keyvals]{language}{code%definition}
\xlsti{language}{code%definition}
\xlstlangoverride{language}{options%keyvals}
\xlstmintedwithlangbadge
\xlstmintedwithoutlangbadge
\xlstSetFrameRule{length}
\xlstSetLeftMargin{length}
\xlstSetNumSep{length}
\xlstSetRightMargin{length}
\xlstsetstyle{style}

xlsterror#B
xlstinfo#B
xlstwarning#B

\RegisterLanguage{language}{lst language}#*
\RegisterLanguage[aliases]{language}{lst language}#*
\xlstlangbadgestyle{arg}#*

# not documented
\LoadLanguage{language}#S
\lstcolordef[mode]{type}{color}#S
\lstcolordef{type}{color}#S
\lstfs#S
\lstfs*#S
\lstfs*[opt]#S
\lstfs[opt]#S
\xlstblacklistisghost#S
\xlstblacklistispresent#S
\xlstcustom#S
\xlstdisablenumhl#S
\xlstenablenumhl#S
\xlstGetStyle{arg}#S
\xlstIfPmode{arg1}{arg2}#S
\xlstInlinePreBreak{arg}#S
\xlstLanguageFilePrefix#S
\xlstLanguageSearchPath#S
\xlstmintedmap{arg1}{arg2}#S
\xlstNumFs{arg}#S
\xlstPreBreak{arg}#S
\xlstRemoveInputBackground#S
\xlstSetInputDefaults{arg}#S
\xlstSetLiterateTable#S
\xlstsetmintedstyle{arg}#S
\xlstSetStyle{arg1}{arg2}#S
\xlstset{arg}#S
\xlstStyles#S