//
// Created by gregory on 27.11.18.
//

#pragma once

#include <string>

class CLocation {
public:
    CLocation& operator=(const CLocation& other);
    std::string ToString() const;

public:
    int lineNumber;
    int firstColumn;
    int lastColumn;
};


