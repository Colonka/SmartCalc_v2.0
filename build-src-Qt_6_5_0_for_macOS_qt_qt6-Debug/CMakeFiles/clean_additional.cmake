# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/s21_calc_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/s21_calc_autogen.dir/ParseCache.txt"
  "CMakeFiles/s21_calc_lib_contr_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/s21_calc_lib_contr_autogen.dir/ParseCache.txt"
  "CMakeFiles/s21_calc_lib_view_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/s21_calc_lib_view_autogen.dir/ParseCache.txt"
  "QCustomPlot-library/lib/CMakeFiles/qcustomplot_autogen.dir/AutogenUsed.txt"
  "QCustomPlot-library/lib/CMakeFiles/qcustomplot_autogen.dir/ParseCache.txt"
  "QCustomPlot-library/lib/qcustomplot_autogen"
  "s21_calc_autogen"
  "s21_calc_lib_contr_autogen"
  "s21_calc_lib_view_autogen"
  )
endif()
