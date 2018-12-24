//
// Created by gregory on 10.12.18.
//

#include <string>
#include "SymbolTable.h"

namespace SymbolsTable {
    bool CTable::AddClass(const std::string &className) {
        for (auto curClass : classes) {
            if (curClass->GetName() == className) {
                return false;
            }
        }
        classes.push_back(new CClassInfo(className));
        return true;
    }

    CClassInfo *CTable::GetClass(const std::string &className) {
        for (auto curClass : classes) {
            if (curClass->GetName() == className) {
                return curClass;
            }
        }
        return nullptr;
    }

    bool CClassInfo::AddVar(const std::string &varName, const std::string &type) {
        for (auto curVar : vars) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }
        vars.push_back(new CVarInfo(varName, type));
        return true;
    }

    bool CClassInfo::AddMethod(const std::string &methodName, const std::string &type) {
        for (auto curMethod : methods) {
            if (curMethod->GetName() == methodName) {
                return false;
            }
        }
        methods.push_back(new CMethodInfo(methodName, type, this));
        return true;
    }

    bool CClassInfo::SetBaseClass(CClassInfo *_baseClass) {
        if (baseClass != nullptr) {
            return false;
        }
        baseClass = _baseClass;
        return true;
    }

    std::string CClassInfo::GetName() const {
        return className;
    }

    CMethodInfo *CClassInfo::GetMethod(const std::string &methodName) const {
        for (auto curMethod : methods) {
            if (curMethod->GetName() == methodName) {
                return curMethod;
            }
        }
        return nullptr;
    }

    CVarInfo *CClassInfo::GetVar(const std::string varName) const {
        for (auto curVar : vars) {
            if (curVar->GetName() == varName) {
                return curVar;
            }
        }
        return nullptr;
    }

    CClassInfo *CClassInfo::GetBaseClass() const {
        return baseClass;
    }

    std::vector<CMethodInfo *> CClassInfo::GetMethods() const {
        return methods;
    }

    std::vector<CVarInfo *> CClassInfo::GerVars() const {
        return vars;
    }

    bool CMethodInfo::AddParamVar(const std::string &varName, const std::string &type) {
        for (auto curVar : curClass->GerVars()) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }

        for (auto curVar : params) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }
        params.push_back(new CVarInfo(varName, type));
        return true;
    }

    bool CMethodInfo::AddLocalVar(const std::string &varName, const std::string &type) {
        for (auto curVar : curClass->GerVars()) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }

        for (auto curVar : params) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }

        for (auto curVar : locals) {
            if (curVar->GetName() == varName) {
                return false;
            }
        }
        locals.push_back(new CVarInfo(varName, type));
        return true;
    }

    std::string CMethodInfo::GetName() const {
        return methodName;
    }

    CVarInfo *CMethodInfo::GetVar(const std::string &varName) const {
        for (auto curVar : curClass->GerVars()) {
            if (curVar->GetName() == varName) {
                return curVar;
            }
        }

        for (auto curVar : locals) {
            if (curVar->GetName() == varName) {
                return curVar;
            }
        }
        for (auto curVar : params) {
            if (curVar->GetName() == varName) {
                return curVar;
            }
        }
        return nullptr;
    }

    std::shared_ptr<CVarInfo >CMethodInfo::GetReturnType() const {
        return returnType;
    }

    std::vector<CVarInfo *> CMethodInfo::GetParams() const {
        return params;
    }

    std::vector<CVarInfo *> CMethodInfo::GetLocals() const {
        return locals;
    }

    std::string CVarInfo::GetName() const {
        return varName;
    }

    std::string CVarInfo::GetType() const {
        return type;
    }
}