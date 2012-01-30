ShaderEffect {
    property variant r: qtlogo
    property variant q: rasp
    property real time: parent.time
    fragmentShader: "
        varying highp vec2 qt_TexCoord0;
        uniform sampler2D r;
        uniform sampler2D q;
        uniform float time;
        void main(void)
        {
            vec2 p = (-1.0 + 2.0 * qt_TexCoord0)*vec2(1.33,1.0);
            vec2 cc = vec2( cos(.25*time), sin(.25*time*1.423) );
            float dmin = 1000.0;
            vec2 zmin = vec2(1000.0,1000.0);
            vec2 z  = p*vec2(1.33,1.0);
            vec2 z2  = z*z;
            float z2s = z2.x+z2.y;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            lowp vec4 color1 = texture2D(q,sqrt(zmin*0.7)+vec2(0.5,0.5));
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            z = cc+vec2(z2.x-z2.y,2.0*z.x*z.y);z2s=z2.x+z2.y;if(z2s<dmin){dmin=z2s;zmin=z2;};z2=z*z;
            lowp vec4 color = texture2D(q,sqrt(zmin*0.7)+vec2(0.5,0.5));
            gl_FragColor = mix(color1,color,color.a);//vec4(zmin.x,zmin.y,color,1.0);
        }
    "
}
