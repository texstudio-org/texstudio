# quran package
# Matthew Bertucci 2023/06/27 for v1.9

#include:ifxetex
#include:biditools
#include:xkeyval
#include:listofitems
#include:xstring
#include:xspace

#keyvals:\usepackage/quran#c
nopar
nonumber
uthmani
uthmani-min
translt
transen
transde
transfa
transfr
trans=#lt,de,en,fa,fr
wordwise
ornbraces
#endkeyvals

\quransurah
\quransurah[surah range]
\quransurah*
\quransurah*[surah range]
\setsurahdefault{range}
\quranayah[surah range]
\quranayah[surah range][ayah range]
\quranayah*[surah range]
\quranayah*[surah range][ayah range]
\quranpage[page range]
\quranpage*[page range]
\quranjuz[juz range]
\quranjuz*[juz range]
\quranhizb[hizb range]
\quranhizb*[hizb range]
\quranquarter[quarter range]
\quranquarter*[quarter range]
\quranruku[ruku range]
\quranruku*[ruku range]
\quranmanzil[manzil range]
\quranmanzil*[manzil range]
\qurantext
\qurantext[index range]
\qurantext*
\qurantext*[index range]
\setqurantextdefault{m-n}

#ifOption:wordwise
\quranayah[surah range][ayah range][chunk range]
\quranayah[surah range][ayah range][chunk range]+
\qurantext[index range][chunk range]
\qurantext[index range][chunk range]+
#endif

\surahname[index]
\surahname*[index]
\basmalah
\Basmalah
\indexconvert{index}{surah macro}{ayah macro}
\surahcount
\ayahcount
\ToggleAyahNumber
\ToggleBasmalah
\SetOrnamentalBraces{starting brace}{ending brace}

## All option-specific commands listed with #S to account for many
## ways of loading, e.g. translt, trans=lt, trans={de,en,lt}, ...
## Listed without #S for obvious option cases

#ifOption:translt
\quransurahlt
\quransurahlt[surah range]
\quransurahlt*
\quransurahlt*[surah range]
\quranayahlt[surah range]
\quranayahlt[surah range][ayah range]
\quranayahlt*[surah range]
\quranayahlt*[surah range][ayah range]
\quranpagelt[page range]
\quranpagelt*[page range]
\quranjuzlt[juz range]
\quranjuzlt*[juz range]
\quranhizblt[hizb range]
\quranhizblt*[hizb range]
\quranquarterlt[quarter range]
\quranquarterlt*[quarter range]
\quranrukult[ruku range]
\quranrukult*[ruku range]
\quranmanzillt[manzil range]
\quranmanzillt*[manzil range]
\qurantextlt
\qurantextlt[index range]
\qurantextlt*
\qurantextlt*[index range]
\basmalahlt
\Basmalahlt
#endif
#ifOption:trans=lt
\quransurahlt
\quransurahlt[surah range]
\quransurahlt*
\quransurahlt*[surah range]
\quranayahlt[surah range]
\quranayahlt[surah range][ayah range]
\quranayahlt*[surah range]
\quranayahlt*[surah range][ayah range]
\quranpagelt[page range]
\quranpagelt*[page range]
\quranjuzlt[juz range]
\quranjuzlt*[juz range]
\quranhizblt[hizb range]
\quranhizblt*[hizb range]
\quranquarterlt[quarter range]
\quranquarterlt*[quarter range]
\quranrukult[ruku range]
\quranrukult*[ruku range]
\quranmanzillt[manzil range]
\quranmanzillt*[manzil range]
\qurantextlt
\qurantextlt[index range]
\qurantextlt*
\qurantextlt*[index range]
\basmalahlt
\Basmalahlt
#endif

