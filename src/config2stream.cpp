#include "config.hpp"

#include <iostream>

namespace Config2Stream
{
  int
  convert(const Config &config_,
          std::ostream &os_)
  {
    std::vector<std::string> keys;

    Config::keys(keys);
    for(uint64_t i = 0; i < keys.size(); i++)
      {
        os_ << keys[i] << '=' << config_.get(keys[i]) << std::endl;
      }

    return 0;
  }
}
