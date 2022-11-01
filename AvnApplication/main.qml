import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import sortFilter 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: window
    visible: true
    color: "#FDFEFE"
    title: "Avn Application1"
    width: 400
    maximumWidth: 400
    maximumHeight: 700
    height: 700
    property  bool selectApplication: true

    Item {
        id: employeeInfor
        anchors.fill: parent
        Text {
            id: nameEmployee
            text: employee.getEmployeesName
            width: 400; height: 200
            font.pointSize: 18
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 10
            horizontalAlignment: Text.AlignHCenter
            lineHeight: 50
            wrapMode: Text.WordWrap
        }

        Rectangle {
            width: 400; height: 200
            anchors.left: employeeInfor.left
            anchors.leftMargin: 80
            anchors.top: employeeInfor.top
            anchors.topMargin: 60
            Component {
                id: contactDelegate
                Item {
                    width: 400; height: 50
                    Row{
                        width: parent.width
                        spacing: 30
                        Image {
                            id: name
                            width: 30
                            height: 30
                            source: icon
                        }
                        TextEdit { text: language
                            width: 40
                        }
                        TextEdit { text: point
                            width: 40
                        }
                        Image {
                            source: point > 5 ? "/data/success.png"
                                              : "/data/fail.png"
                            width: 30
                            height: 30
                        }
                    }
                }
            }

            ListView {
                anchors.fill: parent
                orientation: Qt.Vertical
                model: employee
                delegate: contactDelegate
            }
        }

        Timer {
            id: timer
            interval: 3000; running: true; repeat: true
            onTriggered:
            {
                busyind.visible = false
                tableView.visible = true
            }
        }


        Button{
            id: button
            width: 100
            height: 40
            anchors.left: employeeInfor.left
            anchors.leftMargin: 140
            anchors.top: employeeInfor.top
            anchors.topMargin: 300
            text: selectApplication ? "Refresh" : "Update"
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "blue" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "blue" }
                    }
                }
            }
            onClicked: {
                console.log("button clicked....")
                timer.start()
                busyind.visible = true
                tableView.visible = false
            }
        }
    }

    TextField {
        id: searchBox
        placeholderText: "Search Name..."
        inputMethodHints: Qt.ImhNoPredictiveText
        width: parent.width / 5 * 3
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.centerIn: parent.Center
        anchors.top: parent.top
        anchors.topMargin: 350
    }

    BusyIndicator{
        id: busyind
        visible: false
        width: 150
        height: 150
        anchors.top: parent.top
        anchors.topMargin: 450
        z: 1
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TableView {
        id: tableView
        width: 200
        height: 200
        frameVisible: false
        sortIndicatorVisible: true
        anchors.fill: parent
        Layout.minimumWidth: 500
        Layout.minimumHeight: 240
        Layout.preferredWidth: 500
        Layout.preferredHeight: 400
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 400

        TableViewColumn {
            id: nameColumn
            title: "NAME"
            role: "name"
            horizontalAlignment: Text.AlignLeft
            movable: false
            resizable: false
            width: 200
        }

        TableViewColumn {
            id: gradeColumn
            title: "AVERAGE"
            role: "average"
            horizontalAlignment: Text.AlignHCenter
            movable: false
            resizable: false
            width: 200
        }

        style: TableViewStyle{
            handle: Rectangle {
                implicitWidth: 15
                implicitHeight: 15
                color: "#C0C0C0"
            }
        }

        headerDelegate: Rectangle{
            id: recHeader
            width: styleData.width+20
            height:30
            color:"#008080"
            border.color: "black"
            border.width: 1
            Text {
                anchors.fill:parent
                text:styleData.value
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        model: SortFilterProxyModel {
            id: proxyModel
            source: employeesModel.count > 0 ? employeesModel : employeesModel
            sortOrder: tableView.sortIndicatorOrder
            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: employeesModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""
            filterString: "*" + searchBox.text + "*"
            filterSyntax: SortFilterProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
        }

        onClicked: {
            employee.requestToControllerUpdateInfor(proxyModel.get(row).name, row);
        }
    }
}

