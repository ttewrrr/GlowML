#include <GlowML.h>
#include <iostream>
#include <fileio.h>
#include <parser.h>
#include <converter.h>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.glowml>" << std::endl;
        return 1;
    }
    std::cout << "GlowML Version: " << GLOWML_VERSION << std::endl;
    std::string glowml = readFile(argv[1]);
    std::string parsed = parseGlowML(glowml);
    std::string converted = convertToHTML(parsed);
    writeFile("output.html", converted);
    std::cout << "Conversion complete. Output written to output.html" << std::endl;
    return 0;
}