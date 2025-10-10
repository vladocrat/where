import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import SearchController
import SearchResultModel

Window {
    id: root
    width: 600
    height: 400
    visible: true
    color: "transparent"

    flags: Qt.Dialog | Qt.FramelessWindowHint

    x: Math.round((Screen.width - width) / 2)
    y: Math.round((Screen.height - height) / 2)

    Rectangle {
        radius: 30
        width: parent.width
        height: column.implicitHeight

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
                    if (searchbar.text === "") {
                        SearchController.clear();
                        return;
                    }

                    SearchController.search(searchbar.text);
                }
            }

            Rectangle {
                Layout.minimumWidth: root.width - 20
                Layout.maximumHeight: 1
                Layout.minimumHeight: 1
                Layout.preferredWidth: {
                    if (visible) {
                        return root.width - 20;
                    } else {
                        return 0;
                    }
                }

                Layout.leftMargin: 10
                Layout.rightMargin: 10

                visible: searchbar.text !== "" && searchResults.view.count !== 0
                color: "black"

                Behavior on width {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            SearchResultsView {
                id: searchResults

                Layout.preferredHeight: root.height - searchbar.height - 20
                Layout.minimumWidth: root.width - 20
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                visible: searchbar.text !== "" && searchResults.view.count !== 0
                view.model: SearchResultModel
                view.spacing: 10

                delegate: SearchResultDelegate {
                    implicitWidth: root.width - 20
                    implicitHeight: 45

                    onOpenRequested: function (filePath){
                        SearchController.open(filePath);
                    }

                    onCopyPath: function(filePath) {
                        SearchController.copy(filePath);
                    }
                }
            }
        }
    }
}

