@echo off

del *.log

cd Bin32/

del *.exp
del *.ilk
del *.lib
del *.pdb
rem del Game32.exe
rem del TikiEngine.*.dll

del TikiEditor*
del *.matagen
del *.config
rmdir /S /Q Content

cd ../Bin64

del *.exp
del *.ilk
del *.lib
del *.pdb
rem del Game64.exe
rem del TikiEngine.*.dll

cd ../Data

rmdir /S /Q BinShader

cd ..

rmdir /S /Q Screenshots