#ifOption:transde
\quransurahde
\quransurahde[surah range]
\quransurahde*
\quransurahde*[surah range]
\quranayahde[surah range]
\quranayahde[surah range][ayah range]
\quranayahde*[surah range]
\quranayahde*[surah range][ayah range]
\quranpagede[page range]
\quranpagede*[page range]
\quranjuzde[juz range]
\quranjuzde*[juz range]
\quranhizbde[hizb range]
\quranhizbde*[hizb range]
\quranquarterde[quarter range]
\quranquarterde*[quarter range]
\quranrukude[ruku range]
\quranrukude*[ruku range]
\quranmanzilde[manzil range]
\quranmanzilde*[manzil range]
\qurantextde
\qurantextde[index range]
\qurantextde*
\qurantextde*[index range]
\basmalahde
\Basmalahde
#endif
#ifOption:trans=de
\quransurahde
\quransurahde[surah range]
\quransurahde*
\quransurahde*[surah range]
\quranayahde[surah range]
\quranayahde[surah range][ayah range]
\quranayahde*[surah range]
\quranayahde*[surah range][ayah range]
\quranpagede[page range]
\quranpagede*[page range]
\quranjuzde[juz range]
\quranjuzde*[juz range]
\quranhizbde[hizb range]
\quranhizbde*[hizb range]
\quranquarterde[quarter range]
\quranquarterde*[quarter range]
\quranrukude[ruku range]
\quranrukude*[ruku range]
\quranmanzilde[manzil range]
\quranmanzilde*[manzil range]
\qurantextde
\qurantextde[index range]
\qurantextde*
\qurantextde*[index range]
\basmalahde
\Basmalahde
#endif

#ifOption:transen
\quransurahen
\quransurahen[surah range]
\quransurahen*
\quransurahen*[surah range]
\quranayahen[surah range]
\quranayahen[surah range][ayah range]
\quranayahen*[surah range]
\quranayahen*[surah range][ayah range]
\quranpageen[page range]
\quranpageen*[page range]
\quranjuzen[juz range]
\quranjuzen*[juz range]
\quranhizben[hizb range]
\quranhizben*[hizb range]
\quranquarteren[quarter range]
\quranquarteren*[quarter range]
\quranrukuen[ruku range]
\quranrukuen*[ruku range]
\quranmanzilen[manzil range]
\quranmanzilen*[manzil range]
\qurantexten
\qurantexten[index range]
\qurantexten*
\qurantexten*[index range]
\basmalahen
\Basmalahen
#endif
#ifOption:trans=en
\quransurahen
\quransurahen[surah range]
\quransurahen*
\quransurahen*[surah range]
\quranayahen[surah range]
\quranayahen[surah range][ayah range]
\quranayahen*[surah range]
\quranayahen*[surah range][ayah range]
\quranpageen[page range]
\quranpageen*[page range]
\quranjuzen[juz range]
\quranjuzen*[juz range]
\quranhizben[hizb range]
\quranhizben*[hizb range]
\quranquarteren[quarter range]
\quranquarteren*[quarter range]
\quranrukuen[ruku range]
\quranrukuen*[ruku range]
\quranmanzilen[manzil range]
\quranmanzilen*[manzil range]
\qurantexten
\qurantexten[index range]
\qurantexten*
\qurantexten*[index range]
\basmalahen
\Basmalahen
#endif

