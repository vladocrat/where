import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property alias text: searchbar.text
    property alias searchIconSource: searchIcon.source
    property alias clearSearchIconSource: clearSerachBtn.imgSource
    property alias menuSettingsIconSource: menuSettingsBtn.imgSource
    readonly property alias settingsToggled: menuSettingsBtn.toggled

    signal textEdited();
    signal focusOnResults();

    onFocusChanged: {
        if (root.focus) {
            root.focus = false;
            searchbar.focus = true;
        }
    }

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

            focus: root.visible
            placeholderText: "Where is..."

            background: Rectangle {
                anchors.fill: parent
                anchors.margins: 10
                radius: 30
            }

            onTextEdited: {
                root.textEdited();
            }

            Keys.onPressed: function(event) {
                if (event.key === Qt.Key_Down) {
                    root.focusOnResults();
                }
            }
        }

        WhereButton {
            id: clearSerachBtn

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: 30
            Layout.minimumWidth: 30

            imgSource: root.searchIconSource
            visible: searchbar.text !== ""

            onClicked: {
                searchbar.clear();
            }
        }

        WhereToggleButton {
            id: menuSettingsBtn

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rightMargin: 15
            Layout.maximumWidth: 30
            Layout.minimumWidth: 30
        }
    }
}
