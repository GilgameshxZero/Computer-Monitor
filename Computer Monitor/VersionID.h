#pragma once
#include "VersionBuildInc.h"

#define SVN_LOCAL_MODIFICATIONS $WCMODS?1:0$  // 1 if there are modifications to the local working copy, 0 otherwise
#define SVN_REVISION            $WCREV$       // Highest committed revision number in the working copy
#define SVN_TIME_NOW            $WCNOW$       // Current system date &amp; time

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define VERSION_MAJOR            3
#define VERSION_MINOR            0
#define VERSION_REVISION         0
#define VERSION_BUILD            BUILD_INCREMENT

#define VER_FILE_DESCRIPTION_STR "Computer Monitor"
#define VER_FILE_VERSION         VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR     STRINGIZE(VERSION_MAJOR)     \
                                    "." STRINGIZE(VERSION_MINOR) \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD) \

#define VER_PRODUCTNAME_STR      VER_FILE_DESCRIPTION_STR
#define VER_PRODUCT_VERSION      VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR  VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR    VER_ORIGINAL_FILENAME_STR
#define VER_COPYRIGHT_STR        "Copyright by Yang Yan"

#ifdef _DEBUG
#define VER_VER_DEBUG          VS_FF_DEBUG
#else
#define VER_VER_DEBUG          0
#endif

#define VER_FILEOS               VOS_NT_WINDOWS32
#define VER_FILEFLAGS            VER_VER_DEBUG
#define VER_FILETYPE             VFT_APP
