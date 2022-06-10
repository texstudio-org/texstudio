# listingsutf8 package
# Matthew Bertucci 2022/06/06 for v1.5

#include:listings
#include:inputenc
#include:pdftexcmds
#include:stringenc

# passes all options to listings package
#keyvals:\usepackage/listingsutf8#c
draft
final
savemem
noaspects
lgrind
procnames
hyper
formats
0.21
#endkeyvals

#keyvals:\lstinputlisting
inputencoding=utf8/%<one-byte-encoding%>
#endkeyvals

# from listings options
#ifOption:procnames
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
procnamekeys={%<keywords%>}
moreprocnamekeys={%<keywords%>}
deleteprocnamekeys={%<keywords%>}
procnamestyle=%<style%>
indexprocnames#true,false
#endkeyvals
#endif

#ifOption:hyper
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
hyperref={%<identifiers%>}
morehyperref={%<identifiers%>}
deletehyperref={%<identifiers%>}
hyperanchor=%<two-parameter macro%>
hyperlink=%<two-parameter macro%>
#endkeyvals
#endif

#ifOption:lgrind
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
lgrindef=%<language%>
#endkeyvals
\lstlgrindeffile
#endif

#ifOption:formats
\lstdefineformat{name}{format}
#endif