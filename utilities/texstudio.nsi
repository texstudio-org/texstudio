!define APPNAME "TeXstudio"
!define DESCRIPTION "TeXstudio is a fully featured LaTeX editor."
# These three must be integers
!define VERSIONMAJOR 4
!define VERSIONMINOR 5
!define VERSIONBUILD 3
# These will be displayed by the "Click here for support information" link in "Add/Remove Programs"
# It is possible to use "mailto:" links in here to open the email client
!define HELPURL "https://texstudio.org" # "Support Information" link
!define UPDATEURL "https://texstudio.org" # "Product Updates" link
!define ABOUTURL "https://texstudio.org" # "Publisher" link

!include "FileAssociation.nsh"

# Include Modern UI

!include "MUI2.nsh"

# define the name of the installer
Outfile "texstudio_installer.exe"

RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
InstallDir "$PROGRAMFILES\texstudio"

# Get installation folder from registry if available
InstallDirRegKey HKCU "Software\${APPNAME}" ""

ManifestDPIAware true

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

  ;Show all languages, despite user's codepage
  !define MUI_LANGDLL_ALLLANGUAGES

;--------------------------------
;Language Selection Dialog Settings

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "Software\${APPNAME}" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"


Name "${APPNAME}"

#page directory
#page instfiles
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English" ; The first language is the default language
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_LANGUAGE "German"
  !insertmacro MUI_LANGUAGE "Spanish"
  !insertmacro MUI_LANGUAGE "SpanishInternational"
  !insertmacro MUI_LANGUAGE "SimpChinese"
  !insertmacro MUI_LANGUAGE "TradChinese"
  !insertmacro MUI_LANGUAGE "Japanese"
  !insertmacro MUI_LANGUAGE "Korean"
  !insertmacro MUI_LANGUAGE "Italian"
  !insertmacro MUI_LANGUAGE "Dutch"
  !insertmacro MUI_LANGUAGE "Danish"
  !insertmacro MUI_LANGUAGE "Swedish"
  !insertmacro MUI_LANGUAGE "Norwegian"
  !insertmacro MUI_LANGUAGE "NorwegianNynorsk"
  !insertmacro MUI_LANGUAGE "Finnish"
  !insertmacro MUI_LANGUAGE "Greek"
  !insertmacro MUI_LANGUAGE "Russian"
  !insertmacro MUI_LANGUAGE "Portuguese"
  !insertmacro MUI_LANGUAGE "PortugueseBR"
  !insertmacro MUI_LANGUAGE "Polish"
  !insertmacro MUI_LANGUAGE "Ukrainian"
  !insertmacro MUI_LANGUAGE "Czech"
  !insertmacro MUI_LANGUAGE "Slovak"
  !insertmacro MUI_LANGUAGE "Croatian"
  !insertmacro MUI_LANGUAGE "Bulgarian"
  !insertmacro MUI_LANGUAGE "Hungarian"
  !insertmacro MUI_LANGUAGE "Thai"
  !insertmacro MUI_LANGUAGE "Romanian"
  !insertmacro MUI_LANGUAGE "Latvian"
  !insertmacro MUI_LANGUAGE "Macedonian"
  !insertmacro MUI_LANGUAGE "Estonian"
  !insertmacro MUI_LANGUAGE "Turkish"
  !insertmacro MUI_LANGUAGE "Lithuanian"
  !insertmacro MUI_LANGUAGE "Slovenian"
  !insertmacro MUI_LANGUAGE "Serbian"
  !insertmacro MUI_LANGUAGE "SerbianLatin"
  !insertmacro MUI_LANGUAGE "Arabic"
  !insertmacro MUI_LANGUAGE "Farsi"
  !insertmacro MUI_LANGUAGE "Hebrew"
  !insertmacro MUI_LANGUAGE "Indonesian"
  !insertmacro MUI_LANGUAGE "Mongolian"
  !insertmacro MUI_LANGUAGE "Luxembourgish"
  !insertmacro MUI_LANGUAGE "Albanian"
  !insertmacro MUI_LANGUAGE "Breton"
  !insertmacro MUI_LANGUAGE "Belarusian"
  !insertmacro MUI_LANGUAGE "Icelandic"
  !insertmacro MUI_LANGUAGE "Malay"
  !insertmacro MUI_LANGUAGE "Bosnian"
  !insertmacro MUI_LANGUAGE "Kurdish"
  !insertmacro MUI_LANGUAGE "Irish"
  !insertmacro MUI_LANGUAGE "Uzbek"
  !insertmacro MUI_LANGUAGE "Galician"
  !insertmacro MUI_LANGUAGE "Afrikaans"
  !insertmacro MUI_LANGUAGE "Catalan"
  !insertmacro MUI_LANGUAGE "Esperanto"
  !insertmacro MUI_LANGUAGE "Asturian"
  !insertmacro MUI_LANGUAGE "Basque"
  !insertmacro MUI_LANGUAGE "Pashto"
  !insertmacro MUI_LANGUAGE "ScotsGaelic"
  !insertmacro MUI_LANGUAGE "Georgian"
  !insertmacro MUI_LANGUAGE "Vietnamese"
  !insertmacro MUI_LANGUAGE "Welsh"
  !insertmacro MUI_LANGUAGE "Armenian"
  !insertmacro MUI_LANGUAGE "Corsican"
  !insertmacro MUI_LANGUAGE "Tatar"
  !insertmacro MUI_LANGUAGE "Hindi"

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

