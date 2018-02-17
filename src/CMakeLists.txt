macro(prepend listVar prefix)
   set(${listVar} "")
   foreach(item ${ARGN})
      list(APPEND ${listVar} ${prefix}${item})
   endforeach(item)
endmacro(prepend)

set(tloqtnetcat_core_headers qtnetcatmodel.hpp qtnetcatguiview.hpp qtnetcatcliview.hpp)
set(tloqtnetcat_core_sources qtnetcatmodel.cpp qtnetcatguiview.cpp qtnetcatcliview.cpp)
prepend(tloqtnetcat_core_headers tlo/ ${tloqtnetcat_core_headers})
add_library(tloqtnetcat_core STATIC ${tloqtnetcat_core_headers} ${tloqtnetcat_core_sources})
target_include_directories(tloqtnetcat_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tloqtnetcat_core PUBLIC Qt5::Network Qt5::Widgets)

add_executable(tloqtnetcatgui tloqtnetcatgui.cpp)
target_link_libraries(tloqtnetcatgui PRIVATE tloqtnetcat_core)

add_executable(tloqtnetcat tloqtnetcat.cpp)
target_link_libraries(tloqtnetcat PRIVATE tloqtnetcat_core)
