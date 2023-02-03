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
\py{code%definition}
\py[session]{code%definition}
\pyc{code%definition}
\pyc[session]{code%definition}
\pys{code%definition}
\pys[session]{code%definition}
\pyv|%<code%>|
\pyv[%<session%>]|%<code%>|
\pyv[session]{verbatimSymbol}#S
\pyb{code%definition}
\pyb[session]{code%definition}

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
\pycon{code%definition}
\pycon[session]{code%definition}
\pycons{code%definition}
\pycons[session]{code%definition}
\pyconc{code%definition}
\pyconc[session]{code%definition}
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
\pylab{code%definition}
\pylab[session]{code%definition}
\pylabc{code%definition}
\pylabc[session]{code%definition}
\pylabs{code%definition}
\pylabs[session]{code%definition}
\pylabv|%<code%>|
\pylabv[%<session%>]|%<code%>|
\pylabv[session]{verbatimSymbol}#S
\pylabb{code%definition}
\pylabb[session]{code%definition}

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
\pylabcon{code%definition}
\pylabcon[session]{code%definition}
\pylabconc{code%definition}
\pylabconc[session]{code%definition}
\pylabcons{code%definition}
\pylabcons[session]{code%definition}
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
\sympy{code%definition}
\sympy[session]{code%definition}
\sympyc{code%definition}
\sympyc[session]{code%definition}
\sympys{code%definition}
\sympys[session]{code%definition}
\sympyv|%<code%>|
\sympyv[%<session%>]|%<code%>|
\sympyv[session]{verbatimSymbol}#S
\sympyb{code%definition}
\sympyb[session]{code%definition}

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
\sympycon{code%definition}
\sympycon[session]{code%definition}
\sympycons{code%definition}
\sympycons[session]{code%definition}
\sympyconc{code%definition}
\sympyconc[session]{code%definition}
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
\pythontexcustomc{family}{code%definition}
\pythontexcustomc[position%keyvals]{family}{code%definition}
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
\pygment{lexer}{code%definition}
\begin{pygments}{lexer}#V
\begin{pygments}[fancyvrb settings%keyvals]{lexer}#V
\end{pygments}

\inputpygments{lexer}{file}
\inputpygments[fancyvrb settings%keyvals]{lexer}{file}

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
\rb{code%definition}
\rb[session]{code%definition}
\rbc{code%definition}
\rbc[session]{code%definition}
\rbs{code%definition}
\rbs[session]{code%definition}
\rbv|%<code%>|
\rbv[%<session%>]|%<code%>|
\rbv[session]{verbatimSymbol}#S
\rbb{code%definition}
\rbb[session]{code%definition}
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

\rb{code%definition}#S
\rb[session]{code%definition}#S
\rbc{code%definition}#S
\rbc[session]{code%definition}#S
\rbs{code%definition}#S
\rbs[session]{code%definition}#S
\rbv|%<code%>|#S
\rbv[%<session%>]|%<code%>|#S
\rbv[session]{verbatimSymbol}#S
\rbb{code%definition}#S
\rbb[session]{code%definition}#S
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
\ruby{code%definition}
\ruby[session]{code%definition}
\rubyc{code%definition}
\rubyc[session]{code%definition}
\rubys{code%definition}
\rubys[session]{code%definition}
\rubyv|%<code%>|
\rubyv[%<session%>]|%<code%>|
\rubyv[session]{verbatimSymbol}#S
\rubyb{code%definition}
\rubyb[session]{code%definition}
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

\ruby{code%definition}#S
\ruby[session]{code%definition}#S
\rubyc{code%definition}#S
\rubyc[session]{code%definition}#S
\rubys{code%definition}#S
\rubys[session]{code%definition}#S
\rubyv|%<code%>|#S
\rubyv[%<session%>]|%<code%>|#S
\rubyv[session]{verbatimSymbol}#S
\rubyb{code%definition}#S
\rubyb[session]{code%definition}#S
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
\julia{code%definition}
\julia[session]{code%definition}
\juliac{code%definition}
\juliac[session]{code%definition}
\julias{code%definition}
\julias[session]{code%definition}
\juliav|%<code%>|
\juliav[%<session%>]|%<code%>|
\juliav[session]{verbatimSymbol}#S
\juliab{code%definition}
\juliab[session]{code%definition}
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

