@echo off
cd release
for %%p in (*.exe) do (start %%p) >nul
cd ..