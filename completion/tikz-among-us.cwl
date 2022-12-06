# tikz-among-us package
# Matthew Bertucci 2/22/2022 for v1.2.0
# adapted from cwl written by package author Fernando H. G. Zucatelli
# original: https://www.ctan.org/tex-archive/graphics/pgf/contrib/tikz-among-us/tex/tikz-among-us.cwl

# ======================
# Developed by FHZ -- Brasil
# ======================
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshadings
#include:xifthen

# ======================
# lines with #S added to get color completion
\amongUsOriginal{BodyColor}{EyeColor}#n
\amongUsOriginal[opt]{BodyColor}{EyeColor}#n
\amongUsOriginal{color}{color}#Sn
\amongUsOriginal[opt]{color}{color}#Sn
# ======================

# ======================
\amongUsEyesI{color}#n
\amongUsEyesI[opt]{color}#n
\amongUsEyesAngryI{color}#n
\amongUsEyesAngryI[opt]{color}#n
\amongUsEyesVeryangryI{color}#n
\amongUsEyesVeryangryI[opt]{color}#n
\amongUsEyesHappyI{color}#n
\amongUsEyesHappyI[opt]{color}#n
\amongUsEyesScaredI{color}#n
\amongUsEyesScaredI[opt]{color}#n
# ======================

# ======================
\amongUsBackpackI{BodyColor}#n
\amongUsBackpackI[opt]{BodyColor}#n
\amongUsBackpackI{color}#Sn
\amongUsBackpackI[opt]{color}#Sn
\amongUsBodyI{EyeColor}#n
\amongUsBodyI[opt]{EyeColor}#n
\amongUsBodyI{color}#Sn
\amongUsBodyI[opt]{color}#Sn
\amongUsI{BodyColor}{EyeColor}#n
\amongUsI[opt]{BodyColor}{EyeColor}#n
\amongUsI{color}{color}#Sn
\amongUsI[opt]{color}{color}#Sn
# ======================

# ======================
\impostorSmile{SmileColor}#n
\impostorSmile[opt]{SmileColor}#n
\impostorSmile{color}#Sn
\impostorSmile[opt]{color}#Sn
\impostorTeethUp{TeethColor}#n
\impostorTeethUp[opt]{TeethColor}#n
\impostorTeethUp{color}#Sn
\impostorTeethUp[opt]{color}#Sn
\impostorTeethLw{TeethColor}#n
\impostorTeethLw[opt]{TeethColor}#n
\impostorTeethLw{color}#Sn
\impostorTeethLw[opt]{color}#Sn
\impostorTeeth{TeethColor}#n
\impostorTeeth[opt]{TeethColor}#n
\impostorTeeth{color}#Sn
\impostorTeeth[opt]{color}#Sn
\impostorI{BodyColor}{EyeColor}{SmileColor}{TeethColor}#n
\impostorI[opt]{BodyColor}{EyeColor}{SmileColor}{TeethColor}#n
\impostorTeeth{color}{color}{color}{color}#Sn
\impostorTeeth[opt]{color}{color}{color}{color}#Sn
# ======================

# ======================
\amongUsGhostBodyI{BodyColor}#n
\amongUsGhostBodyI[opt]{BodyColor}#n
\amongUsGhostBodyI{color}#Sn
\amongUsGhostBodyI[opt]{color}#Sn
\amongUsGhostI{BodyColor}{EyeColor}#n
\amongUsGhostI[opt]{BodyColor}{EyeColor}#n
\amongUsGhostI{color}{color}#Sn
\amongUsGhostI[opt]{color}{color}#Sn
# ======================

