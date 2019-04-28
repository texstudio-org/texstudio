# calculus package
# https://ctan.org/pkg/calculator
#
# Created by @ppizarror
# https://github.com/ppizarror/calculator-cwl
# date: Sun 28 Apr

# --------------------------------------------
# 1. Predefined functions
# --------------------------------------------
\ZEROfunction#n
\IDENTITYfunction#n
\SQUAREfunction#n
\SQRTfunction#n
\EXPfunction#n
\COSfunction#n
\TANfunction#n
\COSHfunction#n
\TANHfunction#n
\HEAVISIDEfunction#n
\ONEfunction#n
\RECIPROCALfunction#n
\CUBEfunction#n
\LOGfunction#n
\SINfunction#n
\COTfunction#n
\SINHfunction#n
\COTHfunction#n
\ARCCOSfunction#n
\ARCTANfunction#n
\ARCOSHfunction#n
\ARTANHfunction#n
\ARCSINfunction#n
\ARCCOTfunction#n
\ARSINHfunction#n
\ARCOTHfunction#n

# --------------------------------------------
# 2. Operations with functions
# --------------------------------------------
\CONSTANTfunction{num}{Function}#d
\SUMfunction{function1}{function2}{Function}#d
\SUBTRACTfunction{function1}{function2}{Function}#d
\PRODUCTfunction{function1}{function2}{Function}#d
\QUOTIENTfunction{function1}{function2}{Function}#d
\COMPOSITIONfunction{function1}{function2}{Function}#d
\SCALEfunction{num}{function}{Function}#d
\SCALEVARIABLEfunction{num}{function}{Function}#d
\POWERfunction{function}{num}{Function}#d
\LINEARCOMBINATIONfunction{num1}{function1}{num2}{function2}{Function}#d

# --------------------------------------------
# 3. Polynomial functions
# --------------------------------------------
\newlpoly{Function}{a}{b}#d
\newqpoly{Function}{a}{b}{c}#d
\newcpoly{Function}{a}{b}{c}{d}#d

\renewlpoly#n
\renewqpoly#n
\renewcpoly#n

\ensurelpoly#n
\ensureqpoly#n
\ensurecpoly#n

\forcelpoly#n
\forceqpoly#n
\forcecpoly#n

# --------------------------------------------
# 4. Vector-valued functions
# --------------------------------------------
\PARAMETRICfunction{Xfunction}{Yfunction}{myvectorfunction}#d
\VECTORfunction{Xfunction}{Yfunction}{myvectorfunction}#d
\newvectorfunction{Function}{instructions to compute x,D,y,Dy from t}#d

# --------------------------------------------
# 5. Vector-valued functions in polar coordinates
# --------------------------------------------
\POLARfunction{rfunction}{Polarfunction}#d
\newpolarfunction{Function}{instructions to compute r,Dr from t}#d