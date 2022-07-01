# mandi package
# Matthew Bertucci 12/26/2021 for v3.1.0

#include:luatex
#include:array
#include:iftex
#include:pgfopts
#include:unicode-math

\mandiversion#*

\mandisetup{options%keyvals}

#keyvals:\usepackage/mandi#c,\mandisetup
units=#base,derived,alternate
preciseconstants#true,false
#endkeyvals

\momentum{magnitude}#m
\momentumvector{c1,c2,...}#m
\vectormomentum{c1,c2,...}#m

\momentumvalue{magnitude}#*m
\momentumbaseunits{magnitude}#*m
\momentumderivedunits{magnitude}#*m
\momentumalternateunits{magnitude}#*m
\momentumonlybaseunits#*m
\momentumonlyderivedunits#*m
\momentumonlyalternateunits#*m
\momentumvectorvalue{c1,c2,...}#*m
\vectormomentumvalue{c1,c2,...}#*m
\momentumvectorbaseunits{c1,c2,...}#*m
\vectormomentumbaseunits{c1,c2,...}#*m
\momentumvectorderivedunits{c1,c2,...}#*m
\vectormomentumderivedunits{c1,c2,...}#*m
\momentumvectoralternateunits{c1,c2,...}#*m
\vectormomentumalternateunits{c1,c2,...}#*m
\momentumvectoronlybaseunits#*m
\vectormomentumonlybaseunits#*m
\momentumvectoronlyderivedunits#*m
\vectormomentumonlyderivedunits#*m
\momentumvectoronlyalternateunits#*m
\vectormomentumonlyalternateunits#*m

\checkquantity{name}

\acceleration{magnitude}#m
\accelerationvector{c1,c2,...}#m
\vectoracceleration{c1,c2,...}#m

\accelerationvalue{magnitude}#*m
\accelerationbaseunits{magnitude}#*m
\accelerationderivedunits{magnitude}#*m
\accelerationalternateunits{magnitude}#*m
\accelerationonlybaseunits#*m
\accelerationonlyderivedunits#*m
\accelerationonlyalternateunits#*m
\accelerationvectorvalue{c1,c2,...}#*m
\vectoraccelerationvalue{c1,c2,...}#*m
\accelerationvectorbaseunits{c1,c2,...}#*m
\vectoraccelerationbaseunits{c1,c2,...}#*m
\accelerationvectorderivedunits{c1,c2,...}#*m
\vectoraccelerationderivedunits{c1,c2,...}#*m
\accelerationvectoralternateunits{c1,c2,...}#*m
\vectoraccelerationalternateunits{c1,c2,...}#*m
\accelerationvectoronlybaseunits#*m
\vectoraccelerationonlybaseunits#*m
\accelerationvectoronlyderivedunits#*m
\vectoraccelerationonlyderivedunits#*m
\accelerationvectoronlyalternateunits#*m
\vectoraccelerationonlyalternateunits#*m

\amount{magnitude}#m

\amountvalue{magnitude}#*m
\amountbaseunits{magnitude}#*m
\amountderivedunits{magnitude}#*m
\amountalternateunits{magnitude}#*m
\amountonlybaseunits#*m
\amountonlyderivedunits#*m
\amountonlyalternateunits#*m

\angularacceleration{magnitude}#m
\angularaccelerationvector{c1,c2,...}#m
\vectorangularacceleration{c1,c2,...}#m

\angularaccelerationvalue{magnitude}#*m
\angularaccelerationbaseunits{magnitude}#*m
\angularaccelerationderivedunits{magnitude}#*m
\angularaccelerationalternateunits{magnitude}#*m
\angularaccelerationonlybaseunits#*m
\angularaccelerationonlyderivedunits#*m
\angularaccelerationonlyalternateunits#*m
\angularaccelerationvectorvalue{c1,c2,...}#*m
\vectorangularaccelerationvalue{c1,c2,...}#*m
\angularaccelerationvectorbaseunits{c1,c2,...}#*m
\vectorangularaccelerationbaseunits{c1,c2,...}#*m
\angularaccelerationvectorderivedunits{c1,c2,...}#*m
\vectorangularaccelerationderivedunits{c1,c2,...}#*m
\angularaccelerationvectoralternateunits{c1,c2,...}#*m
\vectorangularaccelerationalternateunits{c1,c2,...}#*m
\angularaccelerationvectoronlybaseunits#*m
\vectorangularaccelerationonlybaseunits#*m
\angularaccelerationvectoronlyderivedunits#*m
\vectorangularaccelerationonlyderivedunits#*m
\angularaccelerationvectoronlyalternateunits#*m
\vectorangularaccelerationonlyalternateunits#*m

\angularfrequency{magnitude}#m

\angularfrequencyvalue{magnitude}#*m
\angularfrequencybaseunits{magnitude}#*m
\angularfrequencyderivedunits{magnitude}#*m
\angularfrequencyalternateunits{magnitude}#*m
\angularfrequencyonlybaseunits#*m
\angularfrequencyonlyderivedunits#*m
\angularfrequencyonlyalternateunits#*m

\angularimpulse{magnitude}#m
\angularimpulsevector{c1,c2,...}#m
\vectorangularimpulse{c1,c2,...}#m

\angularimpulsevalue{magnitude}#*m
\angularimpulsebaseunits{magnitude}#*m
\angularimpulsederivedunits{magnitude}#*m
\angularimpulsealternateunits{magnitude}#*m
\angularimpulseonlybaseunits#*m
\angularimpulseonlyderivedunits#*m
\angularimpulseonlyalternateunits#*m
\angularimpulsevectorvalue{c1,c2,...}#*m
\vectorangularimpulsevalue{c1,c2,...}#*m
\angularimpulsevectorbaseunits{c1,c2,...}#*m
\vectorangularimpulsebaseunits{c1,c2,...}#*m
\angularimpulsevectorderivedunits{c1,c2,...}#*m
\vectorangularimpulsederivedunits{c1,c2,...}#*m
\angularimpulsevectoralternateunits{c1,c2,...}#*m
\vectorangularimpulsealternateunits{c1,c2,...}#*m
\angularimpulsevectoronlybaseunits#*m
\vectorangularimpulseonlybaseunits#*m
\angularimpulsevectoronlyderivedunits#*m
\vectorangularimpulseonlyderivedunits#*m
\angularimpulsevectoronlyalternateunits#*m
\vectorangularimpulseonlyalternateunits#*m

\angularmomentum{magnitude}#m
\angularmomentumvector{c1,c2,...}#m
\vectorangularmomentum{c1,c2,...}#m

\angularmomentumvalue{magnitude}#*m
\angularmomentumbaseunits{magnitude}#*m
\angularmomentumderivedunits{magnitude}#*m
\angularmomentumalternateunits{magnitude}#*m
\angularmomentumonlybaseunits#*m
\angularmomentumonlyderivedunits#*m
\angularmomentumonlyalternateunits#*m
\angularmomentumvectorvalue{c1,c2,...}#*m
\vectorangularmomentumvalue{c1,c2,...}#*m
\angularmomentumvectorbaseunits{c1,c2,...}#*m
\vectorangularmomentumbaseunits{c1,c2,...}#*m
\angularmomentumvectorderivedunits{c1,c2,...}#*m
\vectorangularmomentumderivedunits{c1,c2,...}#*m
\angularmomentumvectoralternateunits{c1,c2,...}#*m
\vectorangularmomentumalternateunits{c1,c2,...}#*m
\angularmomentumvectoronlybaseunits#*m
\vectorangularmomentumonlybaseunits#*m
\angularmomentumvectoronlyderivedunits#*m
\vectorangularmomentumonlyderivedunits#*m
\angularmomentumvectoronlyalternateunits#*m
\vectorangularmomentumonlyalternateunits#*m

\angularvelocity{magnitude}#m
\angularvelocityvector{c1,c2,...}#m
\vectorangularvelocity{c1,c2,...}#m

\angularvelocityvalue{magnitude}#*m
\angularvelocitybaseunits{magnitude}#*m
\angularvelocityderivedunits{magnitude}#*m
\angularvelocityalternateunits{magnitude}#*m
\angularvelocityonlybaseunits#*m
\angularvelocityonlyderivedunits#*m
\angularvelocityonlyalternateunits#*m
\angularvelocityvectorvalue{c1,c2,...}#*m
\vectorangularvelocityvalue{c1,c2,...}#*m
\angularvelocityvectorbaseunits{c1,c2,...}#*m
\vectorangularvelocitybaseunits{c1,c2,...}#*m
\angularvelocityvectorderivedunits{c1,c2,...}#*m
\vectorangularvelocityderivedunits{c1,c2,...}#*m
\angularvelocityvectoralternateunits{c1,c2,...}#*m
\vectorangularvelocityalternateunits{c1,c2,...}#*m
\angularvelocityvectoronlybaseunits#*m
\vectorangularvelocityonlybaseunits#*m
\angularvelocityvectoronlyderivedunits#*m
\vectorangularvelocityonlyderivedunits#*m
\angularvelocityvectoronlyalternateunits#*m
\vectorangularvelocityonlyalternateunits#*m

