@echo off

del *.log

cd Bin32/

del *.exp
del *.ilk
del *.lib
del *.pdb
del TikiEngine.*.dll

del TikiEditor*
del *.matagen
del *.config

cd ../Bin64

del *.exp
del *.ilk
del *.lib
del *.pdb
del TikiEngine.*.dll

cd ../Data

rmdir /S /Q BinShader