# translator package
# Matthew Bertucci 10/24/2021 for v1.12d

#include:keyval

\newtranslation{key%plain}{translation}#*
\newtranslation[options%keyvals]{key%plain}{translation}#*
\renewtranslation{key%plain}{translation}#*
\renewtranslation[options%keyvals]{key%plain}{translation}#*
\providetranslation{key%plain}{translation}#*
\providetranslation[options%keyvals]{key%plain}{translation}#*
\deftranslation{key%plain}{translation}#*
\deftranslation[options%keyvals]{key%plain}{translation}#*

#keyvals:\newtranslation,\renewtranslation,\providetranslation,\deftranslation,\translate,\translatelet
to=%<language%>
#endkeyvals

\ProvidesDictionary{kind}{language}#*
\ProvidesDictionary{kind}{language}[version]#*
\usedictionary{kind}#*
\uselanguage{lang1,lang2,...}#*
\translate{key%plain}#*
\translate[options%keyvals]{key%plain}#*
\translatelet{macro%cmd}{key%plain}#*d
\translatelet[options%keyvals]{macro%cmd}{key%plain}#*d
\languagepath{path}#*
\languagealias{name}{language list}#*
\languagename#*