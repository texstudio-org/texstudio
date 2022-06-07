# datetime2 package
# Matthew Bertucci 11/11/2021 for v1.5.7

#include:tracklang
#include:etoolbox
#include:xkeyval

#ifOption:calc
#include:datetime2-calc
#endif
#ifOption:calc=true
#include:datetime2-calc
#endif

#ifOption:showdow
#include:datetime2-calc
#endif
#ifOption:showdow=true
#include:datetime2-calc
#endif

## 3 Displaying the Date and Time ##
\DTMdisplaydate{year}{month}{day}{day of week}
\DTMDisplaydate{year}{month}{day}{day of week}
\Today
\DTMtoday#*
\DTMToday#*
\DTMdate{%<YYYY%>-%<MM%>-%<DD%>}
\DTMDate{%<YYYY%>-%<MM%>-%<DD%>}
\DTMdate*{%<YYYY%>-%<MM%>-%<DD%>}
\DTMDate*{%<YYYY%>-%<MM%>-%<DD%>}
\DTMdisplaytime{hour}{minute}{second}
\DTMdisplayzone{hour offset}{minute offset}
\DTMcurrenttime
\DTMcurrentzone
\DTMtime{%<hh%>:%<mm%>:%<ss%>}
\DTMdisplay{year}{month}{day}{day of week}{hour}{min}{sec}{hour offset}{min offset}
\DTMDisplay{year}{month}{day}{day of week}{hour}{min}{sec}{hour offset}{min offset}
\DTMnow
\DTMNow

## 4 Storing and Using Dates and Times ##
\DTMsavedate{name}{%<YYYY%>-%<MM%>-%<DD%>}
\DTMsavenoparsedate{name}{YYYY}{MM}{DD}{dow}
\DTMsavetime{name}{%<hh%>:%<mm%>:%<ss%>}
\DTMsavetimezn{name}{%<hh%>:%<mm%>:%<ss%> %<TZh%>:%<TZm%>}
\DTMsavetimestamp{name}{%<YYYY%>-%<MM%>-%<DD%>T%<hh%>:%<mm%>:%<ss%> %<TZh%>:%<TZm%>}
\DTMsavepdftimestamp{name}{PDF data}#*
\DTMsavefrompdfdata{name}{PDF data}
\DTMsavenow{name}
\DTMsavefilemoddate{name}{file}
\DTMmakeglobal{name}
\DTMusedate{name}
\DTMUsedate{name}
\DTMusetime{name}
\DTMusezone{name}
\DTMuse{name}
\DTMUse{name}
\DTMifsaveddate{name}{true}{false}
\DTMfetchyear{name}
\DTMfetchmonth{name}
\DTMfetchday{name}
\DTMfetchdow{name}
\DTMfetchhour{name}
\DTMfetchminute{name}
\DTMfetchsecond{name}
\DTMfetchTZhour{name}
\DTMfetchTZminute{name}

## 5 Styles ##
\DTMsetdatestyle{style name%keyvals}
\DTMsettimestyle{style name%keyvals}
\DTMsetzonestyle{style name%keyvals}
\DTMsetstyle{style name%keyvals}
\DTMtryregional{lang code}{country code}
\DTMtryregional[lang name]{lang code}{country code}
\DTMtryregional*{lang code cs}{country code cs}
\DTMtryregional*[lang name]{lang code cs}{country code cs}

#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
default
iso
yyyymd
ddmmyyyy
dmyyyy
dmyy
ddmmyy
mmddyyyy
mmddyy
mdyyyy
mdyy
pdf
#endkeyvals

#keyvals:\DTMsettimestyle#c
hmmss
#endkeyvals

#keyvals:\DTMsetzonestyle#c
map
hhmm
#endkeyvals

\DTMnewdatestyle{name}{definition}#*
\DTMfinaldot#*
\DTMnewtimestyle{name}{definition}#*
\DTMnewzonestyle{name}{definition}#*
\DTMnewstyle{name}{data style def}{time style def}{zone style def}{full style def}#*
\DTMrenewdatestyle{name}{definition}#*
\DTMrenewtimestyle{name}{definition}#*
\DTMrenewzonestyle{name}{definition}#*
\DTMrenewstyle{name}{definition}#*
\DTMprovidedatestyle{name}{definition}#*
\DTMprovidetimestyle{name}{definition}#*
\DTMprovidezonestyle{name}{definition}#*
\DTMprovidestyle{name}{definition}#*
\DTMifhasstyle{name}{true}{false}#*
\DTMifhasdatestyle{name}{true}{false}#*
\DTMifhastimestyle{name}{true}{false}#*
\DTMifhaszonestyle{name}{true}{false}#*
\DTMtwodigits{number}#*
\DTMcentury{year}#*
\DTMdivhundred{number}#*
\DTMtexorpdfstring{TeX}{PDF}#*
\DTMsep{tag}#*
\DTMusezonemap{hour offset}{minute offset}#*
\DTMdefzonemap{hour offset}{minute offset}{abbr}#*
\DTMNatoZoneMaps#*
\DTMclearmap{hour offset}{minute offset}#*
\DTMresetzones#*
\DTMhaszonemap{hour offset}{minute offset}{true}{false}#*
\DTMusezonemapordefault{hour offset}{minute offset}#*

## 6 Multi-Lingual Support ##
\DTMlangsetup{options%keyvals}
\DTMlangsetup[module list]{options%keyvals}
\RequireDateTimeModule{name}#*
\DTMusemodule{language}{name}
\DTMdialecttomodulemap{dialect}#*

## 7 Standalone Month or Weekday Names ##
\DTMmonthname{month}
\DTMMonthname{month}
\DTMshortmonthname{month}
\DTMshortMonthname{month}

