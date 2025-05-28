//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H

#include <vector>
#include "../model/Publication.h"
#include <memory>

class BasePublicationRepository {
private:
    std::vector<std::shared_ptr<Publication>> publications;

public:
    BasePublicationRepository() = default;

    virtual void load(const std::string &filePath) = 0;

    virtual void save(const std::string &filePath) = 0;

    void add(const std::shared_ptr<Publication> &publication);

    void removeByTitle(const std::string &title);

    std::shared_ptr<Publication> findByTitle(const std::string &title);

    const std::vector<std::shared_ptr<Publication>> &getPublications() const;

    virtual ~BasePublicationRepository() = default;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
