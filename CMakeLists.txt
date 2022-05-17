cmake_minimum_required(VERSION 3.16)

set(CMAKE_PROJECT_NAME qt6_cmake_translations)

project(${CMAKE_PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXXFLAGS} -D_CRT_SECURE_NO_WARNINGS")

find_package(Qt6 6.3.0 COMPONENTS Quick LinguistTools REQUIRED)

set(SOURCE_FILES
    src/main.cpp
)

set(QML_FILES
    qml/main.qml
    qml/Rect.qml
)

set(TS_FILES
    translations/app_en_US.ts
    translations/app_nl_NL.ts
)

add_custom_target(translations)
qt_add_lupdate(translations TS_FILES ${TS_FILES} SOURCES ${QML_FILES})
qt_add_lrelease(translations TS_FILES ${TS_FILES} QM_FILES_OUTPUT_VARIABLE qm_files)
add_dependencies(translations_lrelease translations_lupdate)

qt_add_executable(app${CMAKE_PROJECT_NAME}
    ${SOURCE_FILES}
)
add_dependencies(app${CMAKE_PROJECT_NAME} translations)

qt_add_resources(app${CMAKE_PROJECT_NAME} "translations"
    PREFIX "/i18n"
    BASE "${CMAKE_CURRENT_BINARY_DIR}"
    FILES "${qm_files}"
)

qt_add_qml_module(app${CMAKE_PROJECT_NAME}
    URI App
    VERSION 1.0
    RESOURCE_PREFIX /
    QML_FILES ${QML_FILES}
)

set_target_properties(app${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(app${CMAKE_PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_link_libraries(app${CMAKE_PROJECT_NAME}
    PRIVATE Qt6::Quick
)
