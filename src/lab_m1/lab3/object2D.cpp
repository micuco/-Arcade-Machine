#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(std::string name, glm::vec3 center,
    float radius, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    const int segments = 40;   // cu cât mai mare, cu atât cercul e mai „neted”

    // centru (pentru varianta fill)
    vertices.emplace_back(center, color);

    // punctele de pe circumferin??
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * (float)M_PI * i / segments;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        vertices.emplace_back(glm::vec3(x, y, center.z), color);
    }

    Mesh* circle = new Mesh(name);

    if (fill)
    {
        // triangle fan: 0 = centru, 1..segments+1 = cerc
        for (int i = 1; i <= segments; i++)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
        circle->SetDrawMode(GL_TRIANGLES);
    }
    else
    {
        // doar contur (line loop peste punctele de pe circumferin??)
        for (int i = 1; i <= segments; i++)
            indices.push_back(i);
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

