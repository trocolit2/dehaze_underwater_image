##################
## SOURCE CMAKE ##
##################

find_package(OpenCV REQUIRED)

add_library(dehaze_methods ImageEnhanceViaFusion.cpp)

set(SOURCE_LIBS_LOCAL dehaze_methods ${OpenCV_LIBS} )
set(SOURCE_LIBS ${SOURCE_LIBS_LOCAL} ${SOURCE_LIBS} PARENT_SCOPE)
