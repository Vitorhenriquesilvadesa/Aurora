#include <functional>
#include <string>
#include <unordered_map>

namespace Aurora
{
	using CommandFunction = std::function<void(const std::vector<std::string>&)>;

	class CommandReceptor final
	{
	public:
		static void Execute(const std::vector<std::string>& args);
		static void CallRepl();

	private:
		static void Help(const std::vector<std::string>&);
		static void Version(const std::vector<std::string>& args);
		static void CompileFile(const std::vector<std::string>& args);
		static void ExecuteFile(const std::vector<std::string>& args);
		static void List(const std::vector<std::string>& args);

	private:
		static std::unordered_map<std::string, CommandFunction> s_Commands;
		static std::vector<std::string> s_CommandNames;
	};
}