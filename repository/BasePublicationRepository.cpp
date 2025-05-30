//
// Created by AleXutzZu on 21/05/2025.
//

#include "BasePublicationRepository.h"
#include <algorithm>

void BasePublicationRepository::add(const std::shared_ptr<Publication> &publication) {
    auto result = findByTitle(publication->getTitle());
    if (result) {
        throw std::invalid_argument("Publication with matching title already exists: " + publication->getTitle());
    }
    publications.push_back(publication);
    emit dataAdded(publications.size() - 1);
}

void BasePublicationRepository::removeByTitle(const std::string &title) {
    auto ptr = std::find_if(publications.begin(), publications.end(), [&title](const auto &pub) {
        return pub->getTitle() == title;
    });

    if (ptr == publications.end()) throw std::invalid_argument("Could not find publication with title: " + title);
    int position = ptr - publications.begin();
    publications.erase(ptr);
    emit dataRemoved(position);
}

std::shared_ptr<Publication> BasePublicationRepository::findByTitle(const std::string &title) {
    auto result = std::find_if(publications.begin(), publications.end(), [&title](const auto &publication) {
        return publication->getTitle() == title;
    });
    if (result == publications.end()) return nullptr;
    return *result;
}

const std::vector<std::shared_ptr<Publication>> &BasePublicationRepository::getPublications() const {
    return publications;
}

std::vector<std::string> BasePublicationRepository::tokenize(std::string &&input, char sep) {
    std::vector<std::string> tokens;
    std::stringstream stream(std::move(input));
    std::string token;
    while (std::getline(stream, token, sep)) {
        tokens.push_back(std::move(token));
    }
    return tokens;
}
