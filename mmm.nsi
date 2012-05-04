!include "MUI2.nsh"

Name "Multi Minecraft Manager"
OutFile "mmm-install.exe"

InstallDir "$PROGRAMFILES\mmm"

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

Section
setOutPath $INSTDIR

file "build\libgcc_s_dw2-1.dll"
file "build\libstdc++-6.dll"
file "build\mingwm10.dll"
file "build\mmm.exe"
file "build\QtCore4.dll"
file "build\QtGui4.dll"


createShortCut "$SMPROGRAMS\Multi Minecraft Manager.lnk" \
        "$INSTDIR\mmm.exe"
createShortCut "$DESKTOP\Multi Minecraft Manager.lnk" \
        "$INSTDIR\mmm.exe"

# Uninstall info
writeUninstaller $INSTDIR\mmm-uninstall.exe
writeRegStr HKLM  \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\mmm" \
        "DisplayName" "Multi Minecraft Manager"
writeRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\mmm" \ 
        "UninstallString" "$INSTDIR\mmm-uninstall.exe"


SectionEnd

################

Section "Uninstall"

delete "$INSTDIR\libgcc_s_dw2-1.dll"
delete "$INSTDIR\libstdc++-6.dll"
delete "$INSTDIR\mingwm10.dll"
delete "$INSTDIR\mmm.exe"
delete "$INSTDIR\mmm-uninstall.exe"
delete "$INSTDIR\QtCore4.dll"
delete "$INSTDIR\QtGui4.dll"
delete "$INSTDIR"

delete "$SMPROGRAMS\Multi Minecraft Mangaer.lnk"
delete "$DESKTOP\Multi Minecraft Manager.lnk"
deleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\mmm"
SectionEnd
