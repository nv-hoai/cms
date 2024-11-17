import QtQuick

Rectangle {
    id: root
    implicitWidth: parent.width
    implicitHeight: parent.height

    property alias sourceImage: image.source
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

    Image {
        id: image
        width: root.width-root.width/3
        height: root.height-root.height/3
        anchors.centerIn: parent
        smooth: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
    }
}
