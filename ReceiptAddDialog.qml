import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Dialog {
    id: root
    width: 350
    height: 150
    anchors.centerIn: parent;

    property int customerId: 0;
    property var customer: null;

    function isSaveAllowed() {
        return !(invalidCustomerId.visible)
    }

    onOpened: {
        if (customerId) {
            customerIdInput.value = customerId
            customerId = 0
        }
        customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
    }

    onAccepted: {
        receiveReceiptData(customerIdInput.value)
    }

    header: Text {
        text: "Choose the customer to create receipt"
        font.pixelSize: 12
        font.weight: 40
    }

    function errorWhat() {
        if (!customer)
            return "Invalid customer id"
        if (customer)
            if (customer.status != 1)
                return "This customer doesn't use any service!"
        return "";
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Text {
                text: "Customer's ID"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: customerIdInput
                Layout.preferredHeight: 32
                editable: true
                from: 1
                to: 100

                onValueModified: {
                    customer = SystemManager.customerModel.getCustomer(customerIdInput.value);
                }
            }

            Text {
                text: (customer)?customer.firstName+ " " + customer.lastName:""
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidCustomerId
            visible: errorWhat() != ""
            text: errorWhat()
            font.pixelSize: 16
            font.weight: 40
            color: "red"
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
