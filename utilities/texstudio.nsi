!define APPNAME "TeXstudio"
!define DESCRIPTION "TeXstudio is a fully featured LaTeX editor."
# These three must be integers
!define VERSIONMAJOR 2
!define VERSIONMINOR 12
!define VERSIONBUILD 10
# These will be displayed by the "Click here for support information" link in "Add/Remove Programs"
# It is possible to use "mailto:" links in here to open the email client
!define HELPURL "https://texstudio.org" # "Support Information" link
!define UPDATEURL "https://texstudio.org" # "Product Updates" link
!define ABOUTURL "https://texstudio.org" # "Publisher" link

!include "FileAssociation.nsh"

# define the name of the installer
Outfile "texstudio_installer.exe"

RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
InstallDir "$PROGRAMFILES\texstudio"

Name "${APPNAME}"

page directory
page instfiles

#!macro VerifyUserIsAdmin
#UserInfo::GetAccountType
#pop $0
#${If} $0 != "admin" ;Require admin rights on NT4+
#        messageBox mb_iconstop "Administrator rights required!"
#        setErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
#        quit
#${EndIf}
#!macroend

# default section
Section "install"
 
# define the output path for this file
SetOutPath $INSTDIR
 
# define what to install and place it in the output path
File texstudio.exe

SetOutPath $INSTDIR\translations

File translation\*.qm

SetOutPath $INSTDIR\templates

File templates\*

SetOutPath $INSTDIR\help

File utilities\AUTHORS
File utilities\COPYING
File utilities\latex2e.html
File utilities\latex2e.css
File utilities\license.txt
File utilities\manual\*

SetOutPath $INSTDIR\share\poppler
File /r utilities\poppler-data\*

SetOutPath $INSTDIR\TexTablet
File utilities\TexTablet\*

SetOutPath $INSTDIR\dictionaries
File utilities\dictionaries\*.dic
File utilities\dictionaries\*.aff
File utilities\dictionaries\*.badWords
File utilities\dictionaries\*.stopWords
File utilities\dictionaries\*.stopWords.level2
File utilities\dictionaries\th_*_v2.dat

 
# define uninstaller name
WriteUninstaller $INSTDIR\uninstall.exe

# associate .tex
${registerExtension} $INSTDIR\texstudio.exe ".tex" "tex File"

# Start Menu
createDirectory "$SMPROGRAMS\${APPNAME}"
createShortCut "$SMPROGRAMS\${APPNAME}\${APPNAME}.lnk" \
"$INSTDIR\texstudio.exe" "" ""

# Registry information for add/remove programs
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME} - ${DESCRIPTION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayIcon" "$\"$INSTDIR\logo.ico$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "Publisher" "$\"Benito van der Zander$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "HelpLink" "$\"${HELPURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLUpdateInfo" "$\"${UPDATEURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLInfoAbout" "$\"${ABOUTURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayVersion" "$\"${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}$\""
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "VersionMajor" ${VERSIONMAJOR}
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "VersionMinor" ${VERSIONMINOR}
	# There is no option for modifying or repairing the install
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "NoRepair" 1
 
SectionEnd

# Uninstaller
 
function un.onInit
	SetShellVarContext all
 
	#Verify the uninstaller - last chance to back out
	MessageBox MB_OKCANCEL "Permanently remove ${APPNAME}?" /SD IDOK IDOK next
		Abort
	next:
	#!insertmacro VerifyUserIsAdmin
functionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"

# Remove Start Menu launcher
delete "$SMPROGRAMS\${APPNAME}\${APPNAME}.lnk"
# Try to remove the Start Menu folder - this will only happen if it is empty
rmDir "$SMPROGRAMS\${APPNAME}"
 
# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

# remove file association
${unregisterExtension} ".tex" "tex File"
 
# now delete installed file
Delete $INSTDIR\*

# Try to remove the install directory - this will only happen if it is empty
rmDir $INSTDIR

# Remove uninstaller information from the registry
DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
 
SectionEnd
