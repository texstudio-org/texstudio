# pst-sigsys package
# Matthew Bertucci 3/10/2022 for v1.4

#include:pstricks
#include:pst-node
#include:pst-xkey

\psaxeslabels(x0,y0)(x1,y1)(x2,y2){x label}{y label}
\psaxeslabels{arrows}(x0,y0)(x1,y1)(x2,y2){x label}{y label}#*
\psaxeslabels[options%keyvals](x0,y0)(x1,y1)(x2,y2){x label}{y label}
\psaxeslabels[options%keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2){x label}{y label}#*
\pstick(x,y){ticklength}
\pstick{angle}(x,y){ticklength}
\pstick[options%keyvals](x,y){ticklength}
\pstick[options%keyvals]{angle}(x,y){ticklength}
\psTick(x,y)
\psTick{angle}(x,y)
\psTick[options%keyvals](x,y)
\psTick[options%keyvals]{angle}(x,y)
\pssignal(x,y){node}{stuff}
\pssignal[options%keyvals](x,y){node}{stuff}
\psstem{list}
\psstem(x,∆x){list}
\psstem[options%keyvals]{list}
\psstem[options%keyvals](x,∆x){list}
\pszero(x,y){node}
\pszero[options%keyvals](x,y){node}
\pspole(x,y){node}
\pspole[options%keyvals](x,y){node}
\pscircleop(x,y){node}
\pscircleop[options%keyvals](x,y){node}
\psframeop(x,y){node}
\psframeop[options%keyvals](x,y){node}
\psdisk(x,y){radius}
\psdisk[options%keyvals](x,y){radius}
\psring(x,y){inner radius}{outer radius}
\psring[options%keyvals](x,y){inner radius}{outer radius}
\psdiskc(x,y)(x0,y0){radius}
\psdiskc[options%keyvals](x,y)(x0,y0){radius}
\psldots(x,y)
\psldots{angle}(x,y)
\psldots[options%keyvals](x,y)
\psldots[options%keyvals]{angle}(x,y)
\ldotsnode(x,y){node}
\ldotsnode{angle}(x,y){node}
\ldotsnode[options%keyvals](x,y){node}
\ldotsnode[options%keyvals]{angle}(x,y){node}
\psblock(x,y){node}{stuff}
\psblock[options%keyvals](x,y){node}{stuff}
\psfblock(x,y){node}{stuff}
\psfblock[options%keyvals](x,y){node}{stuff}
\psadaptive{nodeA}(x,y){nodeB}
\psadaptive{arrows}{nodeA}(x,y){nodeB}#*
\psadaptive[options%keyvals]{nodeA}(x,y){nodeB}
\psadaptive[options%keyvals]{arrows}{nodeA}(x,y){nodeB}#*
\psknob(x,y){node}
\psknob[options%keyvals](x,y){node}
\psusampler(x,y){node}{stuff}
\psusampler[options%keyvals](x,y){node}{stuff}
\psdsampler(x,y){node}{stuff}
\psdsampler[options%keyvals](x,y){node}{stuff}
\nclist{nc csname}{list}
\nclist{nc csname}[nc label]{list}
\nclist{arrows}{nc csname}{list}#*
\nclist{arrows}{nc csname}[nc label]{list}#*
\nclist[options%keyvals]{nc csname}{list}
\nclist[options%keyvals]{nc csname}[nc label]{list}
\nclist[options%keyvals]{arrows}{nc csname}{list}#*
\nclist[options%keyvals]{arrows}{nc csname}[nc label]{list}#*
\ncstar{nc csname}{list}{node}
\ncstar{nc csname}[nc label]{list}{node}
\ncstar{arrows}{nc csname}{list}{node}#*
\ncstar{arrows}{nc csname}[nc label]{list}{node}#*
\ncstar[options%keyvals]{nc csname}{list}{node}
\ncstar[options%keyvals]{nc csname}[nc label]{list}{node}
\ncstar[options%keyvals]{arrows}{nc csname}{list}{node}#*
\ncstar[options%keyvals]{arrows}{nc csname}[nc label]{list}{node}#*
\psBraceUp(A)(B){text}
\psBraceUp[options%keyvals](A)(B){text}
\psBraceUp*(A)(B){text}
\psBraceUp*[options%keyvals](A)(B){text}
\psBraceDown(A)(B){text}
\psBraceDown[options%keyvals](A)(B){text}
\psBraceDown*(A)(B){text}
\psBraceDown*[options%keyvals](A)(B){text}
\psBraceRight(A)(B){text}
\psBraceRight[options%keyvals](A)(B){text}
\psBraceRight*(A)(B){text}
\psBraceRight*[options%keyvals](A)(B){text}
\psBraceLeft(A)(B){text}
\psBraceLeft[options%keyvals](A)(B){text}
\psBraceLeft*(A)(B){text}
\psBraceLeft*[options%keyvals](A)(B){text}

\pstsigsysFV#S
\pstsigsysFD#S
\PSTsigsysLoaded#S