## 8 Package Options ##
\DTMsetup{options%keyvals}
#keyvals:\DTMsetup,\usepackage/datetime2#c
yearmonthsep=%<separator%>
monthdaysep=%<separator%>
dayyearsep=%<separator%>
datesep=%<separator%>
hourminsep=%<separator%>
minsecsep=%<separator%>
timesep=%<separator%>
datetimesep=%<separator%>
timezonesep=%<separator%>
showseconds#true,false
showdate#true,false
showzone#true,false
showzoneminutes#true,false
showisoZ#true,false
useregional=#false,text,numeric,num
showdow#true,false
warn#true,false
#endkeyvals

#keyvals:\usepackage/datetime2#c
style=%<style name%>
calc
%<language%>
#endkeyvals

\DTMsetregional
\DTMsetregional[value%keyvals]
#keyvals:\DTMsetregional
false
text
numeric
#endkeyvals

## Miscellaneous ##
\DTMdefboolkey{region}{key%plain}{func}#*
\DTMdefboolkey{region}{key%plain}[default]{func}#*
\DTMdefboolkey{region}{key%plain}[mp]{choice list}[default]{func}#*
\DTMdefchoicekey{region}{key%plain}{choice list}{default}{func}#*
\DTMdefchoicekey{region}{key%plain}[bin]{choice list}{default}{func}#*
\DTMdefkey{region}{key%plain}{func}#*
\DTMdefkey{region}{key%plain}[default]{func}#*
\DTMifbool{region}{key%plain}{true}{false}#*
\DTMifcaseregional{false}{text}{numeric}#*
\DTMsetbool{region}{key%plain}{value}#*
\DTMsetcurrentzone{hour offset}{minute offset}#*
\DTMshowmap{hour offset}{minute offset}#*
\ifDTMshowdow#*
\DTMshowdowtrue#*
\DTMshowdowfalse#*
\ProvidesDateTimeModule{module name}#*
\ifDTMshowseconds#*
\DTMshowsecondstrue#*
\DTMshowsecondsfalse#*
\ifDTMshowzone#*
\DTMshowzonetrue#*
\DTMshowzonefalse#*
\ifDTMshowzoneminutes#*
\DTMshowzoneminutestrue#*
\DTMshowzoneminutesfalse#*
\ifDTMshowisoZ#*
\DTMshowisoZtrue#*
\DTMshowisoZfalse#*
\ifDTMshowdate#*
\DTMshowdatetrue#*
\DTMshowdatefalse#*

## Language Modules ##
# datetime2-bahasai v1.01
\DTMbahasaiordinal{number}#*
\DTMbahasaimonthname{month}#*
\DTMbahasaidaymonthsep#*
\DTMbahasaimonthyearsep#*
\DTMbahasaidatetimesep#*
\DTMbahasaitimezonesep#*
\DTMbahasaidatesep#*
\DTMbahasaitimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
bahasai
bahasai-numeric
#endkeyvals
\DTMbahasaizonemaps#*

# datetime2-basque v1.2a
\DTMbasqueordinal{number}#*
\DTMbasquemonthname{month}#*
\DTMbasquedaymonthsep#*
\DTMbasquemonthyearsep#*
\DTMbasquedatetimesep#*
\DTMbasquetimezonesep#*
\DTMbasquedatesep#*
\DTMbasquetimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
basque
basque-numeric
#endkeyvals
\DTMbasquezonemaps#*

# datetime2-breton v1.2
\DTMbretonordinal{number}#*
\DTMbretonfmtordinal{text}#*
\DTMbretonfmtordsuffix{text}#*
\DTMbretonmonthname{month}#*
\DTMbretondaymonthsep#*
\DTMbretonmonthyearsep#*
\DTMbretondatetimesep#*
\DTMbretontimezonesep#*
\DTMbretondatesep#*
\DTMbretontimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
breton
breton-numeric
#endkeyvals
\DTMbretonzonemaps#*

# datetime2-bulgarian v1.1
\DTMbulgarianordinal{number}#*
\DTMbulgarianyear{year}#*
\DTMbulgarianmonthname{month}#*
\DTMbulgarianMonthname{month}#*
\DTMbulgariandaymonthsep#*
\DTMbulgarianmonthyearsep#*
\DTMbulgariandatetimesep#*
\DTMbulgariantimezonesep#*
\DTMbulgariandatesep#*
\DTMbulgariantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
bulgarian
bulgarian-numeric
#endkeyvals
\DTMbulgarianzonemaps#*

# datetime2-catalan v1.1
\DTMcatalanordinal{number}#*
\DTMcatalanmonthname{month}#*
\DTMcatalanMonthname{month}#*
\DTMcatalandaymonthsep#*
\DTMcatalanmonthyearsep#*
\DTMcatalandatetimesep#*
\DTMcatalantimezonesep#*
\DTMcatalandatesep#*
\DTMcatalantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
catalan
catalan-numeric
#endkeyvals
\DTMcatalanzonemaps#*

# datetime2-croatian v1.0
\DTMcroatianordinal{number}#*
\DTMcroatianyear{year}#*
\DTMcroatianmonthname{month}#*
\DTMcroatianMonthname{month}#*
\DTMcroatianweekdayname{day}#*
\DTMcroatianWeekdayname{day}#*
\DTMcroatianshortWeekdayname{day}#*
\DTMcroatianshortweekdayname{day}#*
\DTMcroatiandaymonthsep#*
\DTMcroatianmonthyearsep#*
\DTMcroatiandatetimesep#*
\DTMcroatiantimezonesep#*
\DTMcroatiandatesep#*
\DTMcroatiantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
croatian
croatian-numeric
#endkeyvals
\DTMcroatianzonemaps#*

# datetime2-czech v1.1
\DTMczechordinal{number}#*
\DTMczechmonthname{month}#*
\DTMczechMonthname{month}#*
\DTMczechdaymonthsep#*
\DTMczechmonthyearsep#*
\DTMczechdatetimesep#*
\DTMczechtimezonesep#*
\DTMczechdatesep#*
\DTMczechtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
czech
czech-numeric
#endkeyvals
\DTMczechzonemaps#*

