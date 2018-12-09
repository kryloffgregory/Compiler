//
// Created by gregory on 10.12.18.
//

#pragma once

#include <string>
#include <vector>

class CVarInfo {
public:
    CVarInfo(const std::string &_name, const std::string &_type) :
            varName(_name), type(_type) {
    }
    std::string GetName() const;
    std::string GetType() const;
private:
    std::string varName;
    std::string type;
};
class CClassInfo;
class CMethodInfo {
    public:
        CMethodInfo( const std::string& name, const std::string& type, CClassInfo* _curClass ) :
                methodName( name ),
                returnType( new CVarInfo( "", type ) ),
                curClass( _curClass )
        {}

        bool AddParamVar( const std::string& varName, const std::string& type );
        bool AddLocalVar( const std::string& varName, const std::string& type );

        std::string GetName() const;
        CVarInfo* GetVar( const std::string& varName ) const;
        CVarInfo* GetReturnType() const;
        std::vector<CVarInfo*> GetParams() const;
        std::vector<CVarInfo*> GetLocals() const;
    private:
        std::string methodName;
        CVarInfo* returnType;
        std::vector<CVarInfo*> params;
        std::vector<CVarInfo*> locals;
        CClassInfo* curClass;
    };
class CClassInfo {
public:
    CClassInfo( const std::string& name ) : className( name ) {}

    bool AddVar( const std::string& varName, const std::string& type );
    bool AddMethod( const std::string& methodName, const std::string& type );

    bool SetBaseClass( CClassInfo* baseClass );

    std::string GetName() const;
    CMethodInfo* GetMethod( const std::string& methodName ) const;
    CVarInfo* GetVar( const std::string varName ) const;
    CClassInfo* GetBaseClass() const;
    std::vector<CMethodInfo*> GetMethods() const;
    std::vector<CVarInfo*> GerVars() const;

private:
    std::string className;
    CClassInfo* baseClass;
    std::vector<CVarInfo*> vars;
    std::vector<CMethodInfo*> methods;
};

class CTable {
public:
    bool AddClass( const std::string& className );

    CClassInfo* GetClass( const std::string& className );
private:
    std::vector<CClassInfo*> classes;
};

