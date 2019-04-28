# calculus package
# https://ctan.org/pkg/calculator
#
# Created by @ppizarror
# https://github.com/ppizarror/calculator-cwl
# date: Sat 27 Apr

# --------------------------------------------
# 1. Predefined functions
# --------------------------------------------
\ZEROfunction
\IDENTITYfunction
\SQUAREfunction
\SQRTfunction
\EXPfunction
\COSfunction
\TANfunction
\COSHfunction
\TANHfunction
\HEAVISIDEfunction
\ONEfunction
\RECIPROCALfunction
\CUBEfunction
\LOGfunction
\SINfunction
\COTfunction
\SINHfunction
\COTHfunction
\ARCCOSfunction
\ARCTANfunction
\ARCOSHfunction
\ARTANHfunction
\ARCSINfunction
\ARCCOTfunction
\ARSINHfunction
\ARCOTHfunction

# --------------------------------------------
# 2. Operations with functions
# --------------------------------------------
\CONSTANTfunction{num}{Function}
\SUMfunction{function1}{function2}{Function}
\SUBTRACTfunction{function1}{function2}{Function}
\PRODUCTfunction{function1}{function2}{Function}
\QUOTIENTfunction{function1}{function2}{Function}
\COMPOSITIONfunction{function1}{function2}{Function}
\SCALEfunction{num}{function}{Function}
\SCALEVARIABLEfunction{num}{function}{Function}
\POWERfunction{function}{num}{Function}
\LINEARCOMBINATIONfunction{num1}{function1}{num2}{function2}{Function}

# --------------------------------------------
# 3. Polynomial functions
# --------------------------------------------
\newlpoly{Function}{a}{b}
\newqpoly{Function}{a}{b}{c}
\newcpoly{Function}{a}{b}{c}{d}

\renewlpoly
\renewqpoly
\renewcpoly

\ensurelpoly
\ensureqpoly
\ensurecpoly

\forcelpoly
\forceqpoly
\forcecpoly

# --------------------------------------------
# 4. Vector-valued functions
# --------------------------------------------
\PARAMETRICfunction{Xfunction}{Yfunction}{myvectorfunction}
\VECTORfunction{Xfunction}{Yfunction}{myvectorfunction}
\newvectorfunction{Function}{instructions to compute x,D,y,Dy from t}

# --------------------------------------------
# 5. Vector-valued functions in polar coordinates
# --------------------------------------------
\POLARfunction{rfunction}{Polarfunction}
\newpolarfunction{Function}{instructions to compute r,Dr from t}