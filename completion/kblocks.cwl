# kblocks package
# Matthew Bertucci 2022/06/24 for v2.0

#include:tikz
#include:circuitikz
#include:tikzlibraryshapes.misc
#include:tikzlibrarymath
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarybackgrounds
#include:tikzlibraryfit
#include:tikzlibraryshadows
#include:tikzlibrarymatrix
#include:tikzlibrarychains
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.text
#include:tikzlibraryshapes.multipart
#include:tikzlibrarygraphs
#include:tikzlibraryexternal
  
\begin{kblock}#\pictureHighlight
\end{kblock}

\ExtractCoordinate{node}#*
\kColorB{color}
\kColorL{color}
\kColorT{color}
\kCoverRect[color]{ref node}{N-shift}{S-shift}{W-shift}{E-shift}
\kCoverRect{ref node}{N-shift}{S-shift}{W-shift}{E-shift}
\kCoverTextAbove{xshift}{yshift}{node name}{text};
\kCoverTextBelow{xshift}{yshift}{node name}{text};
\kCoverTextLeft{xshift}{yshift}{node name}{text};
\kCoverTextRight{xshift}{yshift}{node name}{text};
\kGain[right-of node]{node}{label text}
\kGain{node}{label text}
\kInDown[dist shift]{from node}{to node}{label text}{dir shift}
\kInDown{from node}{to node}{label text}{dir shift}
\kInDownM[dist shift]{from node}{to node}{label text}{dir shift}{style 1-6}
\kInDownM{from node}{to node}{label text}{dir shift}{style 1-6}
\kInLeft[dist shift]{from node}{to node}{label text}{dir shift}
\kInLeft{from node}{to node}{label text}{dir shift}
\kInLeftM[dist shift]{from node}{to node}{label text}{dir shift}{style 1-6}
\kInLeftM{from node}{to node}{label text}{dir shift}{style 1-6}
\kInRight[dist shift]{from node}{to node}{label text}{dir shift}
\kInRight{from node}{to node}{label text}{dir shift}
\kInRightM[dist shift]{from node}{to node}{label text}{dir shift}{style 1-6}
\kInRightM{from node}{to node}{label text}{dir shift}{style 1-6}
\kInUp[dist shift]{from node}{to node}{label text}{dir shift}
\kInUp{from node}{to node}{label text}{dir shift}
\kInUpM[dist shift]{from node}{to node}{label text}{dir shift}{style 1-6}
\kInUpM{from node}{to node}{label text}{dir shift}{style 1-6}
\kJumpCS[label text]{node}
\kJumpCS{node}
\kJumpCSAbove[dist shift]{from node}{to node}{dir shift}{label text}
\kJumpCSAbove{from node}{to node}{dir shift}{label text}
\kJumpCSBelow[dist shift]{from node}{to node}{dir shift}{label text}
\kJumpCSBelow{from node}{to node}{dir shift}{label text}
\kJumpCSLeft[dist shift]{from node}{to node}{dir shift}{label text}
\kJumpCSLeft{from node}{to node}{dir shift}{label text}
\kJumpCSRight[dist shift]{from node}{to node}{dir shift}{label text}
\kJumpCSRight{from node}{to node}{dir shift}{label text}
\kLink[label text]{from node}{to node}
\kLink{from node}{to node}
\kLinkCrossLeftAbove{from node}{to node}
\kLinkCrossLeftBelow{from node}{to node}
\kLinkCrossRightAbove{from node}{to node}
\kLinkCrossRightBelow{from node}{to node}
\kLinkdir[label text]{from node}{to node}{shift}
\kLinkdir{from node}{to node}{shift}
\kLinkHV[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinkHV{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinkHVHLeft[link scale]{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkHVHLeft{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkHVHRight[link scale]{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkHVHRight{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkn[label text]{from node}{to node}
\kLinkn{from node}{to node}
\kLinkndir[label text]{from node}{to node}{shift}
\kLinkndir{from node}{to node}{shift}
\kLinknHV[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknHV{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknVH[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknVH{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknVHHVAbove[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknVHHVAbove{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinknVHHVBelow[link shift]{label text}{from node}{to node}{from-shift}{to-shift}
\kLinknVHHVBelow{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkVH[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinkVH{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kLinkVHHVAbove[link shift]{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkVHHVAbove{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkVHHVBelow[link shift]{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkVHHVBelow{label text}{from node}{to node}{from-shift}{to-shift}
\kLinkVHTFHVAbove{label1}{label2}{node1}{node2}{node3}{x}{y}{xshift}#*
\kLinkVHTFHVAboveRight{label1}{label2}{node1}{node2}{node3}{x}{y}{xshift}#*
\kLinkVHTFHVBelow{label1}{label2}{node1}{node2}{node3}{x}{y}{xshift}#*
\kLinkVHTFHVBelowRight{label1}{label2}{node1}{node2}{node3}{x}{y}{xshift}#*
\kMarkNode{xshift}{yshift}{label text}{node}
\kMarkNodeAbove{xshift}{yshift}{label text}{from node}{to node}
\kMarkNodeBelow{xshift}{yshift}{label text}{from node}{to node}
\kMarkNodeLeft{xshift}{yshift}{label text}{from node}{to node}
\kMarkNodeRight{xshift}{yshift}{label text}{from node}{to node}
\kMinusMinusDown{from node}{to node}{shift}
\kMinusMinusDownA{from node}{to node}{shift}
\kMinusMinusDownB{from node}{to node}{shift}
\kMinusMinusDownL{from node}{to node}{shift}
\kMinusMinusUp{from node}{to node}{shift}
\kMinusMinusUpA{from node}{to node}{shift}
\kMinusMinusUpB{from node}{to node}{shift}
\kMinusMinusUpL{from node}{to node}{shift}
\kMinusPlusDown{from node}{to node}{shift}
\kMinusPlusDownA{from node}{to node}{shift}
\kMinusPlusDownB{from node}{to node}{shift}
\kMinusPlusDownL{from node}{to node}{shift}
\kMinusPlusUp{from node}{to node}{shift}
\kMinusPlusUpA{from node}{to node}{shift}
\kMinusPlusUpB{from node}{to node}{shift}
\kMinusPlusUpL{from node}{to node}{shift}
\kmT{math%formula}
\kmTw{math%formula}
\kOutDown[dist shift]{from node}{to node}{label text}{dir shift}
\kOutDown{from node}{to node}{label text}{dir shift}
\kOutLeft[dist shift]{from node}{to node}{label text}{dir shift}
\kOutLeft{from node}{to node}{label text}{dir shift}
\kOutRight[dist shift]{from node}{to node}{label text}{dir shift}
\kOutRight{from node}{to node}{label text}{dir shift}
\kOutUp[dist shift]{from node}{to node}{label text}{dir shift}
\kOutUp{from node}{to node}{label text}{dir shift}
\kPlusDownPlusUp{from node}{to node}{shift}
\kPlusDownPlusUpA{from node}{to node}{shift}
\kPlusDownPlusUpB{from node}{to node}{shift}
\kPlusDownPlusUpL{from node}{to node}{shift}
\kPlusMinusDown{from node}{to node}{shift}
\kPlusMinusDownA{from node}{to node}{shift}
\kPlusMinusDownB{from node}{to node}{shift}
\kPlusMinusDownL{from node}{to node}{shift}
\kPlusMinusDownPlaceAbove{from node}{to node}{shift}
\kPlusMinusDownPlaceBelow{from node}{to node}{shift}
\kPlusMinusMinus{from node}{to node}{shift}
\kPlusMinusMinusA{from node}{to node}{shift}
\kPlusMinusMinusB{from node}{to node}{shift}
\kPlusMinusMinusL{from node}{to node}{shift}
\kPlusMinusPlus{from node}{to node}{shift}
\kPlusMinusPlusA{from node}{to node}{shift}
\kPlusMinusPlusB{from node}{to node}{shift}
\kPlusMinusPlusL{from node}{to node}{shift}
\kPlusMinusUp{from node}{to node}{shift}
\kPlusMinusUpA{from node}{to node}{shift}
\kPlusMinusUpB{from node}{to node}{shift}
\kPlusMinusUpL{from node}{to node}{shift}
\kPlusPlusDown{from node}{to node}{shift}
\kPlusPlusDownA{from node}{to node}{shift}
\kPlusPlusDownB{from node}{to node}{shift}
\kPlusPlusDownL{from node}{to node}{shift}
\kPlusPlusMinus{from node}{to node}{shift}
\kPlusPlusMinusA{from node}{to node}{shift}
\kPlusPlusMinusB{from node}{to node}{shift}
\kPlusPlusMinusL{from node}{to node}{shift}
\kPlusPlusPlus{from node}{to node}{shift}
\kPlusPlusPlusA{from node}{to node}{shift}
\kPlusPlusPlusB{from node}{to node}{shift}
\kPlusPlusPlusL{from node}{to node}{shift}
\kPlusPlusUp{from node}{to node}{shift}
\kPlusPlusUpA{from node}{to node}{shift}
\kPlusPlusUpB{from node}{to node}{shift}
\kPlusPlusUpL{from node}{to node}{shift}
\kScaleDistX
\kScaleDistX[factor]
\kScaleDistY
\kScaleDistY[factor]
\ksfgCLink[label text]{from node}{to node}{node options}
\ksfgCLink{from node}{to node}{node options}
\ksfgCLinkFlip[label text]{from node}{to node}{node options}
\ksfgCLinkFlip{from node}{to node}{node options}
\ksfgLinkSelfD[label text]{node}
\ksfgLinkSelfD{node}
\ksfgLinkSelfL[label text]{node}
\ksfgLinkSelfL{node}
\ksfgLinkSelfR[label text]{node}
\ksfgLinkSelfR{node}
\ksfgLinkSelfU[label text]{node}
\ksfgLinkSelfU{node}
\ksfgNodeD[link text]{from node}{to node}{label text}{angle}
\ksfgNodeD{from node}{to node}{label text}{angle}
\ksfgNodeL[link text]{from node}{to node}{label text}{angle}
\ksfgNodeL{from node}{to node}{label text}{angle}
\ksfgNodeR[link text]{from node}{to node}{label text}{angle}
\ksfgNodeR{from node}{to node}{label text}{angle}
\ksfgNodeU[link text]{from node}{to node}{label text}{angle}
\ksfgNodeU{from node}{to node}{label text}{angle}
\ksfgNStart{node name}{coord}{label text}
\ksfgStart{node name}{coord}{label text}
\kShadow
\kStartNode[label text]{node name}
\kStartNode{node name}
\kStartNodec[label text]{coord}{node name}
\kStartNodec{coord}{node name}
\kTF{node name}{label text}
\kTFAbove[shift]{from node}{to node}{label text}
\kTFAbove[shift]{from node}{to node}{label text}
\kTFAbove{from node}{to node}{label text}
\kTFAbove{from node}{to node}{label text}
\kTFAboveLeft{yshift}{xshift}{from node}{to node}{label text}
\kTFAboveRight{yshift}{xshift}{from node}{to node}{label text}
\kTFBelow[shift]{from node}{to node}{label text}
\kTFBelow{from node}{to node}{label text}
\kTFBelowLeft{yshift}{xshift}{from node}{to node}{label text}
\kTFBelowRight{yshift}{xshift}{from node}{to node}{label text}
\kTFCs{coord}{node name}{label text}
\kTFLeft[shift]{from node}{to node}{label text}
\kTFLeft{from node}{to node}{label text}
\kTFRight[shift]{from node}{to node}{label text}
\kTFRight{from node}{to node}{label text}
\kVecInDown[dist shift]{from node}{to node}{label text}{dir shift}
\kVecInDown{from node}{to node}{label text}{dir shift}
\kVecInLeft[dist shift]{from node}{to node}{label text}{dir shift}
\kVecInLeft{from node}{to node}{label text}{dir shift}
\kVecInRight[dist shift]{from node}{to node}{label text}{dir shift}
\kVecInRight{from node}{to node}{label text}{dir shift}
\kVecInUp[dist shift]{from node}{to node}{label text}{dir shift}
\kVecInUp{from node}{to node}{label text}{dir shift}
\kVecLink[label text]{from node}{to node}
\kVecLink{from node}{to node}
\kVecLinkdir[label text]{from node}{to node}{shift}
\kVecLinkdir{from node}{to node}{shift}
\kVecLinkHV[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinkHV{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinkn[label text]{from node}{to node}
\kVecLinkn{from node}{to node}
\kVecLinkndir[label text]{from node}{to node}{shift}
\kVecLinkndir{from node}{to node}{shift}
\kVecLinknHV[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinknHV{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinknVH[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinknVH{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinkVH[label text]{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecLinkVH{from node}{to node}{yshift}{xshift}{labelpos 0-9}{mkpt}
\kVecOutDown[dist shift]{from node}{to node}{label text}{dir shift}
\kVecOutDown{from node}{to node}{label text}{dir shift}
\kVecOutLeft[dist shift]{from node}{to node}{label text}{dir shift}
\kVecOutLeft{from node}{to node}{label text}{dir shift}
\kVecOutRight[dist shift]{from node}{to node}{label text}{dir shift}
\kVecOutRight{from node}{to node}{label text}{dir shift}
\kVecOutUp[dist shift]{from node}{to node}{label text}{dir shift}
\kVecOutUp{from node}{to node}{label text}{dir shift}
\kVLinkHVHRight[link scale]{label text}{from node}{to node}{from-shift}{to-shift}
\kVLinkHVHRight{label text}{from node}{to node}{from-shift}{to-shift}

\asumxft#S
\backgroundcolor#S
\colortext#S
\dark#S
\de#S
\dn#S
\ds#S
\dw#S
\dxb#S
\dxina#S
\dxinr#S
\dxj#S
\dxl#S
\dxnax#S
\dxnbx#S
\dxncsx#S
\dxnlx#S
\dxnrx#S
\dxoutr#S
\dxpm#S
\dxpos#S
\dxr#S
\dxt#S
\dxtf#S
\dynay#S
\dynby#S
\dyncsy#S
\dynly#S
\dynry#S
\dypos#S
\dyt#S
\dytf#S
\dytfb#S
\horizdist#S
\linecolor#S
\linepathtype#S
\linetype#S
\minheight#S
\mkpt#S
\phasedist#S
\poslabel#S
\sfghorizdist#S
\textsize#S
\verticdist#S
\xc#S
\xca#S
\xcb#S
\xcr#S
\xe#S
\xf#S
\xn#S
\xon#S
\xone#S
\xonw#S
\xos#S
\xose#S
\xosw#S
\xs#S
\xt#S
\xtohat#S
\xw#S
\yc#S
\yca#S
\ycb#S
\ye#S
\yf#S
\yn#S
\yon#S
\yos#S
\ys#S
\yt#S
\ytohat#S
\yw#S

# deprecated
\kOutLeftM#S
\kOutRightM#S
\kOutUpM#S
\kOutDownM#S
