#pragma once

#include <WString.h>
#include <stdint.h>


enum SeekMode {
    SeekSet = 0,
    SeekCur = 1,
    SeekEnd = 2
};


class File
{
public:
    File(FILE * fp, const String & name);
    const char *name() const;
    operator bool() const;
    size_t size() const;
    size_t write(const uint8_t *buffer, size_t bytes_to_write);
    size_t readBytes(char *buffer, size_t bytes_to_read);
    bool seek(uint32_t pos, SeekMode mode);
    bool seek(uint32_t pos) {
        return seek(pos, SeekSet);
    }
    void close();
private:
    FILE * _fp;
    String _name;
};


class FS
{
public:
    FS();
    void begin();
    File open(const String & file_name, const char * mode);
    bool exists(const String & path) const;
private:
    bool _started;
};


extern FS SPIFFS;