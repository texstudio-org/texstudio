# projlib-titlepage package
# Matthew Bertucci 2022/04/23 for 2022/04/18 release

#include:l3keys2e
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
style=%<style%>
color=#%color
#endkeyvals

titlepage-main#B
titlepage-back#B
