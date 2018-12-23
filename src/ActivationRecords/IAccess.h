//
// Created by gregory on 23.12.18.
//

#pragma once
#include "./IRT/Label.h"
#include "./IRT/Expression.h"
#include "./IRT/Statement.h"

class IAccess {
  public:
    virtual ~IAccess() = default;
    virtual IRT::Expression* GetExp() const = 0;
};

class CInRegAccess : public IAccess {
  public:
    explicit CInRegAccess(IRT::Temp& temp) : _temp(temp) {}

    IRT::Expression* GetExp() const override {
      return new IRT::TempExp(_temp);
    }

  private:
    IRT::Temp _temp;
};

class CInFrameAccess : public IAccess {
  public:
    CInFrameAccess(IAccess* frame_addr, int offset) : _frame_addr(frame_addr), _offset(offset) {}

    IRT::Expression* GetExp() const override {
      if(_offset != 0) {
        return new IRT::MemoryExp(new IRT::BinaryExp(IRT::BinaryExp::BinOp::PLUS, _frame_addr->GetExp(), new IRT::ConstExp(_offset)));
      }
      return new IRT::MemoryExp(_frame_addr->GetExp());
    }

  private:
    IAccess* _frame_addr;
    int _offset;
};