import QtQuick 2.0
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtGraphicalEffects 1.0
import QtQml.Models 2.12

Item {
    id: root

    height: 800
    width: 300

    signal clickedSave(var newNotebook)
    signal clickedAddGroup()
    signal clickedAddLabel()
    signal setGroup()
    signal setLabel()

    property var groupModel
    property var labelsModel

    property var navStack: ""

    AppFlickable {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: btSave.top

        contentHeight: contentColumn.implicitHeight
        bottomMargin: nativeUtils.safeAreaInsets.bottom

        Column {
            id: contentColumn

            anchors.fill: parent

            AppText {
                height: dp(20)
                text: "Название:"
            }

            AppTextField {
                id: titleNotebook
                height: dp(40)
                anchors.left: parent.left
                anchors.right: parent.right
            }

            AppText {
                height: dp(40)
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

                            mouseArea.onClicked: setGroup()

                            rightItem: AppButton {
                                width: height

                                anchors.verticalCenter: parent.verticalCenter
                                AppImage {
                                    anchors.fill: parent
                                    anchors.margins: dp(10)

                                    source: "../../assets/cross.png"
                                }

                                verticalMargin: dp(0)
                                horizontalMargin: dp(0)
                                verticalPadding: dp(0)
                                horizontalPadding: dp(0)

                                flat: true
                            }
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

                    AppButton {
                        height: parent.height / 10
                        Layout.minimumHeight: minimumHeight
                        Layout.fillWidth: true

                        text: "Добавить"

                        verticalMargin: dp(0)
                        horizontalMargin: dp(0)
                        verticalPadding: dp(0)
                        horizontalPadding: dp(0)

                        onClicked: clickedAddGroup()

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
                height: dp(40)
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

                            mouseArea.onClicked: setLabel()

                            rightItem: AppButton {
                                width: height

                                anchors.verticalCenter: parent.verticalCenter
                                AppImage {
                                    anchors.fill: parent
                                    anchors.margins: dp(10)

                                    source: "../../assets/cross.png"
                                }

                                verticalMargin: dp(0)
                                horizontalMargin: dp(0)
                                verticalPadding: dp(0)
                                horizontalPadding: dp(0)

                                flat: true
                            }
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

                    AppButton {
                        height: parent.height / 10
                        Layout.minimumHeight: minimumHeight
                        Layout.fillWidth: true

                        text: "Добавить"

                        verticalMargin: dp(0)
                        horizontalMargin: dp(0)
                        verticalPadding: dp(0)
                        horizontalPadding: dp(0)

                        onClicked: clickedAddLabel()

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

    AppButton {
        id: btSave
        text: "Сохранить"

        minimumHeight: dp(50)

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        verticalMargin: dp(0)
        horizontalMargin: dp(0)
        verticalPadding: dp(0)
        horizontalPadding: dp(0)

        onClicked: {
            clickedSave({t: titleNotebook.text, d: titleNotebook.text})
        }
    }
}
