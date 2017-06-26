#include "LightLevelLog.h"

#include "tracing.h"
#include <FS.h>


LightLevelLog::LightLevelLog(const String & log_file_name) :
  _log_file_name(log_file_name)
{
}

void LightLevelLog::log_light_level(uint32_t time, int16_t light_level)
{
  File log_file = SPIFFS.open(_log_file_name, "a");
  if (!log_file)
  {
    return;
  }

  LightLevelLog::LightLevel light_level_entry;
  light_level_entry.time = time;
  light_level_entry.light_level = light_level;
  unsigned bytes_written = log_file.write((const uint8_t *)&light_level_entry, sizeof(light_level_entry));
  log_file.close();
  if (bytes_written != sizeof(light_level_entry))
  {
    err_printf("Failed to write to log file. Wrote %u of %u bytes.\n", bytes_written, sizeof(light_level_entry));
  }
  else
  {
    inf_printf("Successfully wrote entry to log file: %lu -> %u\n", time, light_level);
  }
}


bool LightLevelLog::get_light_level_history(LightLevel *light_levels, unsigned output_entry_count, unsigned start_entry, unsigned & entries_retrieved) const
{
  entries_retrieved = 0;
  if (!light_levels)
  {
    err_printf("No buffer for light level log\n");
    return false;
  }

  File log_file = SPIFFS.open(_log_file_name, "r");
  if (!log_file)
  {
    err_printf("Failed to open log file %s\n", _log_file_name.c_str());
    return false;
  }

  unsigned entries_in_file = log_file.size() / sizeof(LightLevelLog::LightLevel);
  if (start_entry == entries_in_file)
  {
    inf_printf("No more entries in log file\n");
    return true;
  }
  else if (start_entry > entries_in_file)
  {
    err_printf("Read attempted beyond end of log file.\n");
    return false;
  }

  unsigned entries_to_read = entries_in_file;
  if (output_entry_count < entries_to_read)
  {
    entries_to_read = output_entry_count;
  }

  unsigned bytes_to_read = entries_to_read * sizeof(LightLevelLog::LightLevel);
  unsigned bytes_read = log_file.readBytes((char *)light_levels, bytes_to_read);
  log_file.close();
  if (bytes_read != bytes_to_read)
  {
    err_printf("Failed to read from log file. Read %u of %u bytes.\n", bytes_read, bytes_to_read);
    return false;
  }
  
  entries_retrieved = entries_to_read;
  inf_printf("Successfully read %u entries from log file starting at entry %u.\n", entries_to_read, start_entry);
  return true;
}
