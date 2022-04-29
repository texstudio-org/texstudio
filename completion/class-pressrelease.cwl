# pressrelease class
# Matthew Bertucci 4/27/2022 for v1.0

#include:xkeyval
#include:etoolbox
#include:setspace
#include:geometry
#include:url
#include:refcount

#keyvals:\documentclass/pressrelease#c
10pt
11pt
12pt
letterpaper
a4paper
#endkeyvals

\PRset{options%keyvals}

#keyvals:\PRset#c,\documentclass/pressrelease#c
symbols#true,false
head=#above,below,center,left,right,above center,above left,above right,below center,below left,below right
smashlogo#true,false
logo=#left,right,above,below,above left,above right,below left,below right
releasealign=#center,left,right
ruled#true,false
topinfoalign=#center,left,right
bottominfoalign=#center,left,right
#endkeyvals

#keyvals:\PRset#c
topinfo=%<company/department/location/date%>
bottominfo=%<contact/address/hours/phone/email%>
#endkeyvals

#ifOption:symbols
#include:pressrelease-symbols
#endif
#ifOption:symbols=true
#include:pressrelease-symbols
#endif

\begin{pressrelease}
\end{pressrelease}
\begin{about}
\end{about}

\PRusevar{variable%keyvals}

#keyvals:\PRusevar#c
address
company
contact
date
department
email
encl
fax
headline
hours
location
logo
mobile
phone
release
subheadline
url
#endkeyvals

\PRheadline{text}
\PRsubheadline{text}
\PRrelease{text}
\PRlogo{logo}
\PRcompany{name%text}
\PRdepartment{name%text}
\PRlocation{place%text}
\PRcontact{name}
\PRaddress{text}
\PRphone{number}
\PRmobile{number}
\PRfax{number}
\PRurl{URL}#U
\PRemail{email%URL}#U
\PRemailformat{text}#*
\PRhours{times}
\PRencl{text}

\PRtagformat{text}#*
\PRinfotopline{tag}{details%text}#*
\PRinfobottomline{tag}{details%text}#*
\PRinfoline{tag}{details%text}#*
\PRinfoentry{details%text}#*
\PRenclformat{tag}{details%text}#*
\PRurlformat{tag}{URL}#*U

\PRcontacttext#*
\PRphonetext#*
\PRmobiletext#*
\PRemailtext#*
\PRurltext#*
\PRfaxtext#*
\PRcompanytext#*
\PRdepartmenttext#*
\PRaddresstext#*
\PRhourstext#*
\PRdatetext#*
\PRlocationtext#*
\PRencltext#*
\PRabouttext#*
\PRreleasetext#*
\PRnOfm{n}{m}#*

# not documented
\ifPRheadabove#*
\ifPRloadsymbols#*
\ifPRruled#*
\PRaboutposturlhook#*
\PRdohrule#*
\PRendsignal#*
\PRformatendsignal{arg}#*
\PRheadabovefalse#*
\PRheadabovetrue#*
\PRheadalign{arg}#*
\PRheaderfont{arg}#*
\PRheadformat{arg}#*
\PRinfobottomalign{arg}#*
\PRinfobottombeginhook#*
\PRinfobottomblock{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}{arg9}#*
\PRinfobottomendhook#*
\PRinfotopalign{arg}#*
\PRinfotopbeginhook#*
\PRinfotopblock{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}{arg9}#*
\PRinfotopendhook#*
\PRloadsymbolsfalse#*
\PRloadsymbolstrue#*
\PRlogoalign{arg}#*
\PRlogoformat{arg}#*
\PRreleasealign{arg}#*
\PRreleaseformat{arg}#*
\PRruledfalse#*
\PRruledtrue#*
\PRsubheadformat{arg}#*
\PRthelastpage#*
\thepressrelease#*