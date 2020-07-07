#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec4 color;
};

struct Material {
    float metalness;
    float roughness;
    float ambientOcculation;
    vec4 color;
};

in vec3 normalCamera;
in vec3 eyeDirection;

uniform DirectionalLight dirLight;
uniform Material mat;

out vec3 fragColor;

void main() {
    vec3 reflDir = reflect(-dirLight.direction, normalCamera);
    float smoothness = 1.0f - mat.roughness;
    float cosTheta = dot(normalCamera, dirLight.direction);
    float cosAlpha = dot(eyeDirection, reflDir);
    
    float diff = clamp(0.7f*cosTheta + 0.3f, 0.15f, 1) * mat.roughness;
    float spec = pow(clamp(cosAlpha,0,1), 24*smoothness) * smoothness;
    
    float dirLightPow = dirLight.color.w;
    fragColor = mat.color.xyz * dirLight.color.xyz * dirLightPow * (diff+spec);
}