\cmagneticfield{magnitude}#m
\cmagneticfieldvector{c1,c2,...}#m
\vectorcmagneticfield{c1,c2,...}#m

\cmagneticfieldvalue{magnitude}#*m
\cmagneticfieldbaseunits{magnitude}#*m
\cmagneticfieldderivedunits{magnitude}#*m
\cmagneticfieldalternateunits{magnitude}#*m
\cmagneticfieldonlybaseunits#*m
\cmagneticfieldonlyderivedunits#*m
\cmagneticfieldonlyalternateunits#*m
\cmagneticfieldvectorvalue{c1,c2,...}#*m
\vectorcmagneticfieldvalue{c1,c2,...}#*m
\cmagneticfieldvectorbaseunits{c1,c2,...}#*m
\vectorcmagneticfieldbaseunits{c1,c2,...}#*m
\cmagneticfieldvectorderivedunits{c1,c2,...}#*m
\vectorcmagneticfieldderivedunits{c1,c2,...}#*m
\cmagneticfieldvectoralternateunits{c1,c2,...}#*m
\vectorcmagneticfieldalternateunits{c1,c2,...}#*m
\cmagneticfieldvectoronlybaseunits#*m
\vectorcmagneticfieldonlybaseunits#*m
\cmagneticfieldvectoronlyderivedunits#*m
\vectorcmagneticfieldonlyderivedunits#*m
\cmagneticfieldvectoronlyalternateunits#*m
\vectorcmagneticfieldonlyalternateunits#*m

\currentdensity{magnitude}#m
\currentdensityvector{c1,c2,...}#m
\vectorcurrentdensity{c1,c2,...}#m

\currentdensityvalue{magnitude}#*m
\currentdensitybaseunits{magnitude}#*m
\currentdensityderivedunits{magnitude}#*m
\currentdensityalternateunits{magnitude}#*m
\currentdensityonlybaseunits#*m
\currentdensityonlyderivedunits#*m
\currentdensityonlyalternateunits#*m
\currentdensityvectorvalue{c1,c2,...}#*m
\vectorcurrentdensityvalue{c1,c2,...}#*m
\currentdensityvectorbaseunits{c1,c2,...}#*m
\vectorcurrentdensitybaseunits{c1,c2,...}#*m
\currentdensityvectorderivedunits{c1,c2,...}#*m
\vectorcurrentdensityderivedunits{c1,c2,...}#*m
\currentdensityvectoralternateunits{c1,c2,...}#*m
\vectorcurrentdensityalternateunits{c1,c2,...}#*m
\currentdensityvectoronlybaseunits#*m
\vectorcurrentdensityonlybaseunits#*m
\currentdensityvectoronlyderivedunits#*m
\vectorcurrentdensityonlyderivedunits#*m
\currentdensityvectoronlyalternateunits#*m
\vectorcurrentdensityonlyalternateunits#*m

\direction{magnitude}#m
\directionvector{c1,c2,...}#m
\vectordirection{c1,c2,...}#m

\directionvalue{magnitude}#*m
\directionbaseunits{magnitude}#*m
\directionderivedunits{magnitude}#*m
\directionalternateunits{magnitude}#*m
\directiononlybaseunits#*m
\directiononlyderivedunits#*m
\directiononlyalternateunits#*m
\directionvectorvalue{c1,c2,...}#*m
\vectordirectionvalue{c1,c2,...}#*m
\directionvectorbaseunits{c1,c2,...}#*m
\vectordirectionbaseunits{c1,c2,...}#*m
\directionvectorderivedunits{c1,c2,...}#*m
\vectordirectionderivedunits{c1,c2,...}#*m
\directionvectoralternateunits{c1,c2,...}#*m
\vectordirectionalternateunits{c1,c2,...}#*m
\directionvectoronlybaseunits#*m
\vectordirectiononlybaseunits#*m
\directionvectoronlyderivedunits#*m
\vectordirectiononlyderivedunits#*m
\directionvectoronlyalternateunits#*m
\vectordirectiononlyalternateunits#*m

\displacement{magnitude}#m
\displacementvector{c1,c2,...}#m
\vectordisplacement{c1,c2,...}#m

\displacementvalue{magnitude}#*m
\displacementbaseunits{magnitude}#*m
\displacementderivedunits{magnitude}#*m
\displacementalternateunits{magnitude}#*m
\displacementonlybaseunits#*m
\displacementonlyderivedunits#*m
\displacementonlyalternateunits#*m
\displacementvectorvalue{c1,c2,...}#*m
\vectordisplacementvalue{c1,c2,...}#*m
\displacementvectorbaseunits{c1,c2,...}#*m
\vectordisplacementbaseunits{c1,c2,...}#*m
\displacementvectorderivedunits{c1,c2,...}#*m
\vectordisplacementderivedunits{c1,c2,...}#*m
\displacementvectoralternateunits{c1,c2,...}#*m
\vectordisplacementalternateunits{c1,c2,...}#*m
\displacementvectoronlybaseunits#*m
\vectordisplacementonlybaseunits#*m
\displacementvectoronlyderivedunits#*m
\vectordisplacementonlyderivedunits#*m
\displacementvectoronlyalternateunits#*m
\vectordisplacementonlyalternateunits#*m

\electricdipolemoment{magnitude}#m
\electricdipolemomentvector{c1,c2,...}#m
\vectorelectricdipolemoment{c1,c2,...}#m

\electricdipolemomentvalue{magnitude}#*m
\electricdipolemomentbaseunits{magnitude}#*m
\electricdipolemomentderivedunits{magnitude}#*m
\electricdipolemomentalternateunits{magnitude}#*m
\electricdipolemomentonlybaseunits#*m
\electricdipolemomentonlyderivedunits#*m
\electricdipolemomentonlyalternateunits#*m
\electricdipolemomentvectorvalue{c1,c2,...}#*m
\vectorelectricdipolemomentvalue{c1,c2,...}#*m
\electricdipolemomentvectorbaseunits{c1,c2,...}#*m
\vectorelectricdipolemomentbaseunits{c1,c2,...}#*m
\electricdipolemomentvectorderivedunits{c1,c2,...}#*m
\vectorelectricdipolemomentderivedunits{c1,c2,...}#*m
\electricdipolemomentvectoralternateunits{c1,c2,...}#*m
\vectorelectricdipolemomentalternateunits{c1,c2,...}#*m
\electricdipolemomentvectoronlybaseunits#*m
\vectorelectricdipolemomentonlybaseunits#*m
\electricdipolemomentvectoronlyderivedunits#*m
\vectorelectricdipolemomentonlyderivedunits#*m
\electricdipolemomentvectoronlyalternateunits#*m
\vectorelectricdipolemomentonlyalternateunits#*m

\electricfield{magnitude}#m
\electricfieldvector{c1,c2,...}#m
\vectorelectricfield{c1,c2,...}#m

\electricfieldvalue{magnitude}#*m
\electricfieldbaseunits{magnitude}#*m
\electricfieldderivedunits{magnitude}#*m
\electricfieldalternateunits{magnitude}#*m
\electricfieldonlybaseunits#*m
\electricfieldonlyderivedunits#*m
\electricfieldonlyalternateunits#*m
\electricfieldvectorvalue{c1,c2,...}#*m
\vectorelectricfieldvalue{c1,c2,...}#*m
\electricfieldvectorbaseunits{c1,c2,...}#*m
\vectorelectricfieldbaseunits{c1,c2,...}#*m
\electricfieldvectorderivedunits{c1,c2,...}#*m
\vectorelectricfieldderivedunits{c1,c2,...}#*m
\electricfieldvectoralternateunits{c1,c2,...}#*m
\vectorelectricfieldalternateunits{c1,c2,...}#*m
\electricfieldvectoronlybaseunits#*m
\vectorelectricfieldonlybaseunits#*m
\electricfieldvectoronlyderivedunits#*m
\vectorelectricfieldonlyderivedunits#*m
\electricfieldvectoronlyalternateunits#*m
\vectorelectricfieldonlyalternateunits#*m

\energyflux{magnitude}#m
\energyfluxvector{c1,c2,...}#m
\vectorenergyflux{c1,c2,...}#m

\energyfluxvalue{magnitude}#*m
\energyfluxbaseunits{magnitude}#*m
\energyfluxderivedunits{magnitude}#*m
\energyfluxalternateunits{magnitude}#*m
\energyfluxonlybaseunits#*m
\energyfluxonlyderivedunits#*m
\energyfluxonlyalternateunits#*m
\energyfluxvectorvalue{c1,c2,...}#*m
\vectorenergyfluxvalue{c1,c2,...}#*m
\energyfluxvectorbaseunits{c1,c2,...}#*m
\vectorenergyfluxbaseunits{c1,c2,...}#*m
\energyfluxvectorderivedunits{c1,c2,...}#*m
\vectorenergyfluxderivedunits{c1,c2,...}#*m
\energyfluxvectoralternateunits{c1,c2,...}#*m
\vectorenergyfluxalternateunits{c1,c2,...}#*m
\energyfluxvectoronlybaseunits#*m
\vectorenergyfluxonlybaseunits#*m
\energyfluxvectoronlyderivedunits#*m
\vectorenergyfluxonlyderivedunits#*m
\energyfluxvectoronlyalternateunits#*m
\vectorenergyfluxonlyalternateunits#*m