# datetime2-danish v1.1
\DTMdanishordinal{number}#*
\DTMdanishmonthname{month}#*
\DTMdanishMonthname{month}#*
\DTMdanishweekdayname{day}#*
\DTMdanishWeekdayname{day}#*
\DTMdanishdaymonthsep#*
\DTMdanishmonthyearsep#*
\DTMdanishdatetimesep#*
\DTMdanishtimezonesep#*
\DTMdanishdatesep#*
\DTMdanishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
danish
danish-numeric
#endkeyvals
\DTMdanishzonemaps#*

# datetime2-dutch v1.1
\DTMdutchordinal{number}#*
\DTMdutchmonthname{month}#*
\DTMdutchMonthname{month}#*
\DTMdutchweekdayname{day}#*
\DTMdutchWeekdayname{day}#*
\DTMdutchshortweekdayname{day}#*
\DTMdutchshortWeekdayname{day}#*
\DTMdutchdaymonthsep#*
\DTMdutchmonthyearsep#*
\DTMdutchdatetimesep#*
\DTMdutchtimezonesep#*
\DTMdutchdatesep#*
\DTMdutchtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
dutch
dutch-numeric
#endkeyvals
\DTMdutchzonemaps#*

# datetime2-english v1.05
#keyvals:\DTMlangsetup#c
dowdaysep=%<separator%>
daymonthsep=%<separator%>
monthyearsep=%<separator%>
datesep=%<separator%>
timesep=%<separator%>
datetimesep=%<separator%>
timezonesep=%<separator%>
abbr#true,false
mapzone#true,false
ord=#level,raise,omit,sc
showdayofmonth#true,false
showyear#true,false
monthdaysep=%<separator%>
dayyearsep=%<separator%>
dowmonthsep=%<separator%>
zone=#std,standard,dst,daylight,atlantic,eastern,central,mountain,pacific,alaska,hawaii-aleutian,hawaii,aleutian,samoa,chamorro,clear,newfoundland,central-western,western,christmas,lord-howe,norfolk,cocos,keeling
#endkeyvals
\DTMenglishordinal{number}#*
\DTMenglishst#*
\DTMenglishnd#*
\DTMenglishrd#*
\DTMenglishth#*
\DTMenglishfmtordsuffix{suffix}#*
\DTMenglishmonthname{month}#*
\DTMenglishMonthname{month}#*
\DTMenglishweekdayname{day}#*
\DTMenglishWeekdayname{day}#*
\DTMenglishshortweekdayname{day}#*
\DTMenglishshortWeekdayname{day}#*
\DTMenglisham#*
\DTMenglishpm#*
\DTMenglishmidnight#*
\DTMenglishnoon#*
\DTMenglishampmfmt{text}#*
\DTMenglishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
english
en-GB
en-GB-numeric
en-US
en-US-numeric
en-CA
en-CA-numeric
en-AU
en-AU-numeric
en-NZ
en-NZ-numeric
en-GG
en-GG-numeric
en-JE
en-JE-numeric
en-IM
en-IM-numeric
en-MT
en-MT-numeric
en-IE
en-IE-numeric
#endkeyvals
\DTMenGBdowdaysep#*
\DTMenGBdaymonthsep#*
\DTMenGBmonthyearsep#*
\DTMenGBdatetimesep#*
\DTMenGBtimezonesep#*
\DTMenGBdatesep#*
\DTMenGBtimesep #*
\DTMenGBfmtordsuffix{suffix}#*
\DTMenGBzonemaps#*
\DTMenUSmonthdaysep#*
\DTMenUSdowmonthsep#*
\DTMenUSdayyearsep#*
\DTMenUSdatetimesep#*
\DTMenUStimezonesep#*
\DTMenUSdatesep#*
\DTMenUStimesep#*
\DTMenUSfmtordsuffix{suffix}#*
\DTMenUSzonemaps#*
\DTMenUSstdzonemaps#*
\DTMenUSdstzonemaps#*
\DTMenUSatlanticzonemaps #*
\DTMenUSeasternzonemaps #*
\DTMenUScentralzonemaps#*
\DTMenUSmountainzonemaps#*
\DTMenUSpacificzonemaps#*
\DTMenUSalaskazonemaps#*
\DTMenUShawaiialeutianzonemaps#*
\DTMenUSsamoazonemaps#*
\DTMenUSchamorrozonemaps#*
\DTMenCAmonthdaysep#*
\DTMenCAdowmonthsep#*
\DTMenCAdayyearsep#*
\DTMenCAdatetimesep#*
\DTMenCAtimezonesep#*
\DTMenCAdatesep#*
\DTMenCAtimesep#*
\DTMenCAfmtordsuffix{suffix}#*
\DTMenCAzonemaps#*
\DTMenCAstdzonemaps#*
\DTMenCAdstzonemaps#*
\DTMenCAnewfoundlandzonemaps#*
\DTMenCAatlanticzonemaps#*
\DTMenCAeasternzonemaps#*
\DTMenCAcentralzonemaps#*
\DTMenCAmountainzonemaps#*
\DTMenCApacificzonemaps#*
\DTMenAUdowdaysep#*
\DTMenAUdaymonthsep#*
\DTMenAUmonthyearsep#*
\DTMenAUdatetimesep#*
\DTMenAUtimezonesep#*
\DTMenAUdatesep#*
\DTMenAUtimesep#*
\DTMenAUfmtordsuffix{suffix}#*
\DTMenAUzonemaps#*
\DTMenAUstdzonemaps#*
\DTMenAUdstzonemaps#*
\DTMenAUcentralzonemaps#*
\DTMenAUcentralwesternzonemaps#*
\DTMenAUwesternzonemaps#*
\DTMenAUeasternzonemaps#*
\DTMenAUchrismaszonemaps#*
\DTMenAUlordhowezonemaps#*
\DTMenAUnorfolkzonemaps#*
\DTMenAUcocoszonemaps#*
\DTMenNZdowdaysep#*
\DTMenNZdaymonthsep#*
\DTMenNZmonthyearsep#*
\DTMenNZdatetimesep#*
\DTMenNZtimezonesep#*
\DTMenNZdatesep#*
\DTMenNZtimesep#*
\DTMenNZfmtordsuffix{suffix}#*
\DTMenNZzonemaps#*
\DTMenGGdowdaysep#*
\DTMenGGdaymonthsep#*
\DTMenGGmonthyearsep#*
\DTMenGGdatetimesep#*
\DTMenGGtimezonesep#*
\DTMenGGdatesep#*
\DTMenGGtimesep#*
\DTMenGGfmtordsuffix{suffix}#*
\DTMenGGzonemaps#*
\DTMenJEdowdaysep#*
\DTMenJEdaymonthsep#*
\DTMenJEmonthyearsep#*
\DTMenJEdatetimesep#*
\DTMenJEtimezonesep#*
\DTMenJEdatesep#*
\DTMenJEtimesep#*
\DTMenJEfmtordsuffix{suffix}#*
\DTMenJEzonemaps#*
\DTMenIMdowdaysep#*
\DTMenIMdaymonthsep#*
\DTMenIMmonthyearsep#*
\DTMenIMdatetimesep#*
\DTMenIMtimezonesep#*
\DTMenIMdatesep#*
\DTMenIMtimesep#*
\DTMenIMfmtordsuffix{suffix}#*
\DTMenIMzonemaps#*
\DTMenMTdowdaysep#*
\DTMenMTdaymonthsep#*
\DTMenMTmonthyearsep#*
\DTMenMTdatetimesep#*
\DTMenMTtimezonesep#*
\DTMenMTdatesep#*
\DTMenMTtimesep#*
\DTMenMTfmtordsuffix{suffix}#*
\DTMenMTzonemaps#*
\DTMenIEdowdaysep#*
\DTMenIEdaymonthsep#*
\DTMenIEmonthyearsep#*
\DTMenIEdatetimesep#*
\DTMenIEtimezonesep#*
\DTMenIEdatesep#*
\DTMenIEtimesep#*
\DTMenIEfmtordsuffix{suffix}#*
\DTMenIEzonemaps#*

