#include <iostream>

#include <compiler/Compiler.h>
#include <filesystem>
#include <Logging.h>
#include <vm/VirtualMachine.h>

#include "CommandHelpProvider.h"
#include "CommandReceptor.h"
#include "Repl.h"
#include "Version.h"
#include "CommandNames.h"


namespace Aurora
{
    namespace fs = std::filesystem;

    std::vector<std::string> CommandReceptor::s_CommandNames =
    {
        HELP_NAME,
        VERSION_NAME,
        LIST_NAME,
        COMPILE_FILE,
        EXECUTE_FILE
    };

    std::unordered_map<std::string, CommandFunction> CommandReceptor::s_Commands =
    {
        {HELP_NAME, CommandReceptor::Help},
        {VERSION_NAME, CommandReceptor::Version},
        {LIST_NAME, CommandReceptor::List},
        {COMPILE_FILE, CommandReceptor::CompileFile},
        {EXECUTE_FILE, CommandReceptor::ExecuteFile},
    };

    void CommandReceptor::Execute(const std::vector<std::string>& args)
    {
        if (args.size() < 1)
        {
            std::cerr << "Error: No command provided." << std::endl;
            return;
        }

        std::string commandName = args[0];

        auto it = s_Commands.find(commandName);

        if (it != s_Commands.end() && it->second)
        {
            it->second(args);
        }
        else
        {
            std::cerr << "Error: Command not found." << std::endl;
        }
    }

    void CommandReceptor::CallRepl()
    {
        Repl repl = Repl();
        repl.RunConsole();
    }

    void CommandReceptor::Version(const std::vector<std::string>& args)
    {
        AUR_ASSERT(args.size() == 1, "--version cannot receive arguments.");
        std::cout << "Aurora Alpha " << VERSION_UINT32 << ": " << VERSION_STRING << std::endl;
    }

    void CommandReceptor::CompileFile(const std::vector<std::string>& args)
    {
        AUR_ASSERT(args.size() == 2, "Target file not found. Try like '-c myFile.aur'");

        const std::string& relativePath = args[1];
        fs::path absolutePath = fs::absolute(relativePath);

        AurCompiler compiler = AurCompiler();
        compiler.Compile(absolutePath.string());
    }

    void CommandReceptor::ExecuteFile(const std::vector<std::string>& args)
    {
        AUR_ASSERT(args.size() == 1, "Target file not found. Try like '-e myFile.avm'");

        std::string relativePath = args[1];
        fs::path absolutePath = fs::absolute(relativePath);

        AurVirtualMachine virtualMachine = AurVirtualMachine();
        virtualMachine.ExecuteBytecode(absolutePath.string());
    }

    void CommandReceptor::List(const std::vector<std::string>& args)
    {
        AUR_ASSERT(args.size() == 1, "--list commands cannot receive arguments.");

        for (const std::string& commandName : s_CommandNames)
        {
            std::cout << commandName << std::endl;
        }
    }

    void CommandReceptor::Help(const std::vector<std::string>& args)
    {
        if (args.size() == 1)
        {
            std::cout << "\nAurora Help Section\n" << std::endl;
            std::cout << CommandHelpProvider::HelpForC() << std::endl << std::endl;
            std::cout << CommandHelpProvider::HelpForE() << std::endl << std::endl;
            std::cout << CommandHelpProvider::HelpForVersion() << std::endl << std::endl;
            return;
        }

        std::cout << '\n';
        std::cout << CommandHelpProvider::GetHelpFor(args[1]) << std::endl;
    }
}
