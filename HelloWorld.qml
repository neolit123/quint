// Welcome to quint
// A livecoding environemt for QML and OpenGL shaders 

// Press:
// F1 to toggle hiding this editor overlay
// F2/F3 to change the editor font size
// F5/F6/F7/F8 to load some examples
// Escape or top right icon to exit

Rectangle {
    property real time: parent.time	
	color: "black"
	Text {
		x: 100+100*Math.sin(parent.time)
		y: 200+100.0*Math.cos(parent.time)
		text: "Hello World"
		font.pixelSize: 200
		ColorAnimation on color {
			from: "red"
			to: "blue"
			duration: 5000
			loops: Animation.Infinite
		}
	}
}