\force{magnitude}#m
\forcevector{c1,c2,...}#m
\vectorforce{c1,c2,...}#m

\forcevalue{magnitude}#*m
\forcebaseunits{magnitude}#*m
\forcederivedunits{magnitude}#*m
\forcealternateunits{magnitude}#*m
\forceonlybaseunits#*m
\forceonlyderivedunits#*m
\forceonlyalternateunits#*m
\forcevectorvalue{c1,c2,...}#*m
\vectorforcevalue{c1,c2,...}#*m
\forcevectorbaseunits{c1,c2,...}#*m
\vectorforcebaseunits{c1,c2,...}#*m
\forcevectorderivedunits{c1,c2,...}#*m
\vectorforcederivedunits{c1,c2,...}#*m
\forcevectoralternateunits{c1,c2,...}#*m
\vectorforcealternateunits{c1,c2,...}#*m
\forcevectoronlybaseunits#*m
\vectorforceonlybaseunits#*m
\forcevectoronlyderivedunits#*m
\vectorforceonlyderivedunits#*m
\forcevectoronlyalternateunits#*m
\vectorforceonlyalternateunits#*m

\gravitationalfield{magnitude}#m
\gravitationalfieldvector{c1,c2,...}#m
\vectorgravitationalfield{c1,c2,...}#m

\gravitationalfieldvalue{magnitude}#*m
\gravitationalfieldbaseunits{magnitude}#*m
\gravitationalfieldderivedunits{magnitude}#*m
\gravitationalfieldalternateunits{magnitude}#*m
\gravitationalfieldonlybaseunits#*m
\gravitationalfieldonlyderivedunits#*m
\gravitationalfieldonlyalternateunits#*m
\gravitationalfieldvectorvalue{c1,c2,...}#*m
\vectorgravitationalfieldvalue{c1,c2,...}#*m
\gravitationalfieldvectorbaseunits{c1,c2,...}#*m
\vectorgravitationalfieldbaseunits{c1,c2,...}#*m
\gravitationalfieldvectorderivedunits{c1,c2,...}#*m
\vectorgravitationalfieldderivedunits{c1,c2,...}#*m
\gravitationalfieldvectoralternateunits{c1,c2,...}#*m
\vectorgravitationalfieldalternateunits{c1,c2,...}#*m
\gravitationalfieldvectoronlybaseunits#*m
\vectorgravitationalfieldonlybaseunits#*m
\gravitationalfieldvectoronlyderivedunits#*m
\vectorgravitationalfieldonlyderivedunits#*m
\gravitationalfieldvectoronlyalternateunits#*m
\vectorgravitationalfieldonlyalternateunits#*m

\impulse{magnitude}#m
\impulsevector{c1,c2,...}#m
\vectorimpulse{c1,c2,...}#m

\impulsevalue{magnitude}#*m
\impulsebaseunits{magnitude}#*m
\impulsederivedunits{magnitude}#*m
\impulsealternateunits{magnitude}#*m
\impulseonlybaseunits#*m
\impulseonlyderivedunits#*m
\impulseonlyalternateunits#*m
\impulsevectorvalue{c1,c2,...}#*m
\vectorimpulsevalue{c1,c2,...}#*m
\impulsevectorbaseunits{c1,c2,...}#*m
\vectorimpulsebaseunits{c1,c2,...}#*m
\impulsevectorderivedunits{c1,c2,...}#*m
\vectorimpulsederivedunits{c1,c2,...}#*m
\impulsevectoralternateunits{c1,c2,...}#*m
\vectorimpulsealternateunits{c1,c2,...}#*m
\impulsevectoronlybaseunits#*m
\vectorimpulseonlybaseunits#*m
\impulsevectoronlyderivedunits#*m
\vectorimpulseonlyderivedunits#*m
\impulsevectoronlyalternateunits#*m
\vectorimpulseonlyalternateunits#*m

\magneticdipolemoment{magnitude}#m
\magneticdipolemomentvector{c1,c2,...}#m
\vectormagneticdipolemoment{c1,c2,...}#m

\magneticdipolemomentvalue{magnitude}#*m
\magneticdipolemomentbaseunits{magnitude}#*m
\magneticdipolemomentderivedunits{magnitude}#*m
\magneticdipolemomentalternateunits{magnitude}#*m
\magneticdipolemomentonlybaseunits#*m
\magneticdipolemomentonlyderivedunits#*m
\magneticdipolemomentonlyalternateunits#*m
\magneticdipolemomentvectorvalue{c1,c2,...}#*m
\vectormagneticdipolemomentvalue{c1,c2,...}#*m
\magneticdipolemomentvectorbaseunits{c1,c2,...}#*m
\vectormagneticdipolemomentbaseunits{c1,c2,...}#*m
\magneticdipolemomentvectorderivedunits{c1,c2,...}#*m
\vectormagneticdipolemomentderivedunits{c1,c2,...}#*m
\magneticdipolemomentvectoralternateunits{c1,c2,...}#*m
\vectormagneticdipolemomentalternateunits{c1,c2,...}#*m
\magneticdipolemomentvectoronlybaseunits#*m
\vectormagneticdipolemomentonlybaseunits#*m
\magneticdipolemomentvectoronlyderivedunits#*m
\vectormagneticdipolemomentonlyderivedunits#*m
\magneticdipolemomentvectoronlyalternateunits#*m
\vectormagneticdipolemomentonlyalternateunits#*m

\magneticfield{magnitude}#m
\magneticfieldvector{c1,c2,...}#m
\vectormagneticfield{c1,c2,...}#m

\magneticfieldvalue{magnitude}#*m
\magneticfieldbaseunits{magnitude}#*m
\magneticfieldderivedunits{magnitude}#*m
\magneticfieldalternateunits{magnitude}#*m
\magneticfieldonlybaseunits#*m
\magneticfieldonlyderivedunits#*m
\magneticfieldonlyalternateunits#*m
\magneticfieldvectorvalue{c1,c2,...}#*m
\vectormagneticfieldvalue{c1,c2,...}#*m
\magneticfieldvectorbaseunits{c1,c2,...}#*m
\vectormagneticfieldbaseunits{c1,c2,...}#*m
\magneticfieldvectorderivedunits{c1,c2,...}#*m
\vectormagneticfieldderivedunits{c1,c2,...}#*m
\magneticfieldvectoralternateunits{c1,c2,...}#*m
\vectormagneticfieldalternateunits{c1,c2,...}#*m
\magneticfieldvectoronlybaseunits#*m
\vectormagneticfieldonlybaseunits#*m
\magneticfieldvectoronlyderivedunits#*m
\vectormagneticfieldonlyderivedunits#*m
\magneticfieldvectoronlyalternateunits#*m
\vectormagneticfieldonlyalternateunits#*m

\momentumflux{magnitude}#m
\momentumfluxvector{c1,c2,...}#m
\vectormomentumflux{c1,c2,...}#m

\momentumfluxvalue{magnitude}#*m
\momentumfluxbaseunits{magnitude}#*m
\momentumfluxderivedunits{magnitude}#*m
\momentumfluxalternateunits{magnitude}#*m
\momentumfluxonlybaseunits#*m
\momentumfluxonlyderivedunits#*m
\momentumfluxonlyalternateunits#*m
\momentumfluxvectorvalue{c1,c2,...}#*m
\vectormomentumfluxvalue{c1,c2,...}#*m
\momentumfluxvectorbaseunits{c1,c2,...}#*m
\vectormomentumfluxbaseunits{c1,c2,...}#*m
\momentumfluxvectorderivedunits{c1,c2,...}#*m
\vectormomentumfluxderivedunits{c1,c2,...}#*m
\momentumfluxvectoralternateunits{c1,c2,...}#*m
\vectormomentumfluxalternateunits{c1,c2,...}#*m
\momentumfluxvectoronlybaseunits#*m
\vectormomentumfluxonlybaseunits#*m
\momentumfluxvectoronlyderivedunits#*m
\vectormomentumfluxonlyderivedunits#*m
\momentumfluxvectoronlyalternateunits#*m
\vectormomentumfluxonlyalternateunits#*m

\poynting{magnitude}#m
\poyntingvector{c1,c2,...}#m
\vectorpoynting{c1,c2,...}#m