# sets $SMPROGRAMS to all users 
SetShellVarContext all

# define the output path for this file
SetOutPath $INSTDIR
 
# define what to install and place it in the output path
File texstudio.exe

File *.dll

SetOutPath $INSTDIR\platforms

File platforms\*

SetOutPath $INSTDIR\imageformats

File imageformats\*

SetOutPath $INSTDIR\styles

File styles\*

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
File /r utilities\manual\build\html\*

SetOutPath $INSTDIR\share\poppler
File /r utilities\poppler-data\*

SetOutPath $INSTDIR\share\fonts
File /r travis-ci\mxe\fonts\*

SetOutPath $INSTDIR\TexTablet
File utilities\TexTablet\*

SetOutPath $INSTDIR\dictionaries
File utilities\dictionaries\*.dic
File utilities\dictionaries\*.aff
File utilities\dictionaries\*.badWords
File utilities\dictionaries\*.stopWords
File utilities\dictionaries\*.stopWords.level2
File utilities\dictionaries\th_*_v2.dat

# Store installation folder
WriteRegStr HKCU "Software\${APPNAME}" "" $INSTDIR
# define uninstaller name
WriteUninstaller $INSTDIR\uninstall.exe

# associate .tex/.txss
${registerExtension} $INSTDIR\texstudio.exe ".tex" "tex File"
${registerExtension} $INSTDIR\texstudio.exe ".txss" "txs Session File"

# Start Menu
createShortCut "$SMPROGRAMS\${APPNAME}.lnk" \
"$INSTDIR\texstudio.exe" "" ""

# Registry information for add/remove programs
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayIcon" "$\"$INSTDIR\logo.ico$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "Publisher" "Benito van der Zander"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "HelpLink" "$\"${HELPURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLUpdateInfo" "$\"${UPDATEURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLInfoAbout" "$\"${ABOUTURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayVersion" "${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}"
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

# sets $SMPROGRAMS to all users 
SetShellVarContext all
	
# Remove Start Menu launcher
delete "$SMPROGRAMS\${APPNAME}.lnk"
 
# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

# remove file association
${unregisterExtension} ".tex" "tex File"
 
# now delete installed file
RMDir /r $INSTDIR\translations
RMDir /r $INSTDIR\templates
RMDir /r $INSTDIR\help
RMDir /r $INSTDIR\share
RMDir /r $INSTDIR\imageformats
RMDir /r $INSTDIR\platforms
RMDir /r $INSTDIR\styles
RMDir /r $INSTDIR\TexTablet
RMDir /r $INSTDIR\dictionaries
Delete $INSTDIR\*

# Try to remove the install directory - this will only happen if it is empty
RMDir $INSTDIR

# Remove uninstaller information from the registry
DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
DeleteRegKey /ifempty HKCU "Software\${APPNAME}"
 
SectionEnd
