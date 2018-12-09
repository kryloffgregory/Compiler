//
// Created by gregory on 27.11.18.
//

#include "Location.h"

CLocation& CLocation::operator=(const CLocation& other) {
    lineNumber = other.lineNumber;
    firstColumn = other.firstColumn;
    lastColumn = other.lastColumn;
    return *this;
}

std::string CLocation::ToString() const {
    return "Line: " + std::to_string(lineNumber) + "  Columns: "
    + std::to_string(firstColumn)+"-"+ std::to_string(lastColumn);
}