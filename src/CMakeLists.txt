##################
## SOURCE CMAKE ##
##################

find_package(OpenCV REQUIRED core imgproc)

add_library(dehaze_methods SHARED ImageEnhanceViaFusion.cpp)
target_link_libraries(dehaze_methods ${OpenCV_LIBS})
set(HEADER_FILES ImageEnhanceViaFusion.hpp)

set(SOURCE_LIBS_LOCAL dehaze_methods ${OpenCV_LIBS} )
set(SOURCE_LIBS ${SOURCE_LIBS_LOCAL} ${SOURCE_LIBS} PARENT_SCOPE)

install(TARGETS dehaze_methods
  DESTINATION lib
)

install(FILES ${HEADER_FILES}
    DESTINATION include/${PROJECT_NAME}/
)
