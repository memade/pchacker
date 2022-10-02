@echo off
echo Start compiling the project preparation.

set SOLUTIONNAME=pcdown
set SOLUTIONDIR=%~dp0..\..\
set PROJECTDIR=%SolutionDir%%SOLUTIONNAME%\
set TOOLSDIR=%SolutionDir%..\tools\

echo Project name is '%SOLUTIONNAME%'
echo %SOLUTIONDIR%
echo %PROJECTDIR%
echo %TOOLSDIR%

del /F /S /Q %PROJECTDIR%\res\setup.xml.res.h
call %TOOLSDIR%encryption.exe 9 %PROJECTDIR%\res\setup.xml %PROJECTDIR%\res\setup.xml.res
del /F /S /Q %PROJECTDIR%\res\setup.xml.res

del /F /S /Q %PROJECTDIR%\res\skin.zip.res.h
call %TOOLSDIR%compress.exe %PROJECTDIR%\res\skin %PROJECTDIR%\res\skin.zip
call %TOOLSDIR%encryption.exe 9 %PROJECTDIR%\res\skin.zip %PROJECTDIR%\res\skin.zip.res
del /F /S /Q %PROJECTDIR%\res\skin.zip
del /F /S /Q %PROJECTDIR%\res\skin.zip.res

echo copy src'pcdonw.hpp' to external projects
xcopy %PROJECTDIR%\pcdown.hpp %~d0\__Codeup.Aliyun.Com__\Martell\projects\gamebox\gamebox-2021-final\include\ /Y
xcopy %PROJECTDIR%\pcdown.hpp %~d0\__Codeup.Aliyun.Com__\Martell\projects\gamebox\client\client\Project.Shared\pcdown\ /Y