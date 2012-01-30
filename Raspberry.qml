ShaderEffect {
    property variant r: rasp
    property variant q: qtlogo
    property real time: parent.time
    fragmentShader: "
        varying highp vec2 qt_TexCoord0;
        uniform sampler2D r;
        uniform sampler2D q;
        uniform float time;
        void main(void)
        {
            highp vec2 scale = vec2(16.0/9.0,1.0);
            highp vec2 offset = vec2(-0.7,0.0);
            highp vec2 coords = clamp(qt_TexCoord0*scale+offset,0.,1.);
            lowp vec4 rcol = texture2D(r,coords);
            gl_FragColor = rcol*vec4(1.0,1.0,1.0,1.0);
        }"
    Text {
        text: "This is a\nRaspberry"
        color: "red"
        font.pixelSize: 100
        x: 100; y: 400
    }
}

