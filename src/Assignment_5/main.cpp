#include "consoleInterface.h"
#include "library/library.h"
#include "libraryFactory/libraryFactory.h"
#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{

    if (argc < 2) {
        std::cerr << "Error: enter the path to the file in the command line";
        return 1;
    }
    std::filesystem::path filePath(argv[1]);
    std::string pathString = filePath.string();

    std::optional<Library> libraryOpt = LibraryFactory::createLibrary(pathString);

    if (!libraryOpt.has_value()) {
        std::cerr << "Failed to initialize library. Exiting.\n";
        return 1;
    }
    Library library = libraryOpt.value();
    ConsoleInterface interface(library, pathString);
    int status = -1;
    while (status != 0) {
        status = interface.run();
        if (status > 0) {
            if (library.saveToDirectory(pathString)) {
                std::cout << "Changes successfully saved to files\n";
                if (status == 1)
                    interface.printCustomers();
                if (status == 2)
                    interface.printBooks();
                if (status == 3)
                    interface.printLoans();
            } else {
                std::cerr << "Error saving changes\n";
            }
        }
    }

    return 0;
}