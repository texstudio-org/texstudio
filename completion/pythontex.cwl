# pythontex package
# Matthew Bertucci 12/30/2021 for v0.18

#include:fvextra
#include:etoolbox
#include:xstring
#include:pgfopts
#include:newfloat
#include:currfile
#include:xcolor
#include:upquote

#keyvals:\usepackage/pythontex#c
usefamily=#ruby,rb,julia,juliacon,jl,matlab,octave,bash,sage,rust,rs,R,Rcon,perl,pl,perlsix,psix,javascript,js
gobble=#none,auto
beta#true,false
runall#true,false
rerun=#never,modified,errors,warnings,always
hashdependencies#true,false
autoprint#true,false
autostdout#true,false
debug
makestderr#true,false
stderrfilename=#full,session,genericfile,genericscript
pyfuture=#none,all,default
pyconfuture=#none,all,default
upquote#true,false
fixlr#true,false
keeptemps=#all,code,none
prettyprinter=#pygments,fancyvrb
prettyprintinline#true,false
pygments#true,false
pyginline#true,false
pyglexer=%<pygments lexer%>
pygopt={%<pygments options%>}
fvextfile
fvextfile=%<integer%>
pyconbanner=#none,standard,default,pyversion
pyconfilename=#stdin,console
depythontex#true,false
#endkeyvals

## py family ##
\py{code}
\py[session]{code}
\pyc{code}
\pyc[session]{code}
\pys{code}
\pys[session]{code}
\pyv|%<code%>|
\pyv[%<session%>]|%<code%>|
\pyv[session]{verbatimSymbol}#S
\pyb{code}
\pyb[session]{code}

\begin{pycode}
\begin{pycode}[session]
\begin{pycode}[session][fancyvrb settings%keyvals]#*
\end{pycode}
\begin{pysub}
\begin{pysub}[session]
\begin{pysub}[session][fancyvrb settings%keyvals]#*
\end{pysub}
\begin{pyverbatim}#V
\begin{pyverbatim}[session]#V
\begin{pyverbatim}[session][fancyvrb settings%keyvals]#V
\end{pyverbatim}
\begin{pyblock}
\begin{pyblock}[session]
\begin{pyblock}[session][fancyvrb settings%keyvals]
\end{pyblock}

## pycon family ##
\pycon{code}
\pycon[session]{code}
\pycons{code}
\pycons[session]{code}
\pyconc{code}
\pyconc[session]{code}
\pyconv|%<code%>|
\pyconv[%<session%>]|%<code%>|
\pyconv[session]{verbatimSymbol}#S

\begin{pyconsole}
\begin{pyconsole}[session]
\begin{pyconsole}[session][fancyvrb settings%keyvals]
\end{pyconsole}
\begin{pyconcode}
\begin{pyconcode}[session]
\begin{pyconcode}[session][fancyvrb settings%keyvals]#*
\end{pyconcode}
\begin{pyconsub}
\begin{pyconsub}[session]
\begin{pyconsub}[session][fancyvrb settings%keyvals]#*
\end{pyconsub}
\begin{pyconverbatim}#V
\begin{pyconverbatim}[session]#V
\begin{pyconverbatim}[session][fancyvrb settings%keyvals]#V
\end{pyconverbatim}

## pylab family ##
\pylab{code}
\pylab[session]{code}
\pylabc{code}
\pylabc[session]{code}
\pylabs{code}
\pylabs[session]{code}
\pylabv|%<code%>|
\pylabv[%<session%>]|%<code%>|
\pylabv[session]{verbatimSymbol}#S
\pylabb{code}
\pylabb[session]{code}

\begin{pylabcode}
\begin{pylabcode}[session]
\begin{pylabcode}[session][fancyvrb settings%keyvals]#*
\end{pylabcode}
\begin{pylabsub}
\begin{pylabsub}[session]
\begin{pylabsub}[session][fancyvrb settings%keyvals]#*
\end{pylabsub}
\begin{pylabverbatim}#V
\begin{pylabverbatim}[session]#V
\begin{pylabverbatim}[session][fancyvrb settings%keyvals]#V
\end{pylabverbatim}
\begin{pylabblock}
\begin{pylabblock}[session]
\begin{pylabblock}[session][fancyvrb settings%keyvals]
\end{pylabblock}

## pylabcon family ##
\pylabcon{code}
\pylabcon[session]{code}
\pylabconc{code}
\pylabconc[session]{code}
\pylabcons{code}
\pylabcons[session]{code}
\pylabconv|%<code%>|
\pylabconv[%<session%>]|%<code%>|
\pylabconv[session]{verbatimSymbol}#S

\begin{pylabconsole}
\begin{pylabconsole}[session]
\begin{pylabconsole}[session][fancyvrb settings%keyvals]
\end{pylabconsole}
\begin{pylabconcode}
\begin{pylabconcode}[session]
\begin{pylabconcode}[session][fancyvrb settings%keyvals]#*
\end{pylabconcode}
\begin{pylabconsub}
\begin{pylabconsub}[session]
\begin{pylabconsub}[session][fancyvrb settings%keyvals]#*
\end{pylabconsub}
\begin{pylabconverbatim}#V
\begin{pylabconverbatim}[session]#V
\begin{pylabconverbatim}[session][fancyvrb settings%keyvals]#V
\end{pylabconverbatim}

## sympy family##
\sympy{code}
\sympy[session]{code}
\sympyc{code}
\sympyc[session]{code}
\sympys{code}
\sympys[session]{code}
\sympyv|%<code%>|
\sympyv[%<session%>]|%<code%>|
\sympyv[session]{verbatimSymbol}#S
\sympyb{code}
\sympyb[session]{code}

\begin{sympycode}
\begin{sympycode}[session]
\begin{sympycode}[session][fancyvrb settings%keyvals]#*
\end{sympycode}
\begin{sympysub}
\begin{sympysub}[session]
\begin{sympysub}[session][fancyvrb settings%keyvals]#*
\end{sympysub}
\begin{sympyverbatim}#V
\begin{sympyverbatim}[session]#V
\begin{sympyverbatim}[session][fancyvrb settings%keyvals]#V
\end{sympyverbatim}
\begin{sympyblock}
\begin{sympyblock}[session]
\begin{sympyblock}[session][fancyvrb settings%keyvals]
\end{sympyblock}

