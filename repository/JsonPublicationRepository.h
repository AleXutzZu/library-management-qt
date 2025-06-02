//
// Created by AleXutzZu on 02/06/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_JSONPUBLICATIONREPOSITORY_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_JSONPUBLICATIONREPOSITORY_H

#include "BasePublicationRepository.h"

class JsonPublicationRepository : public BasePublicationRepository {
private:
    static std::shared_ptr<Publication> publicationFromJSON(QJsonObject object);

public:
    void load(const std::string &filePath) override;

    void save(const std::string &filePath) override;

};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_JSONPUBLICATIONREPOSITORY_H
