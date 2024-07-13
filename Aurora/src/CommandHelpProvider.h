#include <string>
#include <unordered_map>
#include <functional>

namespace Aurora
{
	using HelpTextGetter = std::function<const char* ()>;

	class CommandHelpProvider
	{
	public:
		static const char* HelpForVersion();
		static const char* HelpForC();
		static const char* HelpForE();
		static const char* HelpForList();
		static const char* GetHelpFor(const std::string& commandName);

	private:
		static std::unordered_map<std::string, HelpTextGetter> s_HelpTexts;
	};
}