# datetime2-esperanto v1.1
\DTMesperantoordinal{number}#*
\DTMesperantomonthname{month}#*
\DTMesperantoMonthname{month}#*
\DTMesperantodaymonthsep#*
\DTMesperantomonthyearsep#*
\DTMesperantodatetimesep#*
\DTMesperantotimezonesep#*
\DTMesperantodatesep#*
\DTMesperantotimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
esperanto
esperanto-numeric
#endkeyvals
\DTMesperantozonemaps#*

# datetime2-estonian v1.1
\DTMestonianordinal{number}#*
\DTMestonianmonthname{month}#*
\DTMestonianMonthname{month}#*
\DTMestoniandaymonthsep#*
\DTMestonianmonthyearsep#*
\DTMestoniandatetimesep#*
\DTMestoniantimezonesep#*
\DTMestoniandatesep#*
\DTMestoniantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
estonian
estonian-numeric
#endkeyvals
\DTMestonianzonemaps#*

# datetime2-finnish v1.2
\DTMfinnishordinal{number}#*
\DTMfinnishmonthname{month}#*
\DTMfinnishMonthname{month}#*
\DTMfinnishshortmonthname{month}#*
\DTMfinnishshortMonthname{month}#*
\DTMfinnishweekdayname{day}#*
\DTMfinnishWeekdayname{day}#*
\DTMfinnishshortweekdayname{day}#*
\DTMfinnishshortWeekdayname{day}#*
\DTMfinnishdaymonthsep#*
\DTMfinnishmonthyearsep#*
\DTMfinnishdatetimesep#*
\DTMfinnishtimezonesep#*
\DTMfinnishdatesep#*
\DTMfinnishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
finnish
finnish-numeric
#endkeyvals
\DTMfinnishzonemaps#*

# datetime2-french v1.03
\DTMfrenchordinal{number}#*
\DTMfrenchmonthname{month}#*
\DTMfrenchMonthname{month}#*
\DTMfrenchmonthname{month}#*
\DTMfrenchMonthname{month}#*
\DTMfrenchweekdayname{day}#*
\DTMfrenchWeekdayname{day}#*
\DTMfrenchshortweekdayname{day}#*
\DTMfrenchshortWeekdayname{day}#*
\DTMfrenchmidnight#*
\DTMfrenchnoon#*
\DTMfrenchtimesymsep#*
\DTMfrenchhoursym#*
\DTMfrenchdaymonthsep#*
\DTMfrenchmonthyearsep#*
\DTMfrenchdatetimesep#*
\DTMfrenchtimezonesep#*
\DTMfrenchdatesep#*
\DTMfrenchtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
french
french-numeric
#endkeyvals
\DTMfrenchzonemaps#*

# datetime2-galician v1.0
\DTMgalicianordinal{number}#*
\DTMgalicianmonthname{month}#*
\DTMgalicianMonthname{month}#*
\DTMgalicianweekdayname{day}#*
\DTMgalicianWeekdayname{day}#*
\DTMgalicianshortweekdayname{day}#*
\DTMgalicianshortWeekdayname{day}#*
\DTMgaliciandaymonthsep#*
\DTMgalicianmonthyearsep#*
\DTMgaliciandatetimesep#*
\DTMgaliciantimezonesep#*
\DTMgaliciandatesep#*
\DTMgaliciantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
galician
galician-numeric
#endkeyvals
\DTMgalicianzonemaps#*