## sympycon family ##
\sympycon{code}
\sympycon[session]{code}
\sympycons{code}
\sympycons[session]{code}
\sympyconc{code}
\sympyconc[session]{code}
\sympyconv|%<code%>|
\sympyconv[%<session%>]|%<code%>|
\sympyconv[session]{verbatimSymbol}#S

\begin{sympyconsole}
\begin{sympyconsole}[session]
\begin{sympyconsole}[session][fancyvrb settings%keyvals]
\end{sympyconsole}
\begin{sympyconcode}
\begin{sympyconcode}[session]
\begin{sympyconcode}[session][fancyvrb settings%keyvals]#*
\end{sympyconcode}
\begin{sympyconsub}
\begin{sympyconsub}[session]
\begin{sympyconsub}[session][fancyvrb settings%keyvals]#*
\end{sympyconsub}
\begin{sympyconverbatim}#V
\begin{sympyconverbatim}[session]#V
\begin{sympyconverbatim}[session][fancyvrb settings%keyvals]#V
\end{sympyconverbatim}

## customization ##
\pythontexcustomc{family}{code}
\pythontexcustomc[position%keyvals]{family}{code}
\begin{pythontexcustomcode}{family}
\begin{pythontexcustomcode}[position%keyvals]{family}
\end{pythontexcustomcode}

#keyvals:\pythontexcustomc,\begin{pythontexcustomcode}
begin
end
#endkeyvals

\setpythontexfv{fancyvrb settings%keyvals}
\setpythontexfv[family]{fancyvrb settings%keyvals}

\setpythontexprettyprinter{printer%keyvals}
\setpythontexprettyprinter[family]{printer%keyvals}

#keyvals:\setpythontexprettyprinter
fancyvrb
pygments
#endkeyvals

\setpythontexpyglexer{pygments lexer}
\setpythontexpyglexer[family]{pygments lexer}
\setpythontexpygopt{pygments options}
\setpythontexpygopt[family]{pygments options}

\printpythontex
\printpythontex[mode%keyvals]
\printpythontex[mode%keyvals][fancyvrb settings]
\stdoutpythontex
\stdoutpythontex[mode%keyvals]
\stdoutpythontex[mode%keyvals][fancyvrb settings]

\saveprintpythontex{name}
\savestdoutpythontex{name}

\useprintpythontex{name}
\useprintpythontex[mode%keyvals]{name}
\useprintpythontex[mode%keyvals][fancyvrb settings]{name}
\usestdoutpythontex{name}
\usestdoutpythontex[mode%keyvals]{name}
\usestdoutpythontex[mode%keyvals][fancyvrb settings]{name}

\stderrpythontex
\stderrpythontex[mode%keyvals]
\stderrpythontex[mode%keyvals][fancyvrb settings]

\savestderrpythontex{name}

\usestderrpythontex{name}
\usestderrpythontex[mode%keyvals]{name}
\usestderrpythontex[mode%keyvals][fancyvrb settings]{name}

#keyvals:\printpythontex,\stdoutpythontex,\useprintpythontex,\usestdoutpythontex,\stderrpythontex,\usestderrpythontex
raw
verb
verbatim
#endkeyvals

\setpythontexautoprint{true or false}
\setpythontexautostdout{true or false}

## pygments commands and environments ##
\pygment{lexer}{code}
\begin{pygments}{lexer}#V
\begin{pygments}[fancyvrb settings%keyvals]{lexer}#V
\end{pygments}

\inputpygments{lexer}{file}#i
\inputpygments[fancyvrb settings%keyvals]{lexer}{file}#i

\setpygmentsfv{fancyvrb settings%keyvals}
\setpygmentsfv[lexer]{fancyvrb settings%keyvals}

\setpygmentspygopt{pygments options}
\setpygmentspygopt[lexer]{pygments options}

\setpygmentsprettyprinter{printer%keyvals}
#keyvals:\setpygmentsprettyprinter
fancyvrb
pygments
#endkeyvals

## general code typesetting ##
\begin{listing}#V
\end{listing}

\setpythontexlistingenv{envname}#N

## advanced pythontex usage ##
\setpythontexcontext{key-value pairs}
\restartpythontexsession{%<counter value(s)%>}
\setpythontexoutputdir{output directory}
\setpythontexworkingdir{working directory}

### Families not loaded by default ###
# families can be loaded using either "usefamily=family" or "usefamily={family1,family2,...}"
# the highlighter can't parse the latter syntax so we list each set of commands twice:
# once with #S so they're not marked incorrect, and once in an ifOption block for when
# the first option syntax is used (in this case they'll show in the completer)

## rb family ##
#ifOption:usefamily=rb
\rb{code}
\rb[session]{code}
\rbc{code}
\rbc[session]{code}
\rbs{code}
\rbs[session]{code}
\rbv|%<code%>|
\rbv[%<session%>]|%<code%>|
\rbv[session]{verbatimSymbol}#S
\rbb{code}
\rbb[session]{code}
\begin{rbcode}
\begin{rbcode}[session]
\begin{rbcode}[session][fancyvrb settings%keyvals]#*
\end{rbcode}
\begin{rbsub}
\begin{rbsub}[session]
\begin{rbsub}[session][fancyvrb settings%keyvals]#*
\end{rbsub}
\begin{rbverbatim}#V
\begin{rbverbatim}[session]#V
\begin{rbverbatim}[session][fancyvrb settings%keyvals]#V
\end{rbverbatim}
\begin{rbblock}
\begin{rbblock}[session]
\begin{rbblock}[session][fancyvrb settings%keyvals]
\end{rbblock}
#endif

\rb{code}#S
\rb[session]{code}#S
\rbc{code}#S
\rbc[session]{code}#S
\rbs{code}#S
\rbs[session]{code}#S
\rbv|%<code%>|#S
\rbv[%<session%>]|%<code%>|#S
\rbv[session]{verbatimSymbol}#S
\rbb{code}#S
\rbb[session]{code}#S
\begin{rbcode}#S
\begin{rbcode}[session]#S
\begin{rbcode}[session][fancyvrb settings%keyvals]#S
\end{rbcode}#S
\begin{rbsub}#S
\begin{rbsub}[session]#S
\begin{rbsub}[session][fancyvrb settings%keyvals]#S
\end{rbsub}#S
\begin{rbverbatim}#SV
\begin{rbverbatim}[session]#SV
\begin{rbverbatim}[session][fancyvrb settings%keyvals]#SV
\end{rbverbatim}#S
\begin{rbblock}#S
\begin{rbblock}[session]#S
\begin{rbblock}[session][fancyvrb settings%keyvals]#S
\end{rbblock}#S

