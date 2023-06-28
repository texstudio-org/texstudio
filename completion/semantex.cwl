# semantex package
# Matthew Bertucci 2022/09/24 for v0.520

#include:l3keys2e
#include:leftindex
#include:semtex

\NewVariableClass{\Class%cmd}#d
\NewVariableClass{\Class%cmd}[options]#d
\DeclareVariableClass{\Class%cmd}#d
\DeclareVariableClass{\Class%cmd}[options]#d
\NewSymbolClass{\Class%cmd}#d
\NewSymbolClass{\Class%cmd}[options]#d
\DeclareSymbolClass{\Class%cmd}#d
\DeclareSymbolClass{\Class%cmd}[options]#d
\NewSimpleClass{\Class%cmd}#d
\NewSimpleClass{\Class%cmd}[options]#d
\DeclareSimpleClass{\Class%cmd}#d
\DeclareSimpleClass{\Class%cmd}[options]#d
\SemantexBaseObject#*

\NewObject{\Class}{\object%cmd}{symbol%formula}#d
\NewObject{\Class}{\object%cmd}{symbol%formula}[options]#d
\DeclareObject{\Class}{\object%cmd}{symbol%formula}#d
\DeclareObject{\Class}{\object%cmd}{symbol%formula}[options]#d

\SetupClass{\Class}{keyvals}
\SetupObject{\object}{keyvals}
\UseClassInCommand{\Class}{symbol%formula}
\UseClassInCommand{\Class}[options%keyvals]{symbol%formula}

