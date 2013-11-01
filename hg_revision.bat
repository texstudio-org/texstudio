@echo off
cd %0\.. 

hg id -n > hg_temp.txt
set /p local_revision= < hg_temp.txt
hg id -i > hg_temp.txt
set /p global_revision= < hg_temp.txt
del hg_temp.txt

echo const char * TEXSTUDIO_HG_REVISION = "%local_revision%:%global_revision%";  > hg_revision.cpp
%1 -c hg_revision.cpp -o %2/hg_revision.o
