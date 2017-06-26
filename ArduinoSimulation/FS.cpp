#include <FS.h>

#include <stdio.h>


SPIFFS_fs SPIFFS;


File::File(FILE * fp) : _fp(fp)
{

}

File::operator bool() const
{
    return _fp != NULL;
}

size_t File::size() const
{
    long current_pos = ftell(_fp);
    if (current_pos == (long)-1L)
    {
        return (size_t)current_pos;
    }

    if (fseek(_fp, 0, SEEK_END) != 0)
    {
        fseek(_fp, current_pos, SEEK_SET);
        return (size_t)-1L;
    }

    unsigned pos = ftell(_fp);
    
    if (fseek(_fp, current_pos, SEEK_SET) != 0)
    {
        return (size_t)-1L;
    }

    return pos;
}

size_t File::write(const uint8_t *buffer, size_t bytes_to_write)
{
    return fwrite(buffer, 1, bytes_to_write, _fp);
}

unsigned File::readBytes(uint8_t *buffer, size_t bytes_to_read)
{
    return fread(buffer, 1, bytes_to_read, _fp);
}

void File::close()
{
    fclose(_fp);
    _fp = NULL;
}


File SPIFFS_fs::open(const String & file_name, const char * mode)
{
    FILE *fp;
    errno_t err = fopen_s(&fp, file_name.c_str(), mode);
    if (err != 0)
    {
        return File(NULL);
    }

    return File(fp);
}
