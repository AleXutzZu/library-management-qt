cmake_minimum_required(VERSION 3.29)
project(OOP_Project_LibraryManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt6_add_resources(RESOURCES resources/resources.qrc)

add_executable(OOP_Project_LibraryManagement main.cpp
        repository/BasePublicationRepository.cpp
        repository/BasePublicationRepository.h
        model/Publication.cpp
        model/Publication.h
        model/Date.cpp
        model/Date.h
        model/Book.cpp
        model/Book.h
        model/Article.cpp
        model/Article.h
        controller/PublicationController.cpp
        controller/PublicationController.h
        repository/CsvPublicationRepository.cpp
        repository/CsvPublicationRepository.h
        model/UndoAction.cpp
        model/UndoAction.h
        ui/UserInterface.cpp
        ui/UserInterface.h
        ui/PublicationTableModel.cpp
        ui/PublicationTableModel.h
        ${RESOURCES}
)
target_link_libraries(OOP_Project_LibraryManagement
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()


add_subdirectory(tests)