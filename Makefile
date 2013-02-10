# ï∂éöÉRÅ[ÉhÇÕÇrÇiÇhÇr â¸çsÉRÅ[ÉhÇÕÇbÇqÇkÇe
# $Id$

SDKDIR="C:\Program Files\Microsoft SDKs\Windows\v6.1"

CPPFLAGS=/I$(SDKDIR)\Include /EHsc
LDFLAGS=/LIBPATH:$(SDKDIR)\Lib
LDADD=user32.lib ole32.lib amstrmid.lib

all: mdsplayc.exe mdsplayg.exe

mdsplayc.exe: mdsplayc.obj
	link $(LDFLAGS) /OUT:$@ $** $(LDADD)

mdsplayc.obj: mdsplay.cpp
	cl $(CPPFLAGS) /c /DCONSOLE /Fo$@ $**

mdsplayg.exe: mdsplayg.obj
	link $(LDFLAGS) /OUT:$@ $** $(LDADD)

mdsplayg.obj: mdsplay.cpp
	cl $(CPPFLAGS) /c           /Fo$@ $**

clean:
	del mdsplayc.exe mdsplayc.obj mdsplayg.exe mdsplayg.obj