# datetime2-german v3.0
\DTMgermanordinal{number}#*
\DTMgermanweekdayname{day}#*
\DTMgermanWeekdayname{day}#*
\DTMgermanshortweekdayname{day}#*
\DTMgermanshortWeekdayname{day}#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
german
german-numeric
de-DE
de-DE-numeric
de-AT
de-AT-numeric
de-CH
de-CH-numeric
#endkeyvals
\DTMgermanzonemaps#*
\DTMgermanmonthname{month}#*
\DTMdeATmonthname{month}#*
\DTMgermanshortmonthname{month}#*
\DTMdeATshortmonthname{month}#*
\DTMdeCHshortmonthname{month}#*
\DTMgermandowdaysep#*
\DTMgermandaymonthsep#*
\DTMgermanmonthyearsep#*
\DTMgermandatetimesep#*
\DTMgermantimezonesep#*
\DTMgermandatesep#*
\DTMgermantimesep#*
\DTMdeDEdowdaysep#*
\DTMdeDEdaymonthsep#*
\DTMdeDEmonthyearsep#*
\DTMdeDEdatetimesep#*
\DTMdeDEtimezonesep#*
\DTMdeDEdatesep#*
\DTMdeDEtimesep#*
\DTMdeATdowdaysep#*
\DTMdeATdaymonthsep#*
\DTMdeATmonthyearsep#*
\DTMdeATdatetimesep#*
\DTMdeATtimezonesep#*
\DTMdeATdatesep#*
\DTMdeATtimesep#*
\DTMdeCHdowdaysep#*
\DTMdeCHdaymonthsep#*
\DTMdeCHmonthyearsep#*
\DTMdeCHdatetimesep#*
\DTMdeCHtimezonesep#*
\DTMdeCHdatesep#*
\DTMdeCHtimesep#*

# datetime2-greek v1.1
\DTMgreekordinal{number}#*
\DTMgreekmonthname{month}#*
\DTMgreekMonthname{month}#*
\DTMgreekdaymonthsep#*
\DTMgreekmonthyearsep#*
\DTMgreekdatetimesep#*
\DTMgreektimezonesep#*
\DTMgreekdatesep#*
\DTMgreektimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
greek
greek-numeric
#endkeyvals
\DTMgreekzonemaps#*

# datetime2-hebrew v1.1
\DTMhebrewdate#*
\DTMhebrewdatetimesep#*
\DTMhebrewtimezonesep#*
\DTMhebrewdatesep#*
\DTMhebrewtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
hebrew
hebrew-numeric
#endkeyvals
\DTMhebrewzonemaps#*

# datetime2-icelandic v1.1
\DTMicelandicordinal{number}#*
\DTMicelandicmonthname{month}#*
\DTMicelandicMonthname{month}#*
\DTMicelandicdaymonthsep#*
\DTMicelandicmonthyearsep#*
\DTMicelandicdatetimesep#*
\DTMicelandictimezonesep#*
\DTMicelandicdatesep#*
\DTMicelandictimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
icelandic
icelandic-numeric
#endkeyvals
\DTMicelandiczonemaps#*

# datetime2-irish v1.1
\DTMirishordinal{number}#*
\DTMirishmonthname{month}#*
\DTMirishMonthname{month}#*
\DTMirishdaymonthsep#*
\DTMirishmonthyearsep#*
\DTMirishdatetimesep#*
\DTMirishtimezonesep#*
\DTMirishdatesep#*
\DTMirishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
irish
irish-numeric
#endkeyvals
\DTMirishzonemaps#*

# datetime2-italian v1.3
\DTMitalianordinal{number}#*
\DTMitalianmonthname{month}#*
\DTMitalianshortmonthname{month}#*
\DTMitalianweekdayname{day}#*
\DTMitalianshortweekdayname{day}#*
\DTMitaliandaymonthsep#*
\DTMitalianmonthyearsep#*
\DTMitaliandatetimesep#*
\DTMitaliantimezonesep#*
\DTMitaliandatesep#*
\DTMitaliantimesep#*
\DTMitalianam#*
\DTMitalianpm#*
\DTMitalianmidnight#*
\DTMitaliannoon#*
\DTMitalianampmfmt{text}#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
italian
italian-numeric
#endkeyvals
\DTMitalianzonemaps#*

# datetime2-latin v1.1
\DTMlatindatefont{text}#*
\DTMlatinordinal{number}#*
\DTMlatinyear{year}#*
\DTMlatinmonthname{month}#*
\DTMlatindaymonthsep#*
\DTMlatinmonthyearsep#*
\DTMlatindatetimesep#*
\DTMlatintimezonesep#*
\DTMlatindatesep#*
\DTMlatintimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
latin
latin-numeric
#endkeyvals
\DTMlatinzonemaps#*

# datetime2-lsorbian v1.1
\DTMlsorbianordinal{number}#*
\DTMlsorbiannewmonthname{month}#*
\DTMlsorbiannewMonthname{month}#*
\DTMlsorbianoldmonthname{month}#*
\DTMlsorbianoldMonthname{month}#*
\DTMlsorbianmonthname{month}#*
\DTMlsorbianMonthname{month}#*
\DTMlsorbiandaymonthsep#*
\DTMlsorbianmonthyearsep#*
\DTMlsorbiandatetimesep#*
\DTMlsorbiantimezonesep#*
\DTMlsorbiandatesep#*
\DTMlsorbiantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
lsorbian
lsorbian-numeric
#endkeyvals
\DTMlsorbianzonemaps#*

# datetime2-magyar v1.1
\DTMmagyarordinal{number}#*
\DTMmagyaryear{year}#*
\DTMmagyarmonthname{month}#*
\DTMmagyarMonthname{month}#*
\DTMmagyardaymonthsep#*
\DTMmagyarmonthyearsep#*
\DTMmagyardatetimesep#*
\DTMmagyartimezonesep#*
\DTMmagyardatesep#*
\DTMmagyartimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
magyar
magyar-numeric
#endkeyvals
\DTMmagyarzonemaps#*

