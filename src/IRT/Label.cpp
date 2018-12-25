//
// Created by gregory on 23.12.18.
//
#include "Label.h"

namespace Temp {
	int CLabel::nextUniqueId = 0;

	CLabel::CLabel()
	{
		name = CSymbol::GetSymbol( std::to_string( nextUniqueId++ ) );
	}

	CLabel::CLabel( const std::shared_ptr<CSymbol> label ) :
			name( label )
	{}

	const std::shared_ptr<CSymbol> CLabel::GetName() const
	{
		return name;
	}

	int CTemp::nextUniqueId = 0;

	CTemp::CTemp()
	{
		name = CSymbol::GetSymbol( std::to_string( nextUniqueId++ ) );
	}

	CTemp::CTemp( const std::shared_ptr<CSymbol> symbol ) :
			name( symbol )
	{}

	const std::shared_ptr<CSymbol> CTemp::GetName() const
	{
		return name;
	}

}