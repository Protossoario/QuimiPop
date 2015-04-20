# QuimiPop
HackMTY Project

## Important notes on using SDL
Before building and running the project, make sure to include SDL/glew by following the appropriate steps for each platform.

### Windows
Make sure to add the SDL and glew x86 runtime libraries (.dll files downloaded from their respective distributions) and add them to Debug folder on VS, or the directory containing the .EXE.

### OS X
Download the SDL developer files for Mac and install the .framework file by copying it to your Library/Frameworks directory. Don't forget to link the framework from Xcode in the Project->Build Phases tab.