## ruby family ##
#ifOption:usefamily=ruby
\ruby{code}
\ruby[session]{code}
\rubyc{code}
\rubyc[session]{code}
\rubys{code}
\rubys[session]{code}
\rubyv|%<code%>|
\rubyv[%<session%>]|%<code%>|
\rubyv[session]{verbatimSymbol}#S
\rubyb{code}
\rubyb[session]{code}
\begin{rubycode}
\begin{rubycode}[session]
\begin{rubycode}[session][fancyvrb settings%keyvals]#*
\end{rubycode}
\begin{rubysub}
\begin{rubysub}[session]
\begin{rubysub}[session][fancyvrb settings%keyvals]#*
\end{rubysub}
\begin{rubyverbatim}#V
\begin{rubyverbatim}[session]#V
\begin{rubyverbatim}[session][fancyvrb settings%keyvals]#V
\end{rubyverbatim}
\begin{rubyblock}
\begin{rubyblock}[session]
\begin{rubyblock}[session][fancyvrb settings%keyvals]
\end{rubyblock}
#endif

\ruby{code}#S
\ruby[session]{code}#S
\rubyc{code}#S
\rubyc[session]{code}#S
\rubys{code}#S
\rubys[session]{code}#S
\rubyv|%<code%>|#S
\rubyv[%<session%>]|%<code%>|#S
\rubyv[session]{verbatimSymbol}#S
\rubyb{code}#S
\rubyb[session]{code}#S
\begin{rubycode}#S
\begin{rubycode}[session]#S
\begin{rubycode}[session][fancyvrb settings%keyvals]#S
\end{rubycode}#S
\begin{rubysub}#S
\begin{rubysub}[session]#S
\begin{rubysub}[session][fancyvrb settings%keyvals]#S
\end{rubysub}#S
\begin{rubyverbatim}#SV
\begin{rubyverbatim}[session]#SV
\begin{rubyverbatim}[session][fancyvrb settings%keyvals]#SV
\end{rubyverbatim}#S
\begin{rubyblock}#S
\begin{rubyblock}[session]#S
\begin{rubyblock}[session][fancyvrb settings%keyvals]#S
\end{rubyblock}#S

## julia family ##
#ifOption:usefamily=julia
\julia{code}
\julia[session]{code}
\juliac{code}
\juliac[session]{code}
\julias{code}
\julias[session]{code}
\juliav|%<code%>|
\juliav[%<session%>]|%<code%>|
\juliav[session]{verbatimSymbol}#S
\juliab{code}
\juliab[session]{code}
\begin{juliacode}
\begin{juliacode}[session]
\begin{juliacode}[session][fancyvrb settings%keyvals]#*
\end{juliacode}
\begin{juliasub}
\begin{juliasub}[session]
\begin{juliasub}[session][fancyvrb settings%keyvals]#*
\end{juliasub}
\begin{juliaverbatim}#V
\begin{juliaverbatim}[session]#V
\begin{juliaverbatim}[session][fancyvrb settings%keyvals]#V
\end{juliaverbatim}
\begin{juliablock}
\begin{juliablock}[session]
\begin{juliablock}[session][fancyvrb settings%keyvals]
\end{juliablock}
#endif

\julia{code}#S
\julia[session]{code}#S
\juliac{code}#S
\juliac[session]{code}#S
\julias{code}#S
\julias[session]{code}#S
\juliav|%<code%>|#S
\juliav[%<session%>]|%<code%>|#S
\juliav[session]{verbatimSymbol}#S
\juliab{code}#S
\juliab[session]{code}#S
\begin{juliacode}#S
\begin{juliacode}[session]#S
\begin{juliacode}[session][fancyvrb settings%keyvals]#S
\end{juliacode}#S
\begin{juliasub}#S
\begin{juliasub}[session]#S
\begin{juliasub}[session][fancyvrb settings%keyvals]#S
\end{juliasub}#S
\begin{juliaverbatim}#SV
\begin{juliaverbatim}[session]#SV
\begin{juliaverbatim}[session][fancyvrb settings%keyvals]#SV
\end{juliaverbatim}#S
\begin{juliablock}#S
\begin{juliablock}[session]#S
\begin{juliablock}[session][fancyvrb settings%keyvals]#S
\end{juliablock}#S

## juliacon family ##
#ifOption:usefamily=juliacon
\begin{juliaconsole}
\begin{juliaconsole}[session]
\begin{juliaconsole}[session][fancyvrb settings%keyvals]
\end{juliaconsole}
\begin{juliaconcode}
\begin{juliaconcode}[session]
\begin{juliaconcode}[session][fancyvrb settings%keyvals]#*
\end{juliaconcode}
#endif

\begin{juliaconsole}#S
\begin{juliaconsole}[session]#S
\begin{juliaconsole}[session][fancyvrb settings%keyvals]#S
\end{juliaconsole}#S
\begin{juliaconcode}#S
\begin{juliaconcode}[session]#S
\begin{juliaconcode}[session][fancyvrb settings%keyvals]#S
\end{juliaconcode}#S

## jl family ##
#ifOption:usefamily=jl
\jl{code}
\jl[session]{code}
\jlc{code}
\jlc[session]{code}
\jls{code}
\jls[session]{code}
\jlv|%<code%>|
\jlv[%<session%>]|%<code%>|
\jlv[session]{verbatimSymbol}#S
\jlb{code}
\jlb[session]{code}
\begin{jlcode}
\begin{jlcode}[session]
\begin{jlcode}[session][fancyvrb settings%keyvals]#*
\end{jlcode}
\begin{jlsub}
\begin{jlsub}[session]
\begin{jlsub}[session][fancyvrb settings%keyvals]#*
\end{jlsub}
\begin{jlverbatim}#V
\begin{jlverbatim}[session]#V
\begin{jlverbatim}[session][fancyvrb settings%keyvals]#V
\end{jlverbatim}
\begin{jlblock}
\begin{jlblock}[session]
\begin{jlblock}[session][fancyvrb settings%keyvals]
\end{jlblock}
#endif

