# mfirstuc package
# Matthew Bertucci 2022/10/18 for v2.08

#include:etoolbox

#keyvals:\usepackage/mfirstuc#c
expanded
unexpanded
grabfirst
#endkeyvals

## Sentence-Case ##
# Sentence Case Commands #
\MFUsentencecase{text}
\makefirstuc{text}
\xmakefirstuc{text}
\emakefirstuc{text}
\glsmakefirstuc{text}

# Exclusions #
\MFUexcl{cmd}
\MFUskippunc{content%text}

# Blockers #
\MFUblocker{cmd}

# Mappings #
\MFUaddmap{cmd1%cmd}{cmd2%cmd}

## Title-Case ##
\capitalisewords{text}
\capitalisewords*{text}
\xcapitalisewords{text}
\xcapitalisewords*{text}
\ecapitalisewords{text}
\ecapitalisewords*{text}
\MFUwordbreak{puncutation}
\MFUcapword{text}
\ifMFUhyphen#*
\MFUhyphencapword{text}#*
\MFUhyphentrue#*
\MFUhyphenfalse#*
\MFUcapwordfirstuc{word%text}#*
\capitalisefmtwords{text}
\xcapitalisefmtwords{text}
\ecapitalisefmtwords{text}

# Excluding Words From Case-Changing #
\MFUnocap{word%text}
\gMFUnocap{word%text}
\MFUclear

## Miscellaneous ##
# Saving Exclusions, Blockers and Mappings in the aux File #
\MFUsaveatend#*
\MFUsave#*

# All-Caps #
\mfirstucMakeUppercase{text}#*

# deprecated
\MFUapplytofirst{cmd}{text}#S
\mfugrabfirstuc{text}#S
