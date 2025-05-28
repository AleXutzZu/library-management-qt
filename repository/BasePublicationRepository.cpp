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
}

void BasePublicationRepository::removeByTitle(const std::string &title) {
    auto ptr = std::find_if(publications.begin(), publications.end(), [&title](const auto &pub) {
        return pub->getTitle() == title;
    });

    if (ptr == publications.end()) throw std::invalid_argument("Could not find publication with title: " + title);
    publications.erase(ptr);
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
