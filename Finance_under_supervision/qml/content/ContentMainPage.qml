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
    property var icons
    property var notes
    property var labels

    readonly property alias currentTab: tbControl.currentIndex

    onCurrentTabChanged: {
        if(currentTab == 1)
            core.currentGroup = -1
    }

    signal clickedNotes(var idNote)
    signal clickedGroup(var idGroup)

    function setChart()
    {
        runStatisticsChart.value = core.getTotalMinus(core.currentNotebook)
        runStatisticsChart.totalValue = core.getTotalPlus(core.currentNotebook) - core.getTotalMinus(core.currentNotebook)

        runStatisticsLegend.value = runStatisticsChart.value
        runStatisticsLegend.totalValue = runStatisticsChart.totalValue
    }

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

                    value: core.totalMinus
                    totalValue: core.totalPlus

                    activity: "Остаток:"
                }

                RemnantStatisticLegend {
                    id: runStatisticsLegend

                    height: parent.height
                    width: parent.width

                    value: runStatisticsChart.value
                    totalValue: runStatisticsChart.totalValue
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
                                source: _icon

                                anchors.verticalCenter: parent.verticalCenter
                            }

                            property var _sum: core.getTotalSumByGroupId(_id)
                            text: _title
                            detailText: _description
                            rightText: _sum >= 0 ? "+" + _sum : _sum
                            rightTextColor: _sum >= 0 ? "green" : "red"

                            mouseArea.onClicked: clickedGroup(_id)
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

                    onClickedNote: clickedNotes(idNote)
                }
            }
        }

    }
}
