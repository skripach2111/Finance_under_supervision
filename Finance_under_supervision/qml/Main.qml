import Felgo 3.0
import QtQuick 2.0
import "model"
import "logic"
import "pages"
import com.custom 1.0


App {
    // You get free licenseKeys from https://felgo.com/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the Felgo Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from https://felgo.com/licenseKey>"

    // app initialization
    Core {
        id: core

        onComingNotebookModel: {

            list.model = notebookModel

        }
    }

    Page {
        anchors.fill: parent

        ListView {
            id: list

            delegate: AppListItem {
                text: id
                detailText: title
            }

            Component.onCompleted: core.getNotebookModel()
        }
    }

}