\julia{code%definition}#S
\julia[session]{code%definition}#S
\juliac{code%definition}#S
\juliac[session]{code%definition}#S
\julias{code%definition}#S
\julias[session]{code%definition}#S
\juliav|%<code%>|#S
\juliav[%<session%>]|%<code%>|#S
\juliav[session]{verbatimSymbol}#S
\juliab{code%definition}#S
\juliab[session]{code%definition}#S
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
\jl{code%definition}
\jl[session]{code%definition}
\jlc{code%definition}
\jlc[session]{code%definition}
\jls{code%definition}
\jls[session]{code%definition}
\jlv|%<code%>|
\jlv[%<session%>]|%<code%>|
\jlv[session]{verbatimSymbol}#S
\jlb{code%definition}
\jlb[session]{code%definition}
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

\jl{code%definition}#S
\jl[session]{code%definition}#S
\jlc{code%definition}#S
\jlc[session]{code%definition}#S
\jls{code%definition}#S
\jls[session]{code%definition}#S
\jlv|%<code%>|#S
\jlv[%<session%>]|%<code%>|#S
\jlv[session]{verbatimSymbol}#S
\jlb{code%definition}#S
\jlb[session]{code%definition}#S
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
\matlab{code%definition}
\matlab[session]{code%definition}
\matlabc{code%definition}
\matlabc[session]{code%definition}
\matlabs{code%definition}
\matlabs[session]{code%definition}
\matlabv|%<code%>|
\matlabv[%<session%>]|%<code%>|
\matlabv[session]{verbatimSymbol}#S
\matlabb{code%definition}
\matlabb[session]{code%definition}
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

\matlab{code%definition}#S
\matlab[session]{code%definition}#S
\matlabc{code%definition}#S
\matlabc[session]{code%definition}#S
\matlabs{code%definition}#S
\matlabs[session]{code%definition}#S
\matlabv|%<code%>|#S
\matlabv[%<session%>]|%<code%>|#S
\matlabv[session]{verbatimSymbol}#S
\matlabb{code%definition}#S
\matlabb[session]{code%definition}#S
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
\octave{code%definition}
\octave[session]{code%definition}
\octavec{code%definition}
\octavec[session]{code%definition}
\octaves{code%definition}
\octaves[session]{code%definition}
\octavev|%<code%>|
\octavev[%<session%>]|%<code%>|
\octavev[session]{verbatimSymbol}#S
\octaveb{code%definition}
\octaveb[session]{code%definition}
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

\octave{code%definition}#S
\octave[session]{code%definition}#S
\octavec{code%definition}#S
\octavec[session]{code%definition}#S
\octaves{code%definition}#S
\octaves[session]{code%definition}#S
\octavev|%<code%>|#S
\octavev[%<session%>]|%<code%>|#S
\octavev[session]{verbatimSymbol}#S
\octaveb{code%definition}#S
\octaveb[session]{code%definition}#S
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
\bash{code%definition}
\bash[session]{code%definition}
\bashc{code%definition}
\bashc[session]{code%definition}
\bashs{code%definition}
\bashs[session]{code%definition}
\bashv|%<code%>|
\bashv[%<session%>]|%<code%>|
\bashv[session]{verbatimSymbol}#S
\bashb{code%definition}
\bashb[session]{code%definition}
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

