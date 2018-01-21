@echo off
cd %0\.. 

git describe --tags > git_temp.txt
set /p local_revision= < git_temp.txt
del hg_temp.txt

echo const char * TEXSTUDIO_GIT_REVISION = "%local_revision%";  > git_revision.cpp
%1 -c git_revision.cpp -o %2/git_revision.o
