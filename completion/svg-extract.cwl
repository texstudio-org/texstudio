# svg-extract package
# Matthew Bertucci 1/30/2022 for v2.02k

#include:svg

## 3.1. General settings ##
#keyvals:\usepackage/svg-extract#c
on
off
#endkeyvals

## 3.2. Extract independent graphic files ##
#keyvals:\usepackage/svg-extract#c,\svgsetup#c,\includesvg,\includeinkscape
extract#true,false
extractpath=#svgdir,svgpath,svgsubdir,svgsubpath,basedir,basepath,jobdir,jobpath,basesubdir,basesubpath,jobsubdir,jobsubpath,%<path%>
extractname=#filename,name,filenamenumbered,namenumbered,numberedfilename,numberedname,numbered,section,numberedsection,sectionnumbered
extractformat={%<fmt1,fmt2,...%>}
extractwidth=##L
extractheight=##L
extractdistort#true,false
extractscale=%<factor%>
extractpretex=%<code%>
extractapptex=%<code%>
extractpreamble=%<file name%>
extractpreambleend=%<line%>
extractruns=%<number%>
latexexe=%<exe%>
latexopt=%<opt%>
latexext=%<extension%>
dvipsopt=%<opt%>
pstoepsopt=%<opt%>
pstopdfopt=%<opt%>
pdftoepsopt=%<opt%>
pdftopsopt=%<opt%>
clean=#true,false,{%<ext1,ext2,...%>}
exclude
convert=#false,off,no,true,on,yes,magick,imagemagick,convert,gs,ghostscript,gs64,ghostscript64,gs32,ghostscript32
convertformat={%<fmt1,fmt2,...%>}
convertdpi={%<fmt=integer%>}
magickexe=%<exe%>
magicksetting=%<settings%>
magickoperator=%<operators%>
gsexe=%<exe%>
gsdevice=
gsopt=%<opt%>
#endkeyvals

#keyvals:\includesvg,\includeinkscape
extractangle=
#endkeyvals

\svghidepreamblestart
\svghidepreambleend

\svgxoutputbox#*
\svgxsetbox{arg}#*
\svgxsetbox[opt]{arg}#*
\svgxsetpapersize#*