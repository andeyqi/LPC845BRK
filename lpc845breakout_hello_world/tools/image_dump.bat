@echo off

SET BUILD_OUTPUT_DIR=..\Debug
SET BUIND_EXE_NAME=lpc845breakout_hello_world

SET GNU_BUIDLD_INS_DIR=D:\work\gcc-arm-none-eabi-10.3-2021.10\bin
SET PATH=%PATH%;%READ_ELF_INS_DIR%

arm-none-eabi-objdump.exe  %BUILD_OUTPUT_DIR%\%BUIND_EXE_NAME%.axf   -S  -a  > %BUILD_OUTPUT_DIR%\%BUIND_EXE_NAME%.asm
