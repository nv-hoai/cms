import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Dialog {
    id: root
    width: 350
    height: 300
    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.NoAutoClose

    property string serviceName;
    property int customerId;
    property int computerId;
    property int foodId;
    property int timeUsed;
    property int numberOrdered;
    property int customerIndex;
    property int computerIndex;
    property int foodIndex;
    property var customer: null;
    property var computer: null;
    property var food: null;

    header: Text {
        text: "Service's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        computerId = 0;
        foodId = 0;
        if (serviceName == "Hire computer")
            customerId = 0;
        timeUsed = 0;
        numberOrdered = 0;
        if (serviceName == "Hire computer")
            customerIdInput.value = 1;
        else
            customerIdInput.value = customerId;
        computerIdInput.value = 1;
        foodIdInput.value = 1;
        customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
        computer = SystemManager.computerModel.getComputer(computerIdInput.value);
        food = SystemManager.foodModel.getFood(foodIdInput.value);
    }

    onAccepted: {
        customerId = customerIdInput.value;
        if (serviceName == "Hire computer") {
            customerIndex = SystemManager.customerModel.getIndexById(customerId);
            SystemManager.customerModel.setStatus(customerIndex, 2);
            computerId = computerIdInput.value;
            timeUsed = timeUsedInput.text;
            computerIndex = SystemManager.computerModel.getIndexById(computerId);
            SystemManager.computerModel.setStatus(computerIndex, 2);
        }

        if (serviceName == "Order food") {
            foodId = foodIdInput.value;
            numberOrdered = parseInt(numberOrderedInput.text);
        }
        receiveServiceData(serviceName, customerId, computerId, timeUsed, foodId, numberOrdered);
    }

    function isSaveAllowed() {
        return !((serviceName == "Hire computer" &&
                  (invalidCustomerId.visible ||
                   invalidComputerId.visible ||
                   invalidTimeUsed.visible)) ||
                 (serviceName == "Order food" &&
                  (foodNameShow.text == "Invalid food id!" ||
                   invalidNumberOrdered.visible)));
    }

    function checkNumberVisible() {
        if (serviceName == "Hire computer")
            return false
        if (numberOrderedInput.text == "")
            return true;
        if (foodId == foodIdInput.value &&
                numberOrderedInput.text != "0" &&
                    parseInt(numberOrderedInput.text) <= numberOrdered)
            return false;
        if (food) {
            if (food.remain == 0)
                return true;
            if (numberOrderedInput.text == "0")
                return true;
            if (parseInt(numberOrderedInput.text) > (food.remain + ((foodId == foodIdInput.value)?numberOrdered:0)))
                return true;
        }
        return false;
    }

    function checkNumberOrdered() {
        if (numberOrderedInput.text == "")
            return "Number cant be left empty!";
        if (food && food.remain == 0)
            return "Out of stock!";
        if(numberOrderedInput.text == "0")
            return "0 not allowed!"
        if (food)
            return "Not enough food's remain to sell! " +
            "(" + (food.remain + ((foodId == foodIdInput.value)?numberOrdered:0)) + " available)";
        return ""
    }

    function checkComputer() {
        if (!computer)
            return "Invalid computer id"
        if (computer.status != 0)
            switch(computer.status) {
            case 1:
                return "Computer is busy!"
            case 2:
                return "Computer is being registered by the other!"
            case 3:
                return "Computer is cracked!"
            }
        return ""
    }

    function checkCustomer() {
        if (!customer)
            return "Invalid customer id"
        if (customer.status != 0)
            switch(customer.status) {
            case 1:
                return "Customer is now hiring a computer!"
            case 2:
                return "Customer is registering in another service!"
            }
        return ""
    }

    ColumnLayout {
        anchors.fill: parent


        Text {
            text: "Service name: " + serviceName
            font.pixelSize: 16
            font.weight: 40
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Customer's ID: "
                font.pixelSize: 16
                font.weight: 40
            }

            Text {
                visible: serviceName == "Order food"
                text: (customer)?customer.id:""
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: customerIdInput
                visible: serviceName == "Hire computer"
                Layout.fillHeight: true
                editable: true
                from: 1
                to: 100

                onValueModified: {
                    customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
                }
            }

            Text {
                text: (customer)?customer.firstName + " " + customer.lastName: ""
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidCustomerId
            text: root.checkCustomer()
            visible: (serviceName == "Hire computer" && text != "")
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceName == "Hire computer")

            Text {
                text: "Computer's ID"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: computerIdInput
                Layout.fillHeight: true
                editable: true
                from: 1
                to: 100

                onValueModified: {
                    computer = SystemManager.computerModel.getComputer(computerIdInput.value);
                }
            }
        }

        Text {
            id: invalidComputerId
            visible: (serviceName == "Hire computer" && text != "")
            text: root.checkComputer()
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceName == "Hire computer")

            Text {
                text: "Time use"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: timeUsedInput
                text: root.timeUsed
                inputMask: "9999"
                placeholderText: "XXXX"
                Layout.preferredWidth: computerIdInput.width
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }

            Text {
                text: "seconds"
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidTimeUsed
            visible: (serviceName == "Hire computer" && (timeUsedInput.text == "0" || timeUsedInput.text == ""))
            text: (timeUsedInput.text == "0")?"0 not allowed!":"Time use can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceName == "Order food")

            Text {
                text: "Food's ID"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: foodIdInput
                Layout.fillHeight: true
                editable: true
                from: 1
                to: 100

                onValueModified: {
                    food = SystemManager.foodModel.getFood(foodIdInput.value);
                }
            }

            Text {
                id: foodNameShow
                text: (food)?food.name:"Invalid food id!"
                font.pixelSize: 16
                font.weight: 40
                color: (text == "Invalid food id!")?"red":"black"
            }
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceName == "Order food")

            Text {
                text: "Number ordered"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: numberOrderedInput
                text: root.numberOrdered
                inputMask: "999"
                placeholderText: "XXX"
                Layout.preferredWidth: foodIdInput.width
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidNumberOrdered
            visible: root.checkNumberVisible()
            text: root.checkNumberOrdered()
            color: "red"
            font.pixelSize: 16
            font.weight: 40
        }
    }

    footer: DialogButtonBox {
        Button {
            text: "Ok"
            enabled: root.isSaveAllowed()
            onClicked: root.accept()
            implicitHeight: 32
            implicitWidth: 64
        }
        Button {
            text: "Cancel"
            onClicked: root.reject()
            implicitHeight: 32
            implicitWidth: 64
        }
    }
}
