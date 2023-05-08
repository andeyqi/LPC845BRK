import os

if __name__ == '__main__':
    #If the gcc path environment variable is not set, add it as follows
    os.system("arm-none-eabi-objdump.exe  ..\Debug\lpc845breakout_hello_world.axf   -S  -a  > ..\Debug\lpc845breakout_hello_world_py.asm")