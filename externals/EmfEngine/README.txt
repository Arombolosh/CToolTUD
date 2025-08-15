EmfEngine Commercial
------------------------
AUTHOR: Ion Vasilief
------------------------
FEATURES:  EmfEngine enables Qt based applications to easily export graphics created using the 
	QPainter class to the Enhanced MetaFile format (EMF) or to the Windows Metafile format (WMF).
---------------------------------------------------------------------------
DEPENDENCIES: You need Qt (http://qt-project.org) installed on your system in order to build EmfEngine.
---------------------------------------------------------------------------
COMPILING: EmfEngine uses qmake for the building process. qmake is part of a Qt distribution. 
	qmake reads project files (ending with the  "*.pro" suffix) that contain the options and rules how to build a certain project. 
	Please read the qmake documentation for more details.

After installing Qt on your system, type the following command lines: 

	$ qmake
	$ make

if you use MinGW, or:

	$ qmake -tp vc -r

if you use Microsoft Visual Studio (this will generate Visual Studio .vcproj project files in the "src" and "example" folders).
---------------------------------------------------------------------------
USE: a short demo application is provided in the "example" folder of the source archive.
