#include <iostream>
#include <fstream>


int load_vertices(std::ofstream &ofs, const char *dir)
{
    std::string filename = std::string(dir) + "/shapeMU.txt";
    std::ifstream ifs(filename.c_str());

    if (ifs.good()) {
        char first_line[256];
        ifs.getline(first_line, 256);
        std::cout << first_line << std::endl;
        while(!ifs.eof()) {
            float x, y, z;
            ifs >> x >> y >> z;
            ofs << "v " << x / 100000 << ' ' << y / 100000 << ' ' << z / 100000 << '\n';
        }
        ifs.close();
        return 0;
    }
    else {
        return -1;
    }
}

int load_triangles(std::ofstream &ofs, const char *dir)
{
    std::string filename = std::string(dir) + "/tl.txt";
    std::ifstream ifs(filename.c_str());

    if (ifs.good()) {
        char first_line[256];
        ifs.getline(first_line, 256);
        std::cout << first_line << std::endl;

        while(!ifs.eof()) {
            int vi[3];
            ifs >> vi[0] >> vi[1] >> vi[2];
            ofs << "f " << vi[0] << " " << vi[1] << " " << vi[2] << "\n";
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
        std::string dir(argv[1]);
        std::string objfilename = dir + "/mean.obj";
        std::ofstream ofs(objfilename.c_str());

        if (ofs.good()) {

            load_vertices(ofs, dir.c_str());

            load_triangles(ofs, dir.c_str());

            ofs.close();

            return 0;
        }
        else {
            return -2;
        }
    }
}
