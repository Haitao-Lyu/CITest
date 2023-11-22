@echo off
setlocal

echo %VS2022INSTALLDIR%
if "%VS2022INSTALLDIR%"=="" goto BADENV
call "%VS2022INSTALLDIR%\VC\Auxiliary\Build\vcvarsall.bat" x64

msbuild OilTycoonOceanOdyssey/playbuffer/OilTyrant.sln -m -t:Build -p:Configuration=Debug;Platform=x64
if %ERRORLEVEL% neq 0 call :BUILDFAIL
endlocal
echo "==BUILD OK=="
pause
exit 0

:BUILDFAIL
echo "==BUILD FAIL=="
endlocal
pause
exit 1

:BADENV
echo "VS2022INSTALLDIR was not found in environment variables"
echo This is typically set to something like "C:\Program Files\Microsoft Visual Studio\2022\Professional"
endlocal
pause
exit 2