# mode: pst-coil.sty
# dani/2006-02-22

#include:pstricks
#include:pst-node
#include:pst-xkey

\pscoil(x0,y0)(x1,y1)
\pscoil{arrows}(x0,y0)(x1,y1)
\pscoil[options%keyvals](x0,y0)(x1,y1)
\pscoil[options%keyvals]{arrows}(x0,y0)(x1,y1)
\pscoil*(x0,y0)(x1,y1)
\pscoil*{arrows}(x0,y0)(x1,y1)
\pscoil*[options%keyvals](x0,y0)(x1,y1)
\pscoil*[options%keyvals]{arrows}(x0,y0)(x1,y1)

\psCoil{angle1}{angle2}
\psCoil[options%keyvals]{angle1}{angle2}
\psCoil*{angle1}{angle2}
\psCoil*[options%keyvals]{angle1}{angle2}

\pszigzag(x0,y0)(x1,y1)
\pszigzag{arrows}(x0,y0)(x1,y1)
\pszigzag[options%keyvals](x0,y0)(x1,y1)
\pszigzag[options%keyvals]{arrows}(x0,y0)(x1,y1)
\pszigzag*(x0,y0)(x1,y1)
\pszigzag*{arrows}(x0,y0)(x1,y1)
\pszigzag*[options%keyvals](x0,y0)(x1,y1)
\pszigzag*[options%keyvals]{arrows}(x0,y0)(x1,y1)

\pssin(x0,y0)(x1,y1)
\pssin{arrows}(x0,y0)(x1,y1)
\pssin[options%keyvals](x0,y0)(x1,y1)
\pssin[options%keyvals]{arrows}(x0,y0)(x1,y1)
\pssin*(x0,y0)(x1,y1)
\pssin*{arrows}(x0,y0)(x1,y1)
\pssin*[options%keyvals](x0,y0)(x1,y1)
\pssin*[options%keyvals]{arrows}(x0,y0)(x1,y1)

\nccoil{nodeA}{nodeB}
\nccoil{arrows}{nodeA}{nodeB}
\nccoil[options%keyvals]{nodeA}{nodeB}
\nccoil[options%keyvals]{arrows}{nodeA}{nodeB}
\nccoil*{nodeA}{nodeB}
\nccoil*{arrows}{nodeA}{nodeB}
\nccoil*[options%keyvals]{nodeA}{nodeB}
\nccoil*[options%keyvals]{arrows}{nodeA}{nodeB}

\nczigzag{nodeA}{nodeB}
\nczigzag{arrows}{nodeA}{nodeB}
\nczigzag[options%keyvals]{nodeA}{nodeB}
\nczigzag[options%keyvals]{arrows}{nodeA}{nodeB}
\nczigzag*{nodeA}{nodeB}
\nczigzag*{arrows}{nodeA}{nodeB}
\nczigzag*[options%keyvals]{nodeA}{nodeB}
\nczigzag*[options%keyvals]{arrows}{nodeA}{nodeB}

\pccoil{nodeA}{nodeB}
\pccoil{arrows}{nodeA}{nodeB}
\pccoil[options%keyvals]{nodeA}{nodeB}
\pccoil[options%keyvals]{arrows}{nodeA}{nodeB}
\pccoil*{nodeA}{nodeB}
\pccoil*{arrows}{nodeA}{nodeB}
\pccoil*[options%keyvals]{nodeA}{nodeB}
\pccoil*[options%keyvals]{arrows}{nodeA}{nodeB}

\pczigzag{nodeA}{nodeB}
\pczigzag{arrows}{nodeA}{nodeB}
\pczigzag[options%keyvals]{nodeA}{nodeB}
\pczigzag[options%keyvals]{arrows}{nodeA}{nodeB}
\pczigzag*{nodeA}{nodeB}
\pczigzag*{arrows}{nodeA}{nodeB}
\pczigzag*[options%keyvals]{nodeA}{nodeB}
\pczigzag*[options%keyvals]{arrows}{nodeA}{nodeB}

\ncsin{nodeA}{nodeB}
\ncsin{arrows}{nodeA}{nodeB}
\ncsin[options%keyvals]{nodeA}{nodeB}
\ncsin[options%keyvals]{arrows}{nodeA}{nodeB}
\ncsin*{nodeA}{nodeB}
\ncsin*{arrows}{nodeA}{nodeB}
\ncsin*[options%keyvals]{nodeA}{nodeB}
\ncsin*[options%keyvals]{arrows}{nodeA}{nodeB}

\pcsin{nodeA}{nodeB}
\pcsin{arrows}{nodeA}{nodeB}
\pcsin[options%keyvals]{nodeA}{nodeB}
\pcsin[options%keyvals]{arrows}{nodeA}{nodeB}
\pcsin*{nodeA}{nodeB}
\pcsin*{arrows}{nodeA}{nodeB}
\pcsin*[options%keyvals]{nodeA}{nodeB}
\pcsin*[options%keyvals]{arrows}{nodeA}{nodeB}

\PSTcoilsLoaded#S