# datetime2-norsk v1.1
\DTMnorskordinal{number}#*
\DTMnorskmonthname{month}#*
\DTMnorskMonthname{month}#*
\DTMnorskweekdayname{day}#*
\DTMnorskWeekdayname{day}#*
\DTMnorskdaymonthsep#*
\DTMnorskmonthyearsep#*
\DTMnorskdatetimesep#*
\DTMnorsktimezonesep#*
\DTMnorskdatesep#*
\DTMnorsktimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
norsk
norsk-numeric
#endkeyvals
\DTMnorskzonemaps#*

# datetime2-polish v1.1
\DTMpolishordinal{number}#*
\DTMpolishmonthname{month}#*
\DTMpolishMonthname{month}#*
\DTMpolishweekdayname{day}#*
\DTMpolishWeekdayname{day}#*
\DTMpolishdaymonthsep#*
\DTMpolishmonthyearsep#*
\DTMpolishdatetimesep#*
\DTMpolishtimezonesep#*
\DTMpolishdatesep#*
\DTMpolishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
polish
polish-numeric
#endkeyvals
\DTMpolishzonemaps#*

# datetime2-portuges v1.1
\DTMportugesordinal{number}#*
\DTMportugesmonthname{month}#*
\DTMportugesweekdayname{day}#*
\DTMportugesWeekdayname{day}#*
\DTMportugesdaymonthsep#*
\DTMportugesmonthyearsep#*
\DTMportugesdatetimesep#*
\DTMportugestimezonesep#*
\DTMportugesdatesep#*
\DTMportugestimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
portuges
portuges-numeric
#endkeyvals
\DTMportugeszonemaps#*

# datetime2-romanian v1.1
\DTMromanianordinal{number}#*
\DTMromanianmonthname{month}#*
\DTMromanianMonthname{month}#*
\DTMromanianshortmonthname{month}#*
\DTMromanianshortMonthname{month}#*
\DTMromanianweekdayname{day}#*
\DTMromanianWeekdayname{day}#*
\DTMromanianshortweekdayname{day}#*
\DTMromanianshortWeekdayname{day}#*
\DTMromaniandowdaysep#*
\DTMromaniandaymonthsep#*
\DTMromanianmonthyearsep#*
\DTMromaniandatetimesep#*
\DTMromaniantimezonesep#*
\DTMromaniandatesep#*
\DTMromaniantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
romanian
romanian-numeric
#endkeyvals
\DTMromanianzonemaps#*

# datetime2-russian v1.1
\DTMrussianordinal{number}#*
\DTMrussianyear{year}#*
\DTMrussianmonthname{month}#*
\DTMrussianMonthname{month}#*
\DTMrussiandaymonthsep#*
\DTMrussianmonthyearsep#*
\DTMrussiandatetimesep#*
\DTMrussiantimezonesep#*
\DTMrussiandatesep#*
\DTMrussiantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
russian
russian-numeric
#endkeyvals
\DTMrussianzonemaps#*

# datetime2-samin v1.1
\DTMsaminordinal{number}#*
\DTMsaminmonthname{month}#*
\DTMsaminMonthname{month}#*
\DTMsamindaymonthsep#*
\DTMsaminmonthyearsep#*
\DTMsamindatetimesep#*
\DTMsamintimezonesep#*
\DTMsamindatesep#*
\DTMsamintimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
samin
samin-numeric
#endkeyvals
\DTMsaminzonemaps#*

# datetime2-scottish v1.1
\DTMscottishordinal{number}#*
\DTMscottishmonthname{month}#*
\DTMscottishMonthname{month}#*
\DTMscottishdaymonthsep#*
\DTMscottishmonthyearsep#*
\DTMscottishdatetimesep#*
\DTMscottishtimezonesep#*
\DTMscottishdatesep#*
\DTMscottishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
scottish
scottish-numeric
#endkeyvals
\DTMscottishzonemaps#*

