#pragma once

constexpr const char* GLOWML_VERSION = "v0.0.1";

#ifdef _WIN32
  #ifdef GLOWML_EXPORTS
    #define GlowML_API __declspec(dllexport)
  #else
    #define GlowML_API __declspec(dllimport)
  #endif
#else
  #define GlowML_API
#endif