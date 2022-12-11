/*

 mmm   mm    mmmm    mmmmmmmm   mmmmmm      mmmm   mmmmmmmm
 ###   ##   ##""##   """##"""   ""##""    ##""""#  ##""""""
 ##"#  ##  ##    ##     ##        ##     ##"       ##
 ## ## ##  ##    ##     ##        ##     ##        #######
 ##  #m##  ##    ##     ##        ##     ##m       ##
 ##   ###   ##mm##      ##      mm##mm    ##mmmm#  ##mmmmmm
 ""   """    """"       ""      """"""      """"   """"""""

 * This is a dummy file.
     The real device's memory map is putting under:
        Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c

 * This file will be over-written while compiling.
     You can check build_uefi.sh for details:
       ```
       cp Platforms/SurfaceDuo1Pkg/Device/${TARGET_DEVICE}/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.c \
                Platforms/SurfaceDuo1Pkg/Library/PlatformMemoryMapLib/

       stuart_build -c Platforms/SurfaceDuo1Pkg/PlatformBuild.py TOOL_CHAIN_TAG=CLANG38 "TARGET_DEVICE=${TARGET_DEVICE}"
       ```



*/
