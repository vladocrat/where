import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import SearchController
import ModelController
import HotKeyController

Window {
    id: root
    width: 700
    height: 400
    visible: true
    color: "transparent"

    flags: Qt.Dialog | Qt.FramelessWindowHint

    x: Math.round((Screen.width - width) / 2)
    y: Math.round((Screen.height - height) / 2)

    Connections {
        target: HotKeyController

        function onShowSearchBar() {
            if (root.visible) {
                root.hide();
                return;
            }

            root.show();
        }
    }

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
                menuSettingsIconSource: "qrc:/icons/gear.svg"

                onTextEdited: {
                    if (searchbar.text === "") {
                        SearchController.clear();
                        return;
                    }

                    SearchController.search(searchbar.text);
                }

                onFocusOnResults: {
                    if (searchResults.visible) {
                        searchResults.focus = true;
                    }
                }
            }

            Rectangle {
                Layout.maximumHeight: 1
                Layout.minimumHeight: 1
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                width: {
                    if (visible) {
                        return root.width - 20;
                    } else {
                        return 0;
                    }
                }

                visible: settings.visible || searchResults.visible
                color: "black"

                Behavior on width {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            SettingsView {
                id: settings

                Layout.preferredHeight: root.height - searchbar.height - 20
                Layout.minimumWidth: root.width - 20
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                visible: searchbar.settingsToggled

                backendsModel: ModelController.backendsModel
            }

            SearchResultsView {
                id: searchResults

                Layout.preferredHeight: root.height - searchbar.height - 20
                Layout.minimumWidth: root.width - 20
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                visible: searchbar.text !== "" && !searchbar.settingsToggled
                view.model: ModelController.searchResultModel
                view.spacing: 10

                onLoseFocus: {
                    searchResults.focus = false;
                    searchbar.focus = true;
                }

                onOpen: function(currentItem) {
                    currentItem.openRequested(currentItem.filePath + "/" + currentItem.fileName);
                }

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

