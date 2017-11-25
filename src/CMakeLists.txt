cmake_minimum_required(VERSION 2.8.12)
project(RunnerSkypeforlinux)

find_package(ECM 5.12.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

find_package (Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core Quick)
find_package (KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Service Runner TextWidgets PlasmaQuick)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(krunner_skype_SRCS
    skype.cpp
)

add_library(krunner_skype MODULE ${krunner_skype_SRCS})
target_link_libraries(krunner_skype KF5::Runner Qt5::Widgets
                      KF5::I18n
                      KF5::Service
                      KF5::Plasma)
                      
install(TARGETS krunner_skype DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-skype.desktop DESTINATION ${SERVICES_INSTALL_DIR})
