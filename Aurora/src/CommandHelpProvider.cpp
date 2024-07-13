#include <Logging.h>

#include "CommandHelpProvider.h"
#include "CommandNames.h"
#include "Version.h"

namespace Aurora
{
    std::unordered_map<std::string, HelpTextGetter> CommandHelpProvider::s_HelpTexts =
    {
        {VERSION_NAME, HelpForVersion},
        {COMPILE_FILE, HelpForC},
        {EXECUTE_FILE, HelpForE},
        {LIST_NAME, HelpForList},
    };

    const char* CommandHelpProvider::HelpForVersion()
    {
        return 
            "--version: provides a current version details,\n"
            "           like generated number by version data,\n"
            "           and major, minor, patch format.\n";
    }

    const char* CommandHelpProvider::HelpForC()
    {
        return 
            "-c:        compile a file parting from the main file.\n"
            "           Files that are not included within some part\n"
            "           of the program are ignored by default.\n";
    }

    const char* CommandHelpProvider::HelpForE()
    {
        return
            "-e:        execute bytecode from specified file. If the\n"
            "           file references to other files,\n"
            "           they are also executed.\n";
    }

    const char* CommandHelpProvider::HelpForList()
    {
        static std::string helpMessage = "-list:     returns a list for all valid commands in\n"
            "           Aurora Lang " + std::string(VERSION_STRING);

        return helpMessage.c_str();
    }



    const char* CommandHelpProvider::GetHelpFor(const std::string& commandName)
    {
        auto it = s_HelpTexts.find(commandName);

        AUR_ASSERT(it != s_HelpTexts.end(), "Cannot found help for provided command. Type '--list' for valid commands list.");
        return it->second();
    }
}