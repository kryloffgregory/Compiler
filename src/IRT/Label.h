//
// Created by gregory on 23.12.18.
#pragma once

#include <string>
#include "../SymbolTable/Symbol.h"

namespace Temp {

    class CTemp {
    public:

        CTemp();


        explicit CTemp( const CSymbol* _symbol );

        const CSymbol* GetName() const;
    private:

        static int nextUniqueId;
        const CSymbol* name;
    };


    class CLabel {
    public:

        CLabel();


        explicit CLabel( const CSymbol* label );

        const CSymbol* GetName() const;

    private:
        static int nextUniqueId;
        const CSymbol* name;
    };
}