\jl{code}#S
\jl[session]{code}#S
\jlc{code}#S
\jlc[session]{code}#S
\jls{code}#S
\jls[session]{code}#S
\jlv|%<code%>|#S
\jlv[%<session%>]|%<code%>|#S
\jlv[session]{verbatimSymbol}#S
\jlb{code}#S
\jlb[session]{code}#S
\begin{jlcode}#S
\begin{jlcode}[session]#S
\begin{jlcode}[session][fancyvrb settings%keyvals]#S
\end{jlcode}#S
\begin{jlsub}#S
\begin{jlsub}[session]#S
\begin{jlsub}[session][fancyvrb settings%keyvals]#S
\end{jlsub}#S
\begin{jlverbatim}#SV
\begin{jlverbatim}[session]#SV
\begin{jlverbatim}[session][fancyvrb settings%keyvals]#SV
\end{jlverbatim}#S
\begin{jlblock}#S
\begin{jlblock}[session]#S
\begin{jlblock}[session][fancyvrb settings%keyvals]#S
\end{jlblock}#S

## matlab family ##
#ifOption:usefamily=matlab
\matlab{code}
\matlab[session]{code}
\matlabc{code}
\matlabc[session]{code}
\matlabs{code}
\matlabs[session]{code}
\matlabv|%<code%>|
\matlabv[%<session%>]|%<code%>|
\matlabv[session]{verbatimSymbol}#S
\matlabb{code}
\matlabb[session]{code}
\begin{matlabcode}
\begin{matlabcode}[session]
\begin{matlabcode}[session][fancyvrb settings%keyvals]#*
\end{matlabcode}
\begin{matlabsub}
\begin{matlabsub}[session]
\begin{matlabsub}[session][fancyvrb settings%keyvals]#*
\end{matlabsub}
\begin{matlabverbatim}#V
\begin{matlabverbatim}[session]#V
\begin{matlabverbatim}[session][fancyvrb settings%keyvals]#V
\end{matlabverbatim}
\begin{matlabblock}
\begin{matlabblock}[session]
\begin{matlabblock}[session][fancyvrb settings%keyvals]
\end{matlabblock}
#endif

\matlab{code}#S
\matlab[session]{code}#S
\matlabc{code}#S
\matlabc[session]{code}#S
\matlabs{code}#S
\matlabs[session]{code}#S
\matlabv|%<code%>|#S
\matlabv[%<session%>]|%<code%>|#S
\matlabv[session]{verbatimSymbol}#S
\matlabb{code}#S
\matlabb[session]{code}#S
\begin{matlabcode}#S
\begin{matlabcode}[session]#S
\begin{matlabcode}[session][fancyvrb settings%keyvals]#S
\end{matlabcode}#S
\begin{matlabsub}#S
\begin{matlabsub}[session]#S
\begin{matlabsub}[session][fancyvrb settings%keyvals]#S
\end{matlabsub}#S
\begin{matlabverbatim}#SV
\begin{matlabverbatim}[session]#SV
\begin{matlabverbatim}[session][fancyvrb settings%keyvals]#SV
\end{matlabverbatim}#S
\begin{matlabblock}#S
\begin{matlabblock}[session]#S
\begin{matlabblock}[session][fancyvrb settings%keyvals]#S
\end{matlabblock}#S

## octave family ##
#ifOption:usefamily=octave
\octave{code}
\octave[session]{code}
\octavec{code}
\octavec[session]{code}
\octaves{code}
\octaves[session]{code}
\octavev|%<code%>|
\octavev[%<session%>]|%<code%>|
\octavev[session]{verbatimSymbol}#S
\octaveb{code}
\octaveb[session]{code}
\begin{octavecode}
\begin{octavecode}[session]
\begin{octavecode}[session][fancyvrb settings%keyvals]#*
\end{octavecode}
\begin{octavesub}
\begin{octavesub}[session]
\begin{octavesub}[session][fancyvrb settings%keyvals]#*
\end{octavesub}
\begin{octaveverbatim}#V
\begin{octaveverbatim}[session]#V
\begin{octaveverbatim}[session][fancyvrb settings%keyvals]#V
\end{octaveverbatim}
\begin{octaveblock}
\begin{octaveblock}[session]
\begin{octaveblock}[session][fancyvrb settings%keyvals]
\end{octaveblock}
#endif

\octave{code}#S
\octave[session]{code}#S
\octavec{code}#S
\octavec[session]{code}#S
\octaves{code}#S
\octaves[session]{code}#S
\octavev|%<code%>|#S
\octavev[%<session%>]|%<code%>|#S
\octavev[session]{verbatimSymbol}#S
\octaveb{code}#S
\octaveb[session]{code}#S
\begin{octavecode}#S
\begin{octavecode}[session]#S
\begin{octavecode}[session][fancyvrb settings%keyvals]#S
\end{octavecode}#S
\begin{octavesub}#S
\begin{octavesub}[session]#S
\begin{octavesub}[session][fancyvrb settings%keyvals]#S
\end{octavesub}#S
\begin{octaveverbatim}#SV
\begin{octaveverbatim}[session]#SV
\begin{octaveverbatim}[session][fancyvrb settings%keyvals]#SV
\end{octaveverbatim}#S
\begin{octaveblock}#S
\begin{octaveblock}[session]#S
\begin{octaveblock}[session][fancyvrb settings%keyvals]#S
\end{octaveblock}#S

## bash family ##
#ifOption:usefamily=bash
\bash{code}
\bash[session]{code}
\bashc{code}
\bashc[session]{code}
\bashs{code}
\bashs[session]{code}
\bashv|%<code%>|
\bashv[%<session%>]|%<code%>|
\bashv[session]{verbatimSymbol}#S
\bashb{code}
\bashb[session]{code}
\begin{bashcode}
\begin{bashcode}[session]
\begin{bashcode}[session][fancyvrb settings%keyvals]#*
\end{bashcode}
\begin{bashsub}
\begin{bashsub}[session]
\begin{bashsub}[session][fancyvrb settings%keyvals]#*
\end{bashsub}
\begin{bashverbatim}#V
\begin{bashverbatim}[session]#V
\begin{bashverbatim}[session][fancyvrb settings%keyvals]#V
\end{bashverbatim}
\begin{bashblock}
\begin{bashblock}[session]
\begin{bashblock}[session][fancyvrb settings%keyvals]
\end{bashblock}
#endif

