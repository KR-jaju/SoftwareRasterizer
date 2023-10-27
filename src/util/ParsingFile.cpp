#include "util/ParsingFile.hpp"

ParsingFile::ParsingFile(std::string file_name) : file_name(file_name)
{
    readFile();
}

ParsingFile::~ParsingFile()
{
}

static
Vector3 makeVector(Vector4 &start, Vector4 &end)
{
    Vector3 res;

    res.x = end.x - start.x;
    res.y = end.y - start.y;
    res.z = end.z - start.z;
    return res;
}

static
Vector3 makeNormal(Vector3 &v1, Vector3 &v2)
{
    Vector3 res;
    res = v1.cross(v2);
    res.normalized();
    return res;
}

void ParsingFile::makeVertexNormal()
{
    Vector3 v1, v2, normal;
    for (size_t i = 0; i < triangles.size(); i++)
    {
        v1 = makeVector(vertices[triangles[i][0]].position, vertices[triangles[i][1]].position);
        v2 = makeVector(vertices[triangles[i][0]].position, vertices[triangles[i][1]].position);
        normal = makeNormal(v1, v2);
        if (vertices[triangles[i][0]].normal.x == 0 && vertices[triangles[i][0]].normal.y == 0 && \
            vertices[triangles[i][0]].normal.z == 0)
            vertices[triangles[i][0]].normal = normal;
        else
        {
            vertices[triangles[i][0]].normal = vertices[triangles[i][0]].normal + normal;
            vertices[triangles[i][0]].normal = vertices[triangles[i][0]].normal / 2;
            vertices[triangles[i][0]].normal.normalized();
        }

        v1 = makeVector(vertices[triangles[i][1]].position, vertices[triangles[i][2]].position);
        v2 = makeVector(vertices[triangles[i][1]].position, vertices[triangles[i][0]].position);
        normal = makeNormal(v1, v2);
        if (vertices[triangles[i][1]].normal.x == 0 && vertices[triangles[i][1]].normal.y == 0 && \
            vertices[triangles[i][1]].normal.z == 0)
            vertices[triangles[i][1]].normal = normal;
        else
        {
            vertices[triangles[i][1]].normal = vertices[triangles[i][1]].normal + normal;
            vertices[triangles[i][1]].normal = vertices[triangles[i][1]].normal / 2;
            vertices[triangles[i][1]].normal.normalized();
        }

        v1 = makeVector(vertices[triangles[i][2]].position, vertices[triangles[i][0]].position);
        v2 = makeVector(vertices[triangles[i][2]].position, vertices[triangles[i][1]].position);
        normal = makeNormal(v1, v2);
        if (vertices[triangles[i][2]].normal.x == 0 && vertices[triangles[i][2]].normal.y == 0 && \
            vertices[triangles[i][2]].normal.z == 0)
            vertices[triangles[i][2]].normal = normal;
        else
        {
            vertices[triangles[i][2]].normal = vertices[triangles[i][2]].normal + normal;
            vertices[triangles[i][2]].normal = vertices[triangles[i][2]].normal / 2;
            vertices[triangles[i][2]].normal.normalized();
        }
    }
}

void ParsingFile::readFile()
{
    char* c_line = nullptr;
    size_t len = 0;
    std::string str1, str2;
    Vertex vertex;
    std::vector<float> coordinates;

    FILE* input_file = fopen(file_name.c_str(), "r");
    if (input_file == nullptr) return ;
    
    vertex.normal.x = 0;
    vertex.normal.y = 0;
    vertex.normal.z = 0;

    while ((getline(&c_line, &len, input_file)) != -1)
    {
        line = c_line;
        if (line.substr(0, line.find(" ")) == "v")
        {
            str1 = line.substr(line.find(" ") + 1);
            str2 = str1.substr(0, str1.find(" "));
            vertex.position.x = std::stof(str2);
            str1 = str1.substr(str1.find(" ") + 1);
            str2 = str1.substr(0, str1.find(" "));
            vertex.position.y = std::stof(str2);
            str1 = str1.substr(str1.find(" ") + 1);
            vertex.position.z = std::stof(str1);
            vertex.position.w = 1;
            vertices.push_back(vertex);
        }
        else if (line.substr(0, line.find(" ")) == "f")
        {
            coordinates.clear();
            str1 = line.substr(line.find(" ") + 1);
            str2 = str1.substr(0, str1.find(" "));
            coordinates.push_back(std::stod(str2) - 1);
            str1 = str1.substr(str1.find(" ") + 1);
            str2 = str1.substr(0, str1.find(" "));
            coordinates.push_back(std::stod(str2) - 1);
            str1 = str1.substr(str1.find(" ") + 1);
            coordinates.push_back(std::stod(str1) - 1);
            triangles.push_back(coordinates);
        }
    }
    free(c_line);
    fclose(input_file);
    makeVertexNormal();
}

Vertex ParsingFile::getVerticiesFactor(int index)
{
    return vertices[index];
}

std::vector<float> ParsingFile::getTrianglesFactor(int index)
{
    return triangles[index];
}

int ParsingFile::getVerticesSize()
{
    return vertices.size();
}

int ParsingFile::getTrianglesSize()
{
    return triangles.size();
}