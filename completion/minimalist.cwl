# minimalist package
# Matthew Bertucci 2023/01/02 for 2023/01/02 release

#include:amsmath
#include:lineno
#include:projlib-paper
#include:projlib-language
#include:minimalist-plain

#keyvals:\usepackage/minimalist#c
draft#true,false
fast#true,false
title in boldface#true,false
title in scshape#true,false
classical#true,false
runin#true,false
nothms#true,false
nothmnum#true,false
thmnum
thmnum=%<counter%>
theorem style=%<style%>
complex name#true,false
simple name#true,false
no preset names#true,false
regionalref#true,false
originalref#true,false
Chinese
TChinese
English
German
Italian
Portuguese
Brazilian
Spanish
Japanese
Russian
#endkeyvals

#ifOption:classical
# loads minimalist-classical package, however commands same as minimalist-plain except those below
\desculine#*
\seculine#*
\simpleqedsymbol#*
\subseculine#*
#endif
#ifOption:classical=true
\desculine#*
\seculine#*
\simpleqedsymbol#*
\subseculine#*
#endif
