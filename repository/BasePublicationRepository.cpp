//
// Created by AleXutzZu on 21/05/2025.
//

#include "BasePublicationRepository.h"
#include <algorithm>

void BasePublicationRepository::add(const std::shared_ptr<Publication> &publication) {
    for (const auto &pub: publications) {
        if (pub->getTitle() == publication->getTitle()) {
            throw std::invalid_argument("Publication with matching title already exists: " + publication->getTitle());
        }
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
