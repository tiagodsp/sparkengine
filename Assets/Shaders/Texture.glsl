#type vertex
#version 330 core
            
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec4 v_Color;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    v_Position = a_Position;
    v_Normal = a_Normal;
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord);
    //color = vec4(v_TexCoord,0,1);
    //color = vec4(1,0,0,1);
    //color  = vec4(v_Normal, 1);
}