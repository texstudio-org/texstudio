# rest-api package
# Matthew Bertucci 2022/07/02 for v1.4

#include:fontenc
# loads T1 option of fontenc
#include:tabularx
#include:colortbl
#include:transparent
#include:xcolor
#include:color
#include:xifthen
#include:xstring
#include:tikz
#include:mdframed
#include:array
#include:verbatim
#include:listings

\begin{apiRoute}{method}{path}{description%text}
\end{apiRoute}
\begin{routeParameter}
\end{routeParameter}
\begin{routeRequest}{path}
\end{routeRequest}
\begin{routeRequestBody}#V
\end{routeRequestBody}
\begin{routeResponse}{path}
\end{routeResponse}
\begin{routeResponseItem}{status code}{description%text}
\end{routeResponseItem}
\begin{routeResponseItemBody}#V
\end{routeResponseItemBody}

\bodyFormat#*
\breakRoute
\getDeleteBorderColor
\getDeleteColor
\getDeleteLightColor
\getGetBorderColor
\getGetColor
\getGetLightColor
\getPostBorderColor
\getPostColor
\getPostLightColor
\getPutBorderColor
\getPutColor
\getPutLightColor
\method#*
\methodBorderColor
\methodColor
\methodJson
\methodLightColor
\methodXml
\noBreakRoute
\noRouteParameter{text}
\noRouteResponse{text}
\printDescription#*
\routeBreakValue
\routeDescription#*
\routeParamItem{name}{description%text}
\urlPath#*

background#B
deleteLightRed#B
deleteRed#B
deleteRedBorder#B
delimDelete#B
delimGet#B
delimPost#B
delimPut#B
getBlue#B
getBlueBorder#B
getLightBlue#B
numbDelete#B
numbGet#B
numbPost#B
numbPut#B
postGreen#B
postGreenBorder#B
postLightGreen#B
punct#B
putLightOrange#B
putOrange#B
putOrangeBorder#B

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n