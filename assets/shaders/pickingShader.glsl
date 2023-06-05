#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCords;
layout (location = 3) in float aTexId;
layout (location = 4) in float aEntityId;

uniform mat4 uProjection;
uniform mat4 uView;

out vec4 fColor;
out vec2 fTextCords;
out float fTexId;
out float fEntityId;

void main() {
    fColor = aColor;
    fTextCords = aTexCords;
    fTexId = aTexId;
    fEntityId = aEntityId;
    gl_Position = uProjection * uView * vec4(aPos, 1.0);
}

#type fragment
#version 330 core

uniform sampler2D uTextures[16]; // todo at some point use openGL to get the total number of slots available

in vec4 fColor;
in vec2 fTextCords;
in float fTexId;
in float fEntityId;

out vec4 color;

void main() {
    vec4 texColor = vec4(1, 1, 1, 1);

    if (fTexId > 0) {
        int id  = int (fTexId);
        color = fColor * texture(uTextures[id], fTextCords);

    }

    if (texColor.a  < 0.5) { discard; }
    color = vec4(fEntityId, fEntityId, fEntityId, fEntityId);
}

/* Personal guide to shader techniques:
 * 1. taking the average of the 3 colors and setting each equal to that will result in a black and white image.
 * 2. taking the sin of the time and multiplying it by the color results in a fading to black and back to the color.
 * 3. noise function makes static -- float noise = fract(sin(dot(fColor.xy, vec2(12.9898, 78.233))) * 43758.5453);
 *
 */
