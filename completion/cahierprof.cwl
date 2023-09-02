# cahierprof package
# Matthew Bertucci 2023/09/02 for v1.0

#include:geometry
#include:tabularx
#include:colortbl
#include:tikz
#include:tikzlibrarymath
#include:tikzlibrarycalc
#include:microtype
#include:ifthen

#keyvals:\usepackage/cahierprof#c
samedi
#endkeyvals

\setLundiRentree{JJ}{MM}{YYYY}
\EmploiDuTemps{tableau%text}
\setNombreSemaines{nombre}
\setSamedi
\sem{semaine impair%text}{semaine pair%text}
\setDebutToussaint{JJ}{MM}
\setDebutNoel{JJ}{MM}
\setDebutHiver{JJ}{MM}
\setDebutPrintemps{JJ}{MM}
\setFinToussaint{JJ}{MM}
\setFinNoel{JJ}{MM}
\setFinHiver{JJ}{MM}
\setFinPrintemps{JJ}{MM}
\setDNB{JD}{JF}{YY}
\setBac{JD}{JF}{YY}
\setBacPhilo{JJ}{MM}
\setBacfrancais{JJ}{MM}
\setGO{JD}{JF}{YY}
\setLundiPaques{JJ}{MM}
\Classe{nom%text}{nombre}{liste des élèves%text}
\ListeEleves{file}#i

# not documented
\theday#S
\themonth#S
\theyear#S
\thelundiRentree#S
\themonthRentree#S
\theyearRentree#S
\thedayToussaint#S
\themonthToussaint#S
\thedayToussaintFin#S
\themonthToussaintFin#S
\thedayNoel#S
\themonthNoel#S
\thedayNoelFin#S
\themonthNoelFin#S
\thedayHiver#S
\themonthHiver#S
\thedayHiverFin#S
\themonthHiverFin#S
\thedayPrintemps#S
\themonthPrintemps#S
\thedayPrintempsFin#S
\themonthPrintempsFin#S
\thedayPaques#S
\themonthPaques#S
\thedayAscension#S
\thedayAscensionPont#S
\themonthAscension#S
\thedayPentecote#S
\themonthPentecote#S
\thedayDNBDebut#S
\thedayDNBFin#S
\themonthDNB#S
\thedayBacDebut#S
\thedayBacFin#S
\themonthBac#S
\thedayBacPhilo#S
\themonthBacPhilo#S
\thedayBacFrancais#S
\themonthBacFrancais#S
\thedayGODebut#S
\thedayGOFin#S
\themonthGO#S
\thedayRemember#S
\themonthRemember#S
\theyearRemember#S
\nextday#S
\weekend#S
\getDate#S
\getWeek#S
\setJoursFeries#S
\Semaine#S
\thenombreSemaines#S
\TableauClasse{arg1}{arg2}#S
\theFinFevrier#S
\isFerie#S
\isExamen#S