\bash{code}#S
\bash[session]{code}#S
\bashc{code}#S
\bashc[session]{code}#S
\bashs{code}#S
\bashs[session]{code}#S
\bashv|%<code%>|#S
\bashv[%<session%>]|%<code%>|#S
\bashv[session]{verbatimSymbol}#S
\bashb{code}#S
\bashb[session]{code}#S
\begin{bashcode}#S
\begin{bashcode}[session]#S
\begin{bashcode}[session][fancyvrb settings%keyvals]#S
\end{bashcode}#S
\begin{bashsub}#S
\begin{bashsub}[session]#S
\begin{bashsub}[session][fancyvrb settings%keyvals]#S
\end{bashsub}#S
\begin{bashverbatim}#SV
\begin{bashverbatim}[session]#SV
\begin{bashverbatim}[session][fancyvrb settings%keyvals]#SV
\end{bashverbatim}#S
\begin{bashblock}#S
\begin{bashblock}[session]#S
\begin{bashblock}[session][fancyvrb settings%keyvals]#S
\end{bashblock}#S

## sage family ##
#ifOption:usefamily=sage
\sage{code}
\sage[session]{code}
\sagec{code}
\sagec[session]{code}
\sages{code}
\sages[session]{code}
\sagev|%<code%>|
\sagev[%<session%>]|%<code%>|
\sagev[session]{verbatimSymbol}#S
\sageb{code}
\sageb[session]{code}
\begin{sagecode}
\begin{sagecode}[session]
\begin{sagecode}[session][fancyvrb settings%keyvals]#*
\end{sagecode}
\begin{sagesub}
\begin{sagesub}[session]
\begin{sagesub}[session][fancyvrb settings%keyvals]#*
\end{sagesub}
\begin{sageverbatim}#V
\begin{sageverbatim}[session]#V
\begin{sageverbatim}[session][fancyvrb settings%keyvals]#V
\end{sageverbatim}
\begin{sageblock}
\begin{sageblock}[session]
\begin{sageblock}[session][fancyvrb settings%keyvals]
\end{sageblock}
#endif

\sage{code}#S
\sage[session]{code}#S
\sagec{code}#S
\sagec[session]{code}#S
\sages{code}#S
\sages[session]{code}#S
\sagev|%<code%>|#S
\sagev[%<session%>]|%<code%>|#S
\sagev[session]{verbatimSymbol}#S
\sageb{code}#S
\sageb[session]{code}#S
\begin{sagecode}#S
\begin{sagecode}[session]#S
\begin{sagecode}[session][fancyvrb settings%keyvals]#S
\end{sagecode}#S
\begin{sagesub}#S
\begin{sagesub}[session]#S
\begin{sagesub}[session][fancyvrb settings%keyvals]#S
\end{sagesub}#S
\begin{sageverbatim}#SV
\begin{sageverbatim}[session]#SV
\begin{sageverbatim}[session][fancyvrb settings%keyvals]#SV
\end{sageverbatim}#S
\begin{sageblock}#S
\begin{sageblock}[session]#S
\begin{sageblock}[session][fancyvrb settings%keyvals]#S
\end{sageblock}#S

## rust family ##
#ifOption:usefamily=rust
\rust{code}
\rust[session]{code}
\rustc{code}
\rustc[session]{code}
\rusts{code}
\rusts[session]{code}
\rustv|%<code%>|
\rustv[%<session%>]|%<code%>|
\rustv[session]{verbatimSymbol}#S
\rustb{code}
\rustb[session]{code}
\begin{rustcode}
\begin{rustcode}[session]
\begin{rustcode}[session][fancyvrb settings%keyvals]#*
\end{rustcode}
\begin{rustsub}
\begin{rustsub}[session]
\begin{rustsub}[session][fancyvrb settings%keyvals]#*
\end{rustsub}
\begin{rustverbatim}#V
\begin{rustverbatim}[session]#V
\begin{rustverbatim}[session][fancyvrb settings%keyvals]#V
\end{rustverbatim}
\begin{rustblock}
\begin{rustblock}[session]
\begin{rustblock}[session][fancyvrb settings%keyvals]
\end{rustblock}
#endif

\rust{code}#S
\rust[session]{code}#S
\rustc{code}#S
\rustc[session]{code}#S
\rusts{code}#S
\rusts[session]{code}#S
\rustv|%<code%>|#S
\rustv[%<session%>]|%<code%>|#S
\rustv[session]{verbatimSymbol}#S
\rustb{code}#S
\rustb[session]{code}#S
\begin{rustcode}#S
\begin{rustcode}[session]#S
\begin{rustcode}[session][fancyvrb settings%keyvals]#S
\end{rustcode}#S
\begin{rustsub}#S
\begin{rustsub}[session]#S
\begin{rustsub}[session][fancyvrb settings%keyvals]#S
\end{rustsub}#S
\begin{rustverbatim}#SV
\begin{rustverbatim}[session]#SV
\begin{rustverbatim}[session][fancyvrb settings%keyvals]#SV
\end{rustverbatim}#S
\begin{rustblock}#S
\begin{rustblock}[session]#S
\begin{rustblock}[session][fancyvrb settings%keyvals]#S
\end{rustblock}#S

## rs family ##
#ifOption:usefamily=rs
\rs{code}
\rs[session]{code}
\rsc{code}
\rsc[session]{code}
\rss{code}
\rss[session]{code}
\rsv|%<code%>|
\rsv[%<session%>]|%<code%>|
\rsv[session]{verbatimSymbol}#S
\rsb{code}
\rsb[session]{code}
\begin{rscode}
\begin{rscode}[session]
\begin{rscode}[session][fancyvrb settings%keyvals]#*
\end{rscode}
\begin{rssub}
\begin{rssub}[session]
\begin{rssub}[session][fancyvrb settings%keyvals]#*
\end{rssub}
\begin{rsverbatim}#V
\begin{rsverbatim}[session]#V
\begin{rsverbatim}[session][fancyvrb settings%keyvals]#V
\end{rsverbatim}
\begin{rsblock}
\begin{rsblock}[session]
\begin{rsblock}[session][fancyvrb settings%keyvals]
\end{rsblock}
#endif

\rs{code}#S
\rs[session]{code}#S
\rsc{code}#S
\rsc[session]{code}#S
\rss{code}#S
\rss[session]{code}#S
\rsv|%<code%>|#S
\rsv[%<session%>]|%<code%>|#S
\rsv[session]{verbatimSymbol}#S
\rsb{code}#S
\rsb[session]{code}#S
\begin{rscode}#S
\begin{rscode}[session]#S
\begin{rscode}[session][fancyvrb settings%keyvals]#S
\end{rscode}#S
\begin{rssub}#S
\begin{rssub}[session]#S
\begin{rssub}[session][fancyvrb settings%keyvals]#S
\end{rssub}#S
\begin{rsverbatim}#SV
\begin{rsverbatim}[session]#SV
\begin{rsverbatim}[session][fancyvrb settings%keyvals]#SV
\end{rsverbatim}#S
\begin{rsblock}#S
\begin{rsblock}[session]#S
\begin{rsblock}[session][fancyvrb settings%keyvals]#S
\end{rsblock}#S

