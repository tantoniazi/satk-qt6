/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: container
    color: "#2c3e50"
    width: 300
    height: 200

    property string titleText: "Enter Password"
    property string passwordText: ""

    signal accepted(string password)
    signal rejected()

    Text {
        id: title
        text: titleText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        color: "#ecf0f1"
        font.pixelSize: 18
        font.bold: true
    }

    TextField {
        id: passwordField
        objectName: "passwordField"
        text: passwordText
        echoMode: TextField.Password
        anchors.top: title.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        width: 200
        font.pixelSize: 14
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        spacing: 20

        Button {
            text: qsTr("OK")
            onClicked: container.accepted(passwordField.text)
        }

        Button {
            text: qsTr("Cancel")
            onClicked: container.rejected()
        }
    }
}
