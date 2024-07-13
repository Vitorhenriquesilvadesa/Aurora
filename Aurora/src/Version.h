#include <cstdio>
#include <cstdint>

// Define macros for creating version numbers
#define MAKE_VERSION_MINOR(minor) ((minor) << 8)
#define MAKE_VERSION_MAJOR(major) ((major) << 16)
#define MAKE_PATCH(patch) (patch)
#define MAKE_VERSION(major, minor, patch) \
    (MAKE_VERSION_MAJOR(major) | MAKE_VERSION_MINOR(minor) | MAKE_PATCH(patch))

// Extract major, minor, and patch from a version number
#define EXTRACT_MAJOR(version) (((version) >> 16) & 0xFF)
#define EXTRACT_MINOR(version) (((version) >> 8) & 0xFF)
#define EXTRACT_PATCH(version) ((version) & 0xFF)

// Convert version to string
#define VERSION_TO_STRING(version) \
    ([](uint32_t ver) -> std::string { \
        return std::to_string(EXTRACT_MAJOR(ver)) + "." + \
               std::to_string(EXTRACT_MINOR(ver)) + "." + \
               std::to_string(EXTRACT_PATCH(ver)); \
    }(version))

static uint32_t version = MAKE_VERSION(0, 1, 1);

#define VERSION_STRING VERSION_TO_STRING(version)
#define VERSION_UINT32 version