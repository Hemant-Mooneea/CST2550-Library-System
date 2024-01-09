#include <iostream>
#include <regex>

bool hasNonAlpha(std::string str) {
    std::regex regexPattern("[^a-zA-Z]");
    return !std::regex_search(str, regexPattern);
}

int main() {
    std::string testString = "Hello123";

    if (hasNonAlpha(testString)) {
        std::cout << "String contains only alphabetic characters." << std::endl;
    } else {
        std::cout << "String contains non-alphabetic characters." << std::endl;
    }

    return 0;
}