\bash{code%definition}#S
\bash[session]{code%definition}#S
\bashc{code%definition}#S
\bashc[session]{code%definition}#S
\bashs{code%definition}#S
\bashs[session]{code%definition}#S
\bashv|%<code%>|#S
\bashv[%<session%>]|%<code%>|#S
\bashv[session]{verbatimSymbol}#S
\bashb{code%definition}#S
\bashb[session]{code%definition}#S
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
\sage{code%definition}
\sage[session]{code%definition}
\sagec{code%definition}
\sagec[session]{code%definition}
\sages{code%definition}
\sages[session]{code%definition}
\sagev|%<code%>|
\sagev[%<session%>]|%<code%>|
\sagev[session]{verbatimSymbol}#S
\sageb{code%definition}
\sageb[session]{code%definition}
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

\sage{code%definition}#S
\sage[session]{code%definition}#S
\sagec{code%definition}#S
\sagec[session]{code%definition}#S
\sages{code%definition}#S
\sages[session]{code%definition}#S
\sagev|%<code%>|#S
\sagev[%<session%>]|%<code%>|#S
\sagev[session]{verbatimSymbol}#S
\sageb{code%definition}#S
\sageb[session]{code%definition}#S
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
\rust{code%definition}
\rust[session]{code%definition}
\rustc{code%definition}
\rustc[session]{code%definition}
\rusts{code%definition}
\rusts[session]{code%definition}
\rustv|%<code%>|
\rustv[%<session%>]|%<code%>|
\rustv[session]{verbatimSymbol}#S
\rustb{code%definition}
\rustb[session]{code%definition}
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

\rust{code%definition}#S
\rust[session]{code%definition}#S
\rustc{code%definition}#S
\rustc[session]{code%definition}#S
\rusts{code%definition}#S
\rusts[session]{code%definition}#S
\rustv|%<code%>|#S
\rustv[%<session%>]|%<code%>|#S
\rustv[session]{verbatimSymbol}#S
\rustb{code%definition}#S
\rustb[session]{code%definition}#S
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
\rs{code%definition}
\rs[session]{code%definition}
\rsc{code%definition}
\rsc[session]{code%definition}
\rss{code%definition}
\rss[session]{code%definition}
\rsv|%<code%>|
\rsv[%<session%>]|%<code%>|
\rsv[session]{verbatimSymbol}#S
\rsb{code%definition}
\rsb[session]{code%definition}
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

\rs{code%definition}#S
\rs[session]{code%definition}#S
\rsc{code%definition}#S
\rsc[session]{code%definition}#S
\rss{code%definition}#S
\rss[session]{code%definition}#S
\rsv|%<code%>|#S
\rsv[%<session%>]|%<code%>|#S
\rsv[session]{verbatimSymbol}#S
\rsb{code%definition}#S
\rsb[session]{code%definition}#S
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
\R{code%definition}
\R[session]{code%definition}
\Rc{code%definition}
\Rc[session]{code%definition}
\Rs{code%definition}
\Rs[session]{code%definition}
\Rv|%<code%>|
\Rv[%<session%>]|%<code%>|
\Rv[session]{verbatimSymbol}#S
\Rb{code%definition}
\Rb[session]{code%definition}
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

\R{code%definition}#S
\R[session]{code%definition}#S
\Rc{code%definition}#S
\Rc[session]{code%definition}#S
\Rs{code%definition}#S
\Rs[session]{code%definition}#S
\Rv|%<code%>|#S
\Rv[%<session%>]|%<code%>|#S
\Rv[session]{verbatimSymbol}#S
\Rb{code%definition}#S
\Rb[session]{code%definition}#S
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
\perl{code%definition}
\perl[session]{code%definition}
\perlc{code%definition}
\perlc[session]{code%definition}
\perls{code%definition}
\perls[session]{code%definition}
\perlv|%<code%>|
\perlv[%<session%>]|%<code%>|
\perlv[session]{verbatimSymbol}#S
\perlb{code%definition}
\perlb[session]{code%definition}
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

