#include <utility>

//
// Created by gregory on 24.12.18.
//

#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include "Expression.h"
#include "IIRVisitor.h"

namespace IRTree {

    class IStm;
    class IExpr;


    class IRTreePrinter : public IIRTreeVisitor {
    public:
        explicit IRTreePrinter(std::string treeFileName ) :
            minId( 0 ),
            filename(std::move(treeFileName)),
            data( "digraph {\n" ),
            isFlushed(true) {}

        ~IRTreePrinter() override {
            if (!isFlushed)
                Flush();
        }
        //void LinkedVisit( const IStm* node );
        //void LinkedVisit( const IExpr* node );

        void Visit( const CMove* node ) override;

        void Visit( const CExpr* node ) override;

        void Visit( const CJump* node ) override;

        void Visit( const CCondJump* node ) override;

        void Visit( const CSeq* node ) override;

        void Visit( const CConst* node ) override;

        void Visit( const CName* node ) override;

        void Visit( const CTemp* node ) override;

        void Visit( const CBinop* node ) override;

        void Visit( const CMem* node ) override;

        void Visit( const CCall* node ) override;

        void Visit( const CESeq* node ) override;

        void Visit( const CLabel* node ) override;

        void Flush();

    private:

        int minId;

        std::string filename;
        std::string lastNodeName;
        std::string data;
        bool isFlushed;



        void SetNodeLabel( std::string nodeName, std::string nodeLabel );

        void AddEdge( std::string from, std::string to );
        void AddEdge( std::string from, std::string to, std::string edgeName );
        static void decorateName(std::string &stringToDecorate);

        void nextNameWithId( std::string label );
    };

}