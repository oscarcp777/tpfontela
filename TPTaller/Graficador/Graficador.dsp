# Microsoft Developer Studio Project File - Name="Graficador" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Graficador - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Graficador.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Graficador.mak" CFG="Graficador - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Graficador - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Graficador - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Graficador - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "D:\oscarfacu\VC98\SDL-1.2.13\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x2c0a /d "NDEBUG"
# ADD RSC /l 0x2c0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SDLmain.lib SDL.lib /nologo /subsystem:console /machine:I386 /libpath:"D:\oscarfacu\VC98\SDL-1.2.13\lib"

!ELSEIF  "$(CFG)" == "Graficador - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "D:\oscarfacu\VC98\SDL-1.2.13\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x2c0a /d "_DEBUG"
# ADD RSC /l 0x2c0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SDLmain.lib SDL.lib SDL_mixer.lib SDL_ttf.lib SDL_image.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"D:\oscarfacu\VC98\SDL-1.2.13\lib"

!ENDIF 

# Begin Target

# Name "Graficador - Win32 Release"
# Name "Graficador - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\TP2\archivoTexto.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Circulo.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Cuadrado.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Escenario.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Figura.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\main.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Posicion.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Rectangulo.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Segmento.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\TP2\Validador.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\TP2\archivoTexto.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Circulo.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Cuadrado.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Escenario.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Figura.h
# End Source File
# Begin Source File

SOURCE=.\gp.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Posicion.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Rectangulo.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Segmento.h
# End Source File
# Begin Source File

SOURCE=..\TP2\StringUtils.h
# End Source File
# Begin Source File

SOURCE=..\TP2\Validador.h
# End Source File
# End Group
# End Target
# End Project
