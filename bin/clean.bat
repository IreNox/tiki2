﻿@echo off

del *.log

cd Bin32/

del *.exp
del *.ilk
del *.lib
del *.pdb

del TikiEditor*
del *.matagen
del *.config
rmdir /S /Q Content

cd ../Bin64

del *.exp
del *.ilk
del *.lib
del *.pdb

cd ../Data

rmdir /S /Q BinShader

cd ..

rmdir /S /Q Screenshots
