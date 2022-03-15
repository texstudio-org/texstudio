# fontwrap package
# Matthew Bertucci 3/14/2022

#include:xetex
#include:fontspec
#include:xunicode
#include:xltxtra
#include:perltex

\setfontwrapdefaultfont{font}
\setunicodegroupfont{group%keyvals}{font}
\setunicodeblockfont{block%keyvals}{font}
\fontwrap{text}
\setfontwrapallowedmacros{csname1,csname2,...}
\setfontwrapallowedenvironments{envname1,envname2,...}
\begin{verbatimfontwrap}
\end{verbatimfontwrap}

#keyvals:\setunicodegroupfont#c
Arabic
Chinese
CJK
Cyrillic
Diacritics
Greek
Korean
Japanese
Latin
Mathematics
Phonetics
Punctuation
Symbols
Yi
Other
#endkeyvals

#keyvals:\setunicodeblockfont#c
AegeanNumbers
AlphabeticPresentationForms
AncientGreekMusicalNotation
AncientGreekNumbers
ArabicPresentationFormsA
ArabicPresentationFormsB
ArabicSupplement
Arabic
Armenian
Arrows
Balinese
BasicLatin
Bengali
BlockElements
BopomofoExtended
Bopomofo
BoxDrawing
BraillePatterns
Buginese
Buhid
ByzantineMusicalSymbols
CJKCompatibilityForms
CJKCompatibilityIdeographsSupplement
CJKCompatibilityIdeographs
CJKCompatibility
CJKRadicalsSupplement
CJKStrokes
CJKSymbolsandPunctuation
CJKUnifiedIdeographsExtensionA
CJKUnifiedIdeographsExtensionB
CJKUnifiedIdeographs
Cherokee
CombiningDiacriticalMarksSupplement
CombiningDiacriticalMarksforSymbols
CombiningDiacriticalMarks
CombiningHalfMarks
ControlPictures
Coptic
CountingRodNumerals
CuneiformNumbersandPunctuation
Cuneiform
CurrencySymbols
CypriotSyllabary
CyrillicExtendedA
CyrillicExtendedB
CyrillicSupplement
Cyrillic
Deseret
Devanagari
Dingbats
DominoTiles
EnclosedAlphanumerics
EnclosedCJKLettersandMonths
EthiopicExtended
EthiopicSupplement
Ethiopic
GeneralPunctuation
GeometricShapes
GeorgianSupplement
Georgian
Glagolitic
Gothic
GreekExtended
GreekandCoptic
Gujarati
Gurmukhi
HalfwidthandFullwidthForms
HangulCompatibilityJamo
HangulJamo
HangulSyllables
Hanunoo
Hebrew
HighPrivateUseSurrogates
HighSurrogates
Hiragana
IPAExtensions
IdeographicDescriptionCharacters
Kanbun
KangxiRadicals
Kannada
KatakanaPhoneticExtensions
Katakana
Kharoshthi
KhmerSymbols
Khmer
Lao
LatinExtendedAdditional
LatinExtendedA
LatinExtendedB
LatinExtendedC
LatinExtendedD
LatinSupplement
LetterlikeSymbols
Limbu
LinearBIdeograms
LinearBSyllabary
LowSurrogates
MahjongTiles
Malayalam
MathematicalAlphanumericSymbols
MathematicalOperators
MiscellaneousMathematicalSymbolsA
MiscellaneousMathematicalSymbolsB
MiscellaneousSymbolsandArrows
MiscellaneousSymbols
MiscellaneousTechnical
ModifierToneLetters
Mongolian
MusicalSymbols
Myanmar
NKo
NewTaiLue
NumberForms
Ogham
OldItalic
OldPersian
OpticalCharacterRecognition
Oriya
Osmanya
PhagsPa
Phoenician
PhoneticExtensionsSupplement
PhoneticExtensions
PrivateUseArea
Runic
Shavian
Sinhala
SmallFormVariants
SpacingModifierLetters
Specials
SuperscriptsandSubscripts
SupplementalArrowsA
SupplementalArrowsB
SupplementalMathematicalOperators
SupplementalPunctuation
SupplementaryPrivateUseAreaA
SupplementaryPrivateUseAreaB
SylotiNagri
Syriac
Tagalog
Tagbanwa
Tags
TaiLe
TaiXuanJingSymbols
Tamil
Telugu
Thaana
Thai
Tibetan
Tifinagh
Ugaritic
UnifiedCanadianAboriginalSyllabics
VariationSelectorsSupplement
VariationSelectors
VerticalForms
YiRadicals
YiSyllables
YijingHexagramSymbols
#endkeyvals

