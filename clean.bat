@echo off
del *.o /s /Q >nul
rd release /S /Q >nul
rd build\release /S /Q >nul
rd build\debug /S /Q >nul
md build\debug >nul
md build\release >nul
del *.exe /S /Q >nul
md release >nul