# lilyglyphs package
# Matthew Bertucci 2/3/2022 for v1.0

#include:keyval
#include:pgf
#include:adjustbox
#include:ifluatex
#include:ifxetex
#include:luaotfload
#include:luacode

\lilyglyphs#*
\lilyglyphs[options%keyvals]#*

# from core/opticals.inp
\lilyOpticalSuffix#*
\lilyOpticalSize{number}

# from core/keyval.inp
\lilyGlobalOptions{options%keyvals}
\interpretLilyOptions{options%keyvals}#*
\lilyEffectiveScale#*
\lilyEffectiveRaise#*

# from core/genericAccess.inp
\lilyPrint{content%text}#*
\lilyPrint[options%keyvals]{content%text}#*
\currentFontRatio#*
\currentFontSize#*
\normalFontSize#*
\getCurrentFontRatio#*
\lilyScaleImage#*
\lilyImageEffectiveScale#*
\lilyPrintImage{imagefile}#*g
\lilyPrintImage[options%keyvals]{imagefile}#*g
\lilyGetGlyph{slot}#*
\lilyGetGlyphByNumber{char number}#*
\lilyGlyph{slot}#*
\lilyGlyph[options%keyvals]{slot}#*
\lilyGlyphByNumber{char number}#*
\lilyGlyphByNumber[options%keyvals]{char number}#*
\lilyText{text%plain}#*
\lilyText[options%keyvals]{text%plain}#*
\lilyImage{imagefile}#*g
\lilyImage[options%keyvals]{imagefile}#*g

# from core/dotted.inp
\lilyDot#*
\lilyDot[options%keyvals]#*
\lilyCalcDotSpace{scale factor}{curve factor}{offset}{steepness}#*
\lilyDotSpaceF#*
\lilySetDotOptions{curve factor}{offset}{steepness}#*
\lilySetDotOptions[options%keyvals]{curve factor}{offset}{steepness}#*
\lilyDotScale#*
\lilyDotRaise#*
\lilyDotSpace#*
\lilyPrintDot#*
\lilyPrintMoreDots#*
\lilyPrintMoreDots[number]#*

# from commands/clefs.inp
\clefG
\clefG[options%keyvals]
\clefGInline
\clefGInline[options%keyvals]
\clefF
\clefF[options%keyvals]
\clefFInline
\clefFInline[options%keyvals]
\clefC
\clefC[options%keyvals]
\clefCInline
\clefCInline[options%keyvals]

# from commands/numbers.inp
# no user commands

# from commands/timesignatures.inp
\lilyTimeC
\lilyTimeC[options%keyvals]
\lilyTimeCHalf
\lilyTimeCHalf[options%keyvals]
\lilyTimeSignature
\lilyTimeSignature[options%keyvals]

# from commands/dynamics.inp
\lilyDynamics{text%plain}
\lilyDynamics[options%keyvals]{text%plain}
\lilyRF
\lilyRF[options%keyvals]
\lilyRFZ
\lilyRFZ[options%keyvals]
\decrescHairpin
\decrescHairpin[options%keyvals]
\crescHairpin
\crescHairpin[options%keyvals]

# from commands/accidentals.inp
\natural
\natural[options%keyvals]
\flat
\flat[options%keyvals]
\flatflat
\flatflat[options%keyvals]
\sharp
\sharp[options%keyvals]
\sharpArrowup
\sharpArrowup[options%keyvals]
\sharpArrowdown
\sharpArrowdown[options%keyvals]
\sharpArrowboth
\sharpArrowboth[options%keyvals]
\sharpSlashslashStem
\sharpSlashslashStem[options%keyvals]
\sharpSlashslashslashStemstem
\sharpSlashslashslashStemstem[options%keyvals]
\sharpSlashslashslashStem
\sharpSlashslashslashStem[options%keyvals]
\sharpSlashslashStemstemstem
\sharpSlashslashStemstemstem[options%keyvals]
\doublesharp
\doublesharp[options%keyvals]

# from commands/rests.inp
\wholeNoteRest
\wholeNoteRest[options%keyvals]
\wholeNoteRestDotted
\wholeNoteRestDotted[options%keyvals]
\halfNoteRest
\halfNoteRest[options%keyvals]
\halfNoteRestDotted
\halfNoteRestDotted[options%keyvals]
\crotchetRest
\crotchetRest[options%keyvals]
\crotchetRestDotted
\crotchetRestDotted[options%keyvals]
\quaverRest
\quaverRest[options%keyvals]
\quaverRestDotted
\quaverRestDotted[options%keyvals]
\semiquaverRest
\semiquaverRest[options%keyvals]
\semiquaverRestDotted
\semiquaverRestDotted[options%keyvals]

