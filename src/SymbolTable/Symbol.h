//
// Created by gregory on 23.12.18.
//

#pragma once
#include <string>
#include <unordered_map>

class CSymbol {
public:
	static CSymbol* GetSymbol(const std::string& key) {
		auto result = mapping.find(key);
		if (result == mapping.end()) {
			CSymbol *symbol = new CSymbol(key);
			mapping[key] = symbol;
			return symbol;
		}
		else {
			return result->second;
		}
	}

	const std::string& GetString() const { return string_key; };
private:
	CSymbol(const std::string& s) : string_key(s) {};
	const std::string string_key;
	static std::unordered_map<std::string, CSymbol*> mapping;
};