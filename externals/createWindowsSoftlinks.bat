@echo off
echo Bitte mit Adminrechten im externals-Verzeichnis ausführen!

cd /D %~dp0

IF NOT EXIST %CD%"\..\EconomicEfficiencyCalculation\externals\IBK\" (
    echo Falsches Verzeichnis?
    pause
    exit /b 1
)

IF NOT EXIST %CD%\readme.md (
    echo Falsches Verzeichnis?
    pause
    exit /b 1
)

del /Q %CD%\IBK
mklink /d %CD%\IBK %CD%\"..\EconomicEfficiencyCalculation\externals\IBK\"

del /Q %CD%\TiCPP
mklink /d %CD%\TiCPP %CD%\"..\EconomicEfficiencyCalculation\externals\TiCPP\"

del /Q %CD%\Vicus
mklink /d %CD%\Vicus %CD%\"..\EconomicEfficiencyCalculation\externals\Vicus\"


del /Q %CD%\lib_x64
mklink /d %CD%\lib_x64 %CD%\"..\EconomicEfficiencyCalculation\externals\lib_x64\"


del /Q %CD%\IBKMK
mklink /d %CD%\IBKMK %CD%\"..\EconomicEfficiencyCalculation\externals\IBKMK\"


del /Q %CD%\sundials
mklink /d %CD%\sundials %CD%\"..\EconomicEfficiencyCalculation\externals\sundials\"

del /Q %CD%\DataIO
mklink /d %CD%\DataIO %CD%\"..\EconomicEfficiencyCalculation\externals\DataIO\"


del /Q %CD%\Nandrad
mklink /d %CD%\Nandrad %CD%\"..\EconomicEfficiencyCalculation\externals\Nandrad\"

del /Q %CD%\CCM
mklink /d %CD%\CCM %CD%\"..\EconomicEfficiencyCalculation\externals\CCM\"

del /Q %CD%\qwt
mklink /d %CD%\qwt %CD%\"..\EconomicEfficiencyCalculation\externals\qwt\"

del /Q %CD%\SuiteSparse
mklink /d %CD%\SuiteSparse %CD%\"..\EconomicEfficiencyCalculation\externals\SuiteSparse\"

cd.. cd..
del /Q %CD%\QtExt
mklink /d %CD%\QtExt %CD%\"..\EconomicEfficiencyCalculation\externals\QtExt\"

del /Q %CD%\sundials
mklink /d %CD%\sundials %CD%\"..\EconomicEfficiencyCalculation\externals\sundials\"
pause


