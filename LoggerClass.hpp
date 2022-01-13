#pragma once
#include <string>
#include <fstream>
#include <chrono>

namespace Logging
{
    class Logger
    {
    public:
        
        Logger();

        ~Logger()
        {
            mStream.close();
        }

        void WriteLine(std::string content, bool end);
    private:
        std::ofstream mStream;
    };

    class LoggerSingleton
    {
    public:
        LoggerSingleton(LoggerSingleton const&) = delete;             
        LoggerSingleton(LoggerSingleton&&) = delete;                  
        LoggerSingleton& operator=(LoggerSingleton const&) = delete;  
        LoggerSingleton& operator=(LoggerSingleton&&) = delete; 

        static Logger& Instance()
        {
            static Logger Instance;
            return Instance;
        }

    protected:
        LoggerSingleton() {}
        ~LoggerSingleton() {}
    };
}