
#include <vector>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    (void)argc;

    std::vector<char> empty(1024, 0);
    std::ofstream ofs(argv[1], std::ios::binary | std::ios::out);

    for(int i = 0; i < 1024*8; i++)
    {
        if (!ofs.write(&empty[0], empty.size()))
        {
            std::cerr << "problem writing to file" << std::endl;
            return 255;
        }
    }

    ofs.close();

    return 0;
}
