# qrcstamps package
# Matthew Bertucci 2022/05/13 for v1.0

#include:annot_pro
#include:xkeyval

#keyvals:\usepackage/qrcstamps#c
scandoc
!scandoc
basename=%<basename%>
# options passed to insdljs
dvipsone
dvips
textures
pdftex
luatex
dvipdfm
dvipdfmx
xetex
nodljs
debug
execJS
nopro
reqjs
!reqjs
usealtadobe
#endkeyvals

\qrCode{URL}#U
\qrCode[options%keyvals]{URL}#U

#keyvals:\qrCode
name=#Approved,AsIs,Confidential,Departmental,Draft,Experimental,Expired,Final,ForComment,ForPublicRelease,NotApproved,NotForPublicRelease,Sold,TopSecret
width=##L
height=##L
rotate=%<degrees%>
scale=%<factor%>
widthTo=##L
heightTo=##L
customStamp=
ap=
size=#small,medium,large
allowresize#true,false
basename=%<basename%>
contents=%<text%>
#endkeyvals

\QRBase#*