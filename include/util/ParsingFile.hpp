#ifndef PARSINGFILE_HPP
#define PARSINGFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "rasterizer/Vertex.hpp"
#include <string>

class ParsingFile
{
    private:
        std::string file_name;
        std::vector<Vector3> vertices;
        std::vector<Vertex> triangles;
        std::vector<Vector3> normals;
        void readFile();
        void makeVertexNormal();
        void parsingTriangle(char *line, char *str1, std::vector<Vertex>& vec);
    public:
        ParsingFile(std::string file_name);
        ~ParsingFile();
        Vertex getTrianglesFactor(int index);
        int getTrianglesSize();
};
#endif