#ifndef __LIGHT_LEVEL_LOG_H__
#define __LIGHT_LEVEL_LOG_H__


#include <WString.h>
#include <stdint.h>


class LightLevelLog
{
  public:
    struct LightLevel
    {
      uint32_t time;
      uint16_t light_level;
    };

    LightLevelLog(const String & log_file_name);

    void log_light_level(uint32_t time, int16_t light_level);
    bool get_light_level_history(LightLevel *light_levels, unsigned output_entry_count, unsigned & entries_retrieved) const;

  private:
    const String _log_file_name;
};


#endif  // __LIGHT_LEVEL_LOG_H__
