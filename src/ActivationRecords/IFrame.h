//
// Created by gregory on 23.12.18.
//
#pragma once
#include "IFrame.h"
#include "IAccess.h"
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include "IRT/Expression.h"


class IFrame{
  public:
    virtual ~IFrame() = default;
    virtual void AddAddr(const std::string& name, IAccess* addr) = 0;
    virtual void AddFormal(const std::string& name) = 0;
    virtual void AddLocal(const std::string& name) = 0;
    virtual IAccess* GetAccess(const std::string& name) = 0;

    virtual int WordSize() = 0;
    virtual const std::string& Name() const = 0;
    virtual IRT::Expression* CallFunction(const std::string& func_name, IRT::Expression* arg) const = 0;
    virtual int WordSize() const = 0;
};


class MiniJavaFrame : public IFrame {
  public:
    MiniJavaFrame(const std::string &class_symb, const std::string &method_symb) {
      _name = class_symb + "::" + method_symb;
      _size = 0;
      _frame_size = 0;
      IRT::Temp frame_pointer("FRAME_POINTER");
      IRT::Temp ths("THIS");
      IRT::Temp ret_val("RETURN_VALUE");
      AddAddr("FRAME_POINTER", new CInRegAccess(frame_pointer));
      AddAddr("THIS", new CInRegAccess(ths));
      AddAddr("RETURN_VALUE", new CInRegAccess(ret_val));
    }

    void AddAddr(const std::string& name, IAccess* addr) override {
      _addresses[name] = std::unique_ptr<IAccess>(addr);
    }

    void AddFormal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("THIS"), _size));
      _size += _word_size;
    }

    void AddLocal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("FRAME_POINTER"), _frame_size));
      _frame_size += _word_size;
    }

    int WordSize() override {
      return _word_size;
    }

    const std::string& Name() const override {
      return _name;
    }

    IRT::Expression* CallFunction(const std::string& func_name, IRT::Expression* args) const override {
      return new IRT::CallExp(new IRT::NameExp(IRT::Label(func_name)), new IRT::IRExpList(args));
    }

    IAccess* GetAccess(const std::string& name) override {
      auto element = _addresses.find(name);
      if (element != _addresses.end()) {
        return element->second.get();
      }
      return nullptr;
    }
    int WordSize() const override {
        return _word_size;
    }

  private:
    std::string _name;
    int _frame_size;
    int _size;
    std::unordered_map<std::string, std::unique_ptr<IAccess> > _addresses;
    int _word_size = 4;
};