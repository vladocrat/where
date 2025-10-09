import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property alias text: searchbar.text
    property alias searchIconSource: searchIcon.source
    property alias clearSearchIconSource: clearSearchIcon.source
    property alias menuSettingsIconSource: menuSettingsIcon.source

    signal textEdited();

    RowLayout {
       anchors.fill: parent

        Image {
            id: searchIcon

            Layout.alignment: Qt.AlignLeft
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 15
            Layout.maximumWidth: 30
            Layout.minimumWidth: 30

            sourceSize.height: 512
            sourceSize.width: 512
            antialiasing: true

            fillMode: Image.PreserveAspectFit

            visible: searchIcon.status === Image.Ready
            smooth: true
        }

        TextField {
            id: searchbar

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 10

            placeholderText: "Where is..."

            background: Rectangle {
                anchors.fill: parent
                anchors.margins: 10
                radius: 30
            }

            onTextEdited: {
                root.textEdited();
            }
        }

        Image {
            id: clearSearchIcon

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: 30
            Layout.minimumWidth: 30

            sourceSize.height: 512
            sourceSize.width: 512
            antialiasing: true

            fillMode: Image.PreserveAspectFit
            smooth: true

            visible: clearSearchIcon.status === Image.Ready && searchbar.text !== ""
        }

        Image {
            id: menuSettingsIcon

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rightMargin: 15
            Layout.maximumWidth: 30
            Layout.minimumWidth: 30

            sourceSize.height: 512
            sourceSize.width: 512
            antialiasing: true

            fillMode: Image.PreserveAspectFit
            smooth: true

            visible: menuSettingsIcon.status === Image.Ready
        }
    }
}