# datetime2-serbian v2.1
#keyvals:\DTMlangsetup#c
pronunciation=#ekavian,ijekavian
monthi#true,false
leadingzero#true,false
monthord=#arabic,roman,romanlsc
#endkeyvals
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
serbian
serbian-numeric
sr-Latn
sr-Latn-numeric
sr-Latn-RS
sr-Latn-RS-numeric
sr-Latn-ME
sr-Latn-ME-numeric
sr-Latn-BA
sr-Latn-BA-numeric
serbianc
serbianc-numeric
sr-Cyrl
sr-Cyrl-numeric
sr-Cyrl
sr-Cyrl-numeric
sr-Cyrl-RS
sr-Cyrl-RS-numeric
sr-Cyrl-ME
sr-Cyrl-ME-numeric
sr-Cyrl-BA
sr-Cyrl-BA-numeric
#endkeyvals
\DTMserbiancdatesep#*
\DTMserbiancdatetimesep#*
\DTMserbiancdaymonthsep#*
\DTMserbiancdayordinal{number}#*
\DTMserbiancdowdaysep#*
\DTMserbianciMonthname{month}#*
\DTMserbiancimonthname{month}#*
\DTMserbiancmonthordinal{number}#*
\DTMserbiancmonthyearsep#*
\DTMserbiancnoiMonthname{month}#*
\DTMserbiancnoimonthname{month}#*
\DTMserbianctimesep#*
\DTMserbianctimezonesep#*
\DTMserbiancweekdayname{day}#*
\DTMserbiancyrekweekdayname{day}#*
\DTMserbiancyrekWeekdayname{day}#*
\DTMserbiancyrijweekdayname{day}#*
\DTMserbiancyrijWeekdayname{day}#*
\DTMserbiancyrimonthname{month}#*
\DTMserbiancyriMonthname{month}#*
\DTMserbiancyrnoimonthname{month}#*
\DTMserbiancyrnoiMonthname{month}#*
\DTMserbianczonemaps#*
\DTMserbiandatesep#*
\DTMserbiandatetimesep#*
\DTMserbiandaymonthsep#*
\DTMserbiandayordinal{number}#*
\DTMserbiandowdaysep#*
\DTMserbianimonthname{month}#*
\DTMserbianiMonthname{month}#*
\DTMserbianlatekweekdayname{day}#*
\DTMserbianlatekWeekdayname{day}#*
\DTMserbianlatijweekdayname{day}#*
\DTMserbianlatijWeekdayname{day}#*
\DTMserbianlatimonthname{month}#*
\DTMserbianlatiMonthname{month}#*
\DTMserbianlatnoimonthname{month}#*
\DTMserbianlatnoiMonthname{month}#*
\DTMserbianmonthordinal{number}#*
\DTMserbianmonthyearsep#*
\DTMserbiannoimonthname{month}#*
\DTMserbiannoiMonthname{month}#*
\DTMserbianordinalROMAN{number}#*
\DTMserbianordinalroman{number}#*
\DTMserbiantimesep#*
\DTMserbiantimezonesep#*
\DTMserbianweekdayname{day}#*
\DTMserbianweekdayname{day}#*
\DTMserbianzonemaps#*
\DTMsrCyrlBAdatesep#*
\DTMsrCyrlBAdatetimesep#*
\DTMsrCyrlBAdaymonthsep#*
\DTMsrCyrlBAdayordinal{number}#*
\DTMsrCyrlBAdowdaysep#*
\DTMsrCyrlBAiMonthname{month}#*
\DTMsrCyrlBAimonthname{month}#*
\DTMsrCyrlBAmonthordinal{number}#*
\DTMsrCyrlBAmonthyearsep#*
\DTMsrCyrlBAnoiMonthname{month}#*
\DTMsrCyrlBAnoimonthname{month}#*
\DTMsrCyrlBAtimesep#*
\DTMsrCyrlBAtimezonesep#*
\DTMsrCyrlBAweekdayname{day}#*
\DTMsrCyrldatesep#*
\DTMsrCyrldatetimesep#*
\DTMsrCyrldaymonthsep#*
\DTMsrCyrldayordinal{number}#*
\DTMsrCyrldowdaysep#*
\DTMsrCyrliMonthname{month}#*
\DTMsrCyrlimonthname{month}#*
\DTMsrCyrlMEdatesep#*
\DTMsrCyrlMEdatetimesep#*
\DTMsrCyrlMEdaymonthsep#*
\DTMsrCyrlMEdayordinal{number}#*
\DTMsrCyrlMEdowdaysep#*
\DTMsrCyrlMEiMonthname{month}#*
\DTMsrCyrlMEimonthname{month}#*
\DTMsrCyrlMEmonthordinal{number}#*
\DTMsrCyrlMEmonthyearsep#*
\DTMsrCyrlMEnoiMonthname{month}#*
\DTMsrCyrlMEnoimonthname{month}#*
\DTMsrCyrlMEtimesep#*
\DTMsrCyrlMEtimezonesep#*
\DTMsrCyrlMEweekdayname{day}#*
\DTMsrCyrlmonthordinal{number}#*
\DTMsrCyrlmonthyearsep#*
\DTMsrCyrlnoiMonthname{month}#*
\DTMsrCyrlnoimonthname{month}#*
\DTMsrCyrlRSdatesep#*
\DTMsrCyrlRSdatetimesep#*
\DTMsrCyrlRSdaymonthsep#*
\DTMsrCyrlRSdayordinal{number}#*
\DTMsrCyrlRSdowdaysep#*
\DTMsrCyrlRSiMonthname{month}#*
\DTMsrCyrlRSimonthname{month}#*
\DTMsrCyrlRSmonthordinal{number}#*
\DTMsrCyrlRSmonthyearsep#*
\DTMsrCyrlRSnoiMonthname{month}#*
\DTMsrCyrlRSnoimonthname{month}#*
\DTMsrCyrlRStimesep#*
\DTMsrCyrlRStimezonesep#*
\DTMsrCyrlRSweekdayname{day}#*
\DTMsrCyrltimesep#*
\DTMsrCyrltimezonesep#*
\DTMsrCyrlweekdayname{day}#*
\DTMsrLatnBAdatesep#*
\DTMsrLatnBAdatetimesep#*
\DTMsrLatnBAdaymonthsep#*
\DTMsrLatnBAdayordinal{number}#*
\DTMsrLatnBAdowdaysep#*
\DTMsrLatnBAiMonthname{month}#*
\DTMsrLatnBAimonthname{month}#*
\DTMsrLatnBAmonthordinal{number}#*
\DTMsrLatnBAmonthyearsep#*
\DTMsrLatnBAnoiMonthname{month}#*
\DTMsrLatnBAnoimonthname{month}#*
\DTMsrLatnBAtimesep#*
\DTMsrLatnBAtimezonesep#*
\DTMsrLatnBAweekdayname{day}#*
\DTMsrLatndatesep#*
\DTMsrLatndatetimesep#*
\DTMsrLatndaymonthsep#*
\DTMsrLatndayordinal{number}#*
\DTMsrLatndowdaysep#*
\DTMsrLatniMonthname{month}#*
\DTMsrLatnimonthname{month}#*
\DTMsrLatnMEdatesep#*
\DTMsrLatnMEdatetimesep#*
\DTMsrLatnMEdaymonthsep#*
\DTMsrLatnMEdayordinal{number}#*
\DTMsrLatnMEdowdaysep#*
\DTMsrLatnMEiMonthname{month}#*
\DTMsrLatnMEimonthname{month}#*
\DTMsrLatnMEmonthordinal{number}#*
\DTMsrLatnMEmonthyearsep#*
\DTMsrLatnMEnoiMonthname{month}#*
\DTMsrLatnMEnoimonthname{month}#*
\DTMsrLatnMEtimesep#*
\DTMsrLatnMEtimezonesep#*
\DTMsrLatnMEweekdayname{day}#*
\DTMsrLatnmonthordinal{number}#*
\DTMsrLatnmonthyearsep#*
\DTMsrLatnnoiMonthname{month}#*
\DTMsrLatnnoimonthname{month}#*
\DTMsrLatnRSdatesep#*
\DTMsrLatnRSdatetimesep#*
\DTMsrLatnRSdaymonthsep#*
\DTMsrLatnRSdayordinal{number}#*
\DTMsrLatnRSdowdaysep#*
\DTMsrLatnRSiMonthname{month}#*
\DTMsrLatnRSimonthname{month}#*
\DTMsrLatnRSmonthordinal{number}#*
\DTMsrLatnRSmonthyearsep#*
\DTMsrLatnRSnoiMonthname{month}#*
\DTMsrLatnRSnoimonthname{month}#*
\DTMsrLatnRStimesep#*
\DTMsrLatnRStimezonesep#*
\DTMsrLatnRSweekdayname{day}#*
\DTMsrLatntimesep#*
\DTMsrLatntimezonesep#*
\DTMsrLatnweekdayname{day}#*

