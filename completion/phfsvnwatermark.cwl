# phfsvnwatermark package
# Matthew Bertucci 2/8/2022 for v1.0

#include:kvoptions
#include:calc
#include:xcolor
#include:eso-pic

#keyvals:\usepackage/phfsvnwatermark#c
id=#svn,gitnotsvn,svn-multi,svn-multi-currfile
watermark#true,false
placement=#shipout,manual
#endkeyvals

#ifOption:id=svn
#include:svn
#endif

#ifOption:id=gitnotsvn
#include:svn
#endif

#ifOption:id=svn-multi
#include:svn-multi
#endif

#ifOption:id=svn-multi-currfile
#include:currfile
#include:svn-multi
#endif

\phfsvnShipoutWatermarkXposRight#*
\phfsvnShipoutWatermarkYposBaseline#*
\phfsvnVersionIdTag#*
\phfsvnVersionIdTag*#*
\phfsvnVersionIdTagInnerFont#*
\phfsvnVersionIdTagOuterFont#*