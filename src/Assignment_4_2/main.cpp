#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

bool validate(const std::string& message)
{
    if (message.empty()) {
        return false;
    }
    for (char c : message) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
};
std::string toUpperLetter(const std::string& message)
{
    std::string messageCode {};
    for (char c : message) {
        if (c == ' ') {
            continue;
        };
        char upperLetter = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        messageCode.push_back(upperLetter);
    };
    return messageCode;
};

const int AlphabetLength = 26;

std::string encrypt(const std::string& message, const std::string& key)
{
    std::string result {};
    for (int i = 0; i < message.size(); i++) {
        int messageCode = (message[i] - 'A');
        int keyCode = key[i % key.size()] - 'A';
        int encryptedCode = (messageCode + keyCode) % AlphabetLength;
        result += static_cast<char>(encryptedCode + 'A');
    };

    return result;
}
std::string decrypt(const std::string& message, const std::string& key)
{
    std::string result {};
    for (int i = 0; i < message.size(); i++) {
        int messageCode = message[i] - 'A';
        int keyCode = key[i % key.size()] - 'A';
        int decryptedCode = (messageCode - keyCode) % AlphabetLength;

        if (decryptedCode < 0) {
            decryptedCode += AlphabetLength;
        }
        result += static_cast<char>(decryptedCode + 'A');
    };

    return result;
}
int main()
{
    std::string key {};
    std::string message {};
    char yesOrNo {};
    std::string decryptedText = {};

    std::cout << "Enter a keyword to encrypt your message: ";
     std::getline(std::cin, key);

    std::cout << std::endl;

    bool validationKey = validate(key);
    if (!validationKey) {
        std::cout << "Key can't contain numbers and special characters!\n";
        return 1;
    }
    std::string toUpperKey = toUpperLetter(key);

    std::cout << "Enter the message you want to encrypt: ";
     std::getline(std::cin, message);

    bool validationResult = validate(message);
    if (!validationResult) {
        std::cout << "Text can't contain numbers and special characters!\n";
        return 1;
    }
    std::string toUpperResult = toUpperLetter(message);

    std::string encryptedText = encrypt(toUpperResult, toUpperKey);
    std::cout << "Encrypted message: " << encryptedText << std::endl;

    std::cout << "Do you want to decript your message. Yes or no(y/n) ";
    std::cin >> yesOrNo;

    if (yesOrNo == 'y') {
        decryptedText = decrypt(encryptedText, toUpperKey);
        std::cout << "Decrypted message: " << decryptedText << std::endl;
        return 0;
    }
    if (yesOrNo == 'n') {
        return 0;
    } else {
        std::cout << "Invalid option\n";
        return 1;
    }

    return 0;
}