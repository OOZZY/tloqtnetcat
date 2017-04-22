qt5_wrap_ui(uiheaders qtnetcatguiview.ui)
add_library(tloqtnetcatcore STATIC qtcrapnetcat.cpp qtnetcatmodel.cpp ${uiheaders} qtnetcatguiview.cpp qtnetcatcliview.cpp)
# linking to Qt5::<module> causes cmake to use the appropriate include
# directories and compile definitions needed to use Qt <module> when building
# the target
target_link_libraries(tloqtnetcatcore Qt5::Network Qt5::Widgets ${CMAKE_THREAD_LIBS_INIT})
