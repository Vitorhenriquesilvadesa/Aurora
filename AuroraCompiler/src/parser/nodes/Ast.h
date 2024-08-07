#pragma once
#include <Core.h>

namespace Aurora
{
	class AurSyntaxTreeProcessor;

	class AUR_API AurSyntaxTreeNode
	{
	public:
		AurSyntaxTreeNode() = default;
		virtual void AcceptProcessor(AurSyntaxTreeProcessor& processor) = 0;
		virtual ~AurSyntaxTreeNode() = default;
	};
}
