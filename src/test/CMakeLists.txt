include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

### Проверяем если включено покрытие тестами(gcov), то добавляем флаг компиляции
if(CALC_COVERAGE)
add_compile_options("--coverage")
add_link_options("--coverage")
endif()

### Компилируем исполняемый файл
add_executable(
    s21_calc_test
    test.cpp
)

### Линкуем к исполняемому файлу либу модели и либу GTest
target_link_libraries(s21_calc_test PRIVATE s21_calc_lib_back GTest::gtest_main)

### Линкуем GTets
gtest_discover_tests(s21_calc_test)

### Создаем команду для запуска тестов
add_custom_target(check COMMAND s21_calc_test)

### Находим gcovr
find_program(GCOVR_EXECUTABLE gcovr)
if(CALC_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

### При включении покрытия тестами добавляем флаг компиляции к либе модели
    target_compile_options(s21_calc_lib_back PRIVATE --coverage)

### Создаем команду для запуска анализа покрытия тестами
    add_custom_target(coverage
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${CMAKE_SOURCE_DIR}/model # указываем папку с анализируемыми исходниками
                --object-directory=${CMAKE_BINARY_DIR} # указываем папку с бинарниками
                --html --html-details -o ${CMAKE_SOURCE_DIR}/report/report.html # просим создать отчет в HTML
        DEPENDS # говорим, что данная цель зависит от команды check
            check
    )
elseif(MYLIB_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(MYLIB_COVERAGE OFF)
    message(WARNING "Для замеров покрытия кода тестами требуется программа gcovr")
endif()