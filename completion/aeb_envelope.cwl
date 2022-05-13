# aeb_envelope package
# Matthew Bertucci 2022/05/13 for v1.0

#include:xkeyval
#include:graphicx
#include:aeb_pro

#keyvals:\usepackage/aeb_envelope#c
donotmail
path2folder=%<file path%>
envelope=#aeb1,aeb2,adobe1,adobe2,%<pdf file%>
#endkeyvals

\mailTo{keyvals}

#keyvals:\mailTo
UI#true,false
ToName={%<text%>}
From={%<text%>}
To=%<email1;email2;...%>
CC=%<email1;email2;...%>
BCC=%<email1;email2;...%>
Subject={%<text%>
MessageEnvelope={%<text%>
MessageBody={%<text%>
#endkeyvals

\assembleEnvelope
\aebenvDimensions#*
\addressEnv#*
\inputEnvExecJS#*
\setEnvDimensions{width}{height}
\setAddressEnv{%<\put commands%>}
\toggleAttachmentsPanel{color}{text}
\mailtoName#*
\mailtoFrom#*
\mailtoMessageEnvelope#*
\mailtoBCC#*
\mailtoCC#*
\mailtoEmail#*
\mailtoMessageBody#*
\mailtoSubject#*
\mailtoUI#*
\displayAddr{text}

# not documented
\addressEnvAdobei#*
\addressEnvAdobeii#*
\addressEnvAebi#*
\addressEnvAebii#*
\aebEnvPath#*
\mailitNow#*
\pathtoEnv#*