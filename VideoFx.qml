import QtGraphicalEffects 1.0

Item {
	property real time: parent.time
	ShaderEffectSource {
		visible: false
		width: parent.width
		height: parent.height
		id:video
		sourceItem:videooutput
		hideSource:true
		wrapMode: ShaderEffectSource.Repeat
		smooth: true
		mipmap: true
	}
	HueSaturation {
		visible: true
		width: parent.width/2
		height: parent.height/2
		hue: parent.time*0.1
		saturation: Math.sin(parent.time)*2.0
		source: video
	}
	ZoomBlur {
		id: zb
		visible: true
		width: parent.width/2
		height: parent.height/2
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		source: video
		length: Math.sin(parent.time)*100.0
		samples: 20
		horizontalOffset: 0
		verticalOffset: 0
	}
	ShaderEffect {
		// 3D flight
		visible: true
		width: parent.width/2
		height: parent.height/2
		anchors.right: parent.right
    		property variant v: video
		property real time: parent.time
		fragmentShader: "
		varying highp vec2 qt_TexCoord0;
		uniform sampler2D v;
		uniform float time;
		void main(void)
		{
			vec2 p = -1.0 + 2.0 * qt_TexCoord0;
			vec2 uv;
			float an = time*0.1;
			float can = cos(an);
			float san = sin(an);
			float x = p.x*can-p.y*san;
			float y = p.x*san+p.y*can;
			float recipabsy = 10.0/abs(y);
			uv.x = .1*x*recipabsy;
			uv.y = 0.5*time + .1*recipabsy;
   			lowp vec4 wallcol = texture2D(v,uv);
			gl_FragColor = vec4(wallcol.xyz,1.0);
		}"
	}
	ShaderEffect {
		// Raymarched distance field
		visible: true
		width: parent.width/2
		height: parent.height/2
		anchors.bottom: parent.bottom
   		property variant v: video
		property real time: parent.time
		fragmentShader: "
		varying highp vec2 qt_TexCoord0;
		uniform sampler2D v;
		uniform float time;
		uniform float width;
		uniform float height;
		void main(void)
		{
			vec2 p = qt_TexCoord0*2.-1.;
			vec2 q = p*vec2(width/height,1.0);
			float z = 0.;
			float w = 0.;
			vec3 r=normalize(vec3(q,1.));
			vec3 a;
			for(int i=0;i<9;i++){
				a=r*z;
                                a=mod(a+vec3(time*.2,time*.1,time*.2),2.)-1.;
				w=length(a)-.4;
				z+=w;
			}
			a = r*z;
			vec2 a2 = vec2(a.x+time*.2,a.y+.5);
			float d = length(a);
			vec2 tc = mod(a2,1.);
			lowp vec4 vc = texture2D(v,tc)*(1.-d*.2);
			gl_FragColor = vec4(vc.rgb,1.0);
		}"
	}
	DropShadow {
		visible: true
		anchors.fill:qt
		source: qt
		radius: 10
		samples:10
		spread: 0.2
		horizontalOffset:3
		verticalOffset:3
		cached: true
		transparentBorder: true
	}
	Image {
		id: qt
		source: "qt.png"
		anchors.centerIn: parent
	}
}
