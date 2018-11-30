//
// Created by gregory on 27.11.18.
//

#include "Location.h"

Location& Location::operator=(const Location& other) {
    lineNumber = other.lineNumber;
    firstColumn = other.firstColumn;
    lastColumn = other.lastColumn;
    return *this;
}