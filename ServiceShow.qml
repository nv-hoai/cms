import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: servicePage.gridCellWidth-10
    implicitHeight: servicePage.gridCellHeight-10
    color: lrectangleColor
    radius: 4

    property color lrectangleColor: (model.status == 0)?"white":"#81C784"
    property color drectangleColor: (model.status == 0)?"#CCCCCC":"#66BB6A"

    function formatTimeFromSeconds(seconds) {
        var hours = Math.floor(seconds / 3600);
        var minutes = Math.floor((seconds % 3600) / 60);
        var secs = seconds % 60;

        var hoursStr = hours < 10 ? "0" + hours : "" + hours;
        var minutesStr = minutes < 10 ? "0" + minutes : "" + minutes;
        var secondsStr = secs < 10 ? "0" + secs : "" + secs;

        return hoursStr + ":" + minutesStr + ":" + secondsStr;
    }

    Timer {
        id: timer
        interval: 1000
        running: (serviceName == "Hire computer" && status == 1)
        repeat: true
        onTriggered: {
            timeUsed = timeUsed+1
        }
    }

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent
        columns: 2
        rowSpacing: 0

        Text {
            Layout.leftMargin: 64
            text: "ID: "+id
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            text: "Service name: " + serviceName
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                text = Qt.binding(function() {
                    return "Customer's ID: " + customer.id
                })
            }
        }

        Text {
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                text = Qt.binding(function() {
                    return "Customer's name: " + customer.firstName + " " + customer.lastName
                })
            }
        }

        Text {
            visible: (serviceName=="Hire computer")
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        if (computer)
                            return "Computer's ID: " + computer.id
                        return ""
                    })
            }
        }

        Text {
            visible: (serviceName=="Hire computer")
            font.pixelSize: 16

            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        return "Time used: " + root.formatTimeFromSeconds(timeUsed)
                    })
            }
        }

        Text {
            visible: (serviceName=="Order food")
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        if (food)
                            return "Food's name: " + food.name
                        return ""
                    })
            }
        }

        Text {
            visible: (serviceName=="Order food")
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        return "Number ordered: " + numberOrdered
                    })
            }
        }

        Text {
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                    text = Qt.binding(function() {
                        return "Status: " + ((status)?"Confirmed":"Unconfirmed")
                    })
            }
        }
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            root.color = root.drectangleColor
        }

        onExited: {
            root.color = root.lrectangleColor
        }

        onClicked: (mouse) => {
            if (mouse.button === Qt.RightButton)
                contextMenu.popup();
        }


        Menu {
            id: contextMenu
            width: 150
            MenuItem {
                id: confirmButton
                text: "Confirm"
                enabled: model.status == 0
                onTriggered: {
                    SystemManager.confirmService(id)
                    contextMenu.removeItem(changeButton)
                    contextMenu.removeItem(deleteButton)
                    contextMenu.removeItem(confirmButton)
                }
            }

            MenuItem {
                id: seeCustomer
                text: "See customer"
                onTriggered: {
                    swipeView.currentIndex = 1
                    customerPage.searchBar.text = "ID: " + customer.id + ".*" + customer.firstName
                }
            }

            MenuItem {
                id: seeComputer
                text: "See computer"
                onTriggered: {
                    swipeView.currentIndex = 0
                    computerPage.searchBar.text = "ID: " + computer.id + ".*" +computer.cpu
                }
            }

            MenuItem {
                id: seeFood
                text: "See food"
                onTriggered: {
                    if (food) {
                        swipeView.currentIndex = 3
                        foodPage.searchBar.text = "ID: " + food.id + ".*" + food.name
                    }
                }
            }

            MenuItem {
                id: changeButton
                text: "Change"
                enabled: model.status == 0
                onTriggered: {
                    selectedItemIndex = SystemManager.serviceModel.getIndexById(id)
                    serviceChangeDialog.id = id
                    serviceChangeDialog.serviceName = serviceName
                    serviceChangeDialog.customerId = customer.id
                    if (serviceName == "Hire computer") {
                        serviceChangeDialog.computerId = computer.id
                        serviceChangeDialog.timeUsed = timeUsed
                    } else {
                        if (food) {
                            serviceChangeDialog.foodId = food.id
                            serviceChangeDialog.numberOrdered = numberOrdered
                        } else {
                            serviceChangeDialog.foodId = 0
                            serviceChangeDialog.numberOrdered = 0
                        }
                    }
                    serviceChangeDialog.open()
                }
            }

            MenuItem {
                id: deleteButton
                text: "Delete"
                enabled: model.status == 0
                onTriggered: {
                    SystemManager.removeService(id)
                }
            }

            MenuItem {
                id: orderFoodButton
                text: "Order food"
                enabled: model.status == 1
                onTriggered: {
                    serviceAddDialog.serviceName = "Order food"
                    serviceAddDialog.customerId = customer.id
                    serviceAddDialog.open()
                }
            }


            MenuItem {
                id: payBill
                text: "Create receipt"
                enabled: model.status == 1
                onTriggered: {
                    swipeView.currentIndex = 5
                    receiptAddDialog.customerId = customer.id
                    receiptAddDialog.open()
                }
            }

            Component.onCompleted: {
                if (model.status) {
                    contextMenu.removeItem(changeButton)
                    contextMenu.removeItem(deleteButton)
                    contextMenu.removeItem(confirmButton)
                }

                if (serviceName == "Hire computer")
                    contextMenu.removeItem(seeFood)

                if (serviceName == "Order food") {
                    contextMenu.removeItem(orderFoodButton)
                    contextMenu.removeItem(seeComputer)
                }
            }
        }
    }
}
