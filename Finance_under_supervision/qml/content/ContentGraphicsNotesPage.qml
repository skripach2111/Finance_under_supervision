import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.0

Page {
    height: 800
    width: 300

    property var daysNumbers
    property int daysCount: daysNumbers.length
    property var plus
    property var minus

    property int minVal: 0
    property int maxVal: Math.max(...plus) > Math.max(...minus) ? Math.max(...plus) : Math.max(...minus)

    readonly property color minusColor: "red"
    readonly property color plusColor: "green"
    readonly property string plusTitle: "Доходы"
    readonly property string minusTitle: "Расходы"

    Flickable {
        anchors.fill: parent

        contentWidth: chart.width

            ChartView {
                id: chart
                height: parent.height
                width: dp(100)*2*daysCount

                antialiasing: true
                legend.alignment: Qt.AlignBottom
                legend.visible: true

                BarSeries {
                    id: bar
                    labelsVisible: true
                    axisX: BarCategoryAxis {
                        categories: daysNumbers
                        titleText: "Число"
                    }
                    axisY: ValueAxis {
                        min: 0.0
                        max: maxVal + maxVal*0.2
                        titleText: "Заработано/Потрачено"
                    }

                    BarSet {
                        label: plusTitle
                        values: plus
                        color: plusColor
                    }

                    BarSet {
                        label: minusTitle
                        values: minus
                        color: minusColor
                    }
                }
            }
    }
    //    AppButton {
    //        onClicked: {
    //            bar.append(plusTitle, core.getListTotalPlusByDate());
    //            bar.at(bar.count-1).color = plusColor

    //            bar.append(minusTitle, core.getListTotalMinusByDate());
    //            bar.at(bar.count-1).color = minusColor
    //        }
    //    }
}
