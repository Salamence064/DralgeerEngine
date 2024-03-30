#include <iostream>

#pragma once

static constexpr void DEBUG_MESSAGE(std::string const &objectType, std::string const &name,
        std::string const &description, int expected, int obtained)
{
    std::cout << "[DEBUG] " << objectType << " " << name << ":\n\t" << description << "\n\tExpected Value: " << expected << ". Obtained Value: " << obtained << "\n\t";
    if(expected == obtained) {
        std::cout << "[SUCCESS]\n";
    
    } else {
        std::cout << "[FAILED]\n";
    }
};

static constexpr int ERROR_MESSAGE(std::string const &objectType, std::string const &name,
        std::string const &errorType, std::string const &description, int errorCode)
{
    std::cout << "[ERROR] " << objectType << " " << name << ":\n\t[" << errorType << "] " << description << "\n\tError Code " << errorCode << "\n";
    return errorCode;
};

static constexpr void INFO_MESSAGE(std::string const &objectType, std::string const &name,
        std::string const &description)
{
    std::cout << "[INFO] " << objectType << " " << name << ":\n\t" << description << "\n";
};

static constexpr void WARNING_MESSAGE(std::string const &objectType, std::string const &name,
        std::string const &warningType, std::string const &description, int warningCode)
{
    std::cout << "[WARNING] " << objectType << " " << name << ":\n\t[" << warningType << "] " << description << "\n\tWarning Code " << warningCode << "\n";
};
