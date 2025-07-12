#pragma once

#include <GlowML.h>
#include <string>

std::string parseGlowML(const std::string& glowml) {
    std::string version = GLOWML_VERSION; // Use the version defined in GlowML.h
    std::string output = glowml;

    size_t pos = output.find("<glowml>");
    if (pos != std::string::npos) {
        output.replace(pos, 8, "<parsed>");
    }

    return "Parsed GlowML: " + output;
}