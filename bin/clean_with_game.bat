@echo off

call clean.bat

cd Bin32

del Game32.exe
del TikiEngine.*.dll

cd ../Bin64

del Game64.exe
del TikiEngine.*.dll