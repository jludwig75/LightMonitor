#pragma once

#include <WString.h>
#include <stdint.h>


class File
{
public:
    File(FILE * fp);
    operator bool() const;
    size_t size() const;
    size_t write(const uint8_t *buffer, size_t bytes_to_write);
    size_t readBytes(uint8_t *buffer, size_t bytes_to_read);
    void close();
private:
    FILE * _fp;
};


class SPIFFS_fs
{
public:
    File open(const String & file_name, const char * mode);
};


extern SPIFFS_fs SPIFFS;