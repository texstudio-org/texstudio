# pbox package
# Matthew Bertucci 9/11/2021 for v1.2

#include:calc

\pbox{width}{contents%text}
\pbox[position]{width}{contents%text}
\pbox[position][height]{width}{contents%text}
\pbox[position][height][inner-pos]{width}{contents%text}

\settominwidth{cmd}{text}#*
\settominwidth[max-width]{cmd}{text}#*
\widthofpbox{text}#*