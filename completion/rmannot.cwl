# rmannot package
# Matthew Bertucci 2022/05/13 for v2.2.1

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:eforms
#include:graphicxsp
#include:ifthen

#keyvals:\usepackage/rmannot#c
use3D
#endkeyvals

\AcroVer{version}
\AcroVer[option%keyvals]{version}

#keyvals:\AcroVer
win=#32,64
mac
#endkeyvals

\pathToSkins{path%definition}
\saveNamedPath{name}{path%definition}
\saveNamedPath[mime type]{name}{path%definition}
\defineRMPath{cmd}{path%definition}#d

\makePoster{name}{imagefile}#g
\makePoster[options%keyvals]{name}{imagefile}#g
\defaultPoster{code}

\setPosterProps{keyvals}

#keyvals:\setPosterProps
color=%<postscript color%>
xPos=%<number%>
yPos=%<number%>
textColor=%<postscript color%>
relTextSize=%<number%>
textSize=%<number%>
textFont=%<font name%>
#endkeyvals

\rmAnnot{width}{height}{name}
\rmAnnot[options%keyvals]{width}{height}{name}

#keyvals:\rmAnnot
name=%<name%>
enabled=#onclick,pageopen,pagevisible
deactivated=#onclick,pageclose,pageinvisible
windowed#true,false
url#true,false
borderwidth=#none,thin,medium,thick
poster=%<name%>
posternote=%<text%>
defaultposter#true,false
invisible#true,false
skin=#all,none
skinAutoHide#true,false
width=##L
height=##L
scale=%<factor%>
#endkeyvals

\cntrlbrWd#*
\cntrlbrHt#*

\setWindowDimPos{keyvals}

#keyvals:\setWindowDimPos
width={%<KV pairs%>}
height={%<KV pairs%>}
position={%<KV pairs%>}
#endkeyvals

\resetWindowDimPos

#ifOption:use3D
#include:fp
\rmAnnot{width}{height}{name}{3Dmodel}
\rmAnnot[options%keyvals]{width}{height}{name}{3Dmodel}
#keyvals:\rmAnnot
toolbar#true,false
modeltree#true,false
#endkeyvals
\setRmOptions3D{annot name}{options%keyvals}
#keyvals:\setRmOptions3D
3DOptions={%<movie15 options%>}
#endkeyvals
\setRmOptions#S
#endif

# not documented
\AcrobatVer#*
\appType{arg1}#*
\audCtrlHt#*
\audCtrlWd#*
\FileStrmAudioPlayer#*
\FileStrmVideoPlayer#*
\getargsiii{arg1}{arg2}{arg3}#*
\ifuseWinAcrobat#*
\ifVideoPlayerEx#*
\mmGetMetaData#*
\mmGetSource#*
\mmGetVersion#*
\mmGetVideoState#*
\mmIsLooping#*
\mmMute#*
\mmNextCuePoint#*
\mmPause#*
\mmPlay#*
\mmPrevCuePoint#*
\mmRewind#*
\mmSeek#*
\mmSeekCuePoint#*
\mmSetScaleMode#*
\mmSetStageColor#*
\mmShowLoopButton#*
\mmSkin#*
\mmSkinAlpha#*
\mmSkinAutoHide#*
\mmSkinColor#*
\mmSource#*
\mmUseLocal#*
\mmVolume#*
\Name#*
\pathToPlayers{arg1}#*
\PathToSkins#*
\RefObjRm{arg1}#*
\rmaName#*
\rmaNameP#*
\rmaUrlName#*
\rmaUrlNameP#*
\rmDC#*
\rmSkinPath#*
\romanVer#*
\urlName#*
\useVideoPlayerPlus#*
\useVideoPlayerX#*
\useWinAcrobatfalse#*
\useWinAcrobattrue#*
\VideoPlayerExfalse#*
\VideoPlayerExtrue#*