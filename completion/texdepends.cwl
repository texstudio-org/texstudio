# texdepends package
# Matthew Bertucci 2022/07/21 for v2.4.3

#include:ifthen
#include:ifxetex
#include:ifpdf
#include:xstring

#keyvals:\RequirePackage/texdepends#c,\usepackage/texdepends#c
debug#true,false
extension=%<file ext%>
#endkeyvals

\RequireFile{file}