\poyntingvalue{magnitude}#*m
\poyntingbaseunits{magnitude}#*m
\poyntingderivedunits{magnitude}#*m
\poyntingalternateunits{magnitude}#*m
\poyntingonlybaseunits#*m
\poyntingonlyderivedunits#*m
\poyntingonlyalternateunits#*m
\poyntingvectorvalue{c1,c2,...}#*m
\vectorpoyntingvalue{c1,c2,...}#*m
\poyntingvectorbaseunits{c1,c2,...}#*m
\vectorpoyntingbaseunits{c1,c2,...}#*m
\poyntingvectorderivedunits{c1,c2,...}#*m
\vectorpoyntingderivedunits{c1,c2,...}#*m
\poyntingvectoralternateunits{c1,c2,...}#*m
\vectorpoyntingalternateunits{c1,c2,...}#*m
\poyntingvectoronlybaseunits#*m
\vectorpoyntingonlybaseunits#*m
\poyntingvectoronlyderivedunits#*m
\vectorpoyntingonlyderivedunits#*m
\poyntingvectoronlyalternateunits#*m
\vectorpoyntingonlyalternateunits#*m

\torque{magnitude}#m
\torquevector{c1,c2,...}#m
\vectortorque{c1,c2,...}#m

\torquevalue{magnitude}#*m
\torquebaseunits{magnitude}#*m
\torquederivedunits{magnitude}#*m
\torquealternateunits{magnitude}#*m
\torqueonlybaseunits#*m
\torqueonlyderivedunits#*m
\torqueonlyalternateunits#*m
\torquevectorvalue{c1,c2,...}#*m
\vectortorquevalue{c1,c2,...}#*m
\torquevectorbaseunits{c1,c2,...}#*m
\vectortorquebaseunits{c1,c2,...}#*m
\torquevectorderivedunits{c1,c2,...}#*m
\vectortorquederivedunits{c1,c2,...}#*m
\torquevectoralternateunits{c1,c2,...}#*m
\vectortorquealternateunits{c1,c2,...}#*m
\torquevectoronlybaseunits#*m
\vectortorqueonlybaseunits#*m
\torquevectoronlyderivedunits#*m
\vectortorqueonlyderivedunits#*m
\torquevectoronlyalternateunits#*m
\vectortorqueonlyalternateunits#*m

\velocity{magnitude}#m
\velocityvector{c1,c2,...}#m
\vectorvelocity{c1,c2,...}#m

\velocityvalue{magnitude}#*m
\velocitybaseunits{magnitude}#*m
\velocityderivedunits{magnitude}#*m
\velocityalternateunits{magnitude}#*m
\velocityonlybaseunits#*m
\velocityonlyderivedunits#*m
\velocityonlyalternateunits#*m
\velocityvectorvalue{c1,c2,...}#*m
\vectorvelocityvalue{c1,c2,...}#*m
\velocityvectorbaseunits{c1,c2,...}#*m
\vectorvelocitybaseunits{c1,c2,...}#*m
\velocityvectorderivedunits{c1,c2,...}#*m
\vectorvelocityderivedunits{c1,c2,...}#*m
\velocityvectoralternateunits{c1,c2,...}#*m
\vectorvelocityalternateunits{c1,c2,...}#*m
\velocityvectoronlybaseunits#*m
\vectorvelocityonlybaseunits#*m
\velocityvectoronlyderivedunits#*m
\vectorvelocityonlyderivedunits#*m
\velocityvectoronlyalternateunits#*m
\vectorvelocityonlyalternateunits#*m

\velocityc{magnitude}#m
\velocitycvector{c1,c2,...}#m
\vectorvelocityc{c1,c2,...}#m

\velocitycvalue{magnitude}#*m
\velocitycbaseunits{magnitude}#*m
\velocitycderivedunits{magnitude}#*m
\velocitycalternateunits{magnitude}#*m
\velocityconlybaseunits#*m
\velocityconlyderivedunits#*m
\velocityconlyalternateunits#*m
\velocitycvectorvalue{c1,c2,...}#*m
\vectorvelocitycvalue{c1,c2,...}#*m
\velocitycvectorbaseunits{c1,c2,...}#*m
\vectorvelocitycbaseunits{c1,c2,...}#*m
\velocitycvectorderivedunits{c1,c2,...}#*m
\vectorvelocitycderivedunits{c1,c2,...}#*m
\velocitycvectoralternateunits{c1,c2,...}#*m
\vectorvelocitycalternateunits{c1,c2,...}#*m
\velocitycvectoronlybaseunits#*m
\vectorvelocityconlybaseunits#*m
\velocitycvectoronlyderivedunits#*m
\vectorvelocityconlyderivedunits#*m
\velocitycvectoronlyalternateunits#*m
\vectorvelocityconlyalternateunits#*m

\wavenumber{magnitude}#m
\wavenumbervector{c1,c2,...}#m
\vectorwavenumber{c1,c2,...}#m

\wavenumbervalue{magnitude}#*m
\wavenumberbaseunits{magnitude}#*m
\wavenumberderivedunits{magnitude}#*m
\wavenumberalternateunits{magnitude}#*m
\wavenumberonlybaseunits#*m
\wavenumberonlyderivedunits#*m
\wavenumberonlyalternateunits#*m
\wavenumbervectorvalue{c1,c2,...}#*m
\vectorwavenumbervalue{c1,c2,...}#*m
\wavenumbervectorbaseunits{c1,c2,...}#*m
\vectorwavenumberbaseunits{c1,c2,...}#*m
\wavenumbervectorderivedunits{c1,c2,...}#*m
\vectorwavenumberderivedunits{c1,c2,...}#*m
\wavenumbervectoralternateunits{c1,c2,...}#*m
\vectorwavenumberalternateunits{c1,c2,...}#*m
\wavenumbervectoronlybaseunits#*m
\vectorwavenumberonlybaseunits#*m
\wavenumbervectoronlyderivedunits#*m
\vectorwavenumberonlyderivedunits#*m
\wavenumbervectoronlyalternateunits#*m
\vectorwavenumberonlyalternateunits#*m

\area{magnitude}#m

\areavalue{magnitude}#*m
\areabaseunits{magnitude}#*m
\areaderivedunits{magnitude}#*m
\areaalternateunits{magnitude}#*m
\areaonlybaseunits#*m
\areaonlyderivedunits#*m
\areaonlyalternateunits#*m

\areachargedensity{magnitude}#m

\areachargedensityvalue{magnitude}#*m
\areachargedensitybaseunits{magnitude}#*m
\areachargedensityderivedunits{magnitude}#*m
\areachargedensityalternateunits{magnitude}#*m
\areachargedensityonlybaseunits#*m
\areachargedensityonlyderivedunits#*m
\areachargedensityonlyalternateunits#*m

\areamassdensity{magnitude}#m

\areamassdensityvalue{magnitude}#*m
\areamassdensitybaseunits{magnitude}#*m
\areamassdensityderivedunits{magnitude}#*m
\areamassdensityalternateunits{magnitude}#*m
\areamassdensityonlybaseunits#*m
\areamassdensityonlyderivedunits#*m
\areamassdensityonlyalternateunits#*m

\capacitance{magnitude}#m

\capacitancevalue{magnitude}#*m
\capacitancebaseunits{magnitude}#*m
\capacitancederivedunits{magnitude}#*m
\capacitancealternateunits{magnitude}#*m
\capacitanceonlybaseunits#*m
\capacitanceonlyderivedunits#*m
\capacitanceonlyalternateunits#*m

\charge{magnitude}#m

\chargevalue{magnitude}#*m
\chargebaseunits{magnitude}#*m
\chargederivedunits{magnitude}#*m
\chargealternateunits{magnitude}#*m
\chargeonlybaseunits#*m
\chargeonlyderivedunits#*m
\chargeonlyalternateunits#*m

\conductance{magnitude}#m

\conductancevalue{magnitude}#*m
\conductancebaseunits{magnitude}#*m
\conductancederivedunits{magnitude}#*m
\conductancealternateunits{magnitude}#*m
\conductanceonlybaseunits#*m
\conductanceonlyderivedunits#*m
\conductanceonlyalternateunits#*m

\conductivity{magnitude}#m

\conductivityvalue{magnitude}#*m
\conductivitybaseunits{magnitude}#*m
\conductivityderivedunits{magnitude}#*m
\conductivityalternateunits{magnitude}#*m
\conductivityonlybaseunits#*m
\conductivityonlyderivedunits#*m
\conductivityonlyalternateunits#*m

\conventionalcurrent{magnitude}#m

\conventionalcurrentvalue{magnitude}#*m
\conventionalcurrentbaseunits{magnitude}#*m
\conventionalcurrentderivedunits{magnitude}#*m
\conventionalcurrentalternateunits{magnitude}#*m
\conventionalcurrentonlybaseunits#*m
\conventionalcurrentonlyderivedunits#*m
\conventionalcurrentonlyalternateunits#*m

\current{magnitude}#m

\currentvalue{magnitude}#*m
\currentbaseunits{magnitude}#*m
\currentderivedunits{magnitude}#*m
\currentalternateunits{magnitude}#*m
\currentonlybaseunits#*m
\currentonlyderivedunits#*m
\currentonlyalternateunits#*m

\dielectricconstant{magnitude}#m

\dielectricconstantvalue{magnitude}#*m
\dielectricconstantbaseunits{magnitude}#*m
\dielectricconstantderivedunits{magnitude}#*m
\dielectricconstantalternateunits{magnitude}#*m
\dielectricconstantonlybaseunits#*m
\dielectricconstantonlyderivedunits#*m
\dielectricconstantonlyalternateunits#*m