# from commands/scripts.inp
\fermata
\fermata[options%keyvals]
\lilyAccent
\lilyAccent[options%keyvals]
\lilyEspressivo
\lilyEspressivo[options%keyvals]
\lilyStaccato
\lilyStaccato[options%keyvals]
\lilyThumb
\lilyThumb[options%keyvals]
\marcato
\marcato[options%keyvals]
\marcatoDown
\marcatoDown[options%keyvals]
\portato
\portato[options%keyvals]
\portatoDown
\portatoDown[options%keyvals]
\staccatissimo
\staccatissimo[options%keyvals]
\tenuto
\tenuto[options%keyvals]

# from commands/accordion.inp
\accordionBayanBass
\accordionBayanBass[options%keyvals]
\accordionDiscant
\accordionDiscant[options%keyvals]
\accordionDot
\accordionDot[options%keyvals]
\accordionFreeBass
\accordionFreeBass[options%keyvals]
\accordionOldEE
\accordionOldEE[options%keyvals]
\accordionPull
\accordionPull[options%keyvals]
\accordionPush
\accordionPush[options%keyvals]
\accordionStdBass
\accordionStdBass[options%keyvals]

# from commands/singlenotes.inp
\semibreve
\semibreve[options%keyvals]
\wholeNote
\wholeNote[options%keyvals]
\semibreveDotted
\semibreveDotted[options%keyvals]
\wholeNoteDotted
\wholeNoteDotted[options%keyvals]
\minim
\minim[options%keyvals]
\halfNote
\halfNote[options%keyvals]
\minimDown
\minimDown[options%keyvals]
\halfNoteDown
\halfNoteDown[options%keyvals]
\minimDotted
\minimDotted[options%keyvals]
\halfNoteDotted
\halfNoteDotted[options%keyvals]
\minimDottedDown
\minimDottedDown[options%keyvals]
\halfNoteDottedDown
\halfNoteDottedDown[options%keyvals]
\minimDottedDouble
\minimDottedDouble[options%keyvals]
\halfNoteDottedDouble
\halfNoteDottedDouble[options%keyvals]
\minimDottedDoubleDown
\minimDottedDoubleDown[options%keyvals]
\halfNoteDottedDoubleDown
\halfNoteDottedDoubleDown[options%keyvals]
\crotchet
\crotchet[options%keyvals]
\quarterNote
\quarterNote[options%keyvals]
\crotchetDown
\crotchetDown[options%keyvals]
\quarterNoteDown
\quarterNoteDown[options%keyvals]
\crotchetDotted
\crotchetDotted[options%keyvals]
\quarterNoteDotted
\quarterNoteDotted[options%keyvals]
\crotchetDottedDown
\crotchetDottedDown[options%keyvals]
\quarterNoteDottedDown
\quarterNoteDottedDown[options%keyvals]
\crotchetDottedDouble
\crotchetDottedDouble[options%keyvals]
\quarterNoteDottedDouble
\quarterNoteDottedDouble[options%keyvals]
\crotchetDottedDoubleDown
\crotchetDottedDoubleDown[options%keyvals]
\quarterNoteDottedDoubleDown
\quarterNoteDottedDoubleDown[options%keyvals]
\quaver
\quaver[options%keyvals]
\eighthNote
\eighthNote[options%keyvals]
\quaverDown
\quaverDown[options%keyvals]
\eighthNoteDown
\eighthNoteDown[options%keyvals]
\quaverDotted
\quaverDotted[options%keyvals]
\eighthNoteDotted
\eighthNoteDotted[options%keyvals]
\quaverDottedDown
\quaverDottedDown[options%keyvals]
\eighthNoteDottedDown
\eighthNoteDottedDown[options%keyvals]
\quaverDottedDouble
\quaverDottedDouble[options%keyvals]
\eighthNoteDottedDouble
\eighthNoteDottedDouble[options%keyvals]
\quaverDottedDoubleDown
\quaverDottedDoubleDown[options%keyvals]
\eighthNoteDottedDoubleDown
\eighthNoteDottedDoubleDown[options%keyvals]
\semiquaver
\semiquaver[options%keyvals]
\sixteenthNote
\sixteenthNote[options%keyvals]
\semiquaverDown
\semiquaverDown[options%keyvals]
\sixteenthNoteDown
\sixteenthNoteDown[options%keyvals]
\semiquaverDotted
\semiquaverDotted[options%keyvals]
\sixteenthNoteDotted
\sixteenthNoteDotted[options%keyvals]
\semiquaverDottedDown
\semiquaverDottedDown[options%keyvals]
\sixteenthNoteDottedDown
\sixteenthNoteDottedDown[options%keyvals]
\semiquaverDottedDouble
\semiquaverDottedDouble[options%keyvals]
\sixteenthNoteDottedDouble
\sixteenthNoteDottedDouble[options%keyvals]
\semiquaverDottedDoubleDown
\semiquaverDottedDoubleDown[options%keyvals]
\sixteenthNoteDottedDoubleDown
\sixteenthNoteDottedDoubleDown[options%keyvals]
\demisemiquaver
\demisemiquaver[options%keyvals]
\thirtysecondNote
\thirtysecondNote[options%keyvals]
\demisemiquaverDotted
\demisemiquaverDotted[options%keyvals]
\thirtysecondNoteDotted
\thirtysecondNoteDotted[options%keyvals]
\demisemiquaverDottedDouble
\demisemiquaverDottedDouble[options%keyvals]
\thirtysecondNoteDottedDouble
\thirtysecondNoteDottedDouble[options%keyvals]
\demisemiquaverDottedDoubleDown
\demisemiquaverDottedDoubleDown[options%keyvals]
\thirtysecondNoteDottedDoubleDown
\thirtysecondNoteDottedDoubleDown[options%keyvals]
\demisemiquaverDottedDown
\demisemiquaverDottedDown[options%keyvals]
\thirtysecondNoteDottedDown
\thirtysecondNoteDottedDown[options%keyvals]
\demisemiquaverDown
\demisemiquaverDown[options%keyvals]
\thirtysecondNoteDown
\thirtysecondNoteDown[options%keyvals]

