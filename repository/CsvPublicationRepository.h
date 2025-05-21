//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_CSVPUBLICATIONREPOSITORY_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_CSVPUBLICATIONREPOSITORY_H

#include "BasePublicationRepository.h"

class CsvPublicationRepository : public BasePublicationRepository {
public:
    void load(const std::string &filePath) override;

    void save(const std::string &filePath) override;

};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_CSVPUBLICATIONREPOSITORY_H