#keyvals:\SetupClass#c,\SetupObject#c,\UseClassInCommand#c
define keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
define keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
append keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
append keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
prepend keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
prepend keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
remove key=%<key name%>
remove key[%<args%>]=%<key name%>
define arg keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
define arg keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
append arg keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
append arg keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
prepend arg keys={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
prepend arg keys[%<args%>]={{%<key1%>}{%<keys to run%>}%<,{key2}{keys to run},...%>}
remove arg key=%<key name%>
remove arg key[%<args%>]=%<key name%>
execute={%<TeX code%>}
set keys={%<keyvals%>}
set keys x={%<keyvals%>}
data provide={%<data%>}
data set={%<data%>}{%<value%>}
data set x={%<data%>}{%<value%>}
data put left={%<data%>}{%<value%>}
data put left x={%<data%>}{%<value%>}
data put right={%<data%>}{%<value%>}
data put right x={%<data%>}{%<value%>}
data clear={%<data%>}{%<value%>}
bool provide={%<boolean%>}
bool set true={%<boolean%>}
bool set false={%<boolean%>}
bool if TF={%<boolean%>}{%<true%>}{%<false%>}
bool if T={%<boolean%>}{%<true%>}
bool if F={%<boolean%>}{%<false%>}
int provide={%<integer%>}
int set={%<integer%>}{%<value%>}
int incr={%<integer%>}
int if eq TF={%<integer1%>}{%<integer2%>}{%<true%>}{%<false%>}
int if eq T={%<integer1%>}{%<integer2%>}{%<true%>}
int if eq F={%<integer1%>}{%<integer2%>}{%<false%>}
int if greater TF={%<integer1%>}{%<integer2%>}{%<true%>}{%<false%>}
int if greater T={%<integer1%>}{%<integer2%>}{%<true%>}
int if greater F={%<integer1%>}{%<integer2%>}{%<false%>}
int if less TF={%<integer1%>}{%<integer2%>}{%<true%>}{%<false%>}
int if less T={%<integer1%>}{%<integer2%>}{%<true%>}
int if less F={%<integer1%>}{%<integer2%>}{%<false%>}
int clear={%<integer%>}
if blank TF={%<tokens%>}{%<true%>}{%<false%>}
if blank T={%<tokens%>}{%<true%>}
if blank F={%<tokens%>}{%<false%>}
string if eq TF={%<string1%>}{%<string2%>}{%<true%>}{%<false%>}
string if eq T={%<string1%>}{%<string2%>}{%<true%>}
string if eq F={%<string1%>}{%<string2%>}{%<false%>}
ERROR={%<error message%>}
ERROR key value not found={%<key%>}{%<value%>}
ERROR arg key value not found={%<key%>}{%<value%>}
parent=%<\Class%>
class=%<\Class%>
copy=%<\object%>
symbol={%<value%>}
symbol put left=%<value%>
symbol put right=%<value%>
height phantom=%<value%>
slanting phantom=%<value%>
grading position=#upper,lower
command=%<command%>
clear command
return
inner return
right return
left return
left index return
right index return
index return
left arg return
right arg return
arg return
output=%<\Class%>
do output#true,false
output options={%<keys%>}
parse options={%<keys%>}
parse
parse code
math class=%<command%>
default=%<value%>
*
**
slot
dots
* with other sep=%<separator%>
** with other sep=%<separator%>
arg=%<value%>
smash
prime
par#true,false
no par
never par
use par=#true,false,never
par size=#normal,auto,*,%<other%>
left par=%<parenthesis%>
right par=%<parenthesis%>
spar
spar=#normal,auto,*,%<other%>
spar size=#normal,auto,*,%<other%>
left spar=%<parenthesis%>
right spar=%<parenthesis%>
other spar={%<left parenthesis%>}{%<right parenthesis%>}
Other spar={%<left parenthesis%>}{%<right parenthesis%>}{%<normal|auto|*%>}
set arg keys={%<keyvals%>}
set arg keys x={%<keyvals%>}
set arg single keys={%<keyvals%>}
set arg single keys x={%<keyvals%>}
set one arg single key=%<key%>
set one arg single key x=%<key%>
set arg without keyval=%<value%>
set arg without keyval x=%<value%>
pre arg=%<value%>
pre arg put left=%<value%>
post arg=%<value%>
post arg put right=%<value%>
set arg sep=%<value%>
set arg slot=%<value%>
set arg dots=%<value%>
arg keyval=#true,false,single keys,one single keys
arg position=#left,right
next arg with sep#true,false
sep arg=%<value%>
comma arg=%<value%>
arg with other sep={%<separator%>}{%<value%>}
arg dots with other sep=%<separator%>
arg slot with other sep=%<separator%>
arg dots
comma arg dots
arg slot
comma arg slot
clear arg
clear pre arg
clear post arg
upper=%<value%>
sep upper=%<value%>
comman upper=%<value%>
pre upper=%<value%>
pre upper put left=%<value%>
post upper=%<value%>
post upper put right=%<value%>
upper put left=%<value%>
set upper sep=%<value%>
next upper with sep#true,false
upper with other sep={%<separator%>}{%<value%>}
upper slot
sep upper slot
comma upper slot
set upper slot=%<value%>
upper slot with other sep=%<separator%>
upper dots
sep upper dots
comma upper dots
set upper dots=%<value%>
upper dots with other sep=%<separator%>
upper *
upper **
sep upper *
sep upper **
comma upper *
comma upper **
upper * with other sep=%<separator%>
upper ** with other sep=%<separator%>
clear upper
clear pre upper
clear post upper
lower=%<value%>
sep lower=%<value%>
comma lower=%<value%>
pre lower=%<value%>
pre lower put left=%<value%>
post lower=%<value%>
post lower put right=%<value%>
lower put left=%<value%>
set lower sep=%<value%>
next lower with sep#true,false
lower with other sep={%<separator%>}{%<value%>}
lower slot
sep lower slot
comma lower slot
set lower slot=%<value%>
lower slot with other sep=%<separator%>
lower dots
sep lower dots
comma lower dots
set lower dots=%<value%>
lower dots with other sep=%<separator%>
lower *
lower **
sep lower *
sep lower **
comma lower *
comma lower **
lower * with other sep=%<separator%>
lower ** with other sep=%<separator%>
clear lower
clear pre lower
clear post lower
upper left=%<value%>
sep upper left=%<value%>
comman upper left=%<value%>
pre upper left=%<value%>
pre upper left put left=%<value%>
post upper left=%<value%>
post upper left put right=%<value%>
upper left put left=%<value%>
set upper left sep=%<value%>
next upper left with sep#true,false
upper left with other sep={%<separator%>}{%<value%>}
upper left slot
sep upper left slot
comma upper left slot
set upper left slot=%<value%>
upper left slot with other sep=%<separator%>
upper left dots
sep upper left dots
comma upper left dots
set upper left dots=%<value%>
upper left dots with other sep=%<separator%>
upper left *
upper left **
sep upper left *
sep upper left **
comma upper left *
comma upper left **
upper left * with other sep=%<separator%>
upper left ** with other sep=%<separator%>
clear upper left
clear pre upper left
clear post upper left
lower left=%<value%>
sep lower left=%<value%>
comman lower left=%<value%>
pre lower left=%<value%>
pre lower left put left=%<value%>
post lower left=%<value%>
post lower left put right=%<value%>
lower left put left=%<value%>
set lower left sep=%<value%>
next lower left with sep#true,false
lower left with other sep={%<separator%>}{%<value%>}
lower left slot
sep lower left slot
comma lower left slot
set lower left slot=%<value%>
lower left slot with other sep=%<separator%>
lower left dots
sep lower left dots
comma lower left dots
set lower left dots=%<value%>
lower left dots with other sep=%<separator%>
lower left *
lower left **
sep lower left *
sep lower left **
comma lower left *
comma lower left **
lower left * with other sep=%<separator%>
lower left ** with other sep=%<separator%>
clear lower left
clear pre lower left
clear post lower left
d=%<value%>
sep d=%<value%>
comma d=%<value%>
pre d=%<value%>
pre d put left=%<value%>
post d=%<value%>
post d put left=%<value%>
d put left=%<value%>
set d sep=%<value%>
next d with sep#true,false
d with other sep={%<separator%>}{%<value%>}
d slot
sep d slot
comma d slot
set d slot=%<value%>
d slot with other sep=%<separator%>
d dots
sep d dots
comma d dots
set d dots=%<value%>
d dots with other sep=%<separator%>
d *
d **
sep d *
sep d **
comma d *
comma d **
d * with other sep=%<separator%>
d ** with other sep=%<separator%>
clear d
clear pre d
clear post d
i=%<value%>
sep i=%<value%>
comma i=%<value%>
pre i=%<value%>
pre i put left=%<value%>
post d=%<value%>
post i put left=%<value%>
i put left=%<value%>
set i sep=%<value%>
next i with sep#true,false
i with other sep={%<separator%>}{%<value%>}
i slot
sep i slot
comma i slot
set i slot=%<value%>
i slot with other sep=%<separator%>
i dots
sep i dots
comma i dots
set i dots=%<value%>
i dots with other sep=%<separator%>
i *
i **
sep i *
sep i **
comma i *
comma i **
i * with other sep=%<separator%>
i ** with other sep=%<separator%>
clear i
clear pre i
clear post i
#endkeyvals

\SemantexSetup{options%keyvals}

#keyvals:\SemantexSetup#c
keyval parser=%<command%>
single key parser=%<command%>
semtex file#true,false
#endkeyvals

\SemantexRecordObject{command}
\SemantexRecordSource{source%definition}

\SemantexDelimiterSize%<⟨delimiter⟩%>

\SemantexThis
\SemantexSetKeys{keyvals}
\SemantexKeysSet{keyvals}#S
\SemantexSetKeysx{keyvals}
\SemantexKeysSetx{keyvals}#S
\SemantexSetArgKeys{keyvals}
\SemantexArgKeysSet{keyvals}#S
\SemantexSetArgKeysx{keyvals}
\SemantexArgKeysSetx{keyvals}#S
\SemantexSetArgSingleKeys{keyvals}
\SemantexArgSingleKeysSet{keyvals}#S
\SemantexSetArgSingleKeysx{keyvals}
\SemantexArgSingleKeysSetx{keyvals}#S
\SemantexSetOneArgSingleKey{keyvals}
\SemantexOneSingleArgKeySet{keyvals}#S
\SemantexSetOneArgSingleKeyx{keyvals}
\SemantexOneSingleArgKeySetx{keyvals}#S
\SemantexSetArgWithoutKeyval{keyvals}
\SemantexArgWithoutKeyvalSet{keyvals}#S
\SemantexSetArgWithoutKeyvalx{keyvals}
\SemantexArgWithoutKeyvalSetx{keyvals}#S
\SemantexDataProvide{data}
\SemantexDataSet{data}{value}
\SemantexDataSetx{data}{value}
\SemantexDataPutLeft{data}{value}
\SemantexDataPutLeftx{data}{value}
\SemantexDataPutRight{data}{value}
\SemantexDataPutRightx{data}{value}
\SemantexDataGet{data}
\SemantexDataGetExpNot{data}
\SemantexDataClear{data}
\SemantexBoolProvide{boolean}
\SemantexBoolSetTrue{boolean}
\SemantexBoolSetFalse{boolean}
\SemantexBoolIfTF{boolean}{true}{false}
\SemantexBoolIfT{boolean}{true}
\SemantexBoolIfF{boolean}{false}
\SemantexIntProvide{integer}
\SemantexIntGet{integer}
\SemantexIntSet{integer}{value}
\SemantexIntIncr{integer}
\SemantexIntIfEqTF{integer1}{integer2}{true}{false}
\SemantexIntIfEqT{integer1}{integer2}{true}
\SemantexIntIfEqF{integer1}{integer2}{false}
\SemantexIntIfGreaterTF{integer1}{integer2}{true}{false}
\SemantexIntIfGreaterT{integer1}{integer2}{true}
\SemantexIntIfGreaterF{integer1}{integer2}{false}
\SemantexIntIfLessTF{integer1}{integer2}{true}{false}
\SemantexIntIfLessT{integer1}{integer2}{true}
\SemantexIntIfLessF{integer1}{integer2}{false}
\SemantexIntClear{integer}
\SemantexIfBlankTF{tokens}{true}{false}
\SemantexIfBlankT{tokens}{true}
\SemantexIfBlankF{tokens}{false}
\SemantexStrIfEqTF{string1}{string2}{true}{false}
\SemantexStrIfEqT{string1}{string2}{true}
\SemantexStrIfEqF{string1}{string2}{false}
\SemantexERROR{error message}
\SemantexERRORKeyValueNotFound{key%plain}{value}
\SemantexERRORArgKeyValueNotFound{key%plain}{value}
\SemantexExpNot{value}

# not documented
\RecordSemantexDelimiterSize#S
\SemantexDelimiterSizeNoRecord#S
\SemantexMathCloseAuto{arg1}#S
\SemantexMathCloseNoPar#S
\SemantexMathClose{arg1}#S
\SemantexMathOpenAuto{arg1}#S
\SemantexMathOpenNoPar#S
\SemantexMathOpen{arg1}#S
\SemantexVersion#S
\SemantexAddToRecordedSource#S
\SemantexRecordOutput#S
\SemantexID{id}#S
