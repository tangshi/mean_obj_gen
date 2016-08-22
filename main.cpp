#include <iostream>
#include <fstream>
#include "obj.h"

int load_vertices(obj *mean_obj, const char *dir)
{
    std::string filename = dir + "/shapeMU.txt";
    std::ifstream ifs(filename.c_str());

    if (ifs.good()) {
        char first_line[256];
        ifs.getline(first_line, 256);
        std::cout << first_line << std::endl;
        while(!ifs.eof()) {
            float pos[3];
            ifs >> pos[0] >> pos[1] >> pos[2];
            int vi = obj_add_vert(mean_obj);
            obj_set_vert_v(mean_obj, vi, pos);
        }
        ifs.close();
        return 0;
    }
    else {
        return -1;
    }
}

int load_triangles(obj *mean_obj, const char *dir)
{
    std::string filename = dir + "/tl.txt";
    std::ifstream ifs(filename.c_str());

    if (ifs.good()) {
        char first_line[256];
        ifs.getline(first_line, 256);
        std::cout << first_line << std::endl;
        int si = obj_add_surf(mean_obj);
        while(!ifs.eof()) {
            int vi[3];
            ifs >> vi[0] >> vi[1] >> vi[2];
            int pi = obj_add_poly(mean_obj, si);
            obj_set_poly(mean_obj, si, pi, vi);
        }
        ifs.close();
        return 0;
    }
    else {
        return -1;
    }
    
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: %s dir" << std::endl;
        std::cout << "option dir specifies the input and output dir path" << std::endl;
        return -1;
    }
    else {
        obj * mean_obj = obj_create(NULL);

        load_vertices(mean_obj);

        load_triangles(mean_obj);

        std::string objfilename = argv[1] + "/mean.obj";
        obj_write(mean_obj, objfilename.c_str(), NULL, 6);

        return 0;
    }
}
