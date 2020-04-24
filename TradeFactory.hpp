#ifndef TRADEFACTORY_HPP
#define TRADEFACTORY_HPP

#include <string>
#include "Trade.hpp"
#include "Option.hpp"
#include "FileType.hpp"
#include "FileRow.hpp"
#include "FileTypeContainer.hpp"

class TradeFactory
{
private:
	TradeFactory();
public:
	// Constructors/Destructor:
	virtual ~TradeFactory();
	static Trade* CreateTrade(const TradeType& type, const FileTypeContainer* files);
	static Trade* CreateTrade(const TradeType& type, const FileType* files);
};

#endif
