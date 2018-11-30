//
// Created by gregory on 27.11.18.
//

#pragma once

class Location {
public:
    Location& operator=(const Location& other);

public:
    int lineNumber;
    int firstColumn;
    int lastColumn;
};


