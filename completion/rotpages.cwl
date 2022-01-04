# rotpages package
# Matthew Bertucci 1/4/2022 for v3.0

#include:calc
#include:graphics
#include:ifthen

\rotboxpages
\endrotboxpages

\rotboxheight#*
\rotboxwidth#*

\rotboxAtRotationHook{code}#*
\rotboxAtShippingHook{code}#*