# tikzpingus package
# Matthew Bertucci 2023/09/21 for v1.1

#include:etoolbox
#include:tikz
#include:tikzlibraryintersections
#include:tikzlibraryshadings
#include:tikzlibrarypatterns.meta
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibraryshapes.symbols
#include:tikzlibraryshapes.geometric

#keyvals:\usepackage/tikzpingus#c
glows
manual-layers
bare
#endkeyvals

#ifOption:glows
#include:tikzlibraryfadings
#endif

\pingu
\pingu[options%keyvals]
\pingudefaults{options%keyvals}
\pingudefaultsappend{options%keyvals}

#keyvals:\pingu#c,\pingudefaults#c,\pingudefaultsappend#c
random from={{%<keyvals1%>}{%<keyvals2%>}%<...%>}
name=%<text%>
scale=%<factor%>
meta-dots#true,false
left foot=#none,normal,sit,simple,back,chubby,!random
left foot color=#%color
left foot none=#%color
left foot normal=#%color
left foot sit=#%color
left foot simple=#%color
left foot back=#%color
left foot chubby=#%color
right foot=#none,normal,sit,simple,back,chubby,!random
right foot color=#%color
right foot none=#%color
right foot normal=#%color
right foot sit=#%color
right foot simple=#%color
right foot back=#%color
right foot chubby=#%color
feet=#none,normal,sit,simple,back,chubby,!random
feet color=#%color
feet none=#%color
feet normal=#%color
feet sit=#%color
feet simple=#%color
feet back=#%color
feet chubby=#%color
body main=#%color
body head=#%color
body=#%color
body front=#%color
body type=#none,normal,chubby,legacy,tilt-right,tilt-left,!random
height=##L
small size
normal size
large size
left eye=#none,normal,vertical,shiny,wink,shock,devil,sad,angry,hearts,!random
left eye color=#%color
left eye second color=#%color
left eye none=#%color
left eye normal=#%color
left eye vertical=#%color
left eye shiny=#%color
left eye wink=#%color
left eye shock=#%color
left eye devil=#%color
left eye sad=#%color
left eye angry=#%color
left eye hearts=#%color
right eye=#none,normal,vertical,shiny,wink,shock,devil,sad,angry,hearts,!random
right eye color=#%color
right eye second color=#%color
right eye none=#%color
right eye normal=#%color
right eye vertical=#%color
right eye shiny=#%color
right eye wink=#%color
right eye shock=#%color
right eye devil=#%color
right eye sad=#%color
right eye angry=#%color
right eye hearts=#%color
eyes=#none,normal,vertical,shiny,wink,shock,devil,sad,angry,hearts,critical,!random
eyes color=#%color
eyes second color=#%color
eyes none=#%color
eyes normal=#%color
eyes vertical=#%color
eyes shiny=#%color
eyes wink=#%color
eyes shock=#%color
eyes devil=#%color
eyes sad=#%color
eyes angry=#%color
eyes hearts=#%color
eyes critical=#%color
left wing=#none,normal,wave,raise,grab,shock,hug
left wing color=#%color
left wing none=#%color
left wing normal=#%color
left wing wave=#%color
left wing raise=#%color
left wing grab=#%color
left wing shock=#%color
left wing hug=#%color
right wing=#none,normal,wave,raise,grab,shock,hug
right wing color=#%color
right wing none=#%color
right wing normal=#%color
right wing wave=#%color
right wing raise=#%color
right wing grab=#%color
right wing shock=#%color
right wing hug=#%color
wings=#none,normal,wave,raise,grab,shock,hug,!random
wings color=#%color
wings none=#%color
wings normal=#%color
wings wave=#%color
wings raise=#%color
wings grab=#%color
wings shock=#%color
wings hug=#%color
hair 1 color=#%color
hair 2 color=#%color
hair 3 color=#%color
hair 4 color=#%color
hair 5 color=#%color
hairs color=#%color
hairstyle=#none,normal,!random
hairstyle none=#%color
hairstyle normal=#%color
bill=#none,normal,foreground,flat,angry,!random
bill color=#%color
bill none=#%color
bill normal=#%color
bill foreground=#%color
bill flat=#%color
bill angry=#%color
:line
:fill
:ghost parts
:ghost parts=%<opacity%>
:ghost
:ghost=%<opacity%>
:devil
:devil=#%color
:hide
:back
:pingu={%<options%>}
:mix=%<color mix%>
:mix-draw=%<color mix%>
:mix-all=%<color mix%>
heart
heart=#%color
vampire teeth
vampire teeth=#%color
tie
tie=#%color
tie knot=#%color
tie length=##L
tie offset=##L
tie width=##L
tie pattern=%<TeX code%>
tie dots
tie dots=#%color
bow tie
bow tie=#%color
bow tie b=#%color
bow tie knot=#%color
bow tie offset=##L
cup
cup=#%color
cup straw=#%color
cup steam=#%color
cup steam shift=##L
medal
medal=#%color
medal band=#%color
medal shade=#%color
medal shade width=##L
medal text=%<text%>
gold medal
gold medal=%<text%>
silver medal
silver medal=%<text%>
bronze medal
bronze medal=%<text%>
eye patch left
eye patch left=#%color
eye patch right
eye patch right=#%color
monocle left
monocle left=#%color
monocle left glass=#%color
monocle left opacity=%<factor%>
monocle left string=#%color
monocle left string length=##L
monocle left blob=#%color
monocle right
monocle right=#%color
monocle right glass=#%color
monocle right opacity=%<factor%>
monocle right string=#%color
monocle right string length=##L
monocle right blob=#%color
pants
pants=#%color
pants bands#true,false
pants button left=#%color
pants button right=#%color
pants buttons=#%color
pants button left shade=#%color
pants button right shade=#%color
pants buttons shade=#%color
pants no buttons
pants extra height=##L
glow=#%color
glow thick=#%color
glow solid=#%color
glow steps={%<num1,num2,...%>}
glow function={%<function%>}
glow width function={%<function%>}
eye frame=#%color
glasses
glasses=#%color
glasses left fill=#%color
glasses right fill=#%color
glasses fill=#%color
glasses left opacity=%<factor%>
glasses right opacity=%<factor%>
glasses opacity=%<factor%>
glasses line width=##L
sun glasses
sun glasses=#%color
glasses round
glasses round=#%color
glasses round left fill=#%color
glasses round right fill=#%color
glasses round fill=#%color
glasses round left opacity=%<factor%>
glasses round right opacity=%<factor%>
glasses round opacity=%<factor%>
glasses round line width=##L
sun glasses round
sun glasses round=#%color
devil horns
devil horns=#%color
devil wings
devil wings=#%color
devil wings b=#%color
belt
belt=#%color
belt knot color=#%color
head band
head band=#%color
head band bend=%<degrees%>
head band angle=%<degrees%>
head band upper angle=%<degrees%>
head band knot#true,false
head band knot color=#%color
head band knot a color=#%color
head band knot b color=#%color
head band bands#true,false
head band bands a color=#%color
head band bands b color=#%color
rook
rook=#%color
rook back=#%color
rook hatch#true,false
rook shade=#%color
halo
halo=#%color
halo raise=##L
halo glow#true,false
halo above#true,false
strawhat
strawhat=#%color
strawhat ribbon=#%color
strawhat position={%<angle%>:(%<x,y%>){%<scale%>}}
hat
hat=#%color
hat ribbon=#%color
hat base=#%color
hat coronal=#%color
hat position={%<angle%>:(%<x,y%>){%<scale%>}}
mitra
mitra=#%color
mitra height
mitra background=#%color
mitra overset=##L
mitra lower angle=%<degrees%>
mitra upper angle=%<degrees%>
mitra lower band=#%color
mitra lower band height=%<factor%>
mitra upper band=#%color
mitra upper band height=%<factor%>
mitra center band=#%color
mitra center band width=%<factor%>
mitra position{%<angle%>:(%<x,y%>){%<scale%>}}
witch hat
witch hat=#%color
witch hat ribbon=#%color
witch hat base=#%color
witch hat coronal=#%color
witch hat band=#%color
witch hat position={%<angle%>:(%<x,y%>){%<scale%>}}
conical hat
conical hat=#%color
conical hat rounding=##L
conical hat shade=#%color
conical hat height=##L
conical hat width=##L
conical hat position={%<angle%>:(%<x,y%>){%<scale%>}}
cap
cap=#%color
cap padding=##L
cap extra height=##L
construction helmet
construction helmet=#%color
construction helmet padding=##L
construction helmet extra height=##L
construction helmet position={%<angle%>:(%<x,y%>){%<scale%>}}
crown
crown=#%color
crown 3d#true,false
crown back=#%color
crown front bend=%<degrees%>
crown back bend=%<degrees%>
crown gem shade#true,false
crown gem colors={%<clr1%>}{%<clr2%>}{%<clr3%>}{%<clr4%>}{%<clr5%>}{%<clr6%>}{%<clr7%>}
crown gem ring=#%color
crown position={%<angle%>:(%<x,y%>){%<scale%>}}
crown 2d
crown 2d=#%color
princess crown
princess crown=#%color
princess crown 3d#true,false
princess crown back=#%color
princess crown front bend=%<degrees%>
princess crown back bend=%<degrees%>
princess crown gem shade#true,false
princess crown bobbles#true,false
princess crown gem colors={%<clr1%>}{%<clr2%>}{%<clr3%>}{%<clr4%>}
princess crown gem ring=#%color
princess crown position={%<angle%>:(%<x,y%>){%<scale%>}}
princess crown 2d
princess crown 2d=#%color
cake-hat
cake-hat=#%color
cake-hat top=#%color
cake-hat shade=#%color
cake-hat candle=#%color
cake-hat candle fire=#%color
cake-hat candle fire 2=#%color
cake-hat candle fire 3=#%color
cake-hat candle wick=#%color
cake-hat candle shade=#%color
cake-hat candle back=#%color
cake-hat outline=#%color
cake-hat outline width=##L
cake-hat position={%<angle%>:(%<x,y%>){%<scale%>}}
pumpkin-hat
pumpkin-hat=#%color
pumpkin-hat stalk=#%color
pumpkin-hat stalk top=#%color
pumpkin-hat stripe a=#%color
pumpkin-hat stripe b=#%color
pumpkin-hat stripe c=#%color
pumpkin-hat outline=#%color
pumpkin-hat outline width=##L
pumpkin-hat position={%<angle%>:(%<x,y%>){%<scale%>}}
jack o lantern
jack o lantern=#%color
jack o lantern stalk=#%color
jack o lantern stalk top=#%color
jack o lantern stripe a=#%color
jack o lantern stripe b=#%color
jack o lantern stripe c=#%color
jack o lantern back stripe a=#%color
jack o lantern back stripe b=#%color
jack o lantern back stripe c=#%color
jack o lantern background=#%color
jack o lantern outline=#%color
jack o lantern outline width=##L
jack o lantern width=##L
jack o lantern height=##L
jack o lantern position={%<angle%>:(%<x,y%>){%<scale%>}}
jack o lantern helmet=#%color
bee
bee=#%color
bee body=#%color
bee wings=#%color
bee mouth=#%color
bee eyes=#%color
bee blush=#%color
bee position={%<angle%>:(%<x,y%>){%<scale%>}}
on horse
on horse=#%color
on horse flip#true,false
on horse donkey#true,false
on horse has base#true,false
on horse has bounding box#true,false
on horse draw=#%color
on horse mane=#%color
on horse mane draw=#%color
on horse thatch=#%color
on horse thatch draw=#%color
on horse tail=#%color
on horse tail draw=#%color
on horse eyes=#%color
on horse mouth=#%color
on horse nose=#%color
on horse ears=#%color
on horse base=#%color
on horse base draw=#%color
on horse base shade=#%color
on horse base shade draw=#%color
on horse front left hoof=#%color
on horse front right hoof=#%color
on horse back left hoof=#%color
on horse back right hoof=#%color
on horse front hoofs=#%color
on horse back hoofs=#%color
on horse hoofs=#%color
on horse xshift=##L
on horse yshift=##L
on horse scale=%<factor%>
horse behind
horse behind=#%color
vr-headset
vr-headset=#%color
vr-headset band=#%color
vr-headset band top=#%color
vr-headset hair
vr-headset text=%<text%>
vr-headset text color=#%color
headphone
headphone=#%color
headphone left=#%color
headphone right=#%color
headphone left outer=#%color
headphone right outer=#%color
headphone outer=#%color
headphone left inner=#%color
headphone right inner=#%color
headphone inner=#%color
santa hat
santa hat=#%color
santa hat second=#%color
santa hat bobble=#%color
santa beard
santa beard=#%color
santa beard string=#%color
snowball left
snowball left=#%color
snowball left size=##L
snowball left xshift=##L
snowball left yshift=##L
snowball right
snowball right=#%color
snowball right size=##L
snowball right xshift=##L
snowball right yshift=##L
wool hat
wool hat=#%color
wool hat second=#%color
wool hat bobble=#%color
deer hat
deer hat=#%color
deer hat b=#%color
deer hat band=#%color
mask
mask=#%color
mask band=#%color
mask line width=##L
mask band inner=#%color
mask band outer=#%color
blush
blush=#%color
blush second=#%color
blush opacity=%<factor%>
banner=%<text%>
banner band=#%color
banner text color=#%color
banner stick left color=#%color
banner stick right color=#%color
banner sticks color=#%color
banner stick left length=##L
banner stick right length=##L
banner sticks length=##L
banner raise=##L
banner height=##L
banner font=%<font commands%>
banner bent=%<degrees%>
left wing item angle=%<degrees%>
left wing item flip#true,false
right wing item angle=%<degrees%>
right wing item flip#true,false
lollipop left
lollipop left=#%color
lollipop left handle=#%color
lollipop left second=#%color
lollipop right
lollipop right=#%color
lollipop right handle=#%color
lollipop right second=#%color
cane left
cane left=#%color
cane left raise=##L
cane right
cane right=#%color
cane right raise=##L
hand cast left=%<text%>
hand cast left color=#%color
hand cast right=%<text%>
hand cast right color=#%color
sign post left
sign post left=%<text%>
sign post left color=#%color
sign post left font color=#%color
sign post right
sign post right=%<text%>
sign post right color=#%color
sign post right font color=#%color
lightsaber left
lightsaber left=#%color
lightsaber left handle=#%color
lightsaber left deco=#%color
lightsaber left ribbs=#%color
lightsaber left button=#%color
lightsaber left button b=#%color
lightsaber left double#true,alse
lightsaber left color b=#%color
lightsaber left length=##L
lightsaber left length b=##L
lightsaber left yshift=##L
lightsaber left glow#true,false
lightsaber left solid
lightsaber left glow core=#%color
lightsaber left outer glow factor=%<factor%>
lightsaber left disabled
lightsaber right
lightsaber right=#%color
lightsaber right handle=#%color
lightsaber right deco=#%color
lightsaber right ribbs=#%color
lightsaber right button=#%color
lightsaber right button b=#%color
lightsaber right double#true,alse
lightsaber right color b=#%color
lightsaber right length=##L
lightsaber right length b=##L
lightsaber right yshift=##L
lightsaber right glow#true,false
lightsaber right solid
lightsaber right glow core=#%color
lightsaber right outer glow factor=%<factor%>
lightsaber right disabled
light-staff left
light-staff left=#%color
light-staff left length=##L
light-staff left glow length=##L
light-staff left head=#%color
light-staff left staff=#%color
light-staff left core=#%color
light-staff left core width=##L
light-staff left outer glow factor=%<factor%>
light-staff right
light-staff right=#%color
light-staff right length=##L
light-staff right glow length=##L
light-staff right head=#%color
light-staff right staff=#%color
light-staff right core=#%color
light-staff right core width=##L
light-staff right outer glow factor=%<factor%>
broom left
broom left=#%color
broom left length=##L
broom left shift=##L
broom left band=#%color
broom left bristles a=#%color
broom left bristles b=#%color
broom left bristles c=#%color
broom right
broom right=#%color
broom right length=##L
broom right shift=##L
broom right band=#%color
broom right bristles a=#%color
broom right bristles b=#%color
broom right bristles c=#%color
flag left
flag left=#%color
flag left pole=#%color
flag left bobble=#%color
flag left code={%<code%>}
pride flag left
pride flag left=#%color
german flag left
german flag left=#%color
flag right
flag right=#%color
flag right pole=#%color
flag right bobble=#%color
flag right code={%<code%>}
pride flag right
pride flag right=#%color
german flag right
german flag right=#%color
present left
present left=#%color
present left width=##L
present left height=##L
present left ribbon=#%color
present left band=#%color
present left band width=##L
present left xshift=##L
present left yshift=##L
present left band second height=##L
present left band second yshift=##L
present left lid=#%color
present left lid height=##L
present left lid overhang=##L
present left lid yshift=##L
present left lid band=#%color
present right
present right=#%color
present right width=##L
present right height=##L
present right ribbon=#%color
present right band=#%color
present right band width=##L
present right xshift=##L
present right yshift=##L
present right band second height=##L
present right band second yshift=##L
present right lid=#%color
present right lid height=##L
present right lid overhang=##L
present right lid yshift=##L
present right lid band=#%color
staff left
staff left=#%color
staff left length=##L
staff left raise=##L
staff left code={%<TikZ code%>}
staff left code app={%<TikZ code%>}
staff left code app pre={%<TikZ code%>}
spear left
spear left=#%color
cross left
cross left=#%color
staff right
staff right=#%color
staff right length=##L
staff right raise=##L
staff right code={%<TikZ code%>}
staff right code app={%<TikZ code%>}
staff right code app pre={%<TikZ code%>}
spear right
spear right=#%color
cross right
cross right=#%color
hammer left
hammer left=#%color
hammer left handle length=##L
hammer left handle shift=##L
hammer left width=##L
hammer left height=##L
hammer left xshift=##L
hammer left yshift=##L
hammer left handle=#%color
hammer left with knob
hammer left with knob=#%color
hammer right
hammer right=#%color
hammer right handle length=##L
hammer right handle shift=##L
hammer right width=##L
hammer right height=##L
hammer right xshift=##L
hammer right yshift=##L
hammer right handle=#%color
hammer right with knob
hammer right with knob=#%color
magnifier left
magnifier left=#%color
magnifier left handle length=##L
magnifier left handle shift=##L
magnifier left size=##L
magnifier left glass=#%color
magnifier left opacity=%<factor%>
magnifier left thick=##L
magnifier left xshift=##L
magnifier left yshift=##L
magnifier right
magnifier right=#%color
magnifier right handle length=##L
magnifier right handle shift=##L
magnifier right size=##L
magnifier right glass=#%color
magnifier right opacity=%<factor%>
magnifier right thick=##L
magnifier right xshift=##L
magnifier right yshift=##L
plank left
plank left=#%color
plank left width=##L
plank left height=##L
plank left xshift=##L
plank left yshift=##L
plank right
plank right=#%color
plank right width=##L
plank right height=##L
plank right xshift=##L
plank right yshift=##L
laptop left
laptop left=#%color
laptop left bracket=#%color
laptop left lower=#%color
laptop left key=#%color
laptop left display=#%color
laptop left content={%<TikZ code%>}
laptop left mid={%<code%>}
laptop right
laptop right=#%color
laptop right bracket=#%color
laptop right lower=#%color
laptop right key=#%color
laptop right display=#%color
laptop right content={%<TikZ code%>}
laptop right mid={%<code%>}
devil fork left
devil fork left=#%color
devil fork left second=#%color
devil fork left length=##L
devil fork right
devil fork right=#%color
devil fork right second=#%color
devil fork right length=##L
horse left
horse left=#%color
horse left flip#true,false
horse left donkey#true,false
horse left has base#true,false
horse left draw=#%color
horse left mane=#%color
horse left mane draw=#%color
horse left thatch=#%color
horse left thatch draw=#%color
horse left tail=#%color
horse left tail draw=#%color
horse left eyes=#%color
horse left mouth=#%color
horse left nose=#%color
horse left ears=#%color
horse left base=#%color
horse left base draw=#%color
horse left base shade=#%color
horse left base shade draw=#%color
horse left front left hoof=#%color
horse left front right hoof=#%color
horse left back left hoof=#%color
horse left back right hoof=#%color
horse left front hoofs=#%color
horse left back hoofs=#%color
horse left hoofs=#%color
horse left xshift=##L
horse left yshift=##L
horse left on base
horse right
horse right=#%color
horse right flip#true,false
horse right donkey#true,false
horse right has base#true,false
horse right draw=#%color
horse right mane=#%color
horse right mane draw=#%color
horse right thatch=#%color
horse right thatch draw=#%color
horse right tail=#%color
horse right tail draw=#%color
horse right eyes=#%color
horse right mouth=#%color
horse right nose=#%color
horse right ears=#%color
horse right base=#%color
horse right base draw=#%color
horse right base shade=#%color
horse right base shade draw=#%color
horse right front left hoof=#%color
horse right front right hoof=#%color
horse right back left hoof=#%color
horse right back right hoof=#%color
horse right front hoofs=#%color
horse right back hoofs=#%color
horse right hoofs=#%color
horse right xshift=##L
horse right yshift=##L
horse right on base
cloak
cloak=#%color
cloak cap=#%color
cloak wings color=#%color
cloak bottom color=#%color
cloak front color=#%color
cloak padding=##L
cape
cape=#%color
shirt
shirt=#%color
shirt raise=##L
shirt padding=##L
shirt button top=#%color
shirt button middle=#%color
shirt button bottom=#%color
shirt buttons=#%color
shirt button top shade=#%color
shirt button middle shade=#%color
shirt button bottom shade=#%color
shirt buttons shade=#%color
shirt no buttons
shirt above
second shirt
second shirt=#%color
second shirt raise=##L
second shirt neck=#%color
xshift=##L
yshift=##L
#endkeyvals

!hide#B

\pinguloadlibrary{library1,library2,...%keyvals}
\pinguloadlibraries{library1,library2,...%keyvals}#*

#keyvals:\pinguloadlibrary#c,\pinguloadlibraries#c
shirts
glasses
medieval
cloak
christmas
science-fiction
fun
technology
flags
hats
sport
formal
signs
devil
safe
magic
movement
emotions
horse
#endkeyvals

# not documented
\basew#S
\basicfeetbend#S
\eyebaseang#S
\pengu[options]#S
\pinguanglehl#S
\pinguanglehr#S
\pingulightsaberfactor#S
\pingupathxbowtieknot#S
\pingupathxbowtieleft#S
\pingupathxbowtieright#S
\pingupathxtie#S
\pingupathxtieknot#S
\pingupathwitchhatupper#S
\pingulibpathprefix#S
