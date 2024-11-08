# numbersets package
# Matthew Bertucci 2024/10/15 for v0.2.0

\SetupNumberSetsOptions{options%keyvals}
\NumberSet{symbol}
\NumberSet[options%keyvals]{symbol}

#keyvals:\SetupNumberSetsOptions#c,\NumberSet#c
style=#bb,bfup,bfit,%numbersetsstyle
#endkeyvals

\DeclareNumberSetCommand{command}{symbol}#d
\DeclareNumberSetStyle{style%specialDef}{command}#s#%numbersetsstyle
\NaturalNumbers
\Integers
\RationalNumbers
\RealNumbers
\ComplexNumbers
