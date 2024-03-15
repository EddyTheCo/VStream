find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml )

qt_standard_project_setup()

add_library(utils include/utils.hpp src/utils.cpp)


target_link_libraries(utils PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)


target_include_directories(utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_definitions(utils PRIVATE WINDOWS_VSTREAM)

install(TARGETS utils 
    EXPORT ${PROJECT_NAME}-config
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT utils
)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
    COMPONENT utils
)
