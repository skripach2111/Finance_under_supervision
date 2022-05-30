import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12

Page {
    id: root

    height: 800
    width: 300

    property ListModel notes: ListModel {}
    property ListModel labels: ListModel {}
    property int idNote: 0

    rightBarItem: TextButtonBarItem {
        text: "Удалить"
        color: "red"
      }

    Column {
        anchors.fill: parent

        AppPaper {
            height: parent.height / 4
            width: parent.width

            background.color: Theme.colors.tintColor

            Column {
                anchors.fill: parent

                Row {
                    height: parent.height / 3 * 2
                    width: parent.width

                    Item {
                        height: parent.height
                        width: height
                        AppImage {
                            height: parent.height / 2
                            width: height

                            anchors.centerIn: parent

                            source: notes.get(idNote).icon
                        }
                    }

                    Item {
                        height: parent.height
                        width: parent.width

                        anchors.verticalCenter: parent.verticalCenter

                        Column {
                            anchors.fill: parent

                            AppText {
                                id: title

                                width: parent.width

                                text: notes.get(idNote).title
                                color: Theme.colors.backgroundColor
                            }

                            AppText {
                                id: category

                                width: parent.width

                                text: notes.get(idNote).group_title
                                color: Theme.colors.backgroundColor
                            }

                            AppText {
                                id: sum

                                width: parent.width

                                text: notes.get(idNote).sum
                                color: Theme.colors.backgroundColor
                            }

                            AppText {
                                id: date

                                width: parent.width

                                text: notes.get(idNote).date
                                color: Theme.colors.backgroundColor
                            }
                        }
                    }
                }

                Item {
                    height: parent.height / 3
                    width: parent.width

                    GridView {
                        anchors.fill: parent
                        anchors.margins: dp(5)

                        property var cHeight: dp(20)
                        property var cWidth: dp(76)

                        cellHeight: cHeight
                        cellWidth: cWidth

                        model: labels

                        delegate: AppPaper {
                            height: dp(16)
                            width: dp(72)

                            background.color: Theme.colors.tintLightColor

                            radius: 10

                            AppText {
                                anchors.centerIn: parent

                                text: title
                                color: colored
                            }
                        }
                    }
                }
            }
        }

        AppFlickable {
            height: parent.height / 4 * 3
            width: parent.width

            contentHeight: contentColumn.implicitHeight

            Column {
                id: contentColumn
                anchors.fill: parent

                AppText {
                    width: parent.width

                    text: "Описание:"
                }

                AppPaper {
                    height: dp(300)
                    width: parent.width

                    AppText {
                        anchors.fill: parent
                        text: notes.get(idNote).description
                    }
                }

                AppText {
                    width: parent.width

                    text: "Дополнительно:"
                }

                AppPaper {
                    height: dp(300)
                    width: parent.width

                    AppImage {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}

