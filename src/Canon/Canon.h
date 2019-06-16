#pragma once

#include "IRT/Expression.h"
#include "IRT/Statement.h"

class CMoveCall : public IRTree::IStm {
public:
    CMoveCall( std::shared_ptr<const IRTree::CTemp> dst, std::shared_ptr<const IRTree::CCall> src );

    std::shared_ptr<const IRTree::CTemp> Dst() const
    {
        return dst;
    }
    std::shared_ptr<const IRTree::CCall> Src() const
    {
        return src;
    }

    IRTree::CExprList* Kids() const override;
    IRTree::IStm* Build(const IRTree::CExprList* kids) const override;
    void Accept( IRTree::IIRTreeVisitor* visitor ) const override {}

private:
    std::shared_ptr<const IRTree::CTemp> dst;
    std::shared_ptr<const IRTree::CCall> src;
};
typedef std::shared_ptr<CMoveCall> CMoveCallPtr;

class CExprCall : public IRTree::IStm {
public:
    explicit CExprCall( std::shared_ptr<const IRTree::CCall> call );

    std::shared_ptr<const IRTree::CCall> GetCall() const
    {
        return call;
    }

    IRTree::CExprList* Kids() const override;
    IRTree::IStm* Build(const IRTree::CExprList* kids) const override;
    void Accept( IRTree::IIRTreeVisitor* visitor ) const override {}

private:
    std::shared_ptr<const IRTree::CCall> call;
};
typedef std::shared_ptr<const CExprCall> CExprCallPtr;

class CStmExprList {
public:
    CStmExprList( std::shared_ptr<const IRTree::IStm> stm, std::shared_ptr<const IRTree::CExprList> exprs );

    std::shared_ptr<const IRTree::IStm> Stm() const
    {
        return stm;
    }
    std::shared_ptr<const IRTree::CExprList> Exprs() const
    {
        return exprs;
    }

private:
    std::shared_ptr<const IRTree::IStm> stm;
    std::shared_ptr<const IRTree::CExprList> exprs;
};

class CCanon {
public:
    static IRTree::CStmListPtr Linearize( IRTree::CStmPtr stm );

private:
    static CStmExprList nopNull;

    // ����������� ��������������� �����
    static bool isCommute( IRTree::CStmPtr a, IRTree::CExprPtr b );
    // �������� �� ��� ����������� � ����������� ���������
    static bool isNop( IRTree::CStmPtr a );

    static IRTree::CStmPtr createSeq( IRTree::CStmPtr firstStm, IRTree::CStmPtr secondStm );

    static IRTree::CStmPtr doStm( IRTree::CSeqPtr seq );
    static IRTree::CStmPtr doStm( IRTree::CMovePtr  move );
    static IRTree::CStmPtr doStm( IRTree::CCExprPtr expr );
    static IRTree::CStmPtr doStm( IRTree::CStmPtr stm );

    static IRTree::CStmPtr reorderStm( IRTree::CStmPtr stm );

    static IRTree::CESeqPtr doExp( IRTree::CESeqPtr eseq );
    static IRTree::CESeqPtr doExp( IRTree::CExprPtr eseq );

    static IRTree::CESeqPtr reorderExp( IRTree::CExprPtr expr );

    static std::shared_ptr<CStmExprList> reorder( const IRTree::CExprList* exprs );

    static IRTree::CStmListPtr linear( IRTree::CSeqPtr seq, IRTree::CStmListPtr list );
    static IRTree::CStmListPtr linear( IRTree::CStmPtr stm, IRTree::CStmListPtr list );
};