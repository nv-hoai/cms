import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Dialog {
    id: root
    width: 350
    height: 350
    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.NoAutoClose

    property int id;
    property string firstName;
    property string lastName;
    property int age;
    property bool gender;
    property string position;
    property int workedDays;
    property string timeWork;
    property int baseSalary;

    header: Text {
        text: "Employee's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        firstNameInput.text = firstName;
        lastNameInput.text = lastName;
        ageInput.value = age;
        genderInput.currentIndex = genderInput.indexOfValue(gender);
        positionInput.currentIndex = positionInput.indexOfValue(position);
        workedDaysInput.value = workedDays;
        timeWorkInput.currentIndex = timeWorkInput.indexOfValue(timeWork);
        baseSalaryInput.text = baseSalary;
    }

    onAccepted: {
        firstName = firstNameInput.text.substring(0, 30)
        lastName = lastNameInput.text.substring(0, 30)
        age = ageInput.value
        gender = genderInput.currentValue
        position = positionInput.currentValue
        workedDays = workedDaysInput.value
        timeWork = timeWorkInput.currentValue
        baseSalary = parseInt(baseSalaryInput.text)
        updateEmployeeData(selectedItemIndex, firstName, lastName, age, gender, position, workedDays, timeWork, baseSalary)
    }

    function isSaveAllowed() {
        return !(invalidFirstName.visible || invalidLastName.visible || invalidBaseSalary.visible)
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "Id: "+ root.id
            font.pixelSize: 16
            font.weight: 40
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "First name"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: firstNameInput
                text: root.firstName
                placeholderText: "Hoai"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidFirstName
            text: "First name can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            visible: (firstNameInput.text == "")
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Last name"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: lastNameInput
                text: root.lastName
                placeholderText: "Nguyen Van"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidLastName
            text: "Last name can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            visible: (lastNameInput.text == "")
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Age"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: ageInput
                editable: true
                from: 18
                to: 60
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Gender"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: genderInput
                textRole: "text"
                valueRole: "value"
                model: [
                    { value: 0, text: "Female" },
                    { value: 1, text: "Male" }
                ]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Position"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: positionInput
                model: [ "Waiter", "Receptionist", "Billing Clerk"]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Worked days"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: workedDaysInput
                editable: true
                from: 0
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Time work"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: timeWorkInput
                model: [ "07:00-15:00", "15:00-23:00"]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Base salary"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: baseSalaryInput
                text: root.baseSalary
                inputMask: "9999"
                placeholderText: "2000"
                Layout.preferredWidth: timeWorkInput.width
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidBaseSalary
            visible: (baseSalaryInput.text == "" || baseSalaryInput.text == "0")
            text: (baseSalaryInput.text == "")?"Base salary can't be left empty":"Base salary can't be 0!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }
    }

    footer: DialogButtonBox {
        Button {
            text: "Save"
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
