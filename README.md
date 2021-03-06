# Fcode-ProjectC
# Tiku Shopping 
Tiku Shopping is created based on GTK(GIMP ToolKit) is an open-source cross-platform widget toolkit for
creating graphical user interfaces (GUIs). 
To use Tiku Shopping, you need to install the GTK platform on your computer first,
then install CodeBlocks to run program with MSYS2.
There are various methods to install GTK on development machines.
Using MSYS2 which provides a UNIX-like environment for Windows to install GTK is one of our suggested ways.

# HOW TO INSTALL GTK3 
1. Install MSYS2
    * Step 1: Download the installer: 
    http://repo.msys2.org/distrib/x86_64/msys2-x86_64-20190524.exe 
    * Step 2: Run the installer. Click "Next" until "Finish".
    * Step 3: Run msys2.exe in installation folder (C:\msys64)
    * Step 4: First run:  pacman -Syu
    * Step 5: Close msys2.exe, then open it again and run: pacman -Su
    * Step 6: Run: pacman -S mingw-w64-x86_64-gtk3
    * Step 7: Run: pacman -S mingw-w64-x86_64-toolchain base-devel
    * Step 8: When the program asks: Enter a selection (default=all)
        Press Enter.

2. Install CodeBlocks
    * Step 1: Download the installer: codeblocks-20-03-setup.exe
    * Step 2: Run the downloaded installer. 
        Accept the default options.
3. Set up GTK library into CodeBlocks to compile 
    * Step 1: Open CodeBlocks -> Compiler settings -> Linker settings -> Other linker options
     Copy *`pkg-config --libs gtk+-3.0`* and Paste into Other linker options
    * Step 2: Compiler settings -> Search directories 
     Copy and add these lines
        * C:\msys64\mingw64\include\gtk-3.0
        * C:\msys64\mingw64\include\glib-2.0
        * C:\msys64\mingw64\include\harfbuzz
        * C:\msys64\mingw64\lib\glib-2.0\include
        * C:\msys64\mingw64\include\pango-1.0
        * C:\msys64\mingw64\include\cairo
        * C:\msys64\mingw64\include\gdk-pixbuf-2.0
        * C:\msys64\mingw64\include\atk-1.0
    * Step 3: Compiler -> Toolchain executables -> Compiler's installation directory
     Change the directory to complie by Copy *C:\msys64\mingw64* and Paste into **Compiler's installation directory**
     <space><space>
# ABOUT TIKU 
   Tiku Shopping is created based on GTK so it quite visual and easy to interact and
   it owns the basic features of sales software such as register, login, buys, sells, deletes...
    There are some pages about Tiku:
![landing-page](https://scontent.xx.fbcdn.net/v/t1.15752-0/p403x403/157286771_465619201147936_1269036079253581960_n.png?_nc_cat=111&ccb=1-3&_nc_sid=aee45a&_nc_ohc=Dsa56UCXlCsAX9T3A-F&_nc_ad=z-m&_nc_cid=0&_nc_ht=scontent.xx&_nc_tp=30&oh=7c2760f3d1d4f3c51d067dec3f81f4d0&oe=60680154)
    
   Register page: 
   ![register](https://scontent-xsp1-2.xx.fbcdn.net/v/t1.15752-9/156672158_2844349535884843_2310462908160987914_n.png?_nc_cat=102&ccb=1-3&_nc_sid=ae9488&_nc_ohc=ZdNnUMElWdkAX_OMScl&_nc_ht=scontent-xsp1-2.xx&oh=faf32fbab597fc4e920087b30fc7c27f&oe=606ADE43)
   
   Shopping page:
   ![shopping](https://scontent-xsp1-2.xx.fbcdn.net/v/t1.15752-9/154993359_254786026146072_7907272442281241891_n.png?_nc_cat=104&ccb=1-3&_nc_sid=ae9488&_nc_ohc=lJwjviM3dz8AX_GfAYb&_nc_ht=scontent-xsp1-2.xx&oh=8160d4be3389f9364464805eb6c53a7c&oe=6044A37C)
   # CONTRIBUTORS: 
   1. Thu Trang Le: <https://github.com/Nabilee1703>
   2. Truong Le Tuan Kiet: <https://github.com/zhangliejunjie>
   3. Tran Quang Sang: <https://github.com/SangTran-127>
   #SOURCES:
   <https://developer.gnome.org/gtk3/stable>
