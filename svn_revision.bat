@echo #define MK_STRING(x) #x > svn_revision.cpp
@echo const char * TEXMAKERX_SVN_VERSION = MK_STRING(  >> svn_revision.cpp
call svnversion >> svn_revision.cpp
@echo ); >> svn_revision.cpp
%1 -c svn_revision.cpp -o svn_revision.o
