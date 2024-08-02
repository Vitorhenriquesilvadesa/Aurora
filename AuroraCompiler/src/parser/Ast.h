#include <Core.h>

namespace Aurora
{
	class AUR_API AurSyntaxTreeNode;

	class AUR_API AurSintaxTreeProcessor
	{
		virtual void ProcessNode(AurSyntaxTreeNode& node) = 0;
	};

	class AUR_API AurSyntaxTreeNode
	{
	public:
		virtual void AcceptProcessor(AurSintaxTreeProcessor& processor) = 0;
		~AurSyntaxTreeNode() = default;
	};
}