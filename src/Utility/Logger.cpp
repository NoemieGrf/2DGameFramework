#include "Logger.h"

#include <iostream>

void Logger::SetLogLevel(Logger::Level newLevel)
{
    _currentLevel = newLevel;
}

Logger::Level Logger::GetLogLevel()
{
    return _currentLevel;
}

void Logger::LogInfo(const std::string& message)
{
    LogInfo(message.c_str());
}

void Logger::LogInfo(const char* message)
{
    if (static_cast<int>(_currentLevel) > static_cast<int>(Level::Info))
        return;

    std::cout << "[I] " << message << std::endl;
}

void Logger::LogWarn(const std::string& message)
{
    LogWarn(message.c_str());
}

void Logger::LogWarn(const char* message)
{
    if (static_cast<int>(_currentLevel) > static_cast<int>(Level::Warn))
        return;

    std::cout << "[W] " << message << std::endl;
}

void Logger::LogError(const std::string& message)
{
    LogError(message.c_str());
}

void Logger::LogError(const char* message)
{
    if (static_cast<int>(_currentLevel) > static_cast<int>(Level::Error))
        return;

    std::cout << "[E] " << message << std::endl;
}
