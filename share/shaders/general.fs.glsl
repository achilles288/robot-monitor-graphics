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
in vec3 shadowMapProj;
in vec2 texUV;
flat in int flags;

uniform DirectionalLight dirLight;
uniform Material mat;
uniform sampler2D shadowMap;

out vec3 fragColor;


float calculateShadow() {
    vec3 projCoord = 0.5f*shadowMapProj + vec3(0.5f);
    if(projCoord.x < 0.005f || projCoord.x > 0.995f ||
       projCoord.y < 0.005f || projCoord.y > 0.995f ||
       projCoord.z >= 1.0f)
    {
        return 0.0f;
    }
    
    float shadow = 0;
    vec2 texelSize = 1.0f/textureSize(shadowMap, 0);
    for(int i=-2; i<=2; i++) {
        for(int j=-2; j<=2; j++) {
            vec2 dr = texelSize * vec2(i, j);
            float pcfDepth = texture(shadowMap, projCoord.xy + dr).r;
            if(projCoord.z + 0.001f > pcfDepth)
                shadow += 0.8f;
        }
    }
    return shadow / 25;
}


void main() {
    vec3 reflDir = reflect(dirLight.direction, normalCamera);
    float smoothness = 1.0f - mat.roughness;
    float cosTheta = dot(normalCamera, -dirLight.direction);
    float cosAlpha = dot(eyeDirection, reflDir);
    
    float diff = clamp(0.7f*cosTheta + 0.3f, 0.15f, 1) * mat.roughness;
    float spec = pow(clamp(cosAlpha,0,1), 24*smoothness) * smoothness;
    
    float dirLightPow;
    if(bool(flags & (1 << 0))) { // Shadow option
        float shadow = calculateShadow();
        dirLightPow = (1-shadow) * dirLight.color.w;
    }
    else {
        dirLightPow = dirLight.color.w;
    }
    vec3 color = mat.color.xyz;
    fragColor = color * dirLight.color.xyz * dirLightPow * (diff+spec);
}