# ======================
\amoongussCapInnerDetail#n
\amoongussCapWhite#n
\amoongussCapI{BodyColor}#n
\amoongussCapI[opt]{BodyColor}#n
\amoongussCapI{color}#Sn
\amoongussCapI[opt]{color}#Sn
\amoongussBodyI{BodyColor}#n
\amoongussBodyI[opt]{BodyColor}#n
\amoongussBodyI{color}#Sn
\amoongussBodyI[opt]{color}#Sn
\amoongussNoseI{NoseColor}#n
\amoongussNoseI[opt]{NoseColor}#n
\amoongussNoseI{color}#Sn
\amoongussNoseI[opt]{color}#Sn
\amoongussLeftHandI{PokeballColor}#n
\amoongussLeftHandI[opt]{PokeballColor}#n
\amoongussLeftHandI{color}#Sn
\amoongussLeftHandI[opt]{color}#Sn
\amoongussRightHandI{PokeballColor}#n
\amoongussRightHandI[opt]{PokeballColor}#n
\amoongussRightHandI{color}#Sn
\amoongussRightHandI[opt]{color}#Sn
\amoongussI{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussI[opt]{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussI{color}{color}{color}{color}{color}#Sn
\amoongussI[opt]{color}{color}{color}{color}{color}#Sn
# ======================

# ======================
\amoongussGhostBodyI{BodyColor}#n
\amoongussGhostBodyI[opt]{BodyColor}#n
\amoongussGhostBodyI{color}#Sn
\amoongussGhostBodyI[opt]{color}#Sn
\amoongussGhostI{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussGhostI[opt]{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussGhostI{color}{color}{color}{color}{color}#Sn
\amoongussGhostI[opt]{color}{color}{color}{color}{color}#Sn
# ======================

# ======================
\amongUsHandsA{HandColor}#n
\amongUsHandsA[opt]{HandColor}#n
\amongUsHandsA{color}#Sn
\amongUsHandsA[opt]{color}#Sn
\amongUsHandsB{HandColor}#n
\amongUsHandsB[opt]{HandColor}#n
\amongUsHandsB{color}#Sn
\amongUsHandsB[opt]{color}#Sn
\amongUsHandsC{HandColor}#n
\amongUsHandsC[opt]{HandColor}#n
\amongUsHandsC{color}#Sn
\amongUsHandsC[opt]{color}#Sn
\amongUsHandsD{HandColor}#n
\amongUsHandsD[opt]{HandColor}#n
\amongUsHandsD{color}#Sn
\amongUsHandsD[opt]{color}#Sn
\amongUsHandsE{HandColor}#n
\amongUsHandsE[opt]{HandColor}#n
\amongUsHandsE{color}#Sn
\amongUsHandsE[opt]{color}#Sn
\amongUsHandsF{HandColor}#n
\amongUsHandsF[opt]{HandColor}#n
\amongUsHandsF{color}#Sn
\amongUsHandsF[opt]{color}#Sn
\amongUsHandsG{HandColor}#n
\amongUsHandsG[opt]{HandColor}#n
\amongUsHandsG{color}#Sn
\amongUsHandsG[opt]{color}#Sn
# ======================

# ======================
\amongUsEyesII{color}#n
\amongUsEyesII[opt]{color}#n
\amongUsEyesAngryII{color}#n
\amongUsEyesAngryII[opt]{color}#n
\amongUsEyesVeryangryII{color}#n
\amongUsEyesVeryangryII[opt]{color}#n
\amongUsEyesHappyII{color}#n
\amongUsEyesHappyII[opt]{color}#n
\amongUsEyesScaredII{color}#n
\amongUsEyesScaredII[opt]{color}#n
# ======================

# ======================
\amongUsBackpackII{color}#n
\amongUsBackpackII[opt]{color}#n
\amongUsBodyII{color}#n
\amongUsBodyII[opt]{color}#n
\amongUsII{BodyColor}{EyeColor}#n
\amongUsII[opt]{BodyColor}{EyeColor}#n
\amongUsII{color}{color}#Sn
\amongUsII[opt]{color}{color}#Sn
# ======================

# ======================
\amongUsGhostBodyII{BodyColor}#n
\amongUsGhostBodyII[opt]{BodyColor}#n
\amongUsGhostBodyII{color}#Sn
\amongUsGhostBodyII[opt]{color}#Sn
\amongUsGhostII{BodyColor}{EyeColor}#n
\amongUsGhostII[opt]{BodyColor}{EyeColor}#n
\amongUsGhostII{color}{color}#Sn
\amongUsGhostII[opt]{color}{color}#Sn
# ======================

# ======================
\impostorII{BodyColor}{EyeColor}{SmileColor}{TeethColor}#n
\impostorII[opt]{BodyColor}{EyeColor}{SmileColor}{TeethColor}#n
\impostorII{color}{color}{color}{color}#Sn
\impostorII[opt]{color}{color}{color}{color}#Sn
# ======================

# ======================
\amoongussCapII{BodyColor}#n
\amoongussCapII[opt]{BodyColor}#n
\amoongussCapII{color}#Sn
\amoongussCapII[opt]{color}#Sn
\amoongussBodyII{BodyColor}#n
\amoongussBodyII[opt]{BodyColor}#n
\amoongussBodyII{color}#Sn
\amoongussBodyII[opt]{color}#Sn
\amoongussNoseII{NoseColor}#n
\amoongussNoseII[opt]{NoseColor}#n
\amoongussNoseII{color}#Sn
\amoongussNoseII[opt]{color}#Sn
\amoongussLeftHandII{PokeballColor}#n
\amoongussLeftHandII[opt]{PokeballColor}#n
\amoongussLeftHandII{color}#Sn
\amoongussLeftHandII[opt]{color}#Sn
\amoongussRightHandII{PokeballColor}#n
\amoongussRightHandII[opt]{PokeballColor}#n
\amoongussRightHandII{color}#Sn
\amoongussRightHandII[opt]{color}#Sn
\amoongussII{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussII[opt]{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussII{color}{color}{color}{color}{color}#Sn
\amoongussII[opt]{color}{color}{color}{color}{color}#Sn
# ======================

# ======================
\amoongussGhostBodyII{BodyColor}#n
\amoongussGhostBodyII[opt]{BodyColor}#n
\amoongussGhostBodyII{color}#Sn
\amoongussGhostBodyII[opt]{color}#Sn
\amoongussGhostII{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussGhostII[opt]{BodyColor}{EyeColor}{PokeballColor}{PokeballColor}{NoseColor}#n
\amoongussGhostII{color}{color}{color}{color}{color}#Sn
\amoongussGhostII[opt]{color}{color}{color}{color}{color}#Sn
# ======================

# ======================
\amongUsEyesIII{EyeColor}#n
\amongUsEyesIII[opt]{EyeColor}#n
\amongUsEyesIII{color}#Sn
\amongUsEyesIII[opt]{color}#Sn
\amongUsBodyIII{BodyColor}#n
\amongUsBodyIII[opt]{BodyColor}#n
\amongUsBodyIII{color}#Sn
\amongUsBodyIII[opt]{color}#Sn
\amongUsIII{EyeColor}{BodyColor}#n
\amongUsIII[opt]{EyeColor}{BodyColor}#n
\amongUsIII{color}{color}#Sn
\amongUsIII[opt]{color}{color}#Sn
# ======================
