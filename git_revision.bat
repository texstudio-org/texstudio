@echo off
cd /d %~dp0

git describe --tags > git_temp.txt
set /p local_revision= < git_temp.txt
del git_temp.txt

echo const char * TEXSTUDIO_GIT_REVISION = "%local_revision%";  > src\git_revision.cpp
