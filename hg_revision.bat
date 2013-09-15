@echo off
cd %0\.. 
for /f "tokens=2" %%g in ('hg log -l 1 ^| findstr "changeset"') DO @set revision=%%g
echo const char * TEXSTUDIO_HG_REVISION = "%revision%";  > hg_revision.cpp
%1 -c hg_revision.cpp -o %2/hg_revision.o
