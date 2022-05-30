import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtGraphicalEffects 1.0

Item {
    id: root

    height: 800
    width: 300

    property var currentNotebook: 0
    property var groupModel
    property var labelsModel: []
    property var notebooksModel

    AppFlickable {
        anchors.fill: parent

        contentHeight: contentColumn.implicitHeight > height ? contentColumn.implicitHeight : height

        Column {
            id: contentColumn

            anchors.fill: parent

            AppText {
                width: parent.width
                text: notebooksModel.getDataById(core.currentNotebook, 1)
                fontSize: dp(30)
                font.bold: true
            }

            AppText {
                width: parent.width
                text: "Категории:"
            }

            Item {
                height: parent.width

                anchors.left: parent.left
                anchors.right: parent.right

                anchors.leftMargin: parent.width - parent.width / 10 * 9
                anchors.rightMargin: parent.width - parent.width / 10 * 9

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    ListView {
                        clip: true
                        model: root.groupModel
                        delegate: AppListItem {
                            text: _title
                            detailText: _description

                            mouseArea.onClicked: clickedOpen()
                        }

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.leftMargin: dp(5)
                    }

                    Rectangle {
                        height: dp(4)

                        color: "black"

                        Layout.fillWidth: true
                        Layout.minimumHeight: dp(3)
                    }
                }

                Rectangle {
                    id: mask
                    color: "#00000000"
                    radius: dp(40)

                    border.width: dp(3)

                    anchors.fill: parent
                }

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: Rectangle {
                        height: mask.height
                        width: mask.width
                        radius: mask.radius
                    }
                }
            }

            AppText {
                width: parent.width
                text: "Метки:"
            }

            Item {
                height: parent.width

                anchors.left: parent.left
                anchors.right: parent.right

                anchors.leftMargin: parent.width - parent.width / 10 * 9
                anchors.rightMargin: parent.width - parent.width / 10 * 9

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    ListView {
                        clip: true
                        model: root.labelsModel
                        delegate: AppListItem {
                            text: title
                            textColor: colored

                            mouseArea.onClicked: clickedOpen()
                        }

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.leftMargin: dp(5)
                    }

                    Rectangle {
                        height: dp(4)

                        color: "black"

                        Layout.fillWidth: true
                        Layout.minimumHeight: dp(3)
                    }
                }


                Rectangle {
                    color: "#00000000"
                    radius: mask.radius

                    border.width: mask.border.width

                    anchors.fill: parent
                }

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: Rectangle {
                        height: mask.height
                        width: mask.width
                        radius: mask.radius
                    }
                }
            }
        }
    }
}