\duration{magnitude}#m

\durationvalue{magnitude}#*m
\durationbaseunits{magnitude}#*m
\durationderivedunits{magnitude}#*m
\durationalternateunits{magnitude}#*m
\durationonlybaseunits#*m
\durationonlyderivedunits#*m
\durationonlyalternateunits#*m

\electricflux{magnitude}#m

\electricfluxvalue{magnitude}#*m
\electricfluxbaseunits{magnitude}#*m
\electricfluxderivedunits{magnitude}#*m
\electricfluxalternateunits{magnitude}#*m
\electricfluxonlybaseunits#*m
\electricfluxonlyderivedunits#*m
\electricfluxonlyalternateunits#*m

\electricpotential{magnitude}#m

\electricpotentialvalue{magnitude}#*m
\electricpotentialbaseunits{magnitude}#*m
\electricpotentialderivedunits{magnitude}#*m
\electricpotentialalternateunits{magnitude}#*m
\electricpotentialonlybaseunits#*m
\electricpotentialonlyderivedunits#*m
\electricpotentialonlyalternateunits#*m

\electricpotentialdifference{magnitude}#m

\electricpotentialdifferencevalue{magnitude}#*m
\electricpotentialdifferencebaseunits{magnitude}#*m
\electricpotentialdifferencederivedunits{magnitude}#*m
\electricpotentialdifferencealternateunits{magnitude}#*m
\electricpotentialdifferenceonlybaseunits#*m
\electricpotentialdifferenceonlyderivedunits#*m
\electricpotentialdifferenceonlyalternateunits#*m

\electroncurrent{magnitude}#m

\electroncurrentvalue{magnitude}#*m
\electroncurrentbaseunits{magnitude}#*m
\electroncurrentderivedunits{magnitude}#*m
\electroncurrentalternateunits{magnitude}#*m
\electroncurrentonlybaseunits#*m
\electroncurrentonlyderivedunits#*m
\electroncurrentonlyalternateunits#*m

\emf{magnitude}#m

\emfvalue{magnitude}#*m
\emfbaseunits{magnitude}#*m
\emfderivedunits{magnitude}#*m
\emfalternateunits{magnitude}#*m
\emfonlybaseunits#*m
\emfonlyderivedunits#*m
\emfonlyalternateunits#*m

\energy{magnitude}#m

\energyvalue{magnitude}#*m
\energybaseunits{magnitude}#*m
\energyderivedunits{magnitude}#*m
\energyalternateunits{magnitude}#*m
\energyonlybaseunits#*m
\energyonlyderivedunits#*m
\energyonlyalternateunits#*m

\energyinev{magnitude}#m

\energyinevvalue{magnitude}#*m
\energyinevbaseunits{magnitude}#*m
\energyinevderivedunits{magnitude}#*m
\energyinevalternateunits{magnitude}#*m
\energyinevonlybaseunits#*m
\energyinevonlyderivedunits#*m
\energyinevonlyalternateunits#*m

\energyinkev{magnitude}#m

\energyinkevvalue{magnitude}#*m
\energyinkevbaseunits{magnitude}#*m
\energyinkevderivedunits{magnitude}#*m
\energyinkevalternateunits{magnitude}#*m
\energyinkevonlybaseunits#*m
\energyinkevonlyderivedunits#*m
\energyinkevonlyalternateunits#*m

\energyinmev{magnitude}#m

\energyinmevvalue{magnitude}#*m
\energyinmevbaseunits{magnitude}#*m
\energyinmevderivedunits{magnitude}#*m
\energyinmevalternateunits{magnitude}#*m
\energyinmevonlybaseunits#*m
\energyinmevonlyderivedunits#*m
\energyinmevonlyalternateunits#*m

\energydensity{magnitude}#m

\energydensityvalue{magnitude}#*m
\energydensitybaseunits{magnitude}#*m
\energydensityderivedunits{magnitude}#*m
\energydensityalternateunits{magnitude}#*m
\energydensityonlybaseunits#*m
\energydensityonlyderivedunits#*m
\energydensityonlyalternateunits#*m

\entropy{magnitude}#m

\entropyvalue{magnitude}#*m
\entropybaseunits{magnitude}#*m
\entropyderivedunits{magnitude}#*m
\entropyalternateunits{magnitude}#*m
\entropyonlybaseunits#*m
\entropyonlyderivedunits#*m
\entropyonlyalternateunits#*m

\frequency{magnitude}#m

\frequencyvalue{magnitude}#*m
\frequencybaseunits{magnitude}#*m
\frequencyderivedunits{magnitude}#*m
\frequencyalternateunits{magnitude}#*m
\frequencyonlybaseunits#*m
\frequencyonlyderivedunits#*m
\frequencyonlyalternateunits#*m

\gravitationalpotential{magnitude}#m

\gravitationalpotentialvalue{magnitude}#*m
\gravitationalpotentialbaseunits{magnitude}#*m
\gravitationalpotentialderivedunits{magnitude}#*m
\gravitationalpotentialalternateunits{magnitude}#*m
\gravitationalpotentialonlybaseunits#*m
\gravitationalpotentialonlyderivedunits#*m
\gravitationalpotentialonlyalternateunits#*m

\gravitationalpotentialdifference{magnitude}#m

\gravitationalpotentialdifferencevalue{magnitude}#*m
\gravitationalpotentialdifferencebaseunits{magnitude}#*m
\gravitationalpotentialdifferencederivedunits{magnitude}#*m
\gravitationalpotentialdifferencealternateunits{magnitude}#*m
\gravitationalpotentialdifferenceonlybaseunits#*m
\gravitationalpotentialdifferenceonlyderivedunits#*m
\gravitationalpotentialdifferenceonlyalternateunits#*m

\indexofrefraction{magnitude}#m

\indexofrefractionvalue{magnitude}#*m
\indexofrefractionbaseunits{magnitude}#*m
\indexofrefractionderivedunits{magnitude}#*m
\indexofrefractionalternateunits{magnitude}#*m
\indexofrefractiononlybaseunits#*m
\indexofrefractiononlyderivedunits#*m
\indexofrefractiononlyalternateunits#*m

\inductance{magnitude}#m

\inductancevalue{magnitude}#*m
\inductancebaseunits{magnitude}#*m
\inductancederivedunits{magnitude}#*m
\inductancealternateunits{magnitude}#*m
\inductanceonlybaseunits#*m
\inductanceonlyderivedunits#*m
\inductanceonlyalternateunits#*m

\linearchargedensity{magnitude}#m

\linearchargedensityvalue{magnitude}#*m
\linearchargedensitybaseunits{magnitude}#*m
\linearchargedensityderivedunits{magnitude}#*m
\linearchargedensityalternateunits{magnitude}#*m
\linearchargedensityonlybaseunits#*m
\linearchargedensityonlyderivedunits#*m
\linearchargedensityonlyalternateunits#*m

\linearmassdensity{magnitude}#m

\linearmassdensityvalue{magnitude}#*m
\linearmassdensitybaseunits{magnitude}#*m
\linearmassdensityderivedunits{magnitude}#*m
\linearmassdensityalternateunits{magnitude}#*m
\linearmassdensityonlybaseunits#*m
\linearmassdensityonlyderivedunits#*m
\linearmassdensityonlyalternateunits#*m

\lorentzfactor{magnitude}#m

\lorentzfactorvalue{magnitude}#*m
\lorentzfactorbaseunits{magnitude}#*m
\lorentzfactorderivedunits{magnitude}#*m
\lorentzfactoralternateunits{magnitude}#*m
\lorentzfactoronlybaseunits#*m
\lorentzfactoronlyderivedunits#*m
\lorentzfactoronlyalternateunits#*m

\luminousintensity{magnitude}#m

\luminousintensityvalue{magnitude}#*m
\luminousintensitybaseunits{magnitude}#*m
\luminousintensityderivedunits{magnitude}#*m
\luminousintensityalternateunits{magnitude}#*m
\luminousintensityonlybaseunits#*m
\luminousintensityonlyderivedunits#*m
\luminousintensityonlyalternateunits#*m

\magneticcharge{magnitude}#m

\magneticchargevalue{magnitude}#*m
\magneticchargebaseunits{magnitude}#*m
\magneticchargederivedunits{magnitude}#*m
\magneticchargealternateunits{magnitude}#*m
\magneticchargeonlybaseunits#*m
\magneticchargeonlyderivedunits#*m
\magneticchargeonlyalternateunits#*m

\magneticflux{magnitude}#m

\magneticfluxvalue{magnitude}#*m
\magneticfluxbaseunits{magnitude}#*m
\magneticfluxderivedunits{magnitude}#*m
\magneticfluxalternateunits{magnitude}#*m
\magneticfluxonlybaseunits#*m
\magneticfluxonlyderivedunits#*m
\magneticfluxonlyalternateunits#*m

\mass{magnitude}#m

\massvalue{magnitude}#*m
\massbaseunits{magnitude}#*m
\massderivedunits{magnitude}#*m
\massalternateunits{magnitude}#*m
\massonlybaseunits#*m
\massonlyderivedunits#*m
\massonlyalternateunits#*m

