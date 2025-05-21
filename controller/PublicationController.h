//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H

#include "../repository/BasePublicationRepository.h"

class PublicationController {
private:
    std::unique_ptr<BasePublicationRepository> repository;

public:
    explicit PublicationController(std::unique_ptr<BasePublicationRepository> repository);
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
