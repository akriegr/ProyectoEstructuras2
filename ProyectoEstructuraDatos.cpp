#include <iostream>
#include "DBManager.h"
#include <memory>

int main() {
    try {
        auto& dbManager = DBManager::getInstance();

        if (dbManager.connect()) {
            std::cout << "Connected to the database successfully!" << std::endl;
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
