# luatexja-adjust package
# Matthew Bertucci 2022/07/04 for release 2022-02-11

#include:luatexja

\ltjenableadjust
\ltjenableadjust[options%keyvals]
\ltjdisableadjust

#keyvals:\ltjenableadjust
lineend=#false,true,extended
priority#true,false
profile#true,false
linestep#true,false
#endkeyvals

#keyvals:\ltjsetparameter,\ltjglobalsetparameter
stretch_priority={%<keyval list%>}
shrink_priority={%<keyval list%>}
linestep_factor=%<real%>
profile_hgap_factor=%<real%>
#endkeyvals

#keyvals:\ltjgetparameter
stretch_priority
shrink_priority
linestep_factor
profile_hgap_factor
#endkeyvals

\ltjghostbeforejachar
\ltjghostafterjachar

# deprecated
\ltjghostjachar#S