#ifOption:transfr
\quransurahfr
\quransurahfr[surah range]
\quransurahfr*
\quransurahfr*[surah range]
\quranayahfr[surah range]
\quranayahfr[surah range][ayah range]
\quranayahfr*[surah range]
\quranayahfr*[surah range][ayah range]
\quranpagefr[page range]
\quranpagefr*[page range]
\quranjuzfr[juz range]
\quranjuzfr*[juz range]
\quranhizbfr[hizb range]
\quranhizbfr*[hizb range]
\quranquarterfr[quarter range]
\quranquarterfr*[quarter range]
\quranrukufr[ruku range]
\quranrukufr*[ruku range]
\quranmanzilfr[manzil range]
\quranmanzilfr*[manzil range]
\qurantextfr
\qurantextfr[index range]
\qurantextfr*
\qurantextfr*[index range]
\basmalahfr
\Basmalahfr
#endif
#ifOption:trans=fr
\quransurahfr
\quransurahfr[surah range]
\quransurahfr*
\quransurahfr*[surah range]
\quranayahfr[surah range]
\quranayahfr[surah range][ayah range]
\quranayahfr*[surah range]
\quranayahfr*[surah range][ayah range]
\quranpagefr[page range]
\quranpagefr*[page range]
\quranjuzfr[juz range]
\quranjuzfr*[juz range]
\quranhizbfr[hizb range]
\quranhizbfr*[hizb range]
\quranquarterfr[quarter range]
\quranquarterfr*[quarter range]
\quranrukufr[ruku range]
\quranrukufr*[ruku range]
\quranmanzilfr[manzil range]
\quranmanzilfr*[manzil range]
\qurantextfr
\qurantextfr[index range]
\qurantextfr*
\qurantextfr*[index range]
\basmalahfr
\Basmalahfr
#endif

#ifOption:transfa
\quransurahfa
\quransurahfa[surah range]
\quransurahfa*
\quransurahfa*[surah range]
\quranayahfa[surah range]
\quranayahfa[surah range][ayah range]
\quranayahfa*[surah range]
\quranayahfa*[surah range][ayah range]
\quranpagefa[page range]
\quranpagefa*[page range]
\quranjuzfa[juz range]
\quranjuzfa*[juz range]
\quranhizbfa[hizb range]
\quranhizbfa*[hizb range]
\quranquarterfa[quarter range]
\quranquarterfa*[quarter range]
\quranrukufa[ruku range]
\quranrukufa*[ruku range]
\quranmanzilfa[manzil range]
\quranmanzilfa*[manzil range]
\qurantextfa
\qurantextfa[index range]
\qurantextfa*
\qurantextfa*[index range]
\basmalahfa
\Basmalahfa
#endif
#ifOption:trans=fa
\quransurahfa
\quransurahfa[surah range]
\quransurahfa*
\quransurahfa*[surah range]
\quranayahfa[surah range]
\quranayahfa[surah range][ayah range]
\quranayahfa*[surah range]
\quranayahfa*[surah range][ayah range]
\quranpagefa[page range]
\quranpagefa*[page range]
\quranjuzfa[juz range]
\quranjuzfa*[juz range]
\quranhizbfa[hizb range]
\quranhizbfa*[hizb range]
\quranquarterfa[quarter range]
\quranquarterfa*[quarter range]
\quranrukufa[ruku range]
\quranrukufa*[ruku range]
\quranmanzilfa[manzil range]
\quranmanzilfa*[manzil range]
\qurantextfa
\qurantextfa[index range]
\qurantextfa*
\qurantextfa*[index range]
\basmalahfa
\Basmalahfa
#endif

