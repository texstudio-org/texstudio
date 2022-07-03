# iodhbwm-templates package
# Matthew Bertucci 2022/07/02 for v1.2.2

#include:etoolbox
#include:pgfopts
#include:totalcount
# loads figure and table options of totalcount
#include:xpatch

\dhbwsetup{options%keyvals}

#keyvals:\dhbwsetup
titlepage=%<filename%>
declaration=%<filename%>
abstract=%<filename%>
thesis type=#SA,BA,PA
bachelor degree=#BoE,BoA,BoS
bachelor degree type=%<text%>
thesis title=%<text%>
thesis second title=%<text%>
author=%<name%>
date=%<date%>
submission date=%<date%>
location=%<location%>
institute=%<institute%>
institute section=%<section%>
institute logo=%<imagefile%>
student id=%<id%>
course/id=%<id%>
course/name=%<name%>
supervisor=%<name%>
processing period=%<period%>
reviewer=%<name%>
dhbw location=%<location%>
dhbw logo=%<imagefile%>
intro/print titlepage#true,false
intro/print declaration#true,false
intro/print abstract#true,false
intro/print toc#true,false
intro/print lof#true,false
intro/print lot#true,false
intro/print all lists#true,false
intro/print all#true,false
intro/append custom content=%<content%>
intro/roman page numbers#true,false
#endkeyvals

\getAuthor
\getThesisTitle
\getThesisSecondTitle
\getLocation
\getCourseName
\getCourseId
\getStudentId
\getInstituteLogo
\getInstitute
\getInstituteSection
\getSupervisor
\getProcessingPeriod
\getDate
\getSubmissionDate
\getReviewer
\getBachelorDegree
\getThesisType
\getDHBWLocation
\getDHBWLogo
\listofappendices
\dhbwtitlepage
\dhbwdeclaration
\dhbwabstract
\tocchapterpagenumberformat{text}#*
\dhbwfrontmatter
\dhbwmainmatter
\dhbwprintintro
\appendixmore#*
\SavedOriginalchaptertocentry#S
\SavedOriginaladdchaptertocentry#S

# from figure option of totalcount
\totalfigures#*
\iftotalfigures#*

# from table option of totalcount
\totaltables#*
\iftotaltables#*