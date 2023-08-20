# expex-glossonly package
# Matthew Bertucci 2023/08/17 for v0.7

#include:calc
#include:expex

#keyvals:\usepackage/expex-glossonly#c
gb4e
gb4e-emulate
linguex
covington
covington={%<package options%>}
#endkeyvals

#ifOption:gb4e
#include:gb4e
#endif

#ifOption:gb4e-emulate
#include:gb4e-emulate
#endif

#ifOption:linguex
#include:linguex
#endif

#ifOption:covington
#include:covington
#endif