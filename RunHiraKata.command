#!/bin/bash
cd "$(dirname "$0")"
java -Dfile.encoding=UTF-8 -jar HiraKata.jar
read -p "Press Enter to exit..."
