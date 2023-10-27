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
        std::string line;
        std::vector<Vertex> vertices;
        std::vector<std::vector<float> > triangles;
        void readFile();
        void makeVertexNormal();
    public:
        ParsingFile(std::string file_name);
        ~ParsingFile();
        Vertex getVerticiesFactor(int index);
        std::vector<float> getTrianglesFactor(int index);
        int getVerticesSize();
        int getTrianglesSize();
};
#endif