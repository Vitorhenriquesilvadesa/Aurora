#ifdef AURORA_EXPORTS
#define AUR_API __declspec(dllexport)
#else
#define AUR_API __declspec(dllimport)
#endif