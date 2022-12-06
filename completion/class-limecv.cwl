# limecv class
# Matthew Bertucci 12/3/2021 for v0.1.12

#include:kvoptions
#include:ifxetex
#include:ifluatex
#include:calc
#include:xcolor
#include:tabularx
#include:hyperref
#include:url
#include:parskip
#include:xstring
#include:xkeyval
#include:tikz
#include:graphicx
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibrarybackgrounds
#include:tikzlibrarymatrix
#include:fontspec
#include:fontawesome5

#keyvals:\documentclass/limecv#c
print#true,false
path=%<file path%>
sansfont=%<font name%>
monofont=%<font name%>
#endkeyvals

\cvSetLanguage{language}

#keyvals:\cvSetLanguage#c
chinese
dutch
english
french
german
italian
spanish
#endkeyvals

\begin{cvSidebar}
\end{cvSidebar}
\begin{cvSidebar*}
\end{cvSidebar*}

\cvID{first name}{last name}{imagefile}{job position}#g

\begin{cvProfile}
\end{cvProfile}

\begin{cvContact}
\end{cvContact}

\cvContactAddress{address}
\cvContactEmail{link%URL}{email address}#U
\cvContactPhone{phone number}
\cvContactWebsite{URL}{link text}#U
\cvContactGithub{URL}{username}#U
\cvContactGitlab{URL}{username}#U
\cvContactLinkedin{URL}{username}#U
\cvContactTwitter{URL}{username}#U
\cvContactKeybase{URL}{fingerprint}#U

\begin{cvLanguages}
\end{cvLanguages}

\cvLanguage{language}{skill level}

\begin{cvInterests}
\begin{cvInterests}[short]%|
\end{cvInterests}

\cvInterestsPersonal
\cvInterestsProfessional
\cvInterest{icon}{interest}

\begin{cvProjects}
\end{cvProjects}

\cvProject{name}{description%text}
\cvProject[options%keyvals]{name}{description%text}

#keyvals:\cvProject
image=%<imagefile%>
link=%<URL%>
width=##L
height=##L
#endkeyvals

\begin{cvMainContent}
\end{cvMainContent}
\begin{cvMainContent*}#*
\end{cvMainContent*}#*

\begin{cvEducation}
\end{cvEducation}

\cvItem{details%text}

\begin{cvExperience}
\end{cvExperience}

\begin{cvSkills}
\end{cvSkills}

\cvSkillTwo{skill-level1}{skill1}{skill-level2}{skill2}
\cvSkillOne{skill-level}{skill}

\begin{cvReferences}
\end{cvReferences}

\cvAddReference{keyvals}
\cvAddReference*{keyvals}

#keyvals:\cvAddReference,\cvAddReference*
name=
company=
position=
address line 1=
address line 2=
address line 3=
mobile phone=
work phone=
email=
#endkeyvals

\begin{cvCoverLetter}
\end{cvCoverLetter}

\cvBeneficiary{keyvals}

#keyvals:\cvBeneficiary
name=
position=
company=
address line 1=
address line 2=
address line 3=
#endkeyvals

\cvFullName

cvGreen#B
cvGreenLight#B
cvDark#B
cvRed#B
cvAccent#B
cvBackground#B

#keyvals:\tikzset#c
interesticon/.style={%<TikZ styles%>}
interesttext/.style={%<TikZ styles%>}
eventdottext/.style={%<TikZ styles%>}
invisibletimedot/.style={%<TikZ styles%>}
timedot/.style={%<TikZ styles%>}
eventdot/.style={%<TikZ styles%>}
contactIcon/.style={%<TikZ styles%>}
contactText/.style={%<TikZ styles%>}
headerIcon/.style={%<TikZ styles%>}
skillLevel/.style={%<TikZ styles%>}
languageText/.style={%<TikZ styles%>}
skillText/.style={%<TikZ styles%>}
progressArea/.style={%<TikZ styles%>}
progressBar/.style={%<TikZ styles%>}
sectionTitle/.style={%<TikZ styles%>}
sectionEduText/.style={%<TikZ styles%>}
#endkeyvals

\cvColSep#*
\cvNodeSep#*
\cvTimeDotDiameter#*
\cvMargin#*
\cvSideWidth#*
\cvMainWidth#*
\cvTimeDotSep#*
\cvStartEndSep#*
\cvItemSep#*
\cvTableSepWidth#*
\cvCoverLetterHeight#*
\cvCoverLetterWidth#*
\cvPictureWidth#*
\cvProgressAreaWidth#*
\cvProgressAreaHeight#*
\cvSectionSep#*
\cvSectionSBSep#*
\cvTitleLineWidth#*
\cvTitleLineSpacing#*
\cvProjectDetailsSep#*
\cvInterestDetailsSep#*
\cvContactItemSep#*
\cvCoverLetterLineWidth#*
\cvCoverLetterPositionSpacing#*
\cvSBSectionLineWidth#*
\cvCoverLetterLineSpacing#*
\cvIDNameSep#*
\cvPositionSep#*
\cvSkillSep#*
\cvHeaderIconWidth#*

\cvComma#*
\ifnodedefined{node name}{true code}{false code}#*
\globalcolor{color}#*
\faVcard#*
\kright{arg}#*
\kleft{arg}#*
\extract{n}{string}#*
\cvList{envname}{name}{icon}#*N
\cvContactTemplate[opt]{arg1}{arg2}#*
