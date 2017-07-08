#pragma once

#include <Arduino.h>
#include <WString.h>

#include <fcntl.h>

#define	O_READ	1
#define	O_WRITE	2

namespace SDLib {

#define FILE_READ ((uint8_t)O_READ)
#define FILE_WRITE ((uint8_t)(O_READ | O_WRITE | O_CREAT))

	class File
	{
	public:
		File();
		File(FILE * fp, const String & name);
		~File();
		operator bool() const;
		virtual size_t write(const uint8_t *buf, size_t size);
		int read(void *buf, uint16_t nbyte);
		bool seek(uint32_t pos);
		uint32_t size();
		void close();
	private:
		FILE * _fp;
		String _name;
	};

	class SDClass
	{
	public:
		SDClass();
		bool begin(uint8_t chipSelect);
		File open(const String & fileName, uint8_t mode = FILE_READ);
	private:
		bool _started;
	};

}

using namespace SDLib;

extern SDClass SD;