# datetime2-slovak v1.1
\DTMslovakordinal{number}#*
\DTMslovakmonthname{month}#*
\DTMslovakMonthname{month}#*
\DTMslovakdaymonthsep#*
\DTMslovakmonthyearsep#*
\DTMslovakdatetimesep#*
\DTMslovaktimezonesep#*
\DTMslovakdatesep#*
\DTMslovaktimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
slovak
slovak-numeric
#endkeyvals
\DTMslovakzonemaps#*

# datetime2-slovene v1.1
\DTMsloveneordinal{number}#*
\DTMslovenemonthname{month}#*
\DTMsloveneMonthname{month}#*
\DTMslovenedaymonthsep#*
\DTMslovenemonthyearsep#*
\DTMslovenedatetimesep#*
\DTMslovenetimezonesep#*
\DTMslovenedatesep#*
\DTMslovenetimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
slovene
slovene-numeric
#endkeyvals
\DTMslovenezonemaps#*

# datetime2-spanish v1.1
\DTMspanishordinal{number}#*
\DTMspanishmonthname{month}#*
\DTMspanishMonthname{month}#*
\DTMspanishweekdayname{day}#*
\DTMspanishWeekdayname{day}#*
\DTMspanishdaymonthsep#*
\DTMspanishmonthyearsep#*
\DTMspanishdatetimesep#*
\DTMspanishtimezonesep#*
\DTMspanishdatesep#*
\DTMspanishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
spanish
spanish-numeric
#endkeyvals
\DTMspanishzonemaps#*

# datetime2-swedish v1.0
\DTMswedishordinal{number}#*
\DTMswedishmonthname{month}#*
\DTMswedishMonthname{month}#*
\DTMswedishweekdayname{day}#*
\DTMswedishWeekdayname{day}#*
\DTMswedishdaymonthsep#*
\DTMswedishmonthyearsep#*
\DTMswedishdatetimesep#*
\DTMswedishtimezonesep#*
\DTMswedishdatesep#*
\DTMswedishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
swedish
swedish-numeric
#endkeyvals
\DTMswedishzonemaps#*

# datetime2-turkish v1.1
\DTMturkishordinal{number}#*
\DTMturkishmonthname{month}#*
\DTMturkishMonthname{month}#*
\DTMturkishdaymonthsep#*
\DTMturkishmonthyearsep#*
\DTMturkishdatetimesep#*
\DTMturkishtimezonesep#*
\DTMturkishdatesep#*
\DTMturkishtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
turkish
turkish-numeric
#endkeyvals
\DTMturkishzonemaps#*

# datetime2-ukrainian v1.2a
\DTMukrainianordinal{number}#*
\DTMukrainianyear{year}#*
\DTMukrainiannominativemonthname{month}#*
\DTMukrainiannominativeMonthname{month}#*
\DTMukrainiannominativeMonthname{month}#*
\DTMukrainiangenitiveMonthname{month}#*
\DTMukrainiangenitiveMonthname{month}#*
\DTMukrainianshortMonthname{month}#*
\DTMukrainianweekdayname{day}#*
\DTMukrainianWeekdayname{day}#*
\DTMukrainianshortweekdayname{day}#*
\DTMukrainianshortWeekdayname{day}#*
\DTMukrainianmonthname{month}#*
\DTMukrainianMonthname{month}#*
\DTMukrainiandowdaysep#*
\DTMukrainiandaymonthsep#*
\DTMukrainianmonthyearsep#*
\DTMukrainiandatetimesep#*
\DTMukrainiantimezonesep#*
\DTMukrainiandatesep#*
\DTMukrainiantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
ukrainian
ukrainian-numeric
#endkeyvals
\DTMukrainianzonemaps#*

# datetime2-usorbian v1.1
\DTMusorbianordinal{number}#*
\DTMusorbiannewmonthname
\DTMusorbiannewMonthname
\DTMusorbianoldmonthname
\DTMusorbianoldMonthname
\DTMusorbianmonthname{month}#*
\DTMusorbianMonthname{month}#*
\DTMusorbiandaymonthsep#*
\DTMusorbianmonthyearsep#*
\DTMusorbiandatetimesep#*
\DTMusorbiantimezonesep#*
\DTMusorbiandatesep#*
\DTMusorbiantimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
usorbian
usorbian-numeric
#endkeyvals
\DTMusorbianzonemaps#*

# datetime2-welsh v1.1
\DTMwelshordinal{number}#*
\DTMwelshfmtordinal{text}#*
\DTMwelshmonthname{month}#*
\DTMwelshfmtordsuffix{suffix}#*
\DTMwelshdaymonthsep#*
\DTMwelshmonthyearsep#*
\DTMwelshdatetimesep#*
\DTMwelshtimezonesep#*
\DTMwelshdatesep#*
\DTMwelshtimesep#*
#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c,\DTMsetzonestyle#c,\DTMsetstyle#c
welsh
welsh-numeric
#endkeyvals
\DTMwelshzonemaps#*
