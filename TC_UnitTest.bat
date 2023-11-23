:: TeamCity Unit Test Script
@echo off
setlocal

call :RUNUNITTESTS x64 Debug 
call :RUNUNITTESTS x64 Release 

echo [42m
echo " BUILD OK "
echo [0m
endlocal
exit 0

:UNITFAIL
echo [41m
echo "!!UNIT TEST FAILED!! (%1 %2)"
echo [0m
endlocal
exit 1

:RUNUNITTESTS
echo "---- RUN UNIT TESTS (%1 %2) ----"
OilTycoonOceanOdyssey\playbuffer\%1\%2\UnitTest.exe ~[NoTC]
set TEST_RETURN_CODE=%errorlevel%
if %TEST_RETURN_CODE% neq 0 call :UNITFAIL %1 %2
endlocal
exit /b 0