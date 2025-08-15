# Project for C-Tool-Converter session and all its libraries

TEMPLATE=subdirs

# SUBDIRS lists all subprojects
SUBDIRS += \
	IBK \
	IBKMK \
	TiCPP \
	QtExt \
	Nandrad \
	#Vicus \
	sundials \
	SuiteSparse \
	CToolImporter \
	CToolConverter \
	NandradCodeGenerator

# where to find the sub projects
CToolConverter.file = CToolConverter/CToolConverter.pro

# where to find the sub projects
IBK.file = externals/IBK/IBK.pro
IBKMK.file = externals/IBKMK/IBKMK.pro
Nandrad.file = externals/Nandrad/Nandrad.pro
TiCPP.file = externals/TiCPP/TiCPP.pro
#Vicus.file = externals/Vicus/Vicus.pro
sundials.file = externals/sundials/sundials.pro
SuiteSparse.file = externals/SuiteSparse/SuiteSparse.pro
CToolImporter.file = externals/CToolImporter/CToolImporter.pro
NandradCodeGenerator.file = NandradCodeGenerator/NandradCodeGenerator.pro
QtExt.file = externals/QtExt/QtExt.pro


# dependencies
CToolConverter.depends = Nandrad CToolImporter IBK IBKMK TiCPP #Vicus

NandradCodeGenerator.depends = IBK Nandrad QtExt TiCPP
QtExt.depends = IBK IBKMK
Nandrad.depends = IBK TiCPP IBKMK
#Vicus.depends = IBK TiCPP Nandrad IBKMK DataIO CCM glm
IBKMK.depends = IBK sundials
sundials.depends = SuiteSparse
TiCPP.depends = IBK
CToolImporter.depends = IBK IBKMK #Vicus




