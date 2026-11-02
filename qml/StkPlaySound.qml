/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtMultimedia 5.15

Rectangle {
    id: container
    color: "#2c3e50"
    width: 200
    height: 100

    property string source: ""

    MediaPlayer {
        id: player
        source: container.source
        audio.Output {
            id: audioOutput
        }
    }

    Button {
        text: qsTr("Play Sound")
        anchors.centerIn: parent
        onClicked: player.play()
    }
}
