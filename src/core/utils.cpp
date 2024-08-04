#include "utils.h"
#include "constants.h"

#include <iostream>
#include <filesystem>

std::string Utils::_buildType;
std::string Utils::_exetutablePath;

void Utils::init(const std::string &executablePath)
{
#ifdef DEBUG
    std::cout << "Use developer configuration files" << std::endl;
    _buildType = CONFIG::TYPE::DEV;
#else
    std::cout << "Use release configuration files" << std::endl;
    _buildType = CONFIG::TYPE::RELEASE;
#endif

    std::string path = (std::filesystem::current_path() / std::filesystem::path(executablePath)).string();
    // Убираем имя исполняемого файла для получения dirPath до каталоги с исполняшкой
    _exetutablePath = std::move(path.substr(0, path.find_last_of('/')));
}

void Utils::viewCppStandartUsing()
{
    std::cout << "C++ standard used: ";

    #if __cplusplus >= 202002L
        std::cout << "C++20 или новее" << std::endl;
    #elif __cplusplus >= 201703L
        std::cout << "C++17" << std::endl;
    #elif __cplusplus >= 201402L
        std::cout << "C++14" << std::endl;
    #elif __cplusplus >= 201103L
        std::cout << "C++11" << std::endl;
    #else
        std::cout << "C++03 или старее" << std::endl;
    #endif
}

void Utils::viewCppCompilerUsing()
{
    #if defined(__clang__)
        std::cout << "Clang version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << "\n";
    #elif defined(__GNUC__) || defined(__GNUG__)
        std::cout << "GCC version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
    #elif defined(_MSC_VER)
        std::cout << "MSVC version: " << _MSC_VER << "\n";
    #else
        std::cout << "Unknown compiler\n";
    #endif
}

std::string Utils::convertToString(Dir directory)
{
    switch (directory) {
    case Dir::Bin:
        return "/bin/";
    case Dir::Libs:
        return "/libs/";
    case Dir::Config:
        return "/config/";
    case Dir::Certs:
        return "/certs/";
    default:
        return "/";
    }
}

std::string Utils::getPath(Dir directory, const std::string &filename)
{
    std::string path = _exetutablePath;
    if(directory != Dir::Bin) {
        path += "/..";
    }

    path += convertToString(directory);

    if(directory == Dir::Config) {
        // Конфиги делим на Dev и Release
        path += _buildType;
    }

    return path + filename;
}
