# calculus package
# https://ctan.org/pkg/calculator
#
# Created by @ppizarror
# https://github.com/ppizarror/calculator-cwl
# date: Sun 28 Apr

# Matthew Bertucci updated 3/31/2022 for v2.0

#include:calculator

# --------------------------------------------
# 1. Predefined functions
# --------------------------------------------
\ZEROfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ZEROfunction{num}{cmd}{cmd}#Sd
\IDENTITYfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\IDENTITYfunction{num}{cmd}{cmd}#Sd
\SQUAREfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\SQUAREfunction{num}{cmd}{cmd}#Sd
\SQRTfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\SQRTfunction{num}{cmd}{cmd}#Sd
\EXPfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\EXPfunction{num}{cmd}{cmd}#Sd
\COSfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\COSfunction{num}{cmd}{cmd}#Sd
\TANfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\TANfunction{num}{cmd}{cmd}#Sd
\COSHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\COSHfunction{num}{cmd}{cmd}#Sd
\TANHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\TANHfunction{num}{cmd}{cmd}#Sd
\HEAVISIDEfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\HEAVISIDEfunction{num}{cmd}{cmd}#Sd
\ONEfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ONEfunction{num}{cmd}{cmd}#Sd
\RECIPROCALfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\RECIPROCALfunction{num}{cmd}{cmd}#Sd
\CUBEfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\CUBEfunction{num}{cmd}{cmd}#Sd
\LOGfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\LOGfunction{num}{cmd}{cmd}#Sd
\SINfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\SINfunction{num}{cmd}{cmd}#Sd
\COTfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\COTfunction{num}{cmd}{cmd}#Sd
\SINHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\SINHfunction{num}{cmd}{cmd}#Sd
\COTHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\COTHfunction{num}{cmd}{cmd}#Sd
\ARCCOSfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCCOSfunction{num}{cmd}{cmd}#Sd
\ARCTANfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCTANfunction{num}{cmd}{cmd}#Sd
\ARCOSHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCOSHfunction{num}{cmd}{cmd}#Sd
\ARTANHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARTANHfunction{num}{cmd}{cmd}#Sd
\ARCSINfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCSINfunction{num}{cmd}{cmd}#Sd
\ARCCOTfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCCOTfunction{num}{cmd}{cmd}#Sd
\ARSINHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARSINHfunction{num}{cmd}{cmd}#Sd
\ARCOTHfunction{%<num%>}{%<\sol%>}{%<\Dsol%>}
\ARCOTHfunction{num}{cmd}{cmd}#Sd

# --------------------------------------------
# 2. Operations with functions
# --------------------------------------------
\CONSTANTfunction{num}{Function%cmd}#d
\SUMfunction{function1}{function2}{Function%cmd}#d
\SUBTRACTfunction{function1}{function2}{Function%cmd}#d
\PRODUCTfunction{function1}{function2}{Function%cmd}#d
\QUOTIENTfunction{function1}{function2}{Function%cmd}#d
\COMPOSITIONfunction{function1}{function2}{Function%cmd}#d
\SCALEfunction{num}{function}{Function%cmd}#d
\SCALEVARIABLEfunction{num}{function}{Function%cmd}#d
\POWERfunction{function}{num}{Function%cmd}#d
\LINEARCOMBINATIONfunction{num1}{function1}{num2}{function2}{Function%cmd}#d

# --------------------------------------------
# 3. Polynomial functions
# --------------------------------------------
\newlpoly{Function%cmd}{a}{b}#d
\newqpoly{Function%cmd}{a}{b}{c}#d
\newcpoly{Function%cmd}{a}{b}{c}{d}#d

\renewlpoly{Function%cmd}{a}{b}
\renewqpoly{Function%cmd}{a}{b}{c}
\renewcpoly{Function%cmd}{a}{b}{c}{d}

\ensurelpoly{Function%cmd}{a}{b}#d
\ensureqpoly{Function%cmd}{a}{b}{c}#d
\ensurecpoly{Function%cmd}{a}{b}{c}{d}#d

\forcelpoly{Function%cmd}{a}{b}#d
\forceqpoly{Function%cmd}{a}{b}{c}#d
\forcecpoly{Function%cmd}{a}{b}{c}{d}#d

# --------------------------------------------
# 4. Vector-valued functions
# --------------------------------------------
\PARAMETRICfunction{Xfunction}{Yfunction}{myvectorfunction%cmd}#d
\VECTORfunction{Xfunction}{Yfunction}{myvectorfunction%cmd}#d

# --------------------------------------------
# 5. Vector-valued functions in polar coordinates
# --------------------------------------------
\POLARfunction{rfunction}{Polarfunction%cmd}#d

# --------------------------------------------
# 6. Low-level instructions
# --------------------------------------------
\newfunction{%<\Function%>}{%<instructions to compute \y and \Dy from \t%>}
\newfunction{cmd}{def}#Sd
\renewfunction{%<\Function%>}{%<instructions to compute \y and \Dy from \t%>}
\renewfunction{cmd}{def}#S
\ensurefunction{%<\Function%>}{%<instructions to compute \y and \Dy from \t%>}
\ensurefunction{cmd}{def}#Sd
\forcefunction{%<\Function%>}{%<instructions to compute \y and \Dy from \t%>}
\forcefunction{cmd}{def}#Sd

\newvectorfunction{%<\Function%>}{%<instructions to compute \x,\y,\Dx and \Dy from \t%>}
\newvectorfunction{cmd}{def}#Sd
\renewvectorfunction{%<\Function%>}{%<instructions to compute \x,\y,\Dx and \Dy from \t%>}
\renewvectorfunction{cmd}{def}#S
\ensurevectorfunction{%<\Function%>}{%<instructions to compute \x,\y,\Dx and \Dy from \t%>}
\ensurevectorfunction{cmd}{def}#Sd
\forcevectorfunction{%<\Function%>}{%<instructions to compute \x,\y,\Dx and \Dy from \t%>}
\forcevectorfunction{cmd}{def}#Sd

\newpolarfunction{%<\Function%>}{%<instructions to compute \r and \Dr from \t%>}
\newpolarfunction{cmd}{def}#Sd
\renewpolarfunction{%<\Function%>}{%<instructions to compute \r and \Dr from \t%>}
\renewpolarfunction{cmd}{def}#S
\ensurepolarfunction{%<\Function%>}{%<instructions to compute \r and \Dr from \t%>}
\ensurepolarfunction{cmd}{def}#Sd
\forcepolarfunction{%<\Function%>}{%<instructions to compute \r and \Dr from \t%>}
\forcepolarfunction{cmd}{def}#Sd