\perl{code%definition}#S
\perl[session]{code%definition}#S
\perlc{code%definition}#S
\perlc[session]{code%definition}#S
\perls{code%definition}#S
\perls[session]{code%definition}#S
\perlv|%<code%>|#S
\perlv[%<session%>]|%<code%>|#S
\perlv[session]{verbatimSymbol}#S
\perlb{code%definition}#S
\perlb[session]{code%definition}#S
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
\perlsix{code%definition}
\perlsix[session]{code%definition}
\perlsixc{code%definition}
\perlsixc[session]{code%definition}
\perlsixs{code%definition}
\perlsixs[session]{code%definition}
\perlsixv|%<code%>|
\perlsixv[%<session%>]|%<code%>|
\perlsixv[session]{verbatimSymbol}#S
\perlsixb{code%definition}
\perlsixb[session]{code%definition}
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

\perlsix{code%definition}#S
\perlsix[session]{code%definition}#S
\perlsixc{code%definition}#S
\perlsixc[session]{code%definition}#S
\perlsixs{code%definition}#S
\perlsixs[session]{code%definition}#S
\perlsixv|%<code%>|#S
\perlsixv[%<session%>]|%<code%>|#S
\perlsixv[session]{verbatimSymbol}#S
\perlsixb{code%definition}#S
\perlsixb[session]{code%definition}#S
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
\psix{code%definition}
\psix[session]{code%definition}
\psixc{code%definition}
\psixc[session]{code%definition}
\psixs{code%definition}
\psixs[session]{code%definition}
\psixv|%<code%>|
\psixv[%<session%>]|%<code%>|
\psixv[session]{verbatimSymbol}#S
\psixb{code%definition}
\psixb[session]{code%definition}
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

\psix{code%definition}#S
\psix[session]{code%definition}#S
\psixc{code%definition}#S
\psixc[session]{code%definition}#S
\psixs{code%definition}#S
\psixs[session]{code%definition}#S
\psixv|%<code%>|#S
\psixv[%<session%>]|%<code%>|#S
\psixv[session]{verbatimSymbol}#S
\psixb{code%definition}#S
\psixb[session]{code%definition}#S
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
\javascript{code%definition}
\javascript[session]{code%definition}
\javascriptc{code%definition}
\javascriptc[session]{code%definition}
\javascripts{code%definition}
\javascripts[session]{code%definition}
\javascriptv|%<code%>|
\javascriptv[%<session%>]|%<code%>|
\javascriptv[session]{verbatimSymbol}#S
\javascriptb{code%definition}
\javascriptb[session]{code%definition}
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

\javascript{code%definition}#S
\javascript[session]{code%definition}#S
\javascriptc{code%definition}#S
\javascriptc[session]{code%definition}#S
\javascripts{code%definition}#S
\javascripts[session]{code%definition}#S
\javascriptv|%<code%>|#S
\javascriptv[%<session%>]|%<code%>|#S
\javascriptv[session]{verbatimSymbol}#S
\javascriptb{code%definition}#S
\javascriptb[session]{code%definition}#S
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
\js{code%definition}
\js[session]{code%definition}
\jsc{code%definition}
\jsc[session]{code%definition}
\jss{code%definition}
\jss[session]{code%definition}
\jsv|%<code%>|
\jsv[%<session%>]|%<code%>|
\jsv[session]{verbatimSymbol}#S
\jsb{code%definition}
\jsb[session]{code%definition}
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

\js{code%definition}#S
\js[session]{code%definition}#S
\jsc{code%definition}#S
\jsc[session]{code%definition}#S
\jss{code%definition}#S
\jss[session]{code%definition}#S
\jsv|%<code%>|#S
\jsv[%<session%>]|%<code%>|#S
\jsv[session]{verbatimSymbol}#S
\jsb{code%definition}#S
\jsb[session]{code%definition}#S
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
firstnumber=%<auto|last|<integer>%>
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
fileext=%<extension%>
vspace=##L
listparameters={%<code%>}
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
\Depythontex{code%definition}#*
\DepythontexOff#*
\DepythontexOn#*
\makepygments#*
\makepygmentsfv#*
\makepygmentspyg#*
\oldFancyVerbLine#S
\originalleft#S
\originalright#S
