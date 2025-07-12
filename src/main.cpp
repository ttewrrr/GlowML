#include <GlowML.h>
#include <iostream>
#include <fileio.h>
#include <parser.h>
#include <converter.h>
#include <string>

int main () {
    std::cout << "GlowML Version: " << GLOWML_VERSION << std::endl;
    std::string glowml = readFile("example.glowml");
    std::string parsed = parseGlowML(glowml);
    std::string converted = convertToHTML(parsed);
    writeFile("output.html", converted);
    std::cout << "Conversion complete. Output written to output.html" << std::endl;
    return 0;
}