## R family ##
#ifOption:usefamily=R
\R{code}
\R[session]{code}
\Rc{code}
\Rc[session]{code}
\Rs{code}
\Rs[session]{code}
\Rv|%<code%>|
\Rv[%<session%>]|%<code%>|
\Rv[session]{verbatimSymbol}#S
\Rb{code}
\Rb[session]{code}
\begin{Rcode}
\begin{Rcode}[session]
\begin{Rcode}[session][fancyvrb settings%keyvals]#*
\end{Rcode}
\begin{Rsub}
\begin{Rsub}[session]
\begin{Rsub}[session][fancyvrb settings%keyvals]#*
\end{Rsub}
\begin{Rverbatim}#V
\begin{Rverbatim}[session]#V
\begin{Rverbatim}[session][fancyvrb settings%keyvals]#V
\end{Rverbatim}
\begin{Rblock}
\begin{Rblock}[session]
\begin{Rblock}[session][fancyvrb settings%keyvals]
\end{Rblock}
#endif

\R{code}#S
\R[session]{code}#S
\Rc{code}#S
\Rc[session]{code}#S
\Rs{code}#S
\Rs[session]{code}#S
\Rv|%<code%>|#S
\Rv[%<session%>]|%<code%>|#S
\Rv[session]{verbatimSymbol}#S
\Rb{code}#S
\Rb[session]{code}#S
\begin{Rcode}#S
\begin{Rcode}[session]#S
\begin{Rcode}[session][fancyvrb settings%keyvals]#S
\end{Rcode}#S
\begin{Rsub}#S
\begin{Rsub}[session]#S
\begin{Rsub}[session][fancyvrb settings%keyvals]#S
\end{Rsub}#S
\begin{Rverbatim}#SV
\begin{Rverbatim}[session]#SV
\begin{Rverbatim}[session][fancyvrb settings%keyvals]#SV
\end{Rverbatim}#S
\begin{Rblock}#S
\begin{Rblock}[session]#S
\begin{Rblock}[session][fancyvrb settings%keyvals]#S
\end{Rblock}#S

## Rcon family ##
#ifOption:usefamily=juliacon
\begin{Rconsole}
\begin{Rconsole}[session]
\begin{Rconsole}[session][fancyvrb settings%keyvals]
\end{Rconsole}
\begin{Rconcode}
\begin{Rconcode}[session]
\begin{Rconcode}[session][fancyvrb settings%keyvals]#*
\end{Rconcode}
#endif

\begin{Rconsole}#S
\begin{Rconsole}[session]#S
\begin{Rconsole}[session][fancyvrb settings%keyvals]#S
\end{Rconsole}#S
\begin{Rconcode}#S
\begin{Rconcode}[session]#S
\begin{Rconcode}[session][fancyvrb settings%keyvals]#S
\end{Rconcode}#S

## perl family ##
#ifOption:usefamily=perl
\perl{code}
\perl[session]{code}
\perlc{code}
\perlc[session]{code}
\perls{code}
\perls[session]{code}
\perlv|%<code%>|
\perlv[%<session%>]|%<code%>|
\perlv[session]{verbatimSymbol}#S
\perlb{code}
\perlb[session]{code}
\begin{perlcode}
\begin{perlcode}[session]
\begin{perlcode}[session][fancyvrb settings%keyvals]#*
\end{perlcode}
\begin{perlsub}
\begin{perlsub}[session]
\begin{perlsub}[session][fancyvrb settings%keyvals]#*
\end{perlsub}
\begin{perlverbatim}#V
\begin{perlverbatim}[session]#V
\begin{perlverbatim}[session][fancyvrb settings%keyvals]#V
\end{perlverbatim}
\begin{perlblock}
\begin{perlblock}[session]
\begin{perlblock}[session][fancyvrb settings%keyvals]
\end{perlblock}
#endif

\perl{code}#S
\perl[session]{code}#S
\perlc{code}#S
\perlc[session]{code}#S
\perls{code}#S
\perls[session]{code}#S
\perlv|%<code%>|#S
\perlv[%<session%>]|%<code%>|#S
\perlv[session]{verbatimSymbol}#S
\perlb{code}#S
\perlb[session]{code}#S
\begin{perlcode}#S
\begin{perlcode}[session]#S
\begin{perlcode}[session][fancyvrb settings%keyvals]#S
\end{perlcode}#S
\begin{perlsub}#S
\begin{perlsub}[session]#S
\begin{perlsub}[session][fancyvrb settings%keyvals]#S
\end{perlsub}#S
\begin{perlverbatim}#SV
\begin{perlverbatim}[session]#SV
\begin{perlverbatim}[session][fancyvrb settings%keyvals]#SV
\end{perlverbatim}#S
\begin{perlblock}#S
\begin{perlblock}[session]#S
\begin{perlblock}[session][fancyvrb settings%keyvals]#S
\end{perlblock}#S

## perlsix family ##
#ifOption:usefamily=perlsix
\perlsix{code}
\perlsix[session]{code}
\perlsixc{code}
\perlsixc[session]{code}
\perlsixs{code}
\perlsixs[session]{code}
\perlsixv|%<code%>|
\perlsixv[%<session%>]|%<code%>|
\perlsixv[session]{verbatimSymbol}#S
\perlsixb{code}
\perlsixb[session]{code}
\begin{perlsixcode}
\begin{perlsixcode}[session]
\begin{perlsixcode}[session][fancyvrb settings%keyvals]#*
\end{perlsixcode}
\begin{perlsixsub}
\begin{perlsixsub}[session]
\begin{perlsixsub}[session][fancyvrb settings%keyvals]#*
\end{perlsixsub}
\begin{perlsixverbatim}#V
\begin{perlsixverbatim}[session]#V
\begin{perlsixverbatim}[session][fancyvrb settings%keyvals]#V
\end{perlsixverbatim}
\begin{perlsixblock}
\begin{perlsixblock}[session]
\begin{perlsixblock}[session][fancyvrb settings%keyvals]
\end{perlsixblock}
#endif

