# Microsoft Developer Studio Project File - Name="Thing" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Thing - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Thing.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Thing.mak" CFG="Thing - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Thing - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Thing - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Thing - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W4 /GX /Ot /Oi /Oy /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /Ow- /c
# SUBTRACT CPP /Ox /Oa /Og /Os
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386

!ELSEIF  "$(CFG)" == "Thing - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Thing - Win32 Release"
# Name "Thing - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Classes.cpp
# End Source File
# Begin Source File

SOURCE=.\gTools.cpp
# End Source File
# Begin Source File

SOURCE=.\Labirint.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFram.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Thing.cpp
# End Source File
# Begin Source File

SOURCE=.\Thing.rc
# End Source File
# Begin Source File

SOURCE=.\ThingDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ThingForm.cpp
# End Source File
# Begin Source File

SOURCE=.\World.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Classes.h
# End Source File
# Begin Source File

SOURCE=.\Const.h
# End Source File
# Begin Source File

SOURCE=.\gTools.h
# End Source File
# Begin Source File

SOURCE=.\Labirint.h
# End Source File
# Begin Source File

SOURCE=.\LevelDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFram.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SpeedDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Thing.h
# End Source File
# Begin Source File

SOURCE=.\ThingDoc.h
# End Source File
# Begin Source File

SOURCE=.\ThingForm.h
# End Source File
# Begin Source File

SOURCE=.\World.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Sounds"

# PROP Default_Filter "wav"
# Begin Source File

SOURCE=.\res\Sounds\ball.WAV
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Down1.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\F_Down.WAV
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Final.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\FruDown.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Ha.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Item1.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Mandead1.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Monster1.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Monster2.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Mus.wav
# End Source File
# Begin Source File

SOURCE=.\res\Sounds\Odead.wav
# End Source File
# End Group
# Begin Group "Pictures"

# PROP Default_Filter "bmp,wmf"
# Begin Group "Man"

# PROP Default_Filter "*.bmp"
# Begin Source File

SOURCE=.\res\Pictures\man1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\man11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\man12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\man13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\man2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\man3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\manF1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\manF2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\manF3.bmp
# End Source File
# End Group
# Begin Group "Inteface Images"

# PROP Default_Filter "*.bmp"
# Begin Group "Level Numbers"

# PROP Default_Filter "*.bmp"
# Begin Source File

SOURCE=.\res\Pictures\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\bmp52.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\bmp53.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\bmp54.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\bmp55.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\bmp56.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\level.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Pictures\Backgrnd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\Man.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\Title.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Pictures\Empty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\Fruit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pictures\Ground.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Pictures\Thing.ico
# End Source File
# Begin Source File

SOURCE=.\res\Thing.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ThingDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
