# BacklightFix for Xiaomi Vayu
This C program, wonderfully written by ChatGPT, multiplies the brightness of the screen by 16 if it's modified, to counter the effect of the low brightness limit on Droidian 100.
It needs root (sudo) permissions to run.

## Running
In the folder of the application, do `sudo ./brightnessfix`.

NOTE: It'll use about 1% of the CPU when idle, and ~10% when actively changing the brightness.

## Compiling (if you want to modify or optimize it)
Dependencies are `build-essential` (`sudo apt install build-essential`).
To compile, do `gcc -o brightnessfix brightnessfix.c`
