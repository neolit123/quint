ShaderEffect {
    property variant r: minirasp
    property variant q: qtlogo
    property real time: parent.time
    fragmentShader: "
        varying highp vec2 qt_TexCoord0;
        uniform sampler2D r;
        uniform sampler2D q;
        uniform float time;
        void main(void)
        {
            vec2 p = -1.0 + 2.0 * qt_TexCoord0;
            vec2 uv;
            float an = time*.25;
            float can = cos(an);
            float san = sin(an);
            float x = p.x*can-p.y*san;
            float y = p.x*san+p.y*can;
            float recipabsy = 1.0/abs(y);
            uv.x = 1.0*x*recipabsy;
            uv.y = 1.0*time + 1.0*recipabsy;
            lowp vec4 wallcol = texture2D(r,uv);
            gl_FragColor = vec4(wallcol.xyz * y*y, y*y);
        }"
}
