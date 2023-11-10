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
    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        v1 = makeVector(triangles[i].position, triangles[i + 1].position);
        v2 = makeVector(triangles[i].position, triangles[i + 2].position);
        normal = makeNormal(v1, v2);
        if (triangles[i].normal.x.same(0, 0) && triangles[i].normal.y.same(0, 0) && triangles[i].normal.z.same(0, 0))
            triangles[i].normal = normal;
        else
        {
            triangles[i].normal = triangles[i].normal + normal;
            triangles[i].normal = triangles[i].normal / 2;
            triangles[i].normal.normalized();
        }

        v1 = makeVector(triangles[i + 1].position, triangles[i + 2].position);
        v2 = makeVector(triangles[i + 1].position, triangles[i].position);
        normal = makeNormal(v1, v2);
        if (triangles[i + 1].normal.x.same(0, 0) && triangles[i + 1].normal.y.same(0, 0) && triangles[i + 1].normal.z.same(0, 0))
            triangles[i + 1].normal = normal;
        else
        {
            triangles[i + 1].normal = triangles[i + 1].normal + normal;
            triangles[i + 1].normal = triangles[i + 1].normal / 2;
            triangles[i + 1].normal.normalized();
        }

        v1 = makeVector(triangles[i + 2].position, triangles[i].position);
        v2 = makeVector(triangles[i + 2].position, triangles[i + 1].position);
        normal = makeNormal(v1, v2);
        if (triangles[i + 2].normal.x.same(0, 0) && triangles[i + 2].normal.y.same(0, 0) && triangles[i + 2].normal.z.same(0, 0))
            triangles[i + 2].normal = normal;
        else
        {
            triangles[i + 2].normal = triangles[i + 2].normal + normal;
            triangles[i + 2].normal = triangles[i + 2].normal / 2;
            triangles[i + 2].normal.normalized();
        }
    }
}

static
bool mystrncmp(char *line, char *cmp, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (cmp[i] != line[i])
            return false;
    }
    return true;
}

static
void parsingPosition(char *line, char *str1, Vector3 &ver)
{
    int start, end, idx, flag;
    start = 2;
    flag = 0;
    char *endl;
    while (line[start] != '\0' && line[start] != '\n')
    {
        end = start;
        idx = 0;
        while(line[end] != '\0' && line[end] != ' ' && line[end] != '\n')
        {
            str1[idx] = line[end];
            end++;
            idx++;
        }
        str1[idx] = '\0';
        if (flag == 0)
        {
            ver.x = strtof(str1, &endl);
            flag++;
        }
        else if (flag == 1)
        {
            ver.y = strtof(str1, &endl);
            flag++;
        }
        else
            ver.z = strtof(str1, &endl);
        start = end + 1;
    }
}

static
void parsingNormal(char *line, char *str1, Vector3 &ver)
{
    int start, end, idx, flag;
    start = 3;
    flag = 0;
    char *endl;
    while (line[start] != '\0' && line[start] != '\n')
    {
        end = start;
        idx = 0;
        while(line[end] != '\0' && line[end] != ' ' && line[end] != '\n')
        {
            str1[idx] = line[end];
            end++;
            idx++;
        }
        str1[idx] = '\0';
        if (flag == 0)
        {
            ver.x = strtof(str1, &endl);
            flag++;
        }
        else if (flag == 1)
        {
            ver.y = strtof(str1, &endl);
            flag++;
        }
        else
            ver.z = strtof(str1, &endl);
        start = end + 1;
    }
}

void ParsingFile::parsingTriangle(char *line, char *str1, std::vector<Vertex>& vec)
{
    int start, end, idx, mid;
    int index;
    start = 2;
    Vertex vert;
    
    vert.normal.x = 0;
    vert.normal.y = 0;
    vert.normal.z = 0;
    while (line[start] != '\0' && line[start] != '\n')
    {
        end = start;
        idx = 0;
        while(line[end] != '\0' && line[end] != ' ' && line[end] != '\n')
        {
            str1[idx] = line[end];
            end++;
            idx++;
        }
        str1[idx] = '\0';
        mid = 0;
		index = 0;
        while (str1[mid] != '\0' && str1[mid] != '/')
        {
            index *= 10;
            index += str1[mid] - '0';
            mid++;
        }
        vert.position.x = vertices[index - 1].x;
        vert.position.y = vertices[index - 1].y;
        vert.position.z = vertices[index - 1].z;
        vert.position.w = 1;
        if (str1[mid] != '\0')
        {
            while(str1[mid] == '/')
                mid++;
            index = 0;
            while (str1[mid] != '\0')
            {
                index *= 10;
                index += str1[mid] - '0';
                mid++;
            }
            vert.normal = normals[index - 1];
        }
        vec.push_back(vert);
        start = end + 1;
    }
}

void ParsingFile::readFile()
{
    char* c_line = nullptr;
    size_t len = 0;
    char str1[200];
    Vector3 vect;
    std::vector<float> coordinates;
    int normalFlag = 0;
    FILE* input_file = fopen(file_name.c_str(), "r");

    if (input_file == nullptr) return ;
    
    while ((getline(&c_line, &len, input_file)) != -1)
    {
        if (mystrncmp(c_line, const_cast<char*>("v "), 2))
        {
            parsingPosition(c_line, str1, vect);
            vertices.push_back(vect);
        }
        else if (mystrncmp(c_line, const_cast<char*>("vn "), 3))
        {
			parsingNormal(c_line, str1, vect);
            normals.push_back(vect);
            normalFlag = 1;
        }
        else if (mystrncmp(c_line, const_cast<char*>("f "), 2))
        {
			parsingTriangle(c_line, str1, triangles);
        }
    }
    free(c_line);
    fclose(input_file);
    if (normalFlag == 0)
        makeVertexNormal();
}


Vertex ParsingFile::getTrianglesFactor(int index)
{
    return triangles[index];
}

int ParsingFile::getTrianglesSize()
{
    return triangles.size();
}