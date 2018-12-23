//
// Created by gregory on 23.12.18.
//
#pragma once

namespace IRTree {

    class CMove;
    class CExpr;
    class CJump;
    class CCondJump;
    class CSeq;
    class CLabel;
    class CConst;
    class CName;
    class CTemp;
    class CBinop;
    class CMem;
    class CCall;
    class CESeq;

    class IIRTreeVisitor {
    public:
        virtual ~IIRTreeVisitor()
        {}

        virtual void Visit( const CMove* node ) = 0;
        virtual void Visit( const CExpr* node ) = 0;
        virtual void Visit( const CJump* node ) = 0;
        virtual void Visit( const CCondJump* node ) = 0;
        virtual void Visit( const CSeq* node ) = 0;
        virtual void Visit( const CConst* node ) = 0;
        virtual void Visit( const CName* node ) = 0;
        virtual void Visit( const CTemp* node ) = 0;
        virtual void Visit( const CBinop* node ) = 0;
        virtual void Visit( const CMem* node ) = 0;
        virtual void Visit( const CCall* node ) = 0;
        virtual void Visit( const CESeq* node ) = 0;
        virtual void Visit( const CLabel* node ) = 0;
    };

}