import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.3

Page {
    height: 800
    width: 300

    property var notes
    property var labels

    signal clickedNote(var idNote)

    AppListView {
        clip: true
        anchors.fill: parent
        model: notes
        emptyText.text: "Нет записей"

        delegate: AppListItem {
            leftItem: AppImage {
                height: parent.height
                width: height
                source: core.getGroupIconById(_id_group)

                anchors.verticalCenter: parent.verticalCenter
            }

            text: _title
            detailText: core.getGroupTitleById(_id_group)
            rightText: _sum > 0 ? "+" + _sum : _sum
            rightTextColor: _sum > 0 ? "green" : "red"

            mouseArea.onClicked: clickedNote(_id)
        }
    }
}
