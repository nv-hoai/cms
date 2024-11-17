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

    property int numberOrdered;
    property int customerId;
    property int computerId;
    property int foodId;
    property int timeUse;
    property int customerIndex;
    property int computerIndex;
    property int foodIndex;
    property string serviceName;
    property string startTime;
    property var customer: null;
    property var computer: null;
    property var food: null;

    header: Text {
        text: "Service's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        timeUse = 0;
        numberOrdered = 0;
        computerId = 0;
        foodId = 0;
        customerId = 0;
        customerIdInput.value = 1;
        computerIdInput.value = 1;
        foodIdInput.value = 1;
        customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
        computer = SystemManager.computerModel.getComputer(computerIdInput.value);
        food = SystemManager.foodModel.getFood(foodIdInput.value);
    }

    onAccepted: {
        serviceName = serviceNameInput.currentValue;
        customerId = customerIdInput.value;
        customerIndex = SystemManager.customerModel.getIndexById(customerId);
        SystemManager.customerModel.setStatus(customerIndex, 2);
        if (serviceName == "Hire computer") {
            computerId = computerIdInput.value;
            timeUse = timeUseInput.text;
            computerIndex = SystemManager.computerModel.getIndexById(computerId);
            SystemManager.computerModel.setStatus(computerIndex, 2);
        }

        if (serviceName == "Order food") {
            foodId = foodIdInput.value;
            foodIndex = SystemManager.foodModel.getIndexById(foodId);
            numberOrdered = parseInt(numberOrderedInput.text);
            SystemManager.foodModel.setRemain(foodIndex, food.remain - numberOrdered);
        }
        receiveServiceData(serviceName, customerId, computerId, timeUse, foodId, numberOrdered);
    }

    function isSaveAllowed() {
        return !((serviceNameInput.currentValue == "Hire computer" && (customerNameShow.text == "Invalid customer id!" ||
                   invalidComputerId.visible || invalidTimeUse.visible)) ||
                 (serviceNameInput.currentValue == "Order food" && (foodNameShow.text == "Invalid food id!" ||
                   invalidNumberOrdered.visible)));
    }

    function isVisible() {
        if (serviceNameInput.currentValue == "Hire computer")
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

    function errorWhat() {
        if (numberOrderedInput.text == "")
            return "Number cant be left empty!";
        if (food && food.remain == 0)
            return "Out of stock!";
        if(numberOrderedInput.text == "0")
            return "0 not allowed!"
        if (food)
            return "Not enough food's remain to sell! " +
            "(" + (food.remain + ((foodId == foodIdInput.value)?numberOrdered:0)) + " available)";
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Service name"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: serviceNameInput
                model: ["Hire computer", "Order food"]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Customer's ID"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: customerIdInput
                Layout.fillHeight: true
                editable: true
                from: 1
                to: 100

                onValueModified: {
                    customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
                }
            }

            Text {
                id: customerNameShow
                text: (customer)?customer.firstName + " " + customer.lastName: "Invalid customer id!"
                font.pixelSize: 16
                font.weight: 40
                color: (text == "Invalid customer id!")?"red":"black"
            }
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceNameInput.currentValue == "Hire computer")

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

            Text {
                id: invalidComputerId
                visible: (computer)?(computer.status != 0 && computer.id != computerId):false
                text: (computer)?(computer.status == 1)?"Computer is busy!":(computer.status==2)?"Computer is being registered by the other":"Computer is cracked!":""
                font.pixelSize: 16
                font.weight: 40
                color: "red"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceNameInput.currentValue == "Hire computer")

            Text {
                text: "Time use"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: timeUseInput
                text: root.timeUse
                inputMask: "9999"
                placeholderText: "XXXX"
                Layout.preferredWidth: computerIdInput.width
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }

            Text {
                text: "miniutes"
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidTimeUse
            visible: (serviceNameInput.currentValue == "Hire computer" && (timeUseInput.text == "0" || timeUseInput.text == ""))
            text: (timeUseInput.text == "0")?"0 not allowed!":"Time use can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24
            visible: (serviceNameInput.currentValue == "Order food")

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
            visible: (serviceNameInput.currentValue == "Order food")

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
            visible: root.isVisible()
            text: root.errorWhat()
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
