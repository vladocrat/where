import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root
    width: 600
    height: 400
    visible: true
    color: "transparent"

    flags: Qt.Tool | Qt.FramelessWindowHint

    x: Math.round((Screen.width - width) / 2)
    y: Math.round((Screen.height - height) / 2)

    Rectangle {
        radius: 30
        width: parent.width
        height: column.implicitHeight
        //color: "transparent"

        Behavior on height {
            NumberAnimation {
                duration: 400
                easing.type: Easing.InOutQuad
            }
        }

        ColumnLayout {
            id: column
            anchors.margins: 10
            width: parent.width
            spacing: 0

            Searchbar {
                id: searchbar

                Component.onCompleted: {
                    console.log(width, height)
                }

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumHeight: 60
                Layout.maximumHeight: 60
                Layout.alignment: Qt.AlignTop

                searchIconSource: "qrc:/icons/search_icon.svg"
                clearSearchIconSource: "qrc:/icons/cross.svg"
                menuSettingsIconSource: "qrc:/icons/vertical_menu.svg"

                onTextEdited: {
                    if (searchbar.text !== "") {
                        searchResults.startReveal()
                    } else {
                        searchResults.resetReveal()
                    }
                }
            }

            Rectangle {
                Layout.minimumWidth: root.width - 20
                Layout.maximumHeight: 1
                Layout.minimumHeight: 1
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                visible: searchbar.text !== ""
                color: "black"

                onVisibleChanged: {
                    if (visible) {
                        width = root.width - 20;
                    } else {
                        width = 0;
                    }
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            ListModel {
                id: lm

                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
            }


            SearchResultsView {
                id: searchResults

                Layout.preferredHeight: 200
                Layout.minimumWidth: root.width - 20
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10

                visible: searchbar.text !== ""
                view.model: lm

                delegate: Rectangle {
                    implicitWidth: root.width
                    implicitHeight: 20
                    color: "red"
                    opacity: model.shown ? 1.0 : 0.0
                    scale: model.shown ? 1.0 : 0.5

                    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.InOutQuad } }
                    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }
                }
            }
        }
    }
}

