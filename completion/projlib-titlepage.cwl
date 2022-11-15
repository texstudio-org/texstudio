# projlib-titlepage package
# Matthew Bertucci 2022/11/15 for 2022/11/15 release

#include:projlib-logo
#include:projlib-paper
#include:tikz
# loads calc tikzlibrary

\TitlePage{keyvals}
\TitlePage[options]{keyvals}
\ProjLibTitlePage{keyvals}#*
\ProjLibTitlePage[options]{keyvals}#*

#keyvals:\TitlePage,\ProjLibTitlePage
logo=%<graphics%>
title=%<text%>
subtitle=%<text%>
author=%<name%>
date=%<date%>
title-page-name=%<name%>
license-page-name=%<name%>
info=%<text%>
license=%<text%>
style=%<style%>
color=#%color
#endkeyvals

titlepage-main#B
titlepage-back#B
