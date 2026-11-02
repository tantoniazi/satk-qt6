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
    height: 180

    property string titleText: "Confirm"
    property string messageText: ""

    signal accepted()
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

    Text {
        id: message
        text: messageText
        anchors.top: title.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 30
        color: "#bdc3c7"
        font.pixelSize: 14
        wrapMode: Text.WordWrap
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        spacing: 20

        Button {
            text: qsTr("Yes")
            onClicked: container.accepted()
        }

        Button {
            text: qsTr("No")
            onClicked: container.rejected()
        }
    }
}
