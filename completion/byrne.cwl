# byrne package
# Matthew Bertucci 2025/12/05 for v0.2.5

#include:ifmtarg
#include:luamplib

\defineNewPicture{MetaPost code}
\defineNewPicture[offspring scale]{MetaPost code}
\defineNewPicture[offspring scale][main scale]{MetaPost code}
\defineNewPictureBasedOnOld{MetaPost code}
\defineNewPictureBasedOnOld[offspring scale]{MetaPost code}
\defineNewPictureBasedOnOld[offspring scale][main scale]{MetaPost code}
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
\drawLineByPoints{point names}
\drawLineByPoints[vertical align]{point names}
\drawLineByPoints[vertical align][new name]{point names}
\drawPointM{point name}
\drawPointL{point name}
\drawPointL[vertical align]{point name}
\drawPointL[vertical align][lines to omit]{point name}
\drawPoint{point name}
\drawPoint[vertical align]{point name}
\drawPoint[vertical align][lines to omit]{point name}

# not documented
\CreateNewInstanceForPicturefalse#S
\CreateNewInstanceForPicturetrue#S
\currentInlinePicturePlacement#S
\currentInstance#S
\drawDefinedPicture{picture name}{align}#S
\drawImageFromCurrentInstance{picture name}#S
\drawMagnitude[vertical align][opt]{name}#S
\drawMagnitude[vertical align]{name}#S
\drawMagnitude{name}#S
\drawProportionalIndLine{name}#S
\drawProportionalRay{name}#S
\drawSizedRay[opt]{name}#S
\drawSizedRay{name}#S
\drawUnitIndLine[opt]{name}#S
\drawUnitIndLine{name}#S
\formatImageName{picture name}#S
\ifCreateNewInstanceForPicture#S
\lastPict#S
\middp#S
\midht#S
\mpInst#S
\mpPost#S
\mpPre#S
\offsetPicture{top}{bottom}{arg}#S
\pictOffsetBottom#S
\pictOffsetTop#S
\plal#S
\sfA#S
\sfB#S
\tmpalignment#S
\tmpmiddle#S
\mpLastInst#S
\pointlabel{arg}#S
\UseNextPicture#S
\UsePreviousPicture#S
\UseLastPicture#S
\pictVMargins#S
\ifRemoveMarginsFromSmallerPics#S
\RemoveMarginsFromSmallerPicstrue#S
\RemoveMarginsFromSmallerPicsfalse#S