#version 410
layout (location=0) in vec3 position;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;
out vec4 varyingColor;
mat4 rotateX(float rad);
mat4 rotateY(float rad);
mat4 rotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);
void main(void)
{
    float i = gl_InstanceID + tf;
    float a = sin(201.0 * i/8000) * 403.0f;
    float b = sin(301.0 * i/8000) * 401.0f;
    float c = sin(400.0 * i/8000) * 405.0f;

    mat4 localRotX = rotateX(i*2);
    mat4 localRotY = rotateX(i*2);
    mat4 localRotZ = rotateX(i*2);
    mat4 localTrans = buildTranslate(a,b,c);

    mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * newM_matrix;

    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) *0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}
mat4 buildTranslate(float x, float y, float z)
{
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    x, y, z, 1.0 );
    return trans;
}

mat4 buildScale(float x, float y, float z)
{
    mat4 scale = mat4(x, 0.0, 0.0, 0.0,
    0.0, y, 0.0, 0.0,
    0.0, 0.0, z, 0.0,
    0.0, 0.0, 0.0, 1.0 );
    return scale;
}

mat4 rotateX(float rad)
{
    mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
    0.0, cos(rad), -sin(rad), 0.0,
    0.0, sin(rad), cos(rad), 0.0,
    0.0, 0.0, 0.0, 1.0 );
    return xrot;
}

mat4 rotateY(float rad)
{
    mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
    0.0, 1.0, 0.0, 0.0,
    -sin(rad), 0.0, cos(rad), 0.0,
    0.0, 0.0, 0.0, 1.0 );
    return yrot;
}

mat4 rotateZ(float rad)
{
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
    sin(rad), cos(rad), 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0 );
    return zrot;
}