# from commands/beamednotes.inp
\twoBeamedQuavers
\twoBeamedQuavers[options%keyvals]
\threeBeamedQuavers
\threeBeamedQuavers[options%keyvals]
\threeBeamedQuaversI
\threeBeamedQuaversI[options%keyvals]
\threeBeamedQuaversII
\threeBeamedQuaversII[options%keyvals]
\threeBeamedQuaversIII
\threeBeamedQuaversIII[options%keyvals]

# from commands/fancyexamples.inp
\lilyFancyExample
\lilyFancyExample[options%keyvals]

#keyvals:\lilyglyphs,\lilyGlobalOptions,\interpretLilyOptions,\lilyPrint,\lilyPrintImage,\lilyGlyph,\lilyGlyphByNumber,\lilyText,\lilyImage,\lilyDot,\lilySetDotOptions,\clefG,\clefGInline,\clefF,\clefFInline,\clefC,\clefCInline,\lilyTimeC,\lilyTimeCHalf,\lilyTimeSignature,\lilyDynamics{text%plain},\lilyRF,\lilyRFZ,\decrescHairpin,\crescHairpin,\natural,\flat,\flatflat,\sharp,\sharpArrowup,\sharpArrowdown,\sharpArrowboth,\sharpSlashslashStem,\sharpSlashslashslashStemstem,\sharpSlashslashslashStem,\sharpSlashslashStemstemstem,\doublesharp,\wholeNoteRest,\wholeNoteRestDotted,\halfNoteRest,\halfNoteRestDotted,\crotchetRest,\crotchetRestDotted,\quaverRest,\quaverRestDotted,\semiquaverRest,\semiquaverRestDotted,\fermata,\lilyAccent,\lilyEspressivo,\lilyStaccato,\lilyThumb,\marcato,\marcatoDown,\portato,\portatoDown,\staccatissimo,\tenuto,\accordionBayanBass,\accordionDiscant,\accordionDot,\accordionFreeBass,\accordionOldEE,\accordionPull,\accordionPush,\accordionStdBass,\semibreve,\wholeNote,\semibreveDotted,\wholeNoteDotted,\minim,\halfNote,\minimDown,\halfNoteDown,\minimDotted,\halfNoteDotted,\minimDottedDown,\halfNoteDottedDown,\minimDottedDouble,\halfNoteDottedDouble,\minimDottedDoubleDown,\halfNoteDottedDoubleDown,\crotchet,\quarterNote,\crotchetDown,\quarterNoteDown,\crotchetDotted,\quarterNoteDotted,\crotchetDottedDown,\quarterNoteDottedDown,\crotchetDottedDouble,\quarterNoteDottedDouble,\crotchetDottedDoubleDown,\quarterNoteDottedDoubleDown,\quaver,\eighthNote,\quaverDown,\eighthNoteDown,\quaverDotted,\eighthNoteDotted,\quaverDottedDown,\eighthNoteDottedDown,\quaverDottedDouble,\eighthNoteDottedDouble,\quaverDottedDoubleDown,\eighthNoteDottedDoubleDown,\semiquaver,\sixteenthNote,\semiquaverDown,\sixteenthNoteDown,\semiquaverDotted,\sixteenthNoteDotted,\semiquaverDottedDown,\sixteenthNoteDottedDown,\semiquaverDottedDouble,\sixteenthNoteDottedDouble,\semiquaverDottedDoubleDown,\sixteenthNoteDottedDoubleDown,\demisemiquaver,\thirtysecondNote,\demisemiquaverDotted,\thirtysecondNoteDotted,\demisemiquaverDottedDouble,\thirtysecondNoteDottedDouble,\demisemiquaverDottedDoubleDown,\thirtysecondNoteDottedDoubleDown,\demisemiquaverDottedDown,\thirtysecondNoteDottedDown,\demisemiquaverDown,\thirtysecondNoteDown,\twoBeamedQuavers,\threeBeamedQuavers,\threeBeamedQuaversI,\threeBeamedQuaversII,\threeBeamedQuaversIII,\lilyFancyExample
scale=%<factor%>
raise=%<number%>
#endkeyvals