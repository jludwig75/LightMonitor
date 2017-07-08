#include "SD.h"

namespace SDLib {

	File::File() : _fp(NULL), _name()
	{

	}

	File::File(FILE * fp, const String & name) : _fp(fp), _name(name)
	{

	}

	File::~File()
	{
		if (_fp)
		{
			close();
		}
	}


	File::operator bool() const
	{
		return _fp != NULL;
	}

	size_t File::write(const uint8_t *buf, size_t size)
	{
		return fwrite(buf, 1, size, _fp);
	}

	int File::read(void *buf, uint16_t nbyte)
	{
		return fread(buf, 1, nbyte, _fp);
	}

	bool File::seek(uint32_t pos)
	{
		return fseek(_fp, pos, SEEK_SET) == 0;
	}

	uint32_t File::size()
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

	void File::close()
	{
		fclose(_fp);
		_fp = NULL;
	}

	SDClass::SDClass() : _started(false)
	{

	}

	bool SDClass::begin(uint8_t chipSelect)
	{
		_started = true;
		return true;
	}

	File SDClass::open(const String & fileName, uint8_t mode)
	{
		if (!_started) {
			return File();
		}

		String mode_string;
		switch (mode)
		{
		case FILE_READ:
			mode_string = "rb";
			break;
		case FILE_WRITE:
			mode_string = "ab";
			break;
		}
		FILE *fp;
		errno_t err = fopen_s(&fp, fileName.c_str(), mode_string.c_str());
		if (err != 0)
		{
			return File(NULL, "");
		}

		return File(fp, fileName);
	}
}

SDClass SD;