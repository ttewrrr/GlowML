#include <GlowML.h>
#include <string>
#include <sstream>
#include <regex>
#include <unordered_map>

std::string parseGlowML(const std::string &glowml)
{
    std::istringstream iss(glowml);
    std::ostringstream oss;
    std::string line;
    std::string version = GLOWML_VERSION;
    std::unordered_map<std::string, std::string> variables;

    // Try to extract version from GlowML file
    std::regex versionRegex(R"(<glowml\s+(v[\d\.]+)>)");
    std::smatch match;
    if (std::getline(iss, line))
    {
        if (std::regex_search(line, match, versionRegex) && match.size() > 1)
        {
            version = match[1];
        }
    }

    // Professional comment and HTML boilerplate
    oss << "<!-- Generated by GlowML " << version << " -->\n";
    oss << "<!DOCTYPE html>\n<html>\n";

    // First pass: extract variables
    std::vector<std::string> contentLines;
    std::regex varRegex(R"(^\s*var\s+(\w+)\s*=\s*\"([^\"]*)\")");
    do
    {
        if (std::regex_search(line, match, varRegex) && match.size() > 2)
        {
            variables[match[1]] = match[2];
        }
        else
        {
            contentLines.push_back(line);
        }
    } while (std::getline(iss, line));

    // Second pass: process content and substitute variables
    for (const auto &rawLine : contentLines)
    {
        std::string line = rawLine;
        if (line.find("<main>") != std::string::npos)
        {
            oss << "<body>\n";
        }
        else if (line.find("</main>") != std::string::npos)
        {
            oss << "</body>\n";
        }
        else if (line.find("<header>") != std::string::npos)
        {
            oss << "<header>\n";
        }
        else if (line.find("</header>") != std::string::npos)
        {
            oss << "</header>\n";
        }
        else if (line.find("<content>") != std::string::npos)
        {
            oss << "<main>\n";
        }
        else if (line.find("</content>") != std::string::npos)
        {
            oss << "</main>\n";
        }
        else if (line.find("<footer>") != std::string::npos)
        {
            oss << "<footer>\n";
        }
        else if (line.find("</footer>") != std::string::npos)
        {
            oss << "</footer>\n";
        }
        else if (line.find("<glowml") == 0)
        {
            // Skip GlowML version tag
            continue;
        }
        else
        {
            // Substitute variables in the line
            std::regex varRef(R"(\{(\w+)\})");
            std::string replaced;
            std::sregex_iterator it(line.begin(), line.end(), varRef);
            std::sregex_iterator end;
            size_t lastPos = 0;
            replaced.reserve(line.size());
            for (; it != end; ++it)
            {
                replaced.append(line, lastPos, it->position() - lastPos);
                std::string varName = (*it)[1];
                auto found = variables.find(varName);
                if (found != variables.end())
                {
                    replaced.append(found->second);
                }
                else
                {
                    replaced.append(it->str());
                }
                lastPos = it->position() + it->length();
            }
            replaced.append(line, lastPos, std::string::npos);
            oss << replaced << "\n";
        }
    }

    oss << "</html>\n";
    return oss.str();
}