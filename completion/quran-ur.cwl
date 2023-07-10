# quran-ur package
# Matthew Bertucci 4/9/2022 for v0.21

#include:xstring
#include:biditools
#include:xkeyval
#include:quran

#keyvals:\usepackage/quran-ur#c
ahmedali
jalandhry
jawadi
junagarhi
kanzuliman
maududi
najafi
qadri
all
# options passed to quran package
nopar
nonumber
uthmani
uthmani-min
translt
transen
transde
transfa
transfr
trans=#lt,en,de,fa,fr
wordwise
ornbraces
#endkeyvals

\urSetTrans{index}
\urGetTrans

\quransurahur
\quransurahur[surah range]
\quransurahur*
\quransurahur*[surah range]
\quranayahur[surah range]
\quranayahur[surah range][ayah range]
\quranayahur*[surah range]
\quranayahur*[surah range][ayah range]
\quranpageur[page range]
\quranpageur*[page range]
\quranjuzur[juz range]
\quranjuzur*[juz range]
\quranhizbur[hizb range]
\quranhizbur*[hizb range]
\quranquarterur[quarter range]
\quranquarterur*[quarter range]
\quranrukuur[ruku range]
\quranrukuur*[ruku range]
\quranmanzilur[manzil range]
\quranmanzilur*[manzil range]
\qurantextur
\qurantextur[index range]
\qurantextur*
\qurantextur*[index range]
\basmalahur
\Basmalahur

## from options passed to quran package
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

## not documented
\quranurdate#S
\quranurversion#S
