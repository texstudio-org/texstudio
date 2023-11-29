# affilauthor package
# Matthew Bertucci 2023/11/29 for v1.0.1

#include:marvosym

\author{keyvals}

#keyvals:\author#c
name={%<name1,name2,...%>}
mail={%<email1,email2,...%>}
phone={%<num1,num2,...%>}
url={%<URL1,URL2,...%>}
affil={%<affil1,affil2,...%>}
note={%<note1,note2,...%>
#endkeyvals

\affil{keyvals}

#keyvals:\affil#c
id=%<id%>
div=%<text%>
org=%<text%>
addr=%<text%>
street=%<text%>
landmark=%<text%>
pincode=%<text%>
postbox=%<text%>
city=%<text%>
state=%<text%>
country=%<text%>
#endkeyvals

\affilstyle[keyvals]

#keyvals:\affilstyle#c
authfont=%<font commands%>
affilfont=%<font commands%>
mailfont=%<font commands%>
urlfont=%<font commands%>
phonefont=%<font commands%>
notefont=%<font commands%>
notenum=#alpha,fnsym,roman
authspace=##L
affilspace=##L
affilnum=#alpha,Alpha,roman,Roman
#endkeyvals
