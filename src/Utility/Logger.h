#pragma once

#include <string>

class Logger
{
public:
    Logger() = delete;

public:
    enum class Level: int
    {
        Info = 0,
        Warn = 1,
        Error = 2
    };

    static void SetLogLevel(Level newLevel);
    static Level GetLogLevel();

public:
    static void LogInfo(const std::string& message);
    static void LogInfo(const char* message);
    static void LogWarn(const std::string& message);
    static void LogWarn(const char* message);
    static void LogError(const std::string& message);
    static void LogError(const char* message);

private:
    inline static Level _currentLevel = Level::Info;
};