/*
quint: quint.qml

Copyright (C) 2012 Andrew Baldwin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    // Default window size, can be resized by user or fullscreening
    width: 1280
    height: 720
    color: "white"

    // Here should be whatever the user has made
    Item {
        id: tester
        anchors.fill: parent
        property string program: editor.text
        property variant item
        onProgramChanged: createTimer.restart()
        Timer {
            id: createTimer
            interval: 1000
            running: true
            onTriggered: {
                var newItem;
                try {
                    newItem = Qt.createQmlObject("import QtQuick 2.0\n"+tester.program,tester, "testee");
                }

                catch (err) {
                    var lines = err.qmlErrors[0].lineNumber-2;
                    var col = err.qmlErrors[0].columnNumber;
                    var skip=0;
                    var i=0;
                    for (i=0;i<tester.program.length;i++) {
                        if (tester.program[i]=="\n") { skip++; lines--; }
                        if (lines==0) col--;
                        if (col==0) break;
                    }
                    i += skip;
                    // Highlight from i to i+1
                    //editor.selectionStart = i;
                    //editor.selectionStart = i+1;
                    error.text = err.qmlErrors[0].lineNumber+":"+err.qmlErrors[0].message;
                    //editor.select(i,i+1);
                }

                if (newItem) {
                    error.text = "";
                    newItem.anchors.fill = tester;
                    if (tester.item) {
                        tester.item.destroy();
                    }
                    tester.item = newItem;
                    // Good program, so save it for posterity
                    codemodel.program = tester.program;
                }
            }
        }
        ShaderEffectSource {
            id: rasp
            smooth: true
            sourceItem: Image { source:"Raspberry.png"; smooth: true; }
            wrapMode: ShaderEffectSource.Repeat
            mipmap: true
        }
        ShaderEffectSource {
            id: minirasp
            smooth: true
            sourceItem: Image { source:"MiniRaspberry.png"; smooth: true; }
            wrapMode: ShaderEffectSource.Repeat
            //mipmap: true
        }
        ShaderEffectSource {
            id: qtlogo
            smooth: true
            sourceItem: Image { source:"qt-logo.png"; smooth: true; }
            wrapMode: ShaderEffectSource.Repeat
            //mipmap: true
        }
        MediaPlayer {
            id: mp
            source: "big_buck_bunny_720p_surround.avi"
            // playing: false
            Component.onCompleted: {
                playTimer.start();
            }
        }
        Timer {
            id: playTimer
            interval: 5000
            running: true
            onTriggered: {
                mp.playing = true;
            }
        }
        VideoOutput { id:videooutput; source: mp; anchors.fill: parent; visible: false}
        property real time
        NumberAnimation on time {from: 0; to: Math.PI * 2; duration: 5000; loops:Animation.Infinite; running:true}
    }
    // Quit button

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        width: 30
        height: 30
        color: "Grey"
        opacity: 0.5
        Text {
            anchors.centerIn: parent
            color: "white"
            text: "X"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    // Here's the code editor
    Rectangle {
        id: editorParent
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height*0.66
        focus: true
        color: "#7F000000"
        opacity: 1.0
        Behavior on opacity { NumberAnimation { duration: 200 } }
        Keys.onPressed: {
            if (event.key == Qt.Key_Return) {
                codemodel.publish();
            } else if (event.key == Qt.Key_Escape) {
                Qt.quit(); // Tired of using the mouse to quit
            } else if (event.key == Qt.Key_F1) {
                opacity = (opacity==1.0)?0.0:1.0;
            } else if (event.key == Qt.Key_F2) {
                editor.fontScale *= 1.1;
            } else if (event.key == Qt.Key_F3) {
                editor.fontScale /= 1.1;
            } else if (event.key == Qt.Key_F5) {
                editor.text = codemodel.list[1];
            } else if (event.key == Qt.Key_F6) {
                editor.text = codemodel.list[2];
            } else if (event.key == Qt.Key_F7) {
                editor.text = codemodel.list[3];
            } else if (event.key == Qt.Key_F8) {
                editor.text = codemodel.list[4];
            } else if (event.key == Qt.Key_F9) {
                editor.text = codemodel.list[5];
            }

            // console.log(event.key,event.modifiers);
        }

        Flickable {
            id: flick

            anchors.fill: parent
            anchors.leftMargin: 20
            contentWidth: editor.paintedWidth
            contentHeight: editor.paintedHeight

            function ensureVisible(r)
            {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }

            TextEdit {
                id: editor
                text: codemodel.list[0]

                function insert(s) {
                    var before = text.slice(0,cursorPosition);
                    var after = text.slice(cursorposition,text.length-cursorPosition);
                    text = before+s+after;
                }

                height: editorParent.height
                color: "white"
                property real fontScale: 1.0
                font.pointSize: 25*fontScale
                font.family: "Courier"
                Behavior on fontScale { NumberAnimation { duration: 500; easing.type: Easing.InOutQuint } }
                cursorVisible: true
                focus: true
                activeFocusOnPress: true
                onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                cursorDelegate: ShaderEffect {
                    width: 10
                    blending: true
                    fragmentShader: "
                        varying highp vec2 qt_TexCoord0;
                        uniform highp float qt_Opacity;
                        void main(void)
                        {
                            highp float xfunc = smoothstep(0.0,0.1,qt_TexCoord0.x)*smoothstep(1.0,0.1,qt_TexCoord0.x);
                            highp float yfunc = smoothstep(0.0,0.2,qt_TexCoord0.y)*smoothstep(1.0,0.8,qt_TexCoord0.y);
                            gl_FragColor = vec4(1.0,1.0,0.0,1.0)*xfunc*yfunc*qt_Opacity;
                        }"
                }
            }
        }
    }

    // Box for code errors
    Text {
        id: error
        width: editorParent.width
        anchors.top: editorParent.bottom
        font.pointSize: 25*editor.fontScale
        text: ""
        color: "red"
    }

    ShaderEffect {
        // This is the mouse cursor
        // Needed on Raspberry Pi when you have no desktop environment
        id: mousecursor
        width: 21
        height: 21
        x: view.cursorpos.x-10
        y: view.cursorpos.y-10
        blending: true
        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform highp float qt_Opacity;
            void main(void)
            {
                gl_FragColor = vec4(1.0)*clamp(1.0-length(qt_TexCoord0-vec2(0.5,0.5))*4.0,0.0,1.0)*qt_Opacity;
            }"
    }

    Text {
        text: view.fps
        color: "gray"
    }

    Rectangle { width: 1; height: 1; color: "white" } // Workaround bug when shadereffects don't compile
}
