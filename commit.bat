@ECHO off
set /p "p=Message: "
git add .
git commit -m "%p%"