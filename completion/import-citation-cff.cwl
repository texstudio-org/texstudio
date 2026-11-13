# import-citation-cff package
# Matthew Bertucci 2026/11/11 for v0.4.0

#include:lt3luabridge

#keyvals:\usepackage/import-citation-cff#c
check#true,false
style=%<style%>
#endkeyvals

\cffaffiliationcount
\cffaffiliationindex
\cffaffiliation{n}
\cffauthoraffiliationcount{index}
\cffauthoraffiliationindex
\cffauthoraffiliation{index}{k}
\cffauthorindex
\cffauthornames
\cffauthor{index}{field}
\cffcontactindex
\cffcontact{index}{field}
\cffconvertaffiliationindex{index}{k}
\cffcount{path}
\cffdeclareauthorstyle{name}{options%keyvals}
\cffemit{declaration}
\cffforeachaffiliation{code}
\cffforeachauthoraffiliation{index}{code}
\cffforeachauthor{code}
\cffforeachcontact{code}
\cffrenderaffiliation{index}
\cffrenderauthor{index}
\cffsetauthors
\cffsetauthors[options%keyvals]
\cff{path}
\includecff[options%keyvals]{file}
\includecff{file}

#keyvals:\cffsetauthors,\cffdeclareauthorstyle
affiliation-mark=#alph,Alph,arabic,roman,Roman
affiliation=%<template%>
author=%<template%>
contact=%<template%>
name=%<template%>
note={%<index%>}{%<text%>}
separator=%<text%>
style=%<name%>
#endkeyvals

#keyvals:\includecff
source=%<key%>
#endkeyvals