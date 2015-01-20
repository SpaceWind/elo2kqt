@echo off
echo Deploying... 0%%
rd release /S /Q >nul
md release >nul
cls
echo Deploying... 5%%
copy build\release\release\*.exe release\*.* >nul
cls
echo Deploying... 20%%
robocopy data release\data\ /S /E >nul
cls
echo Deploying... 50%%
robocopy build\libs release\ /S /E>nul
cls
echo Deploying...85%%
cd libs
for /r %%p in (*.dll) do (copy %%p ..\release\*.*) >nul
cls
echo Deploying... 100%%
cd ..
echo ready!
