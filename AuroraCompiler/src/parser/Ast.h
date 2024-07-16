#include <Core.h>

namespace Aurora
{
	class AUR_API AurSintaxTreeNode;

	class AUR_API AurSintaxTreeProcessor
	{
		virtual void ProcessNode(AurSintaxTreeNode& node) = 0;
	};

	class AUR_API AurSintaxTreeNode
	{
	public:
		virtual void AcceptProcessor(AurSintaxTreeProcessor& processor) = 0;
		~AurSintaxTreeNode() = default;
	};
}