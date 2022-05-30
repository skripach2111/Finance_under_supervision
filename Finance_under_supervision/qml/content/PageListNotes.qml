import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.3

Page {
    height: 800
    width: 300

    property ListModel notes: ListModel {}
    property ListModel labels: ListModel {}

    signal clickedNote()

    AppListView {
        clip: true
        anchors.fill: parent
        model: notes
        emptyText.text: "Нет записей"

        delegate: AppListItem {
            leftItem: AppImage {
                height: parent.height
                width: height
                source: icon

                anchors.verticalCenter: parent.verticalCenter
            }

            text: title
            detailText: group_title
            rightText: sum > 0 ? "+" + sum : sum
            rightTextColor: sum > 0 ? "green" : "red"

            mouseArea.onClicked: clickedNote()
        }
    }
}
