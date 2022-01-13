#include "LoggerClass.hpp"

namespace Logging
{

    Logger::Logger()
    {
        mStream.open("log.txt", std::ios::app);
    }

    void Logger::WriteLine(std::string content, bool end)
    {
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char timestamp[26];
        ctime_s(timestamp, sizeof timestamp, &now);

        std::string timestampWithoutEndl(timestamp);
        timestampWithoutEndl = timestampWithoutEndl.substr(0, 24);

      
        mStream << content << "  " << (end ? "\n" : timestampWithoutEndl) << std::endl;
    }
}