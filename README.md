# HiraKata
This is a simple C++ program designed to help practice Hiragana and Katakana

To run:
Simply double click the .exe file

To compile:
In the Command Prompt terminal, run this command
g++ -static -static-libstdc++ -static-libgcc -municode -O2 -Wall -Wextra -o hirakata.exe hirakata.cpp -Wl,-subsystem,console

DISCLAIMER:
One limitation of this program is that the same character might appear more than once in the same quiz session. I'll fix this sometime soon.