\mobility{magnitude}#m

\mobilityvalue{magnitude}#*m
\mobilitybaseunits{magnitude}#*m
\mobilityderivedunits{magnitude}#*m
\mobilityalternateunits{magnitude}#*m
\mobilityonlybaseunits#*m
\mobilityonlyderivedunits#*m
\mobilityonlyalternateunits#*m

\momentofinertia{magnitude}#m

\momentofinertiavalue{magnitude}#*m
\momentofinertiabaseunits{magnitude}#*m
\momentofinertiaderivedunits{magnitude}#*m
\momentofinertiaalternateunits{magnitude}#*m
\momentofinertiaonlybaseunits#*m
\momentofinertiaonlyderivedunits#*m
\momentofinertiaonlyalternateunits#*m

\numberdensity{magnitude}#m

\numberdensityvalue{magnitude}#*m
\numberdensitybaseunits{magnitude}#*m
\numberdensityderivedunits{magnitude}#*m
\numberdensityalternateunits{magnitude}#*m
\numberdensityonlybaseunits#*m
\numberdensityonlyderivedunits#*m
\numberdensityonlyalternateunits#*m

\permeability{magnitude}#m

\permeabilityvalue{magnitude}#*m
\permeabilitybaseunits{magnitude}#*m
\permeabilityderivedunits{magnitude}#*m
\permeabilityalternateunits{magnitude}#*m
\permeabilityonlybaseunits#*m
\permeabilityonlyderivedunits#*m
\permeabilityonlyalternateunits#*m

\permittivity{magnitude}#m

\permittivityvalue{magnitude}#*m
\permittivitybaseunits{magnitude}#*m
\permittivityderivedunits{magnitude}#*m
\permittivityalternateunits{magnitude}#*m
\permittivityonlybaseunits#*m
\permittivityonlyderivedunits#*m
\permittivityonlyalternateunits#*m

\planeangle{magnitude}#m

\planeanglevalue{magnitude}#*m
\planeanglebaseunits{magnitude}#*m
\planeanglederivedunits{magnitude}#*m
\planeanglealternateunits{magnitude}#*m
\planeangleonlybaseunits#*m
\planeangleonlyderivedunits#*m
\planeangleonlyalternateunits#*m

\polarizability{magnitude}#m

\polarizabilityvalue{magnitude}#*m
\polarizabilitybaseunits{magnitude}#*m
\polarizabilityderivedunits{magnitude}#*m
\polarizabilityalternateunits{magnitude}#*m
\polarizabilityonlybaseunits#*m
\polarizabilityonlyderivedunits#*m
\polarizabilityonlyalternateunits#*m

\power{magnitude}#m

\powervalue{magnitude}#*m
\powerbaseunits{magnitude}#*m
\powerderivedunits{magnitude}#*m
\poweralternateunits{magnitude}#*m
\poweronlybaseunits#*m
\poweronlyderivedunits#*m
\poweronlyalternateunits#*m

\pressure{magnitude}#m

\pressurevalue{magnitude}#*m
\pressurebaseunits{magnitude}#*m
\pressurederivedunits{magnitude}#*m
\pressurealternateunits{magnitude}#*m
\pressureonlybaseunits#*m
\pressureonlyderivedunits#*m
\pressureonlyalternateunits#*m

\relativepermeability{magnitude}#m

\relativepermeabilityvalue{magnitude}#*m
\relativepermeabilitybaseunits{magnitude}#*m
\relativepermeabilityderivedunits{magnitude}#*m
\relativepermeabilityalternateunits{magnitude}#*m
\relativepermeabilityonlybaseunits#*m
\relativepermeabilityonlyderivedunits#*m
\relativepermeabilityonlyalternateunits#*m

\relativepermittivity{magnitude}#m

\relativepermittivityvalue{magnitude}#*m
\relativepermittivitybaseunits{magnitude}#*m
\relativepermittivityderivedunits{magnitude}#*m
\relativepermittivityalternateunits{magnitude}#*m
\relativepermittivityonlybaseunits#*m
\relativepermittivityonlyderivedunits#*m
\relativepermittivityonlyalternateunits#*m

\resistance{magnitude}#m

\resistancevalue{magnitude}#*m
\resistancebaseunits{magnitude}#*m
\resistancederivedunits{magnitude}#*m
\resistancealternateunits{magnitude}#*m
\resistanceonlybaseunits#*m
\resistanceonlyderivedunits#*m
\resistanceonlyalternateunits#*m

\resistivity{magnitude}#m

\resistivityvalue{magnitude}#*m
\resistivitybaseunits{magnitude}#*m
\resistivityderivedunits{magnitude}#*m
\resistivityalternateunits{magnitude}#*m
\resistivityonlybaseunits#*m
\resistivityonlyderivedunits#*m
\resistivityonlyalternateunits#*m

\solidangle{magnitude}#m

\solidanglevalue{magnitude}#*m
\solidanglebaseunits{magnitude}#*m
\solidanglederivedunits{magnitude}#*m
\solidanglealternateunits{magnitude}#*m
\solidangleonlybaseunits#*m
\solidangleonlyderivedunits#*m
\solidangleonlyalternateunits#*m

\specificheatcapacity{magnitude}#m

\specificheatcapacityvalue{magnitude}#*m
\specificheatcapacitybaseunits{magnitude}#*m
\specificheatcapacityderivedunits{magnitude}#*m
\specificheatcapacityalternateunits{magnitude}#*m
\specificheatcapacityonlybaseunits#*m
\specificheatcapacityonlyderivedunits#*m
\specificheatcapacityonlyalternateunits#*m

\springstiffness{magnitude}#m

\springstiffnessvalue{magnitude}#*m
\springstiffnessbaseunits{magnitude}#*m
\springstiffnessderivedunits{magnitude}#*m
\springstiffnessalternateunits{magnitude}#*m
\springstiffnessonlybaseunits#*m
\springstiffnessonlyderivedunits#*m
\springstiffnessonlyalternateunits#*m

\springstretch{magnitude}#m

\springstretchvalue{magnitude}#*m
\springstretchbaseunits{magnitude}#*m
\springstretchderivedunits{magnitude}#*m
\springstretchalternateunits{magnitude}#*m
\springstretchonlybaseunits#*m
\springstretchonlyderivedunits#*m
\springstretchonlyalternateunits#*m

\stress{magnitude}#m

\stressvalue{magnitude}#*m
\stressbaseunits{magnitude}#*m
\stressderivedunits{magnitude}#*m
\stressalternateunits{magnitude}#*m
\stressonlybaseunits#*m
\stressonlyderivedunits#*m
\stressonlyalternateunits#*m

\strain{magnitude}#m

\strainvalue{magnitude}#*m
\strainbaseunits{magnitude}#*m
\strainderivedunits{magnitude}#*m
\strainalternateunits{magnitude}#*m
\strainonlybaseunits#*m
\strainonlyderivedunits#*m
\strainonlyalternateunits#*m

\temperature{magnitude}#m

\temperaturevalue{magnitude}#*m
\temperaturebaseunits{magnitude}#*m
\temperaturederivedunits{magnitude}#*m
\temperaturealternateunits{magnitude}#*m
\temperatureonlybaseunits#*m
\temperatureonlyderivedunits#*m
\temperatureonlyalternateunits#*m

\volume{magnitude}#m

\volumevalue{magnitude}#*m
\volumebaseunits{magnitude}#*m
\volumederivedunits{magnitude}#*m
\volumealternateunits{magnitude}#*m
\volumeonlybaseunits#*m
\volumeonlyderivedunits#*m
\volumeonlyalternateunits#*m

\volumechargedensity{magnitude}#m

\volumechargedensityvalue{magnitude}#*m
\volumechargedensitybaseunits{magnitude}#*m
\volumechargedensityderivedunits{magnitude}#*m
\volumechargedensityalternateunits{magnitude}#*m
\volumechargedensityonlybaseunits#*m
\volumechargedensityonlyderivedunits#*m
\volumechargedensityonlyalternateunits#*m

\volumemassdensity{magnitude}#m

\volumemassdensityvalue{magnitude}#*m
\volumemassdensitybaseunits{magnitude}#*m
\volumemassdensityderivedunits{magnitude}#*m
\volumemassdensityalternateunits{magnitude}#*m
\volumemassdensityonlybaseunits#*m
\volumemassdensityonlyderivedunits#*m
\volumemassdensityonlyalternateunits#*m

\wavelength{magnitude}#m

\wavelengthvalue{magnitude}#*m
\wavelengthbaseunits{magnitude}#*m
\wavelengthderivedunits{magnitude}#*m
\wavelengthalternateunits{magnitude}#*m
\wavelengthonlybaseunits#*m
\wavelengthonlyderivedunits#*m
\wavelengthonlyalternateunits#*m

\work{magnitude}#m

\workvalue{magnitude}#*m
\workbaseunits{magnitude}#*m
\workderivedunits{magnitude}#*m
\workalternateunits{magnitude}#*m
\workonlybaseunits#*m
\workonlyderivedunits#*m
\workonlyalternateunits#*m

