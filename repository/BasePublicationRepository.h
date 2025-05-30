//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H

#include <vector>
#include "../model/Publication.h"
#include <memory>
#include <QObject>

class BasePublicationRepository : public QObject {
Q_OBJECT
protected:
    std::vector<std::shared_ptr<Publication>> publications;

public:
    BasePublicationRepository(QObject *parent = nullptr) : QObject(parent) {}

    virtual void load(const std::string &filePath) = 0;

    virtual void save(const std::string &filePath) = 0;

    void add(const std::shared_ptr<Publication> &publication);

    void removeByTitle(const std::string &title);

    std::shared_ptr<Publication> findByTitle(const std::string &title);

    const std::vector<std::shared_ptr<Publication>> &getPublications() const;

    virtual ~BasePublicationRepository() = default;

    static std::vector<std::string> tokenize(std::string &&input, char sep = ',') {
        std::vector<std::string> tokens;
        std::stringstream stream(std::move(input));
        std::string token;
        while (std::getline(stream, token, sep)) {
            tokens.push_back(std::move(token));
        }
        return tokens;
    }

signals:

    void dataAdded(int);

    void dataRemoved(int);
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_BASEPUBLICATIONREPOSITORY_H
