//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H

#include <vector>
#include "../model/Publication.h"

class BasePublicationRepository {
private:
    std::vector<Publication *> publications;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
