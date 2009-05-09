# siunitx package
# get it from http://tug.ctan.org/cgi-bin/ctanPackageInformation.py?id=siunitx
# dsarpe 03.07.2008

# Numbers
\num{number}
\num[options]{number}

# Angles
\ang{angle}
\ang[options]{angle}

# Units and values
\SI{value}{unit commands}
\SI[options]{value}{unit commands}
\SI{value}[pre-unit]{unit commands}
\SI[options]{value}[pre-unit]{unit commands}

# Powers of units
\Square
\ssquare
\squared
\cubic
\cubed
\per
\tothe{power}
\raiseto{power}

# Units with no values
\si{unit}
\si[options]{unit}

#
# pre-defined units, prefixes and powers
#
# The seven base SI units
\kilogram
\metre
\second
\mole
\kelvin
\ampere
\candela

# The SI prefixes
\yocto
\zepto
\atto
\femto
\pico
\nano
\micro
\milli
\centi
\deci
\deca
\deka
\hecto
\kilo
\mega
\giga
\tera
\peta
\exa
\zetta
\yotta

# The derived SI units with defined names
\becquerel
\celsius
\coulomb
\farad
\Gray
\ggray
\hertz
\henry
\joule
\katal
\lumen
\lux
\newton
\ohm
\pascal
\radian
\siemens
\sievert
\steradian
\tesla
\volt
\watt
\weber

# Units derived from experiments
\electronvolt
\atomicmassunit
\atomicmass

# Units accepted for use with SI
\bel
\Day
\dday
\degree
\hour
\minute
\arcmin
\neper
\percent
\arcsec
\tonne

# Prefixed and abbreviated units
# Masses
\kilogram
\kg
\femtogram
\fg
\picogram
\pg
\nanogram
\nanog
\microgram
\micg
\milligram
\mg
\atomicmass
\amu
# Lengths
\picometre
\picom
\nanometre
\nm
\micrometre
\micm
\millimetre
\mm
\centimetre
\cm
\decimetre
\dm
\kilometre
\km
# Times
\second
\Sec
\attosecond
\as
\femtosecond
\fs
\picosecond
\ps
\nanosecond
\ns
\microsecond
\mics
\millisecond
\ms
# Moles
\femtomole
\fmol
\picomole
\pmol
\nanomole
\nmol
\micromole
\micmol
\millimole
\mmol
# Currents
\picoampere
\pA
\nanoampere
\nA
\microampere
\micA
\kiloampere
\kA
# Areas
\squarecentimetre
\centimetresquared
\cms
\squaremetre
\squarekilometre
# Volumes
\microlitre
\micl
\millilitre
\ml
\cubiccentimetre
\cmc
\centimetrecubed
\cubicdecimetre
\dmc
# Frequencies
\hertz
\Hz
\millihertz
\mHz
\kilohertz
\kHz
\megahertz
\MHz
\gigahertz
\GHz
\terahertz
\THz
# potentials
\millivolt
\mV
\kilovolt
\kV
# Energies
\kilojoule
\kJ
\electronvolt
\eV
\millielectronvolt
\meV
\kiloelectronvolt
\keV
\megaelectronvolt
\MeV
\gigaelectronvolt
\GeV
\teraelectronvolt
\TeV
\kilowatthour
\kWh
# Powers
\milliwatt
\kilowatt
\megawatt
# Capacitances
\femtofarad
\picofarad
\nanofarad
\microfarad
\millifarad
# Resistances
\kiloohm
\megaohm
\gigaohm
\millisiemens
# Forces
\millinewton
\kilonewton
# Other units
\hectopascal
\megabecquerel
\millisievert

# Additional (temporary) SI units
\angstrom
\are
\curie
\BAR
\bbar
\barn
\gal
\hectare
\millibar
\rad
\rem
\roentgen

# Defining new units
\newunit{new unit command}{text}
\newunit[options]{new unit command}{text}
\renewunit{new unit command}{text}
\renewunit[options]{new unit command}{text}
\provideunit{new unit command}{text}
\provideunit[options]{new unit command}{text}
\newpower{power}{num}
\newpower[post]{power}{num}
\renewpower{power}{num}
\renewpower[post]{power}{num}
\providepower{power}{num}
\providepower[post]{power}{num}
\newprefix{prefix}{symbol}{powers-ten}
\newprefix[binary]{prefix}{symbol}{powers-ten}
\renewprefix{prefix}{symbol}{powers-ten}
\renewprefix[binary]{prefix}{symbol}{powers-ten}
\provideprefix{prefix}{symbol}{powers-ten}
\provideprefix[binary]{prefix}{symbol}{powers-ten}

# Package options inside document
\sisetup

