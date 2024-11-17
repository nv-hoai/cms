import QtQuick

Rectangle {
    id: root
    implicitWidth: parent.width
    implicitHeight: parent.height

    property alias text: buttonInfo.text
    property alias textSize: buttonInfo.font.pixelSize
    property alias buttonRadius: root.radius
    property alias mouseArea: mouseArea
    readonly property color buttonColor: "#CCCCCC"

    color: (function() {
        if (mouseArea.containsPress) {
            return Qt.lighter(root.buttonColor)
        } else if (mouseArea.containsMouse) {
            return root.buttonColor
        }
        return "white"
    })()

    Text {
        id: buttonInfo
        anchors.centerIn: parent
        color: "black"
        font.pixelSize: 16
        font.weight: 40
    }


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
    }
}
