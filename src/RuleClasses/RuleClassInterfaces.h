//
// Created by gregory on 19.11.18.
//

#pragma once

#include "../Visitor.h"

class IItem {
public:
    virtual ~IItem( ) = default;

    virtual void Accept( IVisitor* visitor ) const = 0;
};

// Корневой интерфейс программы
class IProgram : public IItem {
public:
    virtual ~IProgram() = default;
};

// Главный класс
class IMainClass : public IItem {
public:
    virtual ~IMainClass() {}
};


// Описание класса
class IClassDecl : public IItem {
public:
    virtual ~IClassDecl() {}
};

// Объявление переменной
class IVarDecl : public IItem {
public:
    virtual ~IVarDecl() {}
};


// Метод класса
class IMethodDecl : public IItem {
public:
    virtual ~IMethodDecl() {}
};

class IArg: public IItem {
public:
    virtual ~IArg() {}
};


// Тип
class IType : public IItem {
public:
    virtual bool IsPODType() const = 0;
    virtual ~IType() {}
};



// Одна команда (или блок)
class IStatement : public IItem {
public:
    virtual ~IStatement() {}
};



// Арифметическое выражение
class IExp : public IItem{
public:
    virtual ~IExp() {}
};