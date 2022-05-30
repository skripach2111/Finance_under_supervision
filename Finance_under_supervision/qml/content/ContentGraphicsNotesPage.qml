import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.0

Page {
    height: 800
    width: 300

    readonly property var daysNumbers: ["1.11", "2.11", "3.11", "4.11"]
    readonly property int daysCount: daysNumbers.length
    readonly property var plus:  [200, 100, 0, 100]
    readonly property var minus:  [0, 350, 980, 0]

    property int minVal: 0
    property int maxVal: Math.max(...plus) > Math.max(...minus) ? Math.max(...plus) : Math.max(...minus)

    readonly property color minusColor: "red"
    readonly property color plusColor: "green"
    readonly property string plusTitle: "Доходы"
    readonly property string minusTitle: "Расходы"

    ChartView {
        anchors.fill: parent
        antialiasing: true
        legend.alignment: Qt.AlignBottom
        legend.visible: true

        BarSeries {
            labelsVisible: true
            axisX: BarCategoryAxis {
                categories: daysNumbers
                titleText: "Число"
            }
            axisY: ValueAxis {
                min: 0
                max: maxVal
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
