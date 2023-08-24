#type vertex
#version 330 core

layout (location = 0) in vec2 aPos;
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
    gl_Position = uProjection * uView * vec4(aPos, 1.0, 1.0);
}

#type fragment
#version 330 core

uniform sampler2D uTexture;

in vec4 fColor;
in vec2 fTextCoords;
in float fTexId;

out vec4 FragColor;

void main() {
    if (fTexId >= 0) {
        FragColor = fColor * texture(uTexture, fTextCoords);

    } else {
        FragColor = fColor;
    }
}
