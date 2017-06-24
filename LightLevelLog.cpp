#include "LightLevelLog.h"

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
  log_file.write((const uint8_t *)&light_level_entry, sizeof(light_level_entry));

  log_file.close();
}


bool LightLevelLog::get_light_level_history(LightLevel *light_levels, unsigned output_entry_count, unsigned & entries_retrieved) const
{
  entries_retrieved = 0;
  if (!light_levels)
  {
    return false;
  }

  File log_file = SPIFFS.open(_log_file_name, "r");
  if (!log_file)
  {
    return false;
  }

  unsigned entries_in_file = log_file.size() / sizeof(LightLevelLog::LightLevel);

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
    return false;
  }
  
  entries_retrieved = entries_to_read;
  return true;
}
