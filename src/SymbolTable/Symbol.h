#include <utility>

//
// Created by gregory on 23.12.18.
//

#pragma once
#include <string>
#include <unordered_map>
#include <tr1/memory>

class CSymbol {
public:
	static std::shared_ptr<CSymbol> GetSymbol(const std::string& key) {
		auto result = mapping.find(key);
		if (result == mapping.end()) {
			auto symbol = std::make_shared<CSymbol>(CSymbol(key));
			mapping[key] = symbol;
			return symbol;
		}
		else {
			return result->second;
		}
	}

	const std::string& GetString() const { return string_key; };
private:
	explicit CSymbol(std::string s) : string_key(std::move(s)) {};
	const std::string string_key;
	static std::unordered_map<std::string, std::shared_ptr<CSymbol> > mapping;
};