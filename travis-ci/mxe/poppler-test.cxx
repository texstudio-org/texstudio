#include <iostream>
#include <cpp/poppler-version.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Poppler version: " << poppler::version_string() << std::endl;

    return 0;
}
