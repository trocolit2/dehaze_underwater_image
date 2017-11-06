cmake_minimum_required(VERSION 2.8)
project( dehaze_underwater_image-DUI )
find_package( OpenCV 2.4 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB viso
    "src/*.h"
    "src/*.cpp"
)
add_executable( dui ${viso} )
target_link_libraries( dui ${OpenCV_LIBS} )
