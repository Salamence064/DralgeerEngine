    #type vertex
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec4 aColor;
    layout (location = 2) in vec2 aTexCoords;
    layout (location = 3) in float aTexId;

    uniform mat4 uProjection;
    uniform mat4 uView;

    out vec4 fColor;
    out vec2 fTextCoords;
    out float fTexId;

    void main() {
        fColor = aColor;
        fTextCoords = aTexCoords;
        fTexId = aTexId;
        gl_Position = uProjection * uView * vec4(aPos, 1.0);
    }

    #type fragment
    #version 330 core

    uniform sampler2D uTexture[16]; // todo at some point use openGL to get the total number of slots available

    in vec4 fColor;
    in vec2 fTextCoords;
    in float fTexId;

    out vec4 FragColor;

    void main() {
        if (fTexId >= 0) {
            int id  = int (fTexId);
            FragColor = fColor * texture(uTexture[id], fTextCoords);

        } else {
            FragColor = fColor;
        }
    }

    /* Personal guide to shader techniques:
     * 1. taking the average of the 3 colors and setting each equal to that will result in a black and white image.
     * 2. taking the sin of the time and multiplying it by the color results in a fading to black and back to the color.
     * 3. noise function makes static -- float noise = fract(sin(dot(fColor.xy, vec2(12.9898, 78.233))) * 43758.5453);
     *
     */
