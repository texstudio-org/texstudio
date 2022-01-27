# Package epstopdf
# http://ctan.org/tex-archive/macros/latex/contrib/epstopdf
# By astroscion: 2012-02-15

#include:infwarerr
#include:grfext
#include:kvoptions
#include:pdftexcmds

\epstopdfsetup{key-value-list%keyvals}

#keyvals:\epstopdfsetup,\usepackage/epstopdf#c
update#true,false
append#true,false
prepend#true,false
outdir=%<directory%>
suffix=%<string%>
prefersuffix#true,false
program@epstopdf=%<program%>
verbose#true,false
#endkeyvals

\OutputFile
\SourceFile
\SourceExt
\epstopdfDeclareGraphicsRule{ext}{type}{read-file}{command%plain}
\epstopdfcall{arg}
\AppendGraphicsExtensions{ext}
\PrependGraphicsExtensions{ext}
