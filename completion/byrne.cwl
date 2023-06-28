# byrne package
# Matthew Bertucci 2022/07/06 for v0.2.2

#include:ifmtarg
#include:luamplib

\defineNewPicture{MetaPost code}
\defineNewPicture[offspring scale]{MetaPost code}
\defineNewPicture[offspring scale][main scale]{MetaPost code}
\drawCurrentPicture
\defineFromCurrentPicture{vertical align}{picture name}{MetaPost code}
\drawFromCurrentPicture{MetaPost code}
\drawFromCurrentPicture[vertical align]{MetaPost code}
\drawFromCurrentPicture[vertical align][picture name]{MetaPost code}
\drawUnitLine{line name}
\drawUnitLine[line second name]{line name}
\drawProportionalLine{line name}
\drawSizedLine{line name}
\drawSizedLine[line second name]{line name}
\drawUnitRay{line name}
\drawUnitRay[ray name]{line name}
\drawRightAngle
\drawTwoRightAngles
\drawAngle{angle name}
\drawAngleWithSides{angle name}
\drawPolygon{polygon name}
\drawPolygon[vertical align]{polygon name}
\drawPolygon[vertical align][new name]{polygon name}
\drawCircle{circle name}
\drawCircle[vertical align]{circle name}
\drawCircle[vertical align][scale]{circle name}
\drawArc{arc name}
\drawArc[vertical align]{arc name}
\drawArc[vertical align][scale]{arc name}
\drawLine{line name}
\drawLine[vertical align]{line name}
\drawLine[vertical align][new name]{line name}
\drawPointM{point name}
\drawPointL{point name}
\drawPointL[vertical align]{point name}
\drawPointL[vertical align][lines to omit]{point name}
\drawPoint{point name}
\drawPoint[vertical align]{point name}
\drawPoint[vertical align][lines to omit]{point name}

# not documented
\addToUndefineList{picture name}#*
\CreateNewInstanceForPicturefalse#*
\CreateNewInstanceForPicturetrue#*
\currentInlinePicturePlacement#*
\currentInstance#*
\drawDefinedPicture{picture name}{align}#*
\drawImageFromCurrentInstance{picture name}#*
\drawMagnitude[vertical align][opt]{name}#*
\drawMagnitude[vertical align]{name}#*
\drawMagnitude{name}#*
\drawProportionalIndLine{name}#*
\drawProportionalRay{name}#*
\drawSizedRay[opt]{name}#*
\drawSizedRay{name}#*
\drawUnitIndLine[opt]{name}#*
\drawUnitIndLine{name}#*
\formatImageName{picture name}#*
\ifCreateNewInstanceForPicture#*
\lastPict#*
\middp#*
\midht#*
\mpInst#*
\mpPost#*
\mpPre#*
\offsetPicture{top}{bottom}{arg}#*
\pictOffsetBottom#*
\pictOffsetTop#*
\plal#S
\sfA#S
\sfB#S
\tmpalignment#S
\tmpmiddle#S
\undefineList#*
\unmarkPictAsReady{picture name}#*