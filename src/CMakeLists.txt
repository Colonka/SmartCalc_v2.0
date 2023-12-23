cmake_minimum_required(VERSION 3.5)
project(s21_calc VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Задаем флаги компиляции
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -std=c++17
)
endif()

#Задааем переменную для тестирования и выключаем тестирование по дефолту
option(CALC_TESTING "Включить модульное тестирование" OFF)

#Задааем переменную для покрытия тестами и выключаем тестирование по дефолту
option(CALC_COVERAGE "Включить покрытие тестами" OFF)

#Задаем исходники модели
set(MODEL_SRC
    model/s21_calc_model.cpp
    model/s21_calc_model.h
)

#Создаем либу модели
add_library(
    s21_calc_lib_back
    STATIC
    ${MODEL_SRC}
)

if(CALC_TESTING) ### проверяем включено ли модульное тестирование 
    add_subdirectory(test) ### если да, то собираем тесты и покрытие при необходимости
else() ### если нет, то собираем проект
    message(STATUS "Тестирование проекта s21_calc выключено")
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    #Устанавливаем путь до компонентов Qt
    set(CMAKE_PREFIX_PATH "/Users/Anonymous/Qt/6.5.0/macos/lib/cmake")

    #Находим необходимые кьютишные пакеты
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

    #Задаем исходники контроллера
    set(CONTR_SRC
        controller/s21_calc_controller.h
    )

    #Задаем исходники интерфейса
    set(VIEW_SRC
        view/s21_calc_view.cpp
        view/s21_calc_view.h
        view/s21_calc_view.ui
    )

    #Создаем либу контроллера
    add_library(
        s21_calc_lib_contr
        STATIC
        ${CONTR_SRC}
    )

    #Создаем либу интерфейса
    add_library(
        s21_calc_lib_view
        STATIC
        ${VIEW_SRC}
    )

    #Подключаем либу qucustomplot
    add_subdirectory(QCustomPlot-library)

    #Создаем кьютишный таргет сборки
    qt_add_executable(s21_calc
        MANUAL_FINALIZATION
        main.cpp
    )

    #Говорим, что для либы вью нужна обязательна либа модели и контроллера, и что снаружи вью недоступны все методы бэка
    target_link_libraries(s21_calc_lib_view PRIVATE s21_calc_lib_back s21_calc_lib_contr)

    #Говорим, что для либы вью нужны обязательна либы кьюта, и что снаружи вью они недоступны
    target_link_libraries(s21_calc_lib_view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(s21_calc_lib_view PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

    #Говорим, что для таргета билда обязательна либа вью, и что снаружи ее методы недоступны
    target_link_libraries(s21_calc PRIVATE s21_calc_lib_view)

    #Говорим, что для таргета билда обязательна либа qcustomplot, и что снаружи ее методы недоступны
    target_link_libraries(s21_calc PRIVATE qcustomplot)

    set_target_properties(s21_calc PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    install(TARGETS s21_calc
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(s21_calc)
    endif()

endif()
