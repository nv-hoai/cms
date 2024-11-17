cmake_minimum_required(VERSION 3.16)

project(prototype VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick Qml Gui QuickControls2 Svg Charts)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appPBL2
    main.cpp
    app.qrc
)

qt_add_qml_module(appPBL2
    URI prototype
    VERSION 1.0
    QML_FILES
        Main.qml
        TextButton.qml
        CustomPage.qml
        ComputerShow.qml
        ComputerChangeDialog.qml
        CustomerShow.qml
        EmployeeShow.qml
        CustomerAddDialog.qml
        CustomerChangeDialog.qml
        ImageButton.qml
        FoodShow.qml
        ServiceShow.qml
        ComputerAddDiaglog.qml
        EmployeeChangeDialog.qml
        EmployeeAddDialog.qml
        FoodChangeDialog.qml
        FoodAddDialog.qml
        ReceiptShow.qml
        ServiceChangeDialog.qml
        ServiceAddDialog.qml
        ReceiptAddDialog.qml
    SOURCES
        computer.h computer.cpp
        doublelinkedlist.h
        human.h human.cpp
        customer.h customer.cpp
        employee.h employee.cpp
        computermodel.h computermodel.cpp
        customermodel.h customermodel.cpp
        employeemodel.h employeemodel.cpp
        food.h food.cpp
        receipt.h receipt.cpp
        service.h service.cpp
        hirecomputer.h hirecomputer.cpp
        orderfood.h orderfood.cpp
        systemmanager.h systemmanager.cpp
        foodmodel.h foodmodel.cpp
        servicemodel.h servicemodel.cpp
        receiptmodel.h receiptmodel.cpp
        computerfiltermodel.h computerfiltermodel.cpp
        customerfiltermodel.h customerfiltermodel.cpp
        employeefiltermodel.h employeefiltermodel.cpp
        foodfiltermodel.h foodfiltermodel.cpp
        servicefiltermodel.h servicefiltermodel.cpp
    RESOURCES
        data/computer.txt
        data/customer.txt
        data/employee.txt
        data/food.txt
        data/service.txt
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPBL2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPBL2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appPBL2 PRIVATE .)

target_link_libraries(appPBL2 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::Svg
    Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appPBL2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
