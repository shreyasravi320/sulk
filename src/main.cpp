#include "include/sulk.h"

int main()
{
    try
    {
        Sulk sulk = Sulk();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}