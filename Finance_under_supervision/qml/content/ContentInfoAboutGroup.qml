import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12

Item {
    id: root

    height: 800
    width: 300

    property var groupModel: ListModel {}

    function update() {
        content.text = core.getGroupTitleById(core.currentGroup)
        contentImage.source = core.getGroupIconById(core.currentGroup)
        descriptionEdit.text = core.getGroupDescriptionById(core.currentGroup)
    }

    AppFlickable {
        anchors.fill: parent

        contentHeight: contentColumn.implicitHeight
        bottomMargin: nativeUtils.safeAreaInsets.bottom

        Column {
            id: contentColumn

            anchors.fill: parent

            AppListItem {
                id: content
                width: parent.width
                height: width/3

                property var title: ""
                property var icon: ""

                function setImage(img) {
                    contentImage.source = img
                    comIcon.currentIcon = img

                }

                text: core.getGroupTitleById(core.currentGroup)

                leftItem: AppImage {
                    id: contentImage
                    height: parent.height / 4 * 3
                    width: height
                    anchors.verticalCenter: parent.verticalCenter
                    source: core.getGroupIconById(core.currentGroup)
                }
            }

            AppText {
                width: parent.width
                text: "Описание:"
            }

            Item {
                height: contentTextEdit.implicitHeight
                width: parent.width

                Column {
                    id: contentTextEdit
                    anchors.fill: parent

                    AppText {
                        id: descriptionEdit
                        height: contentHeight > dp(150) ? contentHeight : dp(150)
                        width: parent.width
                        text:  core.getGroupDescriptionById(core.currentGroup)
                    }

                    Rectangle {
                        height: dp(1)
                        width: parent.width
                        color: "black"
                    }
                }
            }
        }
    }
}
