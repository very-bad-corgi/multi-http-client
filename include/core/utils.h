// UTILS_H
#pragma once

#include <string>

enum class Dir {
    Config,
    Certs,
    Libs,
    Bin
};

class Utils
{
public:
    Utils() = delete;

    Utils(const Utils&) = delete;
    Utils& operator=(const Utils&) = delete;

    Utils(Utils&&) = delete;
    Utils& operator=(Utils&&) = delete;

    static void init(const std::string &executablePath);

    static void viewCppStandartUsing();
    static void viewCppCompilerUsing();

    static std::string convertToString(Dir directory);
    static std::string getPath(Dir directory = Dir::Bin, const std::string &filename = "");

private:
    static std::string _exetutablePath;
    static std::string _buildType;
};
