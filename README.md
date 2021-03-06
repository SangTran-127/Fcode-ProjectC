# Fcode-ProjectC
# Tiku Shopping 
Tiku Shopping is created based on GTK(GIMP ToolKit) is an open-source cross-platform widget toolkit for
creating graphical user interfaces (GUIs). 
To use Tiku Shopping, you need to install the GTK platform on your computer first,
then install CodeBlocks to run program with MSYS2.
There are various methods to install GTK on development machines.
Using MSYS2 which provides a UNIX-like environment for Windows to install GTK is one of our suggested ways.

1. Install MSYS2
Step 1: Download the installer: 
    http://repo.msys2.org/distrib/x86_64/msys2-x86_64-20190524.exe 
Step 2: Run the installer. Click "Next" until "Finish".
Step 3: Run msys2.exe in installation folder (C:\msys64)
Step 4: First run:  pacman -Syu
Step 5: Close msys2.exe, then open it again and run: pacman -Su
Step 6: Run: pacman -S mingw-w64-x86_64-gtk3
Step 7: Run: pacman -S mingw-w64-x86_64-toolchain base-devel
Step 8: When the program asks: Enter a selection (default=all)
        Press Enter.

2. Install CodeBlocks
Step 1: Download the installer: codeblocks-20-03-setup.exe
Step 2: Run the downloaded installer. 
        Accept the default options.