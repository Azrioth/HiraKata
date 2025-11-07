@echo off
:: Set UTF-8 so kana display properly
chcp 65001 >nul

:: Change directory to where this script is
cd /d "%~dp0"

:: Run the jar
java -Dfile.encoding=UTF-8 -jar HiraKata.jar

:: Keep window open
pause