\perlsix{code}#S
\perlsix[session]{code}#S
\perlsixc{code}#S
\perlsixc[session]{code}#S
\perlsixs{code}#S
\perlsixs[session]{code}#S
\perlsixv|%<code%>|#S
\perlsixv[%<session%>]|%<code%>|#S
\perlsixv[session]{verbatimSymbol}#S
\perlsixb{code}#S
\perlsixb[session]{code}#S
\begin{perlsixcode}#S
\begin{perlsixcode}[session]#S
\begin{perlsixcode}[session][fancyvrb settings%keyvals]#S
\end{perlsixcode}#S
\begin{perlsixsub}#S
\begin{perlsixsub}[session]#S
\begin{perlsixsub}[session][fancyvrb settings%keyvals]#S
\end{perlsixsub}#S
\begin{perlsixverbatim}#SV
\begin{perlsixverbatim}[session]#SV
\begin{perlsixverbatim}[session][fancyvrb settings%keyvals]#SV
\end{perlsixverbatim}#S
\begin{perlsixblock}#S
\begin{perlsixblock}[session]#S
\begin{perlsixblock}[session][fancyvrb settings%keyvals]#S
\end{perlsixblock}#S

## psix family ##
#ifOption:usefamily=psix
\psix{code}
\psix[session]{code}
\psixc{code}
\psixc[session]{code}
\psixs{code}
\psixs[session]{code}
\psixv|%<code%>|
\psixv[%<session%>]|%<code%>|
\psixv[session]{verbatimSymbol}#S
\psixb{code}
\psixb[session]{code}
\begin{psixcode}
\begin{psixcode}[session]
\begin{psixcode}[session][fancyvrb settings%keyvals]#*
\end{psixcode}
\begin{psixsub}
\begin{psixsub}[session]
\begin{psixsub}[session][fancyvrb settings%keyvals]#*
\end{psixsub}
\begin{psixverbatim}#V
\begin{psixverbatim}[session]#V
\begin{psixverbatim}[session][fancyvrb settings%keyvals]#V
\end{psixverbatim}
\begin{psixblock}
\begin{psixblock}[session]
\begin{psixblock}[session][fancyvrb settings%keyvals]
\end{psixblock}
#endif

\psix{code}#S
\psix[session]{code}#S
\psixc{code}#S
\psixc[session]{code}#S
\psixs{code}#S
\psixs[session]{code}#S
\psixv|%<code%>|#S
\psixv[%<session%>]|%<code%>|#S
\psixv[session]{verbatimSymbol}#S
\psixb{code}#S
\psixb[session]{code}#S
\begin{psixcode}#S
\begin{psixcode}[session]#S
\begin{psixcode}[session][fancyvrb settings%keyvals]#S
\end{psixcode}#S
\begin{psixsub}#S
\begin{psixsub}[session]#S
\begin{psixsub}[session][fancyvrb settings%keyvals]#S
\end{psixsub}#S
\begin{psixverbatim}#SV
\begin{psixverbatim}[session]#SV
\begin{psixverbatim}[session][fancyvrb settings%keyvals]#SV
\end{psixverbatim}#S
\begin{psixblock}#S
\begin{psixblock}[session]#S
\begin{psixblock}[session][fancyvrb settings%keyvals]#S
\end{psixblock}#S

## javascript family ##
#ifOption:usefamily=javascript
\javascript{code}
\javascript[session]{code}
\javascriptc{code}
\javascriptc[session]{code}
\javascripts{code}
\javascripts[session]{code}
\javascriptv|%<code%>|
\javascriptv[%<session%>]|%<code%>|
\javascriptv[session]{verbatimSymbol}#S
\javascriptb{code}
\javascriptb[session]{code}
\begin{javascriptcode}
\begin{javascriptcode}[session]
\begin{javascriptcode}[session][fancyvrb settings%keyvals]#*
\end{javascriptcode}
\begin{javascriptsub}
\begin{javascriptsub}[session]
\begin{javascriptsub}[session][fancyvrb settings%keyvals]#*
\end{javascriptsub}
\begin{javascriptverbatim}#V
\begin{javascriptverbatim}[session]#V
\begin{javascriptverbatim}[session][fancyvrb settings%keyvals]#V
\end{javascriptverbatim}
\begin{javascriptblock}
\begin{javascriptblock}[session]
\begin{javascriptblock}[session][fancyvrb settings%keyvals]
\end{javascriptblock}
#endif

\javascript{code}#S
\javascript[session]{code}#S
\javascriptc{code}#S
\javascriptc[session]{code}#S
\javascripts{code}#S
\javascripts[session]{code}#S
\javascriptv|%<code%>|#S
\javascriptv[%<session%>]|%<code%>|#S
\javascriptv[session]{verbatimSymbol}#S
\javascriptb{code}#S
\javascriptb[session]{code}#S
\begin{javascriptcode}#S
\begin{javascriptcode}[session]#S
\begin{javascriptcode}[session][fancyvrb settings%keyvals]#S
\end{javascriptcode}#S
\begin{javascriptsub}#S
\begin{javascriptsub}[session]#S
\begin{javascriptsub}[session][fancyvrb settings%keyvals]#S
\end{javascriptsub}#S
\begin{javascriptverbatim}#SV
\begin{javascriptverbatim}[session]#SV
\begin{javascriptverbatim}[session][fancyvrb settings%keyvals]#SV
\end{javascriptverbatim}#S
\begin{javascriptblock}#S
\begin{javascriptblock}[session]#S
\begin{javascriptblock}[session][fancyvrb settings%keyvals]#S
\end{javascriptblock}#S

## js family ##
#ifOption:usefamily=js
\js{code}
\js[session]{code}
\jsc{code}
\jsc[session]{code}
\jss{code}
\jss[session]{code}
\jsv|%<code%>|
\jsv[%<session%>]|%<code%>|
\jsv[session]{verbatimSymbol}#S
\jsb{code}
\jsb[session]{code}
\begin{jscode}
\begin{jscode}[session]
\begin{jscode}[session][fancyvrb settings%keyvals]#*
\end{jscode}
\begin{jssub}
\begin{jssub}[session]
\begin{jssub}[session][fancyvrb settings%keyvals]#*
\end{jssub}
\begin{jsverbatim}#V
\begin{jsverbatim}[session]#V
\begin{jsverbatim}[session][fancyvrb settings%keyvals]#V
\end{jsverbatim}
\begin{jsblock}
\begin{jsblock}[session]
\begin{jsblock}[session][fancyvrb settings%keyvals]
\end{jsblock}
#endif

