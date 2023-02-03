#tbraun 9.02.2008
# svn-multi aka svnkw ctan package
# updated Matthew Bertucci 11/13/2021 for v2.4d

#include:kvoptions
#include:filehook
#include:currfile

#keyvals:\usepackage/svn-multi#c
old
all
verbatim#true,false
external#true,false
groups#true,false
subgroups#true,false
graphics#true,false
pgfimages#true,false
autoload#true,false
table#true,false
filehooks#true,false
autokw=#false,true,all,ext
#endkeyvals

#ifOption:all
#include:graphics
#include:pgf
\svngraphicsgroup{graphic group name}
\svnignoregraphic{file path/name%file}
\svnconsidergraphic{file path/name%file}
#endif

#ifOption:graphics
#include:graphics
\svngraphicsgroup{graphic group name}
\svnignoregraphic{file path/name%file}
\svnconsidergraphic{file path/name%file}
#endif

#ifOption:pgfimages
#include:pgf
#endif

\svnid{$%<Id%>$}
\svnidlong{$%<HeadURL%>$}{$%<LastChangedDate%>$}{$%<LastRevision%>$}{$%<LastChangedBy%>$}
\svn{$%<keyword%>$}
\svn*{$%<keyword%>$}
\svnkwsave{$%<keyword%>$}

\svngroup{group name}
\thesvngroup
\svnsetcg{group name}
\thesvncg
\svnsubgroup
\svnignoreextensions{ext list}
\svnconsiderextensions{ext list}

\svnrev
\svndate
\svnauthor
\svnfilerev
\svnfiledate
\svnfileauthor
\svncgrev
\svncgauthor
\svncgdate
\svng{group name}{key%plain}
\svnmainurl
\svnmainfilename
\svnsetmainfile
\svnkw{keyword name}
\svnkwdef{keyword name}{value}

\ifsvnfilemodified{true}{false}
\ifsvnmodified{true}{false}

\svnyear
\svnfileyear
\svncgyear
\svnmonth
\svnfilemonth
\svncgmonth
\svnday
\svnfileday
\svncgday
\svnhour
\svnfilehour
\svncghour
\svnminute
\svnfileminute
\svncgminute
\svnsecond
\svnfilesecond
\svncgsecond
\svntimezone
\svnfiletimezone
\svncgtimezone
\svntimezonehour
\svnfiletimezonehour
\svncgtimezonehour
\svntimezoneminute
\svnfiletimezoneminute
\svncgtimezoneminute
\svntime
\svnfiletime
\svncgtime
\svnpdfdate
\svntoday
\svnfiletoday
\svncgtoday
\svnfilefname
\svnfileurl
\svncgfname
\svnurl
\svnfname
\svncgurl

\svnRegisterAuthor{author}{full name}
\svnFullAuthor{author}
\svnFullAuthor*{author}

\svnRegisterRevision{revision number}{tag name}
\svnFullRevision{revision number}
\svnFullRevision*{revision number}

\svnnolinkurl{macro}

\tableofrevisions

\svnrevisionsname#*
\svnbeforetable#*
\svnaftertable#*
\svntable#*
\endsvntable#*
\svntablehead#*
\svntablefoot#*
\svnglobalrow#*
\endsvnglobalrow#*
\svngrouprow#*
\endsvngrouprow#*
\svnsubgrouprow#*
\endsvnsubgrouprow#*
\svnfilerow#*
\endsvnfilerow#*
\svntabglobal#*
\svntabgroup{group name}
\svntabsubgroup{nesting level}{subgroup name}
\svntabfile{nesting level}{file path/name%file}
\svntabrev{revision number}
\svntabauthor{author}
\svntabdate{{%<year%>}{%<month%>}{%<day%>}{%<hour%>}{%<minute%>}{%<second%>}{%<TZ hour%>}{%<TZ minute%>}}

\svnexternal{%<file1%>}%<{file2}...{fileN}%>
\svnexternal[%<group name%>]{%<file1%>}%<{file2}...{fileN}%>
\svnexternalpath{{%<path1%>}%<{path2}...{pathN}%>}
