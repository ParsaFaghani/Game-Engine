#version 330 core

// ورودی‌ها از C++
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float shininess;
uniform float constant;
uniform float linear;
uniform float quadratic;

// داده‌های ورودی از vertex shader
in vec3 FragPos;
in vec3 Normal;

// خروجی رنگ نهایی
out vec4 FragColor;

void main()
{
    // فاصله نور تا پیکسل
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

    // بردارهای نور و سطح
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // نور محیطی (ثابت، بدون افت)
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // نور diffuse (زاویه بین نور و سطح)
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // نور specular (درخشش در جهت بازتاب نور)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    // فقط diffuse و specular رو attenuate کن
    vec3 result = ambient + (diffuse + specular) * attenuation;
    result *= objectColor;

    FragColor = vec4(result, 1.0);
}