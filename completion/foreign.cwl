# foreign package
# Matthew Bertucci 11/13/2021 for v2.7

#include:xpunctuate
#include:xspace

#keyvals:\usepackage/foreign#c
abbreviations
xfrench
xgerman
xlatin
phrases
all
UKenglish
british
#endkeyvals

\defasforeign{phrase%text}
\defasforeign[csname]{phrase%text}
\defnotforeign{phrase%text}
\defnotforeign[csname]{phrase%text}
\redefasforeign{phrase%text}
\redefasforeign[csname]{phrase%text}
\redefnotforeign{phrase%text}
\redefnotforeign[csname]{phrase%text}

\foreign{text}
\notforeign{text}
\foreignfullfont#*
\foreignabbrfont#*

#ifOption:xlatin
\addendum
\Addendum
\adhoc
\Adhoc
\aposteriori
\Aposteriori
\apriori
\Apriori
\caveat
\Caveat
\circa
\Circa
\curriculum
\Curriculum
\erratum
\Erratum
\ibidem
\Ibidem
\idem
\Idem
\sic
\Sic
\viceversa
\Viceversa
\vitae
\Vitae
#endif

#ifOption:xfrench
\ala
\Ala
\visavis
\Visavis
#endif

#ifOption:xgerman
\ansatz
\Ansatz
\gedanken
\Gedanken
#endif

#ifOption:abbreviations
\cf
\eg
\etal
\etc
\etseq
\ibid
\ie
\loccit
\opcit
\viz
\Cf
\Eg
\Etal
\Etc
\Etseq
\Ibid
\Ie
\Loccit
\Opcit
\Viz
#endif

# phrases option loads xfrench and xgerman options
#ifOption:phrases
# from xfrench option
\ala
\Ala
\visavis
\Visavis
# from xgerman option
\ansatz
\Ansatz
\gedanken
\Gedanken
#endif

# all option loads all options
#ifOption:all
# from xlatin option
\addendum
\Addendum
\adhoc
\Adhoc
\aposteriori
\Aposteriori
\apriori
\Apriori
\caveat
\Caveat
\circa
\Circa
\curriculum
\Curriculum
\erratum
\Erratum
\ibidem
\Ibidem
\idem
\Idem
\sic
\Sic
\viceversa
\Viceversa
\vitae
\Vitae
# from xfrench option
\ala
\Ala
\visavis
\Visavis
# from xgerman option
\ansatz
\Ansatz
\gedanken
\Gedanken
# from abbreviations option
\cf
\eg
\etal
\etc
\etseq
\ibid
\ie
\loccit
\opcit
\viz
\Cf
\Eg
\Etal
\Etc
\Etseq
\Ibid
\Ie
\Loccit
\Opcit
\Viz
#endif