\quransurahlt#S
\quransurahlt[surah range]#S
\quransurahlt*#S
\quransurahlt*[surah range]#S
\quranayahlt[surah range]#S
\quranayahlt[surah range][ayah range]#S
\quranayahlt*[surah range]#S
\quranayahlt*[surah range][ayah range]#S
\quranpagelt[page range]#S
\quranpagelt*[page range]#S
\quranjuzlt[juz range]#S
\quranjuzlt*[juz range]#S
\quranhizblt[hizb range]#S
\quranhizblt*[hizb range]#S
\quranquarterlt[quarter range]#S
\quranquarterlt*[quarter range]#S
\quranrukult[ruku range]#S
\quranrukult*[ruku range]#S
\quranmanzillt[manzil range]#S
\quranmanzillt*[manzil range]#S
\qurantextlt#S
\qurantextlt[index range]#S
\qurantextlt*#S
\qurantextlt*[index range]#S
\basmalahlt#S
\Basmalahlt#S
\quransurahde#S
\quransurahde[surah range]#S
\quransurahde*#S
\quransurahde*[surah range]#S
\quranayahde[surah range]#S
\quranayahde[surah range][ayah range]#S
\quranayahde*[surah range]#S
\quranayahde*[surah range][ayah range]#S
\quranpagede[page range]#S
\quranpagede*[page range]#S
\quranjuzde[juz range]#S
\quranjuzde*[juz range]#S
\quranhizbde[hizb range]#S
\quranhizbde*[hizb range]#S
\quranquarterde[quarter range]#S
\quranquarterde*[quarter range]#S
\quranrukude[ruku range]#S
\quranrukude*[ruku range]#S
\quranmanzilde[manzil range]#S
\quranmanzilde*[manzil range]#S
\qurantextde#S
\qurantextde[index range]#S
\qurantextde*#S
\qurantextde*[index range]#S
\basmalahde#S
\Basmalahde#S
\quransurahen#S
\quransurahen[surah range]#S
\quransurahen*#S
\quransurahen*[surah range]#S
\quranayahen[surah range]#S
\quranayahen[surah range][ayah range]#S
\quranayahen*[surah range]#S
\quranayahen*[surah range][ayah range]#S
\quranpageen[page range]#S
\quranpageen*[page range]#S
\quranjuzen[juz range]#S
\quranjuzen*[juz range]#S
\quranhizben[hizb range]#S
\quranhizben*[hizb range]#S
\quranquarteren[quarter range]#S
\quranquarteren*[quarter range]#S
\quranrukuen[ruku range]#S
\quranrukuen*[ruku range]#S
\quranmanzilen[manzil range]#S
\quranmanzilen*[manzil range]#S
\qurantexten#S
\qurantexten[index range]#S
\qurantexten*#S
\qurantexten*[index range]#S
\basmalahen#S
\Basmalahen#S
\quransurahfr#S
\quransurahfr[surah range]#S
\quransurahfr*#S
\quransurahfr*[surah range]#S
\quranayahfr[surah range]#S
\quranayahfr[surah range][ayah range]#S
\quranayahfr*[surah range]#S
\quranayahfr*[surah range][ayah range]#S
\quranpagefr[page range]#S
\quranpagefr*[page range]#S
\quranjuzfr[juz range]#S
\quranjuzfr*[juz range]#S
\quranhizbfr[hizb range]#S
\quranhizbfr*[hizb range]#S
\quranquarterfr[quarter range]#S
\quranquarterfr*[quarter range]#S
\quranrukufr[ruku range]#S
\quranrukufr*[ruku range]#S
\quranmanzilfr[manzil range]#S
\quranmanzilfr*[manzil range]#S
\qurantextfr#S
\qurantextfr[index range]#S
\qurantextfr*#S
\qurantextfr*[index range]#S
\basmalahfr#S
\Basmalahfr#S
\quransurahfa#S
\quransurahfa[surah range]#S
\quransurahfa*#S
\quransurahfa*[surah range]#S
\quranayahfa[surah range]#S
\quranayahfa[surah range][ayah range]#S
\quranayahfa*[surah range]#S
\quranayahfa*[surah range][ayah range]#S
\quranpagefa[page range]#S
\quranpagefa*[page range]#S
\quranjuzfa[juz range]#S
\quranjuzfa*[juz range]#S
\quranhizbfa[hizb range]#S
\quranhizbfa*[hizb range]#S
\quranquarterfa[quarter range]#S
\quranquarterfa*[quarter range]#S
\quranrukufa[ruku range]#S
\quranrukufa*[ruku range]#S
\quranmanzilfa[manzil range]#S
\quranmanzilfa*[manzil range]#S
\qurantextfa#S
\qurantextfa[index range]#S
\qurantextfa*#S
\qurantextfa*[index range]#S
\basmalahfa#S
\Basmalahfa#S

# not documented
\qurandate#S
\quranversion#S
\showitemsmacro{arg}#S
\ChangeQtPar#S
