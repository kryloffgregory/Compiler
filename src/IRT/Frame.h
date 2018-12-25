//
// Created by gregory on 23.12.18.
//


#include "../SymbolTable/Symbol.h"
#include "Label.h"
#include "Expression.h"
#include "../SymbolTable/SymbolTable.h"

#include <map>
#include <memory>

namespace Frame {
    class IAccess;

    class CFrame {
    public:
        CFrame( const SymbolsTable::CClassInfo* classInfo, const SymbolsTable::CMethodInfo* methodInfo, const SymbolsTable::CTable* table );

        void SetStatements( std::shared_ptr<const IRTree::IStm> statements );
        std::shared_ptr<IAccess> GetVar( const std::string &name ) const;

        std::shared_ptr<Temp::CTemp> GetFramePtr() const;
        std::shared_ptr<Temp::CTemp> GetThisPtr() const;
        std::shared_ptr<Temp::CTemp> GetReturnPtr() const;

        const std::shared_ptr<CSymbol> GetName() const;

        std::shared_ptr<const IRTree::IStm> GetRootStm() const;

        static const int WORD_SIZE = 4;
    private:
        std::map<std::string, std::shared_ptr<IAccess>> formals;
        std::map<std::string, std::shared_ptr<IAccess>> locals;

        std::shared_ptr<CSymbol> frameName;

        std::shared_ptr<const IRTree::IStm> root;

        std::shared_ptr<Temp::CTemp> framePtr;
        std::shared_ptr<Temp::CTemp> thisPtr;
        std::shared_ptr<Temp::CTemp> returnPtr;
    };


    class IAccess {
    public:
        virtual const IRTree::CExprPtr GetExp( const Frame::CFrame& framePtr ) const = 0;
        virtual ~IAccess() = default;
    };

    // Ðåàëèçàöèÿ äëÿ ïåðåìåííûõ íà ñòåêå
    class CInFrame : public IAccess {
    public:
        explicit CInFrame( int offset );

        const IRTree::CExprPtr GetExp( const Frame::CFrame& framePtr ) const;
    private:
        const int offset;
    };


    class CInObject : public IAccess {
    public:
        explicit CInObject( int _offset ) : offset( _offset ) {}

        const IRTree::CExprPtr GetExp( const Frame::CFrame& frameRegPtr ) const;
    private:
        const int offset;
    };

    class CFormalParamInStack : public IAccess {
    public:
        explicit CFormalParamInStack( int _offset ) : offset( _offset ) {}

        const IRTree::CExprPtr GetExp( const Frame::CFrame& frameRegPtr ) const;
    private:

        const int offset;
    };
}