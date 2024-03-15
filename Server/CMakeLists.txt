find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Quick Qml Multimedia)

qt_standard_project_setup()

qt_add_executable(server src/server.cpp)


qt6_add_qml_module(server
        URI  Esterv.StreamServer
        VERSION 1.0
        SOURCES
        src/mserver.cpp include/mserver.hpp
        QML_FILES
        "qml/server.qml"
        RESOURCE_PREFIX
        "/esterVtech.com/imports"
        IMPORT_PATH ${CMAKE_BINARY_DIR}
        OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Esterv/StreamServer
        )


target_link_libraries(server PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Network Qt6::Multimedia utils)

set_target_properties(server PROPERTIES
	WIN32_EXECUTABLE ON
	MACOSX_BUNDLE ON
	)

target_include_directories(server PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(TARGETS server
    BUNDLE  DESTINATION .
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
if(QTDEPLOY)
    qt_generate_deploy_qml_app_script(
        TARGET server
        OUTPUT_SCRIPT deploy_script
    )
install(SCRIPT ${deploy_script})
endif(QTDEPLOY)