\autfontunicodedata#*
\fontwrapallowedenvironments#*
\fontwrapallowedmacros#*
\fontwrapdefaultCJKfont#*
\fontwrapdefaultfont#*
\perlfontwrap{text}{data}{allowed macros}{allowed envs}#*
\setunicodegroupArabicFont{font}#*
\setunicodegroupCJKFont{font}#*
\setunicodegroupChineseFont{font}#*
\setunicodegroupCyrillicFont{font}#*
\setunicodegroupDiacriticsFont{font}#*
\setunicodegroupGreekFont{font}#*
\setunicodegroupJapaneseFont{font}#*
\setunicodegroupKoreanFont{font}#*
\setunicodegroupLatinFont{font}#*
\setunicodegroupMathematicsFont{font}#*
\setunicodegroupOtherFont{font}#*
\setunicodegroupPhoneticsFont{font}#*
\setunicodegroupPunctuationFont{font}#*
\setunicodegroupSymbolsFont{font}#*
\setunicodegroupYiFont{font}#*
\unicodeblockAegeanNumbersFont#*
\unicodeblockAegeanNumbers{font macro}#*
\unicodeblockAlphabeticPresentationFormsFont#*
\unicodeblockAlphabeticPresentationForms{font macro}#*
\unicodeblockAncientGreekMusicalNotationFont#*
\unicodeblockAncientGreekMusicalNotation{font macro}#*
\unicodeblockAncientGreekNumbersFont#*
\unicodeblockAncientGreekNumbers{font macro}#*
\unicodeblockArabicFont#*
\unicodeblockArabicPresentationFormsAFont#*
\unicodeblockArabicPresentationFormsA{font macro}#*
\unicodeblockArabicPresentationFormsBFont#*
\unicodeblockArabicPresentationFormsB{font macro}#*
\unicodeblockArabicSupplementFont#*
\unicodeblockArabicSupplement{font macro}#*
\unicodeblockArabic{font macro}#*
\unicodeblockArmenianFont#*
\unicodeblockArmenian{font macro}#*
\unicodeblockArrowsFont#*
\unicodeblockArrows{font macro}#*
\unicodeblockBalineseFont#*
\unicodeblockBalinese{font macro}#*
\unicodeblockBasicLatinFont#*
\unicodeblockBasicLatin{font macro}#*
\unicodeblockBengaliFont#*
\unicodeblockBengali{font macro}#*
\unicodeblockBlockElementsFont#*
\unicodeblockBlockElements{font macro}#*
\unicodeblockBopomofoExtendedFont#*
\unicodeblockBopomofoExtended{font macro}#*
\unicodeblockBopomofoFont#*
\unicodeblockBopomofo{font macro}#*
\unicodeblockBoxDrawingFont#*
\unicodeblockBoxDrawing{font macro}#*
\unicodeblockBraillePatternsFont#*
\unicodeblockBraillePatterns{font macro}#*
\unicodeblockBugineseFont#*
\unicodeblockBuginese{font macro}#*
\unicodeblockBuhidFont#*
\unicodeblockBuhid{font macro}#*
\unicodeblockByzantineMusicalSymbolsFont#*
\unicodeblockByzantineMusicalSymbols{font macro}#*
\unicodeblockCJKCompatibilityFont#*
\unicodeblockCJKCompatibilityFormsFont#*
\unicodeblockCJKCompatibilityForms{font macro}#*
\unicodeblockCJKCompatibilityIdeographsFont#*
\unicodeblockCJKCompatibilityIdeographsSupplementFont#*
\unicodeblockCJKCompatibilityIdeographsSupplement{font macro}#*
\unicodeblockCJKCompatibilityIdeographs{font macro}#*
\unicodeblockCJKCompatibility{font macro}#*
\unicodeblockCJKRadicalsSupplementFont#*
\unicodeblockCJKRadicalsSupplement{font macro}#*
\unicodeblockCJKStrokesFont#*
\unicodeblockCJKStrokes{font macro}#*
\unicodeblockCJKSymbolsandPunctuationFont#*
\unicodeblockCJKSymbolsandPunctuation{font macro}#*
\unicodeblockCJKUnifiedIdeographsExtensionAFont#*
\unicodeblockCJKUnifiedIdeographsExtensionA{font macro}#*
\unicodeblockCJKUnifiedIdeographsExtensionBFont#*
\unicodeblockCJKUnifiedIdeographsExtensionB{font macro}#*
\unicodeblockCJKUnifiedIdeographsFont#*
\unicodeblockCJKUnifiedIdeographs{font macro}#*
\unicodeblockCherokeeFont#*
\unicodeblockCherokee{font macro}#*
\unicodeblockCombiningDiacriticalMarksFont#*
\unicodeblockCombiningDiacriticalMarksSupplementFont#*
\unicodeblockCombiningDiacriticalMarksSupplement{font macro}#*
\unicodeblockCombiningDiacriticalMarksforSymbolsFont#*
\unicodeblockCombiningDiacriticalMarksforSymbols{font macro}#*
\unicodeblockCombiningDiacriticalMarks{font macro}#*
\unicodeblockCombiningHalfMarksFont#*
\unicodeblockCombiningHalfMarks{font macro}#*
\unicodeblockControlPicturesFont#*
\unicodeblockControlPictures{font macro}#*
\unicodeblockCopticFont#*
\unicodeblockCoptic{font macro}#*
\unicodeblockCountingRodNumeralsFont#*
\unicodeblockCountingRodNumerals{font macro}#*
\unicodeblockCuneiformFont#*
\unicodeblockCuneiformNumbersandPunctuationFont#*
\unicodeblockCuneiformNumbersandPunctuation{font macro}#*
\unicodeblockCuneiform{font macro}#*
\unicodeblockCurrencySymbolsFont#*
\unicodeblockCurrencySymbols{font macro}#*
\unicodeblockCypriotSyllabaryFont#*
\unicodeblockCypriotSyllabary{font macro}#*
\unicodeblockCyrillicExtendedAFont#*
\unicodeblockCyrillicExtendedA{font macro}#*
\unicodeblockCyrillicExtendedBFont#*
\unicodeblockCyrillicExtendedB{font macro}#*
\unicodeblockCyrillicFont#*
\unicodeblockCyrillicSupplementFont#*
\unicodeblockCyrillicSupplement{font macro}#*
\unicodeblockCyrillic{font macro}#*
\unicodeblockDeseretFont#*
\unicodeblockDeseret{font macro}#*
\unicodeblockDevanagariFont#*
\unicodeblockDevanagari{font macro}#*
\unicodeblockDingbatsFont#*
\unicodeblockDingbats{font macro}#*
\unicodeblockDominoTilesFont#*
\unicodeblockDominoTiles{font macro}#*
\unicodeblockEnclosedAlphanumericsFont#*
\unicodeblockEnclosedAlphanumerics{font macro}#*
\unicodeblockEnclosedCJKLettersandMonthsFont#*
\unicodeblockEnclosedCJKLettersandMonths{font macro}#*
\unicodeblockEthiopicExtendedFont#*
\unicodeblockEthiopicExtended{font macro}#*
\unicodeblockEthiopicFont#*
\unicodeblockEthiopicSupplementFont#*
\unicodeblockEthiopicSupplement{font macro}#*
\unicodeblockEthiopic{font macro}#*
\unicodeblockGeneralPunctuationFont#*
\unicodeblockGeneralPunctuation{font macro}#*
\unicodeblockGeometricShapesFont#*
\unicodeblockGeometricShapes{font macro}#*
\unicodeblockGeorgianFont#*
\unicodeblockGeorgianSupplementFont#*
\unicodeblockGeorgianSupplement{font macro}#*
\unicodeblockGeorgian{font macro}#*
\unicodeblockGlagoliticFont#*
\unicodeblockGlagolitic{font macro}#*
\unicodeblockGothicFont#*
\unicodeblockGothic{font macro}#*
\unicodeblockGreekExtendedFont#*
\unicodeblockGreekExtended{font macro}#*
\unicodeblockGreekandCopticFont#*
\unicodeblockGreekandCoptic{font macro}#*
\unicodeblockGujaratiFont#*
\unicodeblockGujarati{font macro}#*
\unicodeblockGurmukhiFont#*
\unicodeblockGurmukhi{font macro}#*
\unicodeblockHalfwidthandFullwidthFormsFont#*
\unicodeblockHalfwidthandFullwidthForms{font macro}#*
\unicodeblockHangulCompatibilityJamoFont#*
\unicodeblockHangulCompatibilityJamo{font macro}#*
\unicodeblockHangulJamoFont#*
\unicodeblockHangulJamo{font macro}#*
\unicodeblockHangulSyllablesFont#*
\unicodeblockHangulSyllables{font macro}#*
\unicodeblockHanunooFont#*
\unicodeblockHanunoo{font macro}#*
\unicodeblockHebrewFont#*
\unicodeblockHebrew{font macro}#*
\unicodeblockHighPrivateUseSurrogatesFont#*
\unicodeblockHighPrivateUseSurrogates{font macro}#*
\unicodeblockHighSurrogatesFont#*
\unicodeblockHighSurrogates{font macro}#*
\unicodeblockHiraganaFont#*
\unicodeblockHiragana{font macro}#*
\unicodeblockIPAExtensionsFont#*
\unicodeblockIPAExtensions{font macro}#*
\unicodeblockIdeographicDescriptionCharactersFont#*
\unicodeblockIdeographicDescriptionCharacters{font macro}#*
\unicodeblockKanbunFont#*
\unicodeblockKanbun{font macro}#*
\unicodeblockKangxiRadicalsFont#*
\unicodeblockKangxiRadicals{font macro}#*
\unicodeblockKannadaFont#*
\unicodeblockKannada{font macro}#*
\unicodeblockKatakanaFont#*
\unicodeblockKatakanaPhoneticExtensionsFont#*
\unicodeblockKatakanaPhoneticExtensions{font macro}#*
\unicodeblockKatakana{font macro}#*
\unicodeblockKharoshthiFont#*
\unicodeblockKharoshthi{font macro}#*
\unicodeblockKhmerFont#*
\unicodeblockKhmerSymbolsFont#*
\unicodeblockKhmerSymbols{font macro}#*
\unicodeblockKhmer{font macro}#*
\unicodeblockLaoFont#*
\unicodeblockLao{font macro}#*
\unicodeblockLatinExtendedAFont#*
\unicodeblockLatinExtendedAdditionalFont#*
\unicodeblockLatinExtendedAdditional{font macro}#*
\unicodeblockLatinExtendedA{font macro}#*
\unicodeblockLatinExtendedBFont#*
\unicodeblockLatinExtendedB{font macro}#*
\unicodeblockLatinExtendedCFont#*
\unicodeblockLatinExtendedC{font macro}#*
\unicodeblockLatinExtendedDFont#*
\unicodeblockLatinExtendedD{font macro}#*
\unicodeblockLatinSupplementFont#*
\unicodeblockLatinSupplement{font macro}#*
\unicodeblockLetterlikeSymbolsFont#*
\unicodeblockLetterlikeSymbols{font macro}#*
\unicodeblockLimbuFont#*
\unicodeblockLimbu{font macro}#*
\unicodeblockLinearBIdeogramsFont#*
\unicodeblockLinearBIdeograms{font macro}#*
\unicodeblockLinearBSyllabaryFont#*
\unicodeblockLinearBSyllabary{font macro}#*
\unicodeblockLowSurrogatesFont#*
\unicodeblockLowSurrogates{font macro}#*
\unicodeblockMahjongTilesFont#*
\unicodeblockMahjongTiles{font macro}#*
\unicodeblockMalayalamFont#*
\unicodeblockMalayalam{font macro}#*
\unicodeblockMathematicalAlphanumericSymbolsFont#*
\unicodeblockMathematicalAlphanumericSymbols{font macro}#*
\unicodeblockMathematicalOperatorsFont#*
\unicodeblockMathematicalOperators{font macro}#*
\unicodeblockMiscellaneousMathematicalSymbolsAFont#*
\unicodeblockMiscellaneousMathematicalSymbolsA{font macro}#*
\unicodeblockMiscellaneousMathematicalSymbolsBFont#*
\unicodeblockMiscellaneousMathematicalSymbolsB{font macro}#*
\unicodeblockMiscellaneousSymbolsFont#*
\unicodeblockMiscellaneousSymbolsandArrowsFont#*
\unicodeblockMiscellaneousSymbolsandArrows{font macro}#*
\unicodeblockMiscellaneousSymbols{font macro}#*
\unicodeblockMiscellaneousTechnicalFont#*
\unicodeblockMiscellaneousTechnical{font macro}#*
\unicodeblockModifierToneLettersFont#*
\unicodeblockModifierToneLetters{font macro}#*
\unicodeblockMongolianFont#*
\unicodeblockMongolian{font macro}#*
\unicodeblockMusicalSymbolsFont#*
\unicodeblockMusicalSymbols{font macro}#*
\unicodeblockMyanmarFont#*
\unicodeblockMyanmar{font macro}#*
\unicodeblockNKoFont#*
\unicodeblockNKo{font macro}#*
\unicodeblockNewTaiLueFont#*
\unicodeblockNewTaiLue{font macro}#*
\unicodeblockNumberFormsFont#*
\unicodeblockNumberForms{font macro}#*
\unicodeblockOghamFont#*
\unicodeblockOgham{font macro}#*
\unicodeblockOldItalicFont#*
\unicodeblockOldItalic{font macro}#*
\unicodeblockOldPersianFont#*
\unicodeblockOldPersian{font macro}#*
\unicodeblockOpticalCharacterRecognitionFont#*
\unicodeblockOpticalCharacterRecognition{font macro}#*
\unicodeblockOriyaFont#*
\unicodeblockOriya{font macro}#*
\unicodeblockOsmanyaFont#*
\unicodeblockOsmanya{font macro}#*
\unicodeblockPhagsPaFont#*
\unicodeblockPhagsPa{font macro}#*
\unicodeblockPhoenicianFont#*
\unicodeblockPhoenician{font macro}#*
\unicodeblockPhoneticExtensionsFont#*
\unicodeblockPhoneticExtensionsSupplementFont#*
\unicodeblockPhoneticExtensionsSupplement{font macro}#*
\unicodeblockPhoneticExtensions{font macro}#*
\unicodeblockPrivateUseAreaFont#*
\unicodeblockPrivateUseArea{font macro}#*
\unicodeblockRunicFont#*
\unicodeblockRunic{font macro}#*
\unicodeblockShavianFont#*
\unicodeblockShavian{font macro}#*
\unicodeblockSinhalaFont#*
\unicodeblockSinhala{font macro}#*
\unicodeblockSmallFormVariantsFont#*
\unicodeblockSmallFormVariants{font macro}#*
\unicodeblockSpacingModifierLettersFont#*
\unicodeblockSpacingModifierLetters{font macro}#*
\unicodeblockSpecialsFont#*
\unicodeblockSpecials{font macro}#*
\unicodeblockSuperscriptsandSubscriptsFont#*
\unicodeblockSuperscriptsandSubscripts{font macro}#*
\unicodeblockSupplementalArrowsAFont#*
\unicodeblockSupplementalArrowsA{font macro}#*
\unicodeblockSupplementalArrowsBFont#*
\unicodeblockSupplementalArrowsB{font macro}#*
\unicodeblockSupplementalMathematicalOperatorsFont#*
\unicodeblockSupplementalMathematicalOperators{font macro}#*
\unicodeblockSupplementalPunctuationFont#*
\unicodeblockSupplementalPunctuation{font macro}#*
\unicodeblockSupplementaryPrivateUseAreaAFont#*
\unicodeblockSupplementaryPrivateUseAreaA{font macro}#*
\unicodeblockSupplementaryPrivateUseAreaBFont#*
\unicodeblockSupplementaryPrivateUseAreaB{font macro}#*
\unicodeblockSylotiNagriFont#*
\unicodeblockSylotiNagri{font macro}#*
\unicodeblockSyriacFont#*
\unicodeblockSyriac{font macro}#*
\unicodeblockTagalogFont#*
\unicodeblockTagalog{font macro}#*
\unicodeblockTagbanwaFont#*
\unicodeblockTagbanwa{font macro}#*
\unicodeblockTagsFont#*
\unicodeblockTags{font macro}#*
\unicodeblockTaiLeFont#*
\unicodeblockTaiLe{font macro}#*
\unicodeblockTaiXuanJingSymbolsFont#*
\unicodeblockTaiXuanJingSymbols{font macro}#*
\unicodeblockTamilFont#*
\unicodeblockTamil{font macro}#*
\unicodeblockTeluguFont#*
\unicodeblockTelugu{font macro}#*
\unicodeblockThaanaFont#*
\unicodeblockThaana{font macro}#*
\unicodeblockThaiFont#*
\unicodeblockThai{font macro}#*
\unicodeblockTibetanFont#*
\unicodeblockTibetan{font macro}#*
\unicodeblockTifinaghFont#*
\unicodeblockTifinagh{font macro}#*
\unicodeblockUgariticFont#*
\unicodeblockUgaritic{font macro}#*
\unicodeblockUnifiedCanadianAboriginalSyllabicsFont#*
\unicodeblockUnifiedCanadianAboriginalSyllabics{font macro}#*
\unicodeblockVariationSelectorsFont#*
\unicodeblockVariationSelectorsSupplementFont#*
\unicodeblockVariationSelectorsSupplement{font macro}#*
\unicodeblockVariationSelectors{font macro}#*
\unicodeblockVerticalFormsFont#*
\unicodeblockVerticalForms{font macro}#*
\unicodeblockYiRadicalsFont#*
\unicodeblockYiRadicals{font macro}#*
\unicodeblockYiSyllablesFont#*
\unicodeblockYiSyllables{font macro}#*
\unicodeblockYijingHexagramSymbolsFont#*
\unicodeblockYijingHexagramSymbols{font macro}#*
\unicodegroupArabicFont#*
\unicodegroupCJKFont#*
\unicodegroupChineseFont#*
\unicodegroupCyrillicFont#*
\unicodegroupDiacriticsFont#*
\unicodegroupGreekFont#*
\unicodegroupJapaneseFont#*
\unicodegroupKoreanFont#*
\unicodegroupLatinFont#*
\unicodegroupMathematicsFont#*
\unicodegroupOtherFont#*
\unicodegroupPhoneticsFont#*
\unicodegroupPunctuationFont#*
\unicodegroupSymbolsFont#*
\unicodegroupYiFont#*