\youngsmodulus{magnitude}#m

\youngsmodulusvalue{magnitude}#*m
\youngsmodulusbaseunits{magnitude}#*m
\youngsmodulusderivedunits{magnitude}#*m
\youngsmodulusalternateunits{magnitude}#*m
\youngsmodulusonlybaseunits#*m
\youngsmodulusonlyderivedunits#*m
\youngsmodulusonlyalternateunits#*m

\newscalarquantity{name}{base units}
\newscalarquantity{name}{base units}[derived units]
\newscalarquantity{name}{base units}[derived units][alt units]
\renewscalarquantity{name}{base units}
\renewscalarquantity{name}{base units}[derived units]
\renewscalarquantity{name}{base units}[derived units][alt units]
\newvectorquantity{name}{base units}
\newvectorquantity{name}{base units}[derived units]
\newvectorquantity{name}{base units}[derived units][alt units]
\renewvectorquantity{name}{base units}
\renewvectorquantity{name}{base units}[derived units]
\renewvectorquantity{name}{base units}[derived units][alt units]

\alwaysusebaseunits
\alwaysusederivedunits
\alwaysusealternateunits

\hereusebaseunits{content}
\hereusederivedunits{content}
\hereusealternateunits{content}

\begin{usebaseunits}
\end{usebaseunits}
\begin{usederivedunits}
\end{usederivedunits}
\begin{usealternateunits}
\end{usealternateunits}

\oofpez#m

\oofpezapproximatevalue#*m
\oofpezprecisevalue#*m
\oofpezmathsymbol#*m
\oofpezbaseunits#*m
\oofpezderivedunits#*m
\oofpezalternateunits#*m
\oofpezonlybaseunits#*m
\oofpezonlyderivedunits#*m
\oofpezonlyalternateunits#*m

\checkconstant{name}

\avogadro#m
\avogadroapproximatevalue#*m
\avogadroprecisevalue#*m
\avogadromathsymbol#*m
\avogadrobaseunits#*m
\avogadroderivedunits#*m
\avogadroalternateunits#*m
\avogadroonlybaseunits#*m
\avogadroonlyderivedunits#*m
\avogadroonlyalternateunits#*m

\biotsavartconstant#m

\biotsavartconstantapproximatevalue#*m
\biotsavartconstantprecisevalue#*m
\biotsavartconstantmathsymbol#*m
\biotsavartconstantbaseunits#*m
\biotsavartconstantderivedunits#*m
\biotsavartconstantalternateunits#*m
\biotsavartconstantonlybaseunits#*m
\biotsavartconstantonlyderivedunits#*m
\biotsavartconstantonlyalternateunits#*m

\bohrradius#m

\bohrradiusapproximatevalue#*m
\bohrradiusprecisevalue#*m
\bohrradiusmathsymbol#*m
\bohrradiusbaseunits#*m
\bohrradiusderivedunits#*m
\bohrradiusalternateunits#*m
\bohrradiusonlybaseunits#*m
\bohrradiusonlyderivedunits#*m
\bohrradiusonlyalternateunits#*m

\boltzmann#m

\boltzmannapproximatevalue#*m
\boltzmannprecisevalue#*m
\boltzmannmathsymbol#*m
\boltzmannbaseunits#*m
\boltzmannderivedunits#*m
\boltzmannalternateunits#*m
\boltzmannonlybaseunits#*m
\boltzmannonlyderivedunits#*m
\boltzmannonlyalternateunits#*m

\coulombconstant#m

\coulombconstantapproximatevalue#*m
\coulombconstantprecisevalue#*m
\coulombconstantmathsymbol#*m
\coulombconstantbaseunits#*m
\coulombconstantderivedunits#*m
\coulombconstantalternateunits#*m
\coulombconstantonlybaseunits#*m
\coulombconstantonlyderivedunits#*m
\coulombconstantonlyalternateunits#*m

\earthmass#m

\earthmassapproximatevalue#*m
\earthmassprecisevalue#*m
\earthmassmathsymbol#*m
\earthmassbaseunits#*m
\earthmassderivedunits#*m
\earthmassalternateunits#*m
\earthmassonlybaseunits#*m
\earthmassonlyderivedunits#*m
\earthmassonlyalternateunits#*m

\earthmoondistance#m

\earthmoondistanceapproximatevalue#*m
\earthmoondistanceprecisevalue#*m
\earthmoondistancemathsymbol#*m
\earthmoondistancebaseunits#*m
\earthmoondistancederivedunits#*m
\earthmoondistancealternateunits#*m
\earthmoondistanceonlybaseunits#*m
\earthmoondistanceonlyderivedunits#*m
\earthmoondistanceonlyalternateunits#*m

\earthradius#m

\earthradiusapproximatevalue#*m
\earthradiusprecisevalue#*m
\earthradiusmathsymbol#*m
\earthradiusbaseunits#*m
\earthradiusderivedunits#*m
\earthradiusalternateunits#*m
\earthradiusonlybaseunits#*m
\earthradiusonlyderivedunits#*m
\earthradiusonlyalternateunits#*m

\earthsundistance#m

\earthsundistanceapproximatevalue#*m
\earthsundistanceprecisevalue#*m
\earthsundistancemathsymbol#*m
\earthsundistancebaseunits#*m
\earthsundistancederivedunits#*m
\earthsundistancealternateunits#*m
\earthsundistanceonlybaseunits#*m
\earthsundistanceonlyderivedunits#*m
\earthsundistanceonlyalternateunits#*m

\electroncharge#m

\electronchargeapproximatevalue#*m
\electronchargeprecisevalue#*m
\electronchargemathsymbol#*m
\electronchargebaseunits#*m
\electronchargederivedunits#*m
\electronchargealternateunits#*m
\electronchargeonlybaseunits#*m
\electronchargeonlyderivedunits#*m
\electronchargeonlyalternateunits#*m

\electronCharge#m

\electronChargeapproximatevalue#*m
\electronChargeprecisevalue#*m
\electronChargemathsymbol#*m
\electronChargebaseunits#*m
\electronChargederivedunits#*m
\electronChargealternateunits#*m
\electronChargeonlybaseunits#*m
\electronChargeonlyderivedunits#*m
\electronChargeonlyalternateunits#*m

\electronmass#m

\electronmassapproximatevalue#*m
\electronmassprecisevalue#*m
\electronmassmathsymbol#*m
\electronmassbaseunits#*m
\electronmassderivedunits#*m
\electronmassalternateunits#*m
\electronmassonlybaseunits#*m
\electronmassonlyderivedunits#*m
\electronmassonlyalternateunits#*m

\elementarycharge#m

\elementarychargeapproximatevalue#*m
\elementarychargeprecisevalue#*m
\elementarychargemathsymbol#*m
\elementarychargebaseunits#*m
\elementarychargederivedunits#*m
\elementarychargealternateunits#*m
\elementarychargeonlybaseunits#*m
\elementarychargeonlyderivedunits#*m
\elementarychargeonlyalternateunits#*m

\finestructure#m

\finestructureapproximatevalue#*m
\finestructureprecisevalue#*m
\finestructuremathsymbol#*m
\finestructurebaseunits#*m
\finestructurederivedunits#*m
\finestructurealternateunits#*m
\finestructureonlybaseunits#*m
\finestructureonlyderivedunits#*m
\finestructureonlyalternateunits#*m

\hydrogenmass#m

\hydrogenmassapproximatevalue#*m
\hydrogenmassprecisevalue#*m
\hydrogenmassmathsymbol#*m
\hydrogenmassbaseunits#*m
\hydrogenmassderivedunits#*m
\hydrogenmassalternateunits#*m
\hydrogenmassonlybaseunits#*m
\hydrogenmassonlyderivedunits#*m
\hydrogenmassonlyalternateunits#*m

\moonearthdistance#m

\moonearthdistanceapproximatevalue#*m
\moonearthdistanceprecisevalue#*m
\moonearthdistancemathsymbol#*m
\moonearthdistancebaseunits#*m
\moonearthdistancederivedunits#*m
\moonearthdistancealternateunits#*m
\moonearthdistanceonlybaseunits#*m
\moonearthdistanceonlyderivedunits#*m
\moonearthdistanceonlyalternateunits#*m

\moonmass#m

\moonmassapproximatevalue#*m
\moonmassprecisevalue#*m
\moonmassmathsymbol#*m
\moonmassbaseunits#*m
\moonmassderivedunits#*m
\moonmassalternateunits#*m
\moonmassonlybaseunits#*m
\moonmassonlyderivedunits#*m
\moonmassonlyalternateunits#*m

\moonradius#m

\moonradiusapproximatevalue#*m
\moonradiusprecisevalue#*m
\moonradiusmathsymbol#*m
\moonradiusbaseunits#*m
\moonradiusderivedunits#*m
\moonradiusalternateunits#*m
\moonradiusonlybaseunits#*m
\moonradiusonlyderivedunits#*m
\moonradiusonlyalternateunits#*m

