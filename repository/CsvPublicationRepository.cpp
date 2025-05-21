//
// Created by AleXutzZu on 21/05/2025.
//

#include "CsvPublicationRepository.h"
#include <fstream>

void CsvPublicationRepository::load(const std::string &filePath) {
    std::ifstream input(filePath);
    if (!input) throw std::runtime_error("Could not open file: " + filePath);
    //TODO Read data
    //Before doing that we need to implement it at the class level of Book & Article
}

void CsvPublicationRepository::save(const std::string &filePath) {
    std::ofstream output(filePath);
    if (!output) throw std::runtime_error("Could not open file: " + filePath);
    //TODO Save data
    //Before doing that we need to implement it at the class level of Publication, Book & Article
}
