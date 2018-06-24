@echo off

echo. > out.txt

for /r %%i in (*.hpp *.cpp) do (
    if not "%%~ni" == "CMakeCXXCompilerId" (
        echo. >> out.txt
        echo //  >> out.txt
        echo // %%~dpnxi >> out.txt
        echo //  >> out.txt
        type "%%~fi" >> out.txt
        echo. >> out.txt
	)
)

pause