\mzofp#m

\mzofpapproximatevalue#*m
\mzofpprecisevalue#*m
\mzofpmathsymbol#*m
\mzofpbaseunits#*m
\mzofpderivedunits#*m
\mzofpalternateunits#*m
\mzofponlybaseunits#*m
\mzofponlyderivedunits#*m
\mzofponlyalternateunits#*m

\neutronmass#m

\neutronmassapproximatevalue#*m
\neutronmassprecisevalue#*m
\neutronmassmathsymbol#*m
\neutronmassbaseunits#*m
\neutronmassderivedunits#*m
\neutronmassalternateunits#*m
\neutronmassonlybaseunits#*m
\neutronmassonlyderivedunits#*m
\neutronmassonlyalternateunits#*m

\oofpezcs#m

\oofpezcsapproximatevalue#*m
\oofpezcsprecisevalue#*m
\oofpezcsmathsymbol#*m
\oofpezcsbaseunits#*m
\oofpezcsderivedunits#*m
\oofpezcsalternateunits#*m
\oofpezcsonlybaseunits#*m
\oofpezcsonlyderivedunits#*m
\oofpezcsonlyalternateunits#*m

\planck#m

\planckapproximatevalue#*m
\planckprecisevalue#*m
\planckmathsymbol#*m
\planckbaseunits#*m
\planckderivedunits#*m
\planckalternateunits#*m
\planckonlybaseunits#*m
\planckonlyderivedunits#*m
\planckonlyalternateunits#*m

\planckbar#m

\planckbarapproximatevalue#*m
\planckbarprecisevalue#*m
\planckbarmathsymbol#*m
\planckbarbaseunits#*m
\planckbarderivedunits#*m
\planckbaralternateunits#*m
\planckbaronlybaseunits#*m
\planckbaronlyderivedunits#*m
\planckbaronlyalternateunits#*m

\planckc#m

\planckcapproximatevalue#*m
\planckcprecisevalue#*m
\planckcmathsymbol#*m
\planckcbaseunits#*m
\planckcderivedunits#*m
\planckcalternateunits#*m
\planckconlybaseunits#*m
\planckconlyderivedunits#*m
\planckconlyalternateunits#*m

\protoncharge#m

\protonchargeapproximatevalue#*m
\protonchargeprecisevalue#*m
\protonchargemathsymbol#*m
\protonchargebaseunits#*m
\protonchargederivedunits#*m
\protonchargealternateunits#*m
\protonchargeonlybaseunits#*m
\protonchargeonlyderivedunits#*m
\protonchargeonlyalternateunits#*m

\protonCharge#m

\protonChargeapproximatevalue#*m
\protonChargeprecisevalue#*m
\protonChargemathsymbol#*m
\protonChargebaseunits#*m
\protonChargederivedunits#*m
\protonChargealternateunits#*m
\protonChargeonlybaseunits#*m
\protonChargeonlyderivedunits#*m
\protonChargeonlyalternateunits#*m

\protonmass#m

\protonmassapproximatevalue#*m
\protonmassprecisevalue#*m
\protonmassmathsymbol#*m
\protonmassbaseunits#*m
\protonmassderivedunits#*m
\protonmassalternateunits#*m
\protonmassonlybaseunits#*m
\protonmassonlyderivedunits#*m
\protonmassonlyalternateunits#*m

\rydberg#m

\rydbergapproximatevalue#*m
\rydbergprecisevalue#*m
\rydbergmathsymbol#*m
\rydbergbaseunits#*m
\rydbergderivedunits#*m
\rydbergalternateunits#*m
\rydbergonlybaseunits#*m
\rydbergonlyderivedunits#*m
\rydbergonlyalternateunits#*m

\speedoflight#m

\speedoflightapproximatevalue#*m
\speedoflightprecisevalue#*m
\speedoflightmathsymbol#*m
\speedoflightbaseunits#*m
\speedoflightderivedunits#*m
\speedoflightalternateunits#*m
\speedoflightonlybaseunits#*m
\speedoflightonlyderivedunits#*m
\speedoflightonlyalternateunits#*m

\stefanboltzmann#m

\stefanboltzmannapproximatevalue#*m
\stefanboltzmannprecisevalue#*m
\stefanboltzmannmathsymbol#*m
\stefanboltzmannbaseunits#*m
\stefanboltzmannderivedunits#*m
\stefanboltzmannalternateunits#*m
\stefanboltzmannonlybaseunits#*m
\stefanboltzmannonlyderivedunits#*m
\stefanboltzmannonlyalternateunits#*m

\sunearthdistance#m

\sunearthdistanceapproximatevalue#*m
\sunearthdistanceprecisevalue#*m
\sunearthdistancemathsymbol#*m
\sunearthdistancebaseunits#*m
\sunearthdistancederivedunits#*m
\sunearthdistancealternateunits#*m
\sunearthdistanceonlybaseunits#*m
\sunearthdistanceonlyderivedunits#*m
\sunearthdistanceonlyalternateunits#*m

\sunradius#m

\sunradiusapproximatevalue#*m
\sunradiusprecisevalue#*m
\sunradiusmathsymbol#*m
\sunradiusbaseunits#*m
\sunradiusderivedunits#*m
\sunradiusalternateunits#*m
\sunradiusonlybaseunits#*m
\sunradiusonlyderivedunits#*m
\sunradiusonlyalternateunits#*m

\surfacegravfield#m

\surfacegravfieldapproximatevalue#*m
\surfacegravfieldprecisevalue#*m
\surfacegravfieldmathsymbol#*m
\surfacegravfieldbaseunits#*m
\surfacegravfieldderivedunits#*m
\surfacegravfieldalternateunits#*m
\surfacegravfieldonlybaseunits#*m
\surfacegravfieldonlyderivedunits#*m
\surfacegravfieldonlyalternateunits#*m

\universalgrav#m

\universalgravapproximatevalue#*m
\universalgravprecisevalue#*m
\universalgravmathsymbol#*m
\universalgravbaseunits#*m
\universalgravderivedunits#*m
\universalgravalternateunits#*m
\universalgravonlybaseunits#*m
\universalgravonlyderivedunits#*m
\universalgravonlyalternateunits#*m

\vacuumpermeability#m

\vacuumpermeabilityapproximatevalue#*m
\vacuumpermeabilityprecisevalue#*m
\vacuumpermeabilitymathsymbol#*m
\vacuumpermeabilitybaseunits#*m
\vacuumpermeabilityderivedunits#*m
\vacuumpermeabilityalternateunits#*m
\vacuumpermeabilityonlybaseunits#*m
\vacuumpermeabilityonlyderivedunits#*m
\vacuumpermeabilityonlyalternateunits#*m

\vacuumpermittivity#m

\vacuumpermittivityapproximatevalue#*m
\vacuumpermittivityprecisevalue#*m
\vacuumpermittivitymathsymbol#*m
\vacuumpermittivitybaseunits#*m
\vacuumpermittivityderivedunits#*m
\vacuumpermittivityalternateunits#*m
\vacuumpermittivityonlybaseunits#*m
\vacuumpermittivityonlyderivedunits#*m
\vacuumpermittivityonlyalternateunits#*m

\newphysicalconstant{name}{symbol}{approx val}{precise val}{base units}
\newphysicalconstant{name}{symbol}{approx val}{precise val}{base units}[derived units]
\newphysicalconstant{name}{symbol}{approx val}{precise val}{base units}[derived units][alt units]
\renewphysicalconstant{name}{symbol}{approx val}{precise val}{base units}
\renewphysicalconstant{name}{symbol}{approx val}{precise val}{base units}[derived units]
\renewphysicalconstant{name}{symbol}{approx val}{precise val}{base units}[derived units][alt units]

\alwaysuseapproximateconstants
\alwaysusepreciseconstants

\hereuseapproximateconstants{content}
\hereusepreciseconstants{content}

\begin{useapproximateconstants}
\end{useapproximateconstants}
\begin{usepreciseconstants}
\end{usepreciseconstants}

\per#m
\usk#m
\unit{magnitude}{unit}#m
\emptyunit#m
\ampere#m
\atomicmassunit#m
\candela#m
\coulomb#m
\degree#m
\electronvolt#m
\ev#m
\farad#m
\henry#m
\hertz#m
\joule#m
\kelvin#m
\kev#m
\kiloelectronvolt#m
\kilogram#m
\lightspeed #m
\megaelectronvolt#m
\meter#m
\metre#m
\mev#m
\mole#m
\newton#m
\ohm#m
\pascal#m
\radian#m
\second#m
\siemens#m
\steradian#m
\tesla#m
\volt#m
\watt#m
\weber#m
\tothetwo#*m
\tothethree#*m
\tothefour#*m
\inverse#m
\totheinversetwo#*m
\totheinversethree#*m
\totheinversefour#*m

\tento{number}#m
\timestento{number}#m
\xtento{number}#m

\mivector{c1,c2,...}#m
\mivector[delimiter]{c1,c2,...}#m
\mivector{c1,c2,...}[units]#m
\mivector[delimiter]{c1,c2,...}[units]#m
