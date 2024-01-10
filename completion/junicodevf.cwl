# junicodevf package
# Matthew Bertucci 2023/01/10 for v2.206

#include:luatex
#include:ifluatex
#include:xkeyval
#include:fontspec

#keyvals:\usepackage/junicodevf#c
light
medium
semibold
condensed
semicondensed
semiexpanded
expanded
weightadjustment=%<number%>
widthadjustment=%<number%>
lining
tabular
proportional
oldstyle
MainFeatures={%<font features%>}
MainRegularFeatures={%<font features%>}
MainItalicFeatures={%<font features%>}
MainBoldFeatures={%<font features%>}
MainBoldItalicFeatures={%<font features%>}
MainRegularSizeFeatures={%<font features%>}
MainItalicSizeFeatures={%<font features%>}
MainBoldSizeFeatures={%<font features%>}
MainBoldItalicSizeFeatures={%<font features%>}
ENLAOneSizeFeatures={%<font features%>}
ENLATwoSizeFeatures={%<font features%>}
ENLAThreeSizeFeatures={%<font features%>}
ENLAFourSizeFeatures={%<font features%>}
#endkeyvals

\EnlargedOne
\EnlargedOneItalic
\EnlargedTwo
\EnlargedTwoItalic
\EnlargedThree
\EnlargedThreeItalic
\EnlargedFour
\EnlargedFourItalic

\textcv{variant}{text}
\textcv[index]{variant}{text}
\jcv{variant}
\jcv[index]{variant}

\AltThornEth
\textAltThornEth{text}
\InsularLetterForms
\textInsularLetterForms{text}
\IPAAlternates
\textIPAAlternates{text}
\HighOverline
\textHighOverline{text}
\MediumHighOverline
\textMediumHighOverline{text}
\EnlargedMinuscules
\textEnlargedMinuscules{text}
\Underdotted
\textUnderdotted{text}
\ContextualLongS
\textContextualLongS{text}
\AlternateFigures
\textAlternateFigures{text}
\EntitiesAndTags
\textEntitiesAndTags{text}
\EarlyEnglishFuthorc
\textEarlyEnglishFuthorc{text}
\ElderFuthark
\textElderFuthark{text}
\YoungerFuthark
\textYoungerFuthark{text}
\LongBranchToShortTwig
\textLongBranchToShortTwig{text}
\ContextualRRotunda
\textContextualRRotunda{text}
\RareDigraphs
\textRareDigraphs{text}
\OldStylePunctuation
\textOldStylePunctuation{text}
\LatinToGothic
\textLatinToGothic{text}
\LowDiacritics
\textLowDiacritics{text}

\jcvA#*
\jcva#*
\jcvB#*
\jcvb#*
\jcvC#*
\jcvc#*
\jcvD#*
\jcvd#*
\jcvE#*
\jcve#*
\jcvF#*
\jcvf#*
\jcvG#*
\jcvg#*
\jcvH#*
\jcvh#*
\jcvI#*
\jcvi#*
\jcvJ#*
\jcvj#*
\jcvK#*
\jcvk#*
\jcvL#*
\jcvl#*
\jcvM#*
\jcvm#*
\jcvN#*
\jcvn#*
\jcvO#*
\jcvo#*
\jcvP#*
\jcvp#*
\jcvQ#*
\jcvq#*
\jcvR#*
\jcvr#*
\jcvS#*
\jcvs#*
\jcvT#*
\jcvt#*
\jcvU#*
\jcvu#*
\jcvV#*
\jcvv#*
\jcvW#*
\jcvw#*
\jcvX#*
\jcvx#*
\jcvY#*
\jcvy#*
\jcvZ#*
\jcvz#*
\jcvAogonek#*
\jcvaogonek#*
\jcvaa#*
\jcvAE#*
\jcvae#*
\jcvAO#*
\jcvao#*
\jcvav#*
\jcvdbar#*
\jcvdcroat#*
\jcvEogonek#*
\jcvYogh#*
\jcvlhighstroke#*
\jcvoPolish#*
\jcvthorncrossed#*
\jcvspacingzigzag#*
\jcvglottal#*
\jcvTironianEt#*
\jcvperiod#*
\jcvmiddot#*
\jcvcomma#*
\jcvsemicolon#*
\jcvpunctuselevatus#*
\jcvexclam#*
\jcvquestion#*
\jcvASCIItilde#*
\jcvasterisk#*
\jcvslash#*
\jcvrum#*
\jcvcombiningzigzag#*
\jcvspacingusabbrev#*
\jcvetabbrev#*
\jcvmacron#*
\jcvcombiningopena#*
\jcvcombininginsulard#*
\jcvcombiningrrotunda#*
\jcvcombiningdieresis#*
\jcvcombiningoverline#*
\jcvHcombiningdoublemacron#*
\jcvEng#*
\jcvbrevebelow#*
\jcvcurrency#*
\jcvlb#*
\jcvsterling#*
\jcvGermanpenny#*
\jcvflorin#*
\jcvounce#*

# not documented
\MainDef#S
\MainRegDef#S
\MainItalicDef#S
\MainBoldDef#S
\MainBoldItalicDef#S
\ENLAOneSizeDef#S
\ENLATwoSizeDef#S
\ENLAThreeSizeDef#S
\ENLAFourSizeDef#S
\makemainfontcommand{arg1}{arg2}{arg3}{arg4}{arg5}#S
