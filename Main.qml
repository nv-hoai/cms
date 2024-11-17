import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

ApplicationWindow {
    id: mainWindow
    width: Screen.width
    height: Screen.height
    visible: true
    title: "prototype"
    color: "white"

    property int selectedItemIndex: -1

    ComputerAddDiaglog {
        id: computerAddDialog
    }

    CustomerAddDialog {
        id: customerAddDialog
    }

    EmployeeAddDialog {
        id: employeeAddDialog
    }

    ServiceAddDialog {
        id: serviceAddDialog
    }

    FoodAddDialog {
        id: foodAddDialog
    }

    ReceiptAddDialog {
        id: receiptAddDialog
    }

    ComputerChangeDialog {
        id: computerChangeDialog
    }

    CustomerChangeDialog {
        id: customerChangeDialog
    }

    EmployeeChangeDialog {
        id: employeeChangeDialog
    }

    ServiceChangeDialog {
        id: serviceChangeDialog
    }

    FoodChangeDialog {
        id: foodChangeDialog
    }

    signal receiveComputerData(string cpu, int ram, int position, int status, int cost)
    signal receiveCustomerData(string firstName, string lastName, int age, bool gender)
    signal receiveEmployeeData(string firstName, string lastName, int age, bool gender,
                               string position, int workedDays, string timeWork, real baseSalary)
    signal receiveServiceData(string serviceName, int customerId, int computerId, int timeUse,
                              int foodId, int numberOrdered)
    signal receiveFoodData(string name, int remain, int cost, string imageSource)
    signal receiveReceiptData(int customerId)
    signal updateComputerData(int index, string cpu, int ram, int position, int status, int cost)
    signal updateCustomerData(int index, string firstName, string lastName, int age, bool gender)
    signal updateEmployeeData(int index, string firstName, string lastName, int age, bool gender,
                              string position, int workedDays, string timeWork, real baseSalary)
    signal updateServiceData(int index, string serviceName, int customerId, int computerId, int timeUse,
                             int foodId, int numberOrdered)
    signal updateFoodData(int index, string name, int remain, int cost, string imageSource)

    onReceiveComputerData: (cpu, ram, position, status, cost) => {
        SystemManager.computerModel.add(cpu, ram, position, status, cost);
    }

    onReceiveCustomerData: (firstName, lastName, age, gender) => {
        SystemManager.customerModel.add(firstName, lastName, age, gender);
    }

    onReceiveEmployeeData: (firstName, lastName, age, gender, position, workedDays, timeWork, baseSalary) => {
        SystemManager.employeeModel.add(firstName, lastName, age, gender, position, workedDays, timeWork, baseSalary);
    }

    onReceiveServiceData: (serviceName, customerId, computerId, timeUse, foodId, numberOrdered) => {
        if (serviceName == "Hire computer")
            SystemManager.serviceModel.addHireComputer(serviceName, SystemManager.customerModel.getCustomer(customerId),
                                                  SystemManager.computerModel.getComputer(computerId), timeUse);
        if (serviceName == "Order food")
            SystemManager.serviceModel.addOrderFood(serviceName, SystemManager.customerModel.getCustomer(customerId),
                                                  SystemManager.foodModel.getFood(foodId), numberOrdered);
    }

    onReceiveFoodData: (name, remain, cost, imageSource) => {
        SystemManager.foodModel.add(name, remain, cost, imageSource);
    }

    onReceiveReceiptData: (customerId) => {
        SystemManager.createReceipt(customerId);
    }

    onUpdateComputerData: (index, cpu, ram, position, status, cost) => {
        SystemManager.computerModel.setCpu(index, cpu);
        SystemManager.computerModel.setRam(index, ram);
        SystemManager.computerModel.setPosition(index, position);
        SystemManager.computerModel.setStatus(index, status);
        SystemManager.computerModel.setCost(index, cost);
    }

    onUpdateCustomerData: (index, firstName, lastName, age, gender) => {
        SystemManager.customerModel.setCustomerFirstName(index, firstName);
        SystemManager.customerModel.setCustomerLastName(index, lastName);
        SystemManager.customerModel.setCustomerAge(index, age);
        SystemManager.customerModel.setCustomerGender(index, gender);
    }

    onUpdateEmployeeData: (index, firstName, lastName, age, gender, position, workedDays, timeWork, baseSalary) => {
        SystemManager.employeeModel.setEmployeeFirstName(index, firstName);
        SystemManager.employeeModel.setEmployeeLastName(index, lastName);
        SystemManager.employeeModel.setEmployeeAge(index, age);
        SystemManager.employeeModel.setEmployeeGender(index, gender);
        SystemManager.employeeModel.setPosition(index, position);
        SystemManager.employeeModel.setWorkedDays(index, workedDays);
        SystemManager.employeeModel.setTimeWork(index, timeWork);
        SystemManager.employeeModel.setBaseSalary(index, baseSalary);
    }

    onUpdateServiceData: (index, serviceName, customerId, computerId, timeUse, foodId, numberOrdered) => {
        SystemManager.serviceModel.setServiceName(index, serviceName);
        SystemManager.serviceModel.setCustomer(index, SystemManager.customerModel.getCustomer(customerId));
        if (serviceName == "Hire computer") {
            SystemManager.serviceModel.setComputer(index, SystemManager.computerModel.getComputer(computerId));
            SystemManager.serviceModel.setTimeUse(index, timeUse);
        }
        if (serviceName == "Order food") {
            SystemManager.serviceModel.setFood(index, SystemManager.foodModel.getFood(foodId));
            SystemManager.serviceModel.setNumberOrdered(index, numberOrdered);
        }
    }

    onUpdateFoodData: (index, name, remain, cost, imageSource) => {
        SystemManager.foodModel.setName(index, name);
        SystemManager.foodModel.setRemain(index, remain);
        SystemManager.foodModel.setCost(index, cost);
        SystemManager.foodModel.setImageSource(index, imageSource);
    }

    RowLayout {
        id: toolBar
        Layout.fillWidth: true
        Layout.minimumHeight: logo.implicitHeight

        Rectangle {
            id: logo
            implicitWidth: 50
            implicitHeight: 50
            color: "black"
            Text {
                anchors.centerIn: parent
                text: "CMS"
                font.pixelSize: 24
                font.weight: 40
                color: "white"
            }
        }

        Text {
            Layout.fillWidth: true
            text: "Cybercafe Management System"
            color: "black"
            font.pixelSize: 16
            font.weight: 40
        }
    }

    RowLayout {
        anchors.top: toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 0

        Rectangle {
            id: sideBarBackground
            implicitWidth: 300
            Layout.fillHeight: true
            color: "white"

            ColumnLayout {
                id: sideBar
                anchors.fill: parent
                spacing: 0

                TextButton {
                    text: "Computers"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 0
                    }
                }

                TextButton {
                    text: "Customers"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 1
                    }
                }

                TextButton {
                    text: "Employees"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 2
                    }
                }

                TextButton {
                    text: "Foods"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 3
                    }
                }

                TextButton {
                    text: "Services"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 4
                    }
                }


                TextButton {
                    text: "Receipts"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 5
                    }
                }


                TextButton {
                    text: "Analysis"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 6
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                TextButton {
                    text: "Settings"
                    Layout.fillWidth: true
                    implicitHeight: sideBar.width/6
                    mouseArea.onClicked: {
                        swipeView.currentIndex = 7
                    }
                }
            }
        }

        SwipeView {
            id: swipeView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            currentIndex: 0
            interactive: false

            Component.onCompleted: contentItem.highlightMoveDuration = 0;


            CustomPage {
                id: computerPage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Computer Management"
                headerDetails: "List of computer:"
                gridModel: SystemManager.computerFilterModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: 110
                gridDelegate: ComputerShow {}
                pagePadding: 16

                searchBar.onTextChanged: {
                    SystemManager.computerFilterModel.filterText = searchBar.text
                }

                newMouseArea.onClicked: {
                    computerAddDialog.open();
                }

                saveMouseArea.onClicked: {
                    SystemManager.saveComputerData();
                }
            }


            CustomPage {
                id: customerPage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Customer Management"
                headerDetails: "List of customers:"
                gridModel: SystemManager.customerFilterModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: 110
                gridDelegate: CustomerShow {}
                pagePadding: 16

                searchBar.onTextChanged: {
                    SystemManager.customerFilterModel.filterText = searchBar.text
                }

                newMouseArea.onClicked: {
                    customerAddDialog.open();
                }
            }

            CustomPage {
                id: employeePage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Employee Management"
                headerDetails: "List of employees:"
                gridModel: SystemManager.employeeFilterModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: 120
                gridDelegate: EmployeeShow {}
                pagePadding: 16

                searchBar.onTextChanged: {
                    SystemManager.employeeFilterModel.filterText = searchBar.text
                }

                newMouseArea.onClicked: {
                    employeeAddDialog.open();
                }
            }

            CustomPage {
                id: foodPage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Food Management"
                headerDetails: "List of foods:"
                gridModel: SystemManager.foodFilterModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: 110
                gridDelegate: FoodShow {}
                pagePadding: 16

                searchBar.onTextChanged: {
                    SystemManager.foodFilterModel.filterText = searchBar.text
                }

                newMouseArea.onClicked: {
                    foodAddDialog.open();
                }
            }

            CustomPage {
                id: servicePage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Service Management"
                headerDetails: "List of services:"
                gridModel: SystemManager.serviceFilterModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: 110
                gridDelegate: ServiceShow {}
                pagePadding: 16

                searchBar.onTextChanged: {
                    SystemManager.serviceFilterModel.filterText = searchBar.text
                }

                newMouseArea.onClicked: {
                    serviceAddDialog.open();
                }
            }


            CustomPage {
                id: receiptPage
                Layout.fillWidth: true
                Layout.fillHeight: true
                headerText: "Receipt Management"
                headerDetails: "List of receipts:"
                gridModel: SystemManager.receiptModel
                gridCellWidth: swipeView.width/3+swipeView.width/9
                gridCellHeight: gridCellWidth
                gridDelegate: ReceiptShow {}
                pagePadding: 16

                searchBar.visible: false

                newMouseArea.onClicked: {
                    receiptAddDialog.open();
                }
            }

            CustomPage {
                id: alysisPage
                headerText: "Analysis"
                headerDetails: "Chart:"

                searchBar.visible: false
            }

            CustomPage {
                id: settingPage
                headerText: "Settings"
                headerDetails: "Available settings can be change"
            }
        }
    }
}
