echo off
cls

echo d | xcopy /S /Y headers ..\headers
xcopy /Y main.c ..
xcopy /Y initialize.c ..
xcopy /Y data.c ..
xcopy /Y drawFunctions.c ..

cd ..


echo.
echo.
echo.

tcc -Werror -Wall -lSDL2 -o main.exe main.c data.c initialize.c drawFunctions.c

echo.
echo.
echo.

del main.c
del initialize.c
del data.c
del drawFunctions.c
rmdir /S /Q headers

xcopy /Y main.exe SDL_Game\

pause
