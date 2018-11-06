#pragma once

class KeyReader
{
public:
    KeyReader();
    ~KeyReader();

    bool readKey(char& key);
};
