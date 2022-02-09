# epspdfconversion package
# Matthew Bertucci 2/7/2022 for v0.61

#include:epstopdf-base
#include:graphics
#include:kvoptions

\epspdfconversionsetup{options%keyvals}

#keyvals:\usepackage/epspdfconversion#c,\epspdfconversionsetup
cmd=%<command%>
gray
GRAY
grey
GREY
nogrey
nogray
target=#default,printer,prepress,screen,ebook
default
printer
prepress
screen
ebook
pdfversion=#default,1.2,1.3,1.4
bbox#true,false
pdftopdf#true,false
pstopdf#true,false
pdftops
nopdftops
hires
no-hires
custom={%<GhostScript options%>}
psoptions={%<pdftops options%>}
pagenumber=%<number%>
simple
help
update#true,false
verbose#true,false
prefersuffix#true,false
suffix=%<suffix%>
outdir=%<directory%>
prepend#true,false
#endkeyvals

\epspdfconversioncmdline{command}

\CheckOutdir#*
\MinorVersion#*