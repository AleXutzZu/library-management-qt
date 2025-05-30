//
// Created by AleXutzZu on 21/05/2025.
//

#include "CsvPublicationRepository.h"
#include "../model/Article.h"
#include "../model/Book.h"
#include <fstream>

void CsvPublicationRepository::load(const std::string &filePath) {
    std::ifstream input(filePath);
    if (!input) throw std::runtime_error("Could not open file: " + filePath);
    //First line should be the header: type, title, date, authors, pages, publication, citations, journal
    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)) {
        auto tokens = BasePublicationRepository::tokenize(std::move(line));
        if (tokens.size() != 8) throw std::runtime_error("Invalid number of columns");

        std::string &title = tokens[1];
        const std::string &date = tokens[2];
        std::string &authors = tokens[3];

        auto authorsVec = BasePublicationRepository::tokenize(std::move(authors), ';');

        if (authorsVec.empty()) throw std::runtime_error("Invalid author list");

        Date dateObj;
        std::stringstream str(date);
        str >> dateObj;
        if (!dateObj.isValid()) throw std::runtime_error("Invalid date: " + date);

        if (tokens[0] == "Article") {
            std::string &citations = tokens[6];
            std::string &journal = tokens[7];
            int result;

            try {
                result = std::stoi(citations);
            } catch (std::exception &e) {
                throw std::runtime_error("Invalid value for citation field: " + citations);
            }

            auto article = std::make_shared<Article>(authorsVec, title, dateObj, journal, result);
            this->add(article);
        } else if (tokens[0] == "Book") {
            std::string &pages = tokens[4];
            std::string &publisher = tokens[5];
            int result;
            try {
                result = std::stoi(pages);
            } catch (std::exception &e) {
                throw std::runtime_error("Invalid value for pages field: " + pages);
            }

            auto book = std::make_shared<Book>(authorsVec, title, dateObj, result, publisher);
            this->add(book);
        } else throw std::runtime_error("Invalid value for type field: " + tokens[0]);
    }
}

void CsvPublicationRepository::save(const std::string &filePath) {
    std::ofstream output(filePath);
    if (!output) throw std::runtime_error("Could not open file: " + filePath);
    //TODO Save data
    //Before doing that we need to implement it at the class level of Publication, Book & Article
}
