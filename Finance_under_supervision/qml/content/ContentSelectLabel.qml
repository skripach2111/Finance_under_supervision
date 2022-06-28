import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQml 2.12

Item {
    height: 800
    width: 300

    signal selectLabel(var id, var title, var color)

    ListView {
        anchors.fill: parent

        clip: true
        model: core.labelModel
        delegate: AppListItem {
            id: delegateLabel
            text: _title
            textColor: _color

            mouseArea.onClicked: selectLabel(_id, _title, _color)
        }

        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.leftMargin: dp(5)
    }
}