\js{code}#S
\js[session]{code}#S
\jsc{code}#S
\jsc[session]{code}#S
\jss{code}#S
\jss[session]{code}#S
\jsv|%<code%>|#S
\jsv[%<session%>]|%<code%>|#S
\jsv[session]{verbatimSymbol}#S
\jsb{code}#S
\jsb[session]{code}#S
\begin{jscode}#S
\begin{jscode}[session]#S
\begin{jscode}[session][fancyvrb settings%keyvals]#S
\end{jscode}#S
\begin{jssub}#S
\begin{jssub}[session]#S
\begin{jssub}[session][fancyvrb settings%keyvals]#S
\end{jssub}#S
\begin{jsverbatim}#SV
\begin{jsverbatim}[session]#SV
\begin{jsverbatim}[session][fancyvrb settings%keyvals]#SV
\end{jsverbatim}#S
\begin{jsblock}#S
\begin{jsblock}[session]#S
\begin{jsblock}[session][fancyvrb settings%keyvals]#S
\end{jsblock}#S

\makepythontexfamily{engine}#*
\makepythontexfamily[options%keyvals]{engine}#*

#keyvals:\makepythontexfamily#c
prettyprinter=#pygments,fancyvrb
pyglexer=%<pygments lexer%>
pygopt={%<pygments options%>}
console#true,false
#endkeyvals

## fancyvrb (and fvextra) keys ##
#keyvals:\begin{pycode},\begin{pysub},\begin{pyverbatim},\begin{pyblock},\begin{pyconsole},\begin{pyconcode},\begin{pyconsub},\begin{pyconverbatim},\begin{pylabcode},\begin{pylabsub},\begin{pylabverbatim},\begin{pylabblock},\begin{pylabconsole},\begin{pylabconcode},\begin{pylabconsub},\begin{pylabconverbatim},\begin{sympycode},\begin{sympysub},\begin{sympyverbatim},\begin{sympyblock},\begin{sympyconsole},\begin{sympyconcode},\begin{sympyconsub},\begin{sympyconverbatim},\setpythontexfv,\begin{pygments},\inputpygments,\setpygmentsfv,\begin{rbcode},\begin{rbsub},\begin{rbverbatim},\begin{rbblock},\begin{rubycode},\begin{rubysub},\begin{rubyverbatim},\begin{rubyblock},\begin{juliacode},\begin{juliasub},\begin{juliaverbatim},\begin{juliablock},\begin{juliaconsole},\begin{juliaconcode},\begin{jlcode},\begin{jlsub},\begin{jlverbatim},\begin{jlblock},\begin{matlabcode},\begin{matlabsub},\begin{matlabverbatim},\begin{matlabblock},\begin{octavecode},\begin{octavesub},\begin{octaveverbatim},\begin{octaveblock},\begin{bashcode},\begin{bashsub},\begin{bashverbatim},\begin{bashblock},\begin{sagecode},\begin{sagesub},\begin{sageverbatim},\begin{sageblock},\begin{rustcode},\begin{rustsub},\begin{rustverbatim},\begin{rustblock},\begin{rscode},\begin{rssub},\begin{rsverbatim},\begin{rsblock},\begin{Rcode},\begin{Rsub},\begin{Rverbatim},\begin{Rblock},\begin{Rconsole},\begin{Rconcode},\begin{perlcode},\begin{perlsub},\begin{perlverbatim},\begin{perlblock},\begin{perlsixcode},\begin{perlsixsub},\begin{perlsixverbatim},\begin{perlsixblock},\begin{psixcode},\begin{psixsub},\begin{psixverbatim},\begin{psixblock},\begin{javascriptcode},\begin{javascriptsub},\begin{javascriptverbatim},\begin{javascriptblock},\begin{jscode},\begin{jssub},\begin{jsverbatim},\begin{jsblock}
commentchar=%<single char%>
gobble=%<integer%>
formatcom=%<commands%>
formatcom*=%<commands%>
fontfamily=%<family%>
fontsize=%<size macro%>
fontshape=%<shape%>
fontseries=%<series%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label=%<label text%>
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=#auto,last,integer
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=%<factor%>
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes={%<code%>}
codes*={%<code%>}
defineactive={%<code%>}
defineactive*={%<code%>}
reflabel=##l
beameroverlays#true,false
curlyquotes#true,false
extra#true,false
fontencoding=%<encoding%>
highlightcolor=#%color
highlightlines={%<line ranges%>}
linenos#true,false
mathescape#true,false
numberfirstline#true,false
numbers=#none,left,right,both
retokenize#true,false
space=%<macro%>
spacecolor=#%color
stepnumberfromfirst#true,false
stepnumberoffsetvalues#true,false
tab=%<macro%>
tabcolor=#%color
breakafter=%<string%>
breakaftergroup#true,false
breakaftersymbolpre=%<string%>
breakaftersymbolpost=%<string%>
breakanywhere#true,false
breakanywheresymbolpre=%<string%>
breakanywheresymbolpost=%<string%>
breakautoindent#true,false
breakbefore=%<string%>
breakbeforegroup#true,false
breakbeforesymbolpre=%<string%>
breakbeforesymbolpost=%<string%>
breakindent=##L
breakindentnchars=%<integer%>
breaklines#true,false
breaksymbol=%<string%>
breaksymbolleft=%<string%>
breaksymbolright=%<string%>
breaksymbolindent=##L
breaksymbolindentnchars=%<integer%>
breaksymbolindentleft=##L
breaksymbolindentleftnchars=%<integer%>
breaksymbolindentright=##L
breaksymbolindentrightnchars=%<integer%>
breaksymbolsep=##L
breaksymbolsepnchars=%<integer%>
breaksymbolsepleft=##L
breaksymbolsepleftnchars=%<integer%>
breaksymbolsepright=##L
breaksymbolseprightnchars=%<integer%>
breakbytoken#true,false
breakbytokenanywhere#true,false
#endkeyvals

# miscellaneous
\DepyFile#*
\DepyListing#*
\DepyMacro#*
\Depythontex{code}#*
\DepythontexOff#*
\DepythontexOn#*
\makepygments#*
\makepygmentsfv#*
\makepygmentspyg#*
\oldFancyVerbLine#S
\originalleft#S
\originalright#S