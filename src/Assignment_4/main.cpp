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

std::string encrypt(std::string funcResult, int key)
{
    std::string result = "";
    for (int i = 0; i < funcResult.size(); i++) {
        int encryptedCode = (funcResult[i] + key - 'A') % AlphabetLength + 'A';
        result += static_cast<char>(encryptedCode);
    };

    return result;
}
std::string decrypt(std::string encryptedText, int key)
{
    std::string result = "";
    for (int i = 0; i < encryptedText.size(); i++) {
        int decryptedCode = (encryptedText[i] - key - 'A') % AlphabetLength;
        if (decryptedCode < 0) {
            decryptedCode += AlphabetLength;
            ;
        }
        decryptedCode += 'A';

        result += static_cast<char>(decryptedCode);
    };

    return result;
}
int main()
{
    int key = 0;
    std::string message {};
    char yesOrNo {};
    int keyToDecrypt {};
    std::string decryptedText = {};

    std::cout << "Enter a number to create a key for your message: ";
    std::cin >> key;
    std::cout << std::endl;
    std::cout << "Enter the message you want to encrypt: ";
    std::getline(std::cin, message);

    bool validationResult = validate(message);
    if (!validationResult) {
        std::cout << "Text can't contain numbers and special characters!\n";
        return 1;
    }

    std::string toUpperResult = toUpperLetter(message);

    std::string encryptedText = encrypt(toUpperResult, key);
    std::cout << "Encrypted message: " << encryptedText << std::endl;

    std::cout << "Do you want to decript your message. Yes or no(y/n) ";
    std::cin >> yesOrNo;

    if (yesOrNo == 'y') {
        std::cout << "Enter a key to decrypt your message: ";
        std::cin >> keyToDecrypt;
        if (keyToDecrypt != key) {
            std::cout << "Wrong key! Decryption failed.\n";
            return 1;
        }
        decryptedText = decrypt(encryptedText, keyToDecrypt);
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