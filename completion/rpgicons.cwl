# rpgicons package
# Matthew Bertucci 2024/04/30 for v1.8.2

#keyvals:\usepackage/rpgicons#c
l3
pgf
# specific to l3
compat
opacity
# specific to pgf
pics
#endkeyvals

# l3 option loaded by default
#include:l3draw

\die{shape}{integer}
\die{shape}[options%keyvals]{integer}
\die[style]{shape}{integer}
\die[style]{shape}[options%keyvals]{integer}
\ability{shape}
\ability{shape}[options%keyvals]
\ability[style]{shape}
\ability[style]{shape}[options%keyvals]
\saving{shape}
\saving{shape}[options%keyvals]
\saving[style]{shape}
\saving[style]{shape}[options%keyvals]
\spell{shape}
\spell{shape}[options%keyvals]
\spellschool{shape}
\spellschool{shape}[options%keyvals]
\spellschool[style]{shape}
\spellschool[style]{shape}[options%keyvals]
\damage{shape}
\damage{shape}[options%keyvals]
\attack{shape}
\attack{shape}[options%keyvals]
\condition{shape}
\condition{shape}[options%keyvals]

\RPGIconsUseIcon{shape}#*
\RPGIconsUseIcon[options%keyvals]{shape}#*
\RPGIconsUseIcon[options%keyvals][integer]{shape}#*
\RPGIconsUseIcon*{shape}#*
\RPGIconsUseIcon*[options%keyvals]{shape}#*
\RPGIconsUseIcon*[options%keyvals][integer]{shape}#*

\RPGIconsDie{shape}{integer}#*
\RPGIconsDie{shape}[options%keyvals]{integer}#*
\RPGIconsDie[style]{shape}{integer}#*
\RPGIconsDie[style]{shape}[options%keyvals]{integer}#*
\RPGIconsAbility{shape}#*
\RPGIconsAbility{shape}[options%keyvals]#*
\RPGIconsAbility[style]{shape}#*
\RPGIconsAbility[style]{shape}[options%keyvals]#*
\RPGIconsSaving{shape}#*
\RPGIconsSaving{shape}[options%keyvals]#*
\RPGIconsSaving[style]{shape}#*
\RPGIconsSaving[style]{shape}[options%keyvals]#*
\RPGIconsSpell{shape}#*
\RPGIconsSpell{shape}[options%keyvals]#*
\RPGIconsSpellschool{shape}#*
\RPGIconsSpellschool{shape}[options%keyvals]#*
\RPGIconsSpellschool[style]{shape}#*
\RPGIconsSpellschool[style]{shape}[options%keyvals]#*
\RPGIconsDamage{shape}#*
\RPGIconsDamage{shape}[options%keyvals]#*
\RPGIconsAttack{shape}#*
\RPGIconsAttack{shape}[options%keyvals]#*
\RPGIconsCondition{shape}#*
\RPGIconsCondition{shape}[options%keyvals]#*

\rpgiconsset{options%keyvals}

#keyvals:\die#c,\ability#c,\saving#c,\spell#c,\spellschool#c,\damage#c,\attack#c,\condition#c,\RPGIconsUseIcon#c,\RPGIconsUseIcon*#c,\RPGIconsDie#c,\RPGIconsAbility#c,\RPGIconsSaving#c,\RPGIconsSpell#c,\RPGIconsSpellschool#c,\RPGIconsDamage#c,\RPGIconsAttack#c,\RPGIconsCondition#c,\rpgiconsset#c
frame=#ability,damage,saving,spellschool
stroke=#%color
fill=#%color
text=#%color
color=#%color
background=#%color
stroke opacity=%<factor%>
fill opacity=%<factor%>
text opacity=%<factor%>
opacity=%<factor%>
background opacity=%<factor%>
line width=##L
scale=%<factor%>
scale inner=%<factor%>
rotate=%<degrees%>
accessible
accessible=#basic,full,false
every die={%<options%>}
every ability={%<options%>}
every saving={%<options%>}
every spell={%<options%>}
every spellschool={%<options%>}
every damage={%<options%>}
every attack={%<options%>}
every condition={%<options%>}
every %<shape%>={%<options%>}
before sep=##L
after sep=##L
baseline=##L
#endkeyvals

\roll{roll syntax}
\RPGIconsRoll{roll syntax}#*

#keyvals:\rpgiconsset#c
roll syntax={%<syntax%>}
#endkeyvals

# specific to pgf option
#ifOption:pgf
#include:tikz
\rpgiconsdie{shape}{integer}#*
\rpgiconsdie{shape}[options%keyvals]{integer}#*
\rpgiconsdie[style]{shape}{integer}#*
\rpgiconsdie[style]{shape}[options%keyvals]{integer}#*
\rpgiconsability{shape}#*
\rpgiconsability{shape}[options%keyvals]#*
\rpgiconsability[style]{shape}#*
\rpgiconsability[style]{shape}[options%keyvals]#*
\rpgiconssaving{shape}#*
\rpgiconssaving{shape}[options%keyvals]#*
\rpgiconssaving[style]{shape}#*
\rpgiconssaving[style]{shape}[options%keyvals]#*
\rpgiconsspell{shape}#*
\rpgiconsspell{shape}[options%keyvals]#*
\rpgiconsspellschool{shape}#*
\rpgiconsspellschool{shape}[options%keyvals]#*
\rpgiconsspellschool[style]{shape}#*
\rpgiconsspellschool[style]{shape}[options%keyvals]#*
\rpgiconsdamage{shape}#*
\rpgiconsdamage{shape}[options%keyvals]#*
\rpgiconsattack{shape}#*
\rpgiconsattack{shape}[options%keyvals]#*
\rpgiconscondition{shape}#*
\rpgiconscondition{shape}[options%keyvals]#*
\provideprotectedrpgicon{command}{shape}{box name}
\provideprotectedrpgicon{command}{shape}[options]{box name}
\provideprotectedrpgicon{command}[style]{shape}{box name}
\provideprotectedrpgicon{command}[style]{shape}[options]{box name}
\useprotectedrpgicon{box name}
\rpgiconsroll{roll syntax}
#endif