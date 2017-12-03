/*
 * This file is part of MXE. See LICENSE.md for licensing information.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <hunspell.hxx>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    std::ofstream dic ("hunspell-test.dic");
    dic << "2\nHello\nWorld";
    dic.close();
    std::ofstream aff ("hunspell-test.aff");
    aff << "SET UTF-8\nTRY loredWH\nMAXDIFF 1";
    aff.close();
    Hunspell h("hunspell-test.aff", "hunspell-test.dic");

    if (h.spell(std::string("Hello")) == 0)
    {
        std::cerr << "Error: hunspell marked correct word as wrong" << std::endl;
    }
    if (h.spell(std::string("wrld")) != 0)
    {
        std::cerr << "Error: hunspell marked wrong word as correct" << std::endl;
    }

    std::vector<std::string> result;
    result = h.suggest(std::string("ell"));
    for (unsigned int i = 0; i < result.size(); i++) std::cout << result[i];

    return 0;
}
