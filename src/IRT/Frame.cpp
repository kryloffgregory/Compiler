//
// Created by gregory on 24.12.18.
//
#include "Frame.h"

namespace Frame {

	CInFrame::CInFrame( int _offset ) :
		offset( _offset )
	{}

	const IRTree::CExprPtr CInFrame::GetExp( const Frame::CFrame& framePtr ) const
	{
		return IRTree::CExprPtr( new IRTree::CMem( std::shared_ptr<const IRTree::IExpr>(
			new IRTree::CBinop( IRTree::CBinop::MINUS,
			std::shared_ptr<const IRTree::IExpr>( new IRTree::CTemp( framePtr.GetFramePtr() ) ),
			IRTree::CExprPtr( new IRTree::CBinop( IRTree::CBinop::MUL,
			IRTree::CExprPtr( new IRTree::CConst( offset + 1 ) ), IRTree::CExprPtr( new IRTree::CConst( framePtr.WORD_SIZE ) ) ) ) ) ) ) );
	}

	const IRTree::CExprPtr CInObject::GetExp( const Frame::CFrame& frameRegPtr ) const
	{
		return IRTree::CExprPtr( new IRTree::CMem(
			IRTree::CExprPtr( new IRTree::CBinop(
			IRTree::CBinop::PLUS, IRTree::CExprPtr( new IRTree::CTemp( frameRegPtr.GetThisPtr() ) ),
			IRTree::CExprPtr( new IRTree::CBinop( IRTree::CBinop::MUL,
			IRTree::CExprPtr( new IRTree::CConst( offset ) ),
			IRTree::CExprPtr( new IRTree::CConst( frameRegPtr.WORD_SIZE ) ) ) ) ) ) ) );
	}

	const IRTree::CExprPtr CFormalParamInStack::GetExp( const Frame::CFrame& frameRegPtr ) const
	{
		return IRTree::CExprPtr( new IRTree::CMem(
			IRTree::CExprPtr( new IRTree::CBinop(
			IRTree::CBinop::PLUS, IRTree::CExprPtr( new IRTree::CTemp( frameRegPtr.GetFramePtr() ) ),
			IRTree::CExprPtr( new IRTree::CBinop( IRTree::CBinop::MUL,
			IRTree::CExprPtr( new IRTree::CConst( offset ) ),
			IRTree::CExprPtr( new IRTree::CConst( frameRegPtr.WORD_SIZE ) ) ) ) ) ) ) );
	}

	CFrame::CFrame( const SymbolsTable::CClassInfo* classInfo, const SymbolsTable::CMethodInfo* methodInfo,
		const SymbolsTable::CTable* table ) :
		frameName(CSymbol::GetSymbol( classInfo->GetName() + "__" + methodInfo->GetName() ))
	{

		do {

			for( int i = 0; i < classInfo->GerVars().size(); ++i ) {
				locals[classInfo->GerVars()[i]->GetName()] = std::shared_ptr<IAccess>( new CInObject( i ) );
			}
		} while( classInfo->GetBaseClass() != NULL );

		// Ëîêàëüíûå ïåðåìåííûå ìåòîäà
		for( int i = 0; i < methodInfo->GetLocals().size(); ++i ) {
			locals[methodInfo->GetLocals()[i]->GetName()] = std::shared_ptr<IAccess>( new CInFrame( i ) );
		}
		// Ïàðàìåòðû ìåòîäà
		for( int i = 0; i < methodInfo->GetParams().size(); ++i ) {
			formals[methodInfo->GetParams()[i]->GetName()] = std::shared_ptr<IAccess>( new CFormalParamInStack( i ) );
		}

		framePtr = std::make_shared<Temp::CTemp>( CSymbol::GetSymbol(frameName->GetString() + "__FP") );
		thisPtr = std::make_shared<Temp::CTemp>( CSymbol::GetSymbol( frameName->GetString( ) + "__TP" ) );
		returnPtr = std::make_shared<Temp::CTemp>( CSymbol::GetSymbol( frameName->GetString( ) + "__RP" ) );
	}

	void CFrame::SetStatements( std::shared_ptr<const IRTree::IStm> statements )
	{
		root = statements;
	}

	std::shared_ptr<IAccess> CFrame::GetVar( const std::string  &name ) const
	{
		if( formals.find( name ) != formals.end() ) {
			return formals.find( name )->second;
		}
		if( locals.find( name ) != locals.end() ) {
			return locals.find( name )->second;
		}
		return 0;
	}

	std::shared_ptr<Temp::CTemp> CFrame::GetFramePtr() const
	{
		return framePtr;
	}

	std::shared_ptr<Temp::CTemp> CFrame::GetThisPtr() const
	{
		return thisPtr;
	}

	std::shared_ptr<Temp::CTemp> CFrame::GetReturnPtr() const
	{
		return returnPtr;
	}

	const std::shared_ptr<CSymbol> CFrame::GetName() const
	{
		return frameName;
	}

	std::shared_ptr<const IRTree::IStm> CFrame::GetRootStm() const
	{
		return root;
	}

}