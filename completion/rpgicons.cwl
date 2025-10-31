# rpgicons package
# Matthew Bertucci 2025/10/29 for v2.1.0

#keyvals:\usepackage/rpgicons#c
l3
pgf
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
\alignment{shape}
\alignment{shape}[options%keyvals]
\alignment[style]{shape}
\alignment[style]{shape}[options%keyvals]
\currency{shape}{integer}
\currency{shape}[options%keyvals]{integer}

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
\RPGIconsAlignment{shape}#*
\RPGIconsAlignment{shape}[options%keyvals]#*
\RPGIconsAlignment[style]{shape}#*
\RPGIconsAlignment[style]{shape}[options%keyvals]#*
\RPGIconsCurrency{shape}{integer}#*
\RPGIconsCurrency{shape}[options%keyvals]{integer}#*

\rpgiconsset{options%keyvals}

#keyvals:\die#c,\ability#c,\saving#c,\spell#c,\spellschool#c,\damage#c,\attack#c,\condition#c,\alignment#c,\currency#c,\RPGIconsUseIcon#c,\RPGIconsUseIcon*#c,\RPGIconsDie#c,\RPGIconsAbility#c,\RPGIconsSaving#c,\RPGIconsSpell#c,\RPGIconsSpellschool#c,\RPGIconsDamage#c,\RPGIconsAttack#c,\RPGIconsCondition#c,\RPGIconsAlignment#c,\RPGIconsCurrency#c,\rpgiconsset#c
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
every die={%<options%>}
every ability={%<options%>}
every saving={%<options%>}
every spell={%<options%>}
every spellschool={%<options%>}
every damage={%<options%>}
every attack={%<options%>}
every condition={%<options%>}
every alignment={%<options%>}
every currency={%<options%>}
every %<shape%>={%<options%>}
every die add={%<options%>}
every ability add={%<options%>}
every saving add={%<options%>}
every spell add={%<options%>}
every spellschool add={%<options%>}
every damage add={%<options%>}
every attack add={%<options%>}
every condition add={%<options%>}
every alignment add={%<options%>}
every currency add={%<options%>}
every %<shape%> add={%<options%>}
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
\rpgiconscurrency{shape}#*
\rpgiconscurrency{shape}[options%keyvals]#*
\provideprotectedrpgicon{command}{shape}{box name}
\provideprotectedrpgicon{command}{shape}[options]{box name}
\provideprotectedrpgicon{command}[style]{shape}{box name}
\provideprotectedrpgicon{command}[style]{shape}[options]{box name}
\useprotectedrpgicon{box name}
\rpgiconsroll{roll syntax}
#endif
