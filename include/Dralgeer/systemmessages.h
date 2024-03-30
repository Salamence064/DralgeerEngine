#include <iostream>

#pragma once

// ? A header including macros for system messages
// todo update to just be constexprs


#define DEBUG_MESSAGE(objectType, name, description, expected, obtained) \
({ \
    std::cout << "[DEBUG] " << objectType << " " << name << ":\n\t" << description << "\n\tExpected Value: " << expected << ". Obtained Value: " << obtained << "\n\t"; \
    if((expected) == (obtained)) { \
        std::cout << "[SUCCESS]\n"; \
    \
    } else { \
        std::cout << "[FAILED]\n"; \
    } \
    \
    (expected) == (obtained) \
})

#define ERROR_MESSAGE(objectType, name, errorType, description, errorCode) \
({ \
    std::cout << "[ERROR] " << objectType << " " << name << ":\n\t[" << errorType << "] " << description << "\n\tError Code " << errorCode << "\n"; \
    errorCode; \
})


#define INFO_MESSAGE(objectType, name, description) \
({ \
    std::cout << "[INFO] " << objectType << " " << name << ":\n\t" << description << "\n"; \
    1; \
})

#define WARNING_MESSAGE(objectType, name, warningType, description, warningCode) \
({ \
    std::cout << "[WARNING] " << objectType << " " << name << ":\n\t[" << warningType << "] " << description << "\n\tWarning Code " << warningCode << "\n"; \
})
