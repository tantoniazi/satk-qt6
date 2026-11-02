/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: button
    objectName: "stkButton"
    text: qsTr("")
    font.pixelSize: 16
    background: Rectangle {
        color: button.down ? "#34495e" : "#2c3e50"
        radius: 4
        border.color: "#ecf0f1"
        border.width: 1
    }
    contentItem: Text {
        text: button.text
        font: button.font
        color: "#ecf0f1"
    }
}
