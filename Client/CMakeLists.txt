find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Quick Qml )

qt_standard_project_setup()

qt_add_executable(client src/client.cpp)


qt6_add_qml_module(client
        URI  Esterv.StreamClient
        VERSION 1.0
        SOURCES
        src/mclient.cpp include/mclient.hpp
        QML_FILES
        "qml/client.qml"
        RESOURCE_PREFIX
        "/esterVtech.com/imports"
        IMPORT_PATH ${CMAKE_BINARY_DIR}
        OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Esterv/StreamClient
        )


target_link_libraries(client PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Network utils)

set_target_properties(client PROPERTIES
	WIN32_EXECUTABLE ON
	MACOSX_BUNDLE ON
	)

target_include_directories(client PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(TARGETS client
    BUNDLE  DESTINATION .
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
if(QTDEPLOY)
    qt_generate_deploy_qml_app_script(
        TARGET client
        OUTPUT_SCRIPT deploy_script
    )
install(SCRIPT ${deploy_script})
endif(QTDEPLOY)
