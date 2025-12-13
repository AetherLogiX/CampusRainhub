cmake_minimum_required(VERSION 3.16)
project(RainHub VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置CMake路径（如果未设置）
if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "E:/Qt/6.5.3/mingw_64" CACHE PATH "Qt安装路径")
endif()

# 查找Qt6（如果找不到则尝试Qt5）
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql Network)

# 设置Qt的MOC、UIC、RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Control
    ${CMAKE_CURRENT_SOURCE_DIR}/View
)

# 源文件
set(SOURCES
    main.cpp
    Model/User.cpp
    Model/Stationlocal.cpp
    Model/StationUtils.cpp
    Control/SystemManger.cpp
)

# 头文件
set(HEADERS
    Model/User.h
    Model/RainGear.hpp
    Model/RainGear_subclasses.hpp
    Model/RainGearFactory.h
    Model/GlobalEnum.hpp
    Model/Stationlocal.h
    Model/StationUtils.h
    Control/DBHelper.h
    Control/RainGearDAO.hpp
)

# 资源文件
set(RESOURCES
    rgear_icons/icons.qrc
    map_resources/map.qrc
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# 链接Qt库
target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

# Windows特定配置
if(WIN32)
    # MySQL库路径
    set(MYSQL_LIB_DIR "C:/Program Files/MySQL/MySQL Server 8.0/lib")
    set(MYSQL_DLL "${MYSQL_LIB_DIR}/libmysql.dll")
    
    # 链接MySQL库
    target_link_directories(${PROJECT_NAME} PRIVATE ${MYSQL_LIB_DIR})
    target_link_libraries(${PROJECT_NAME} libmysql)
    
    # 复制MySQL DLL到输出目录
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MYSQL_DLL}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    
    # 复制Qt的MySQL插件DLL（如果存在）
    get_target_property(QT_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake LOCATION)
    if(QT_QMAKE_EXECUTABLE)
        get_filename_component(QT_BIN_DIR ${QT_QMAKE_EXECUTABLE} DIRECTORY)
        get_filename_component(QT_PREFIX_DIR ${QT_BIN_DIR} DIRECTORY)
        set(QT_PLUGIN_DIR "${QT_PREFIX_DIR}/plugins/sqldrivers")
        set(QT_MYSQL_PLUGIN "${QT_PLUGIN_DIR}/qsqlmysql.dll")
        
        if(EXISTS "${QT_MYSQL_PLUGIN}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_MYSQL_PLUGIN}"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
            )
        endif()
    endif()
endif()

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Debug/Release配置
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX "d"
)

