# xcntperchap package
# Matthew Bertucci 1/8/2021 for v0.5

#include:zref-counter
#include:l3keys2e
#include:xassoccnt

\RegisterTrackCounter{track counter}{counter1,counter2,...}
\RegisterMultipleTrackCounters{trackcounter1,trackcounter2,...}{counter1,counter2,...}

\ObtainTrackedValue{track level}{tracked counter}
\ObtainTrackedValue[counter value]{track level}{tracked counter}
\ObtainTrackedValueExp{track level}{tracked counter}
\ObtainTrackedValueExp[counter value]{track level}{tracked counter}

\tracklabel{label}#l
\tracklabel[counter]{label}#l
\tracklabel*{label}
\tracklabel*[counter]{label}

\ObtainTrackedValueByLabel{label}{tracked counter}#r
\ObtainTrackedValueByLabel[counter]{label}{tracked counter}#r

\AddToTrackedCounters{trackedcounter1,trackedcounter2,...}{counter value}

# deprecated
\RegisterCounters{track counter}{counter1,counter2,...}#S

# not documented
\CloseTrackFileForWrite#*
\GetStoredValues#*
\LoadTrackedValues#*
\OpenTrackFileForWrite{file}#*
\StoreCounterValues{arg}#*
\TrackCounters#*
\cntperchapsetup#S
\xcntperchappackageversion#S