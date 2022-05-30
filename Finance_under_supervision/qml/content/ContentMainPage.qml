import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.3

import "../controls"

Item {
    id: root

    height: 800
    width: 300

    property var groups
    property ListModel icons: ListModel {}
    property ListModel notes: ListModel {}
    property ListModel labels: ListModel {}

    readonly property alias currentTav: tbControl.currentIndex

    signal clickedNotes()
    signal clickedGroup()

    Column {
        anchors.fill: parent

        AppPaper {
            height: parent.height / 5
            width: parent.width

            background.color: Theme.colors.tintColor
            //radius: dp(5)

            Row {
                anchors.fill: parent

                RemnantStatisticChart {
                    id: runStatisticsChart

                    height: parent.height
                    width: parent.height

                    value: 2500
                    totalValue: 640

                    activity: "Остаток:"
                }

                RemnantStatisticLegend {
                    id: runStatisticsLegend

                    height: parent.height
                    width: parent.width

                    value: 2500
                    totalValue: 640
                }

            }
        }

        TabControl {
            id: tbControl

            NavigationItem {
                title: "Категории"

                Page {
                    AppListView {
                        clip: true
                        anchors.fill: parent
                        model: groups
                        emptyText.text: "Нет категорий"

                        delegate: AppListItem {
                            leftItem: AppImage {
                                height: parent.height
                                width: height
                                source: icon

                                anchors.verticalCenter: parent.verticalCenter
                            }

                            property var _sum: 0
                            text: _title
                            detailText: _description
                            rightText: _sum >= 0 ? "+" + _sum : _sum
                            rightTextColor: _sum >= 0 ? "green" : "red"

                            mouseArea.onClicked: clickedGroup()
                        }
                    }
                }
            }
            NavigationItem {
                title: "История"
                icon: IconType.arrowright

                PageListNotes {
                    notes: root.notes
                    labels: root.labels

                    onClickedNote: clickedNotes()
                }
            }
        }

    }
}
