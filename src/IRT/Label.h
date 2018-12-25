//
// Created by gregory on 23.12.18.
#pragma once

#include <string>
#include "../SymbolTable/Symbol.h"
#include <tr1/memory>

namespace Temp {

    class CTemp {
    public:

        CTemp();


        explicit CTemp(std::shared_ptr<CSymbol> _symbol );

        const std::shared_ptr<CSymbol> GetName() const;
    private:

        static int nextUniqueId;
        std::shared_ptr<CSymbol> name;
    };


    class CLabel {
    public:

        CLabel();


        explicit CLabel(std::shared_ptr<CSymbol> label );

        const std::shared_ptr<CSymbol> GetName() const;

    private:
        static int nextUniqueId;
        std::shared_ptr<CSymbol> name;
    };
}