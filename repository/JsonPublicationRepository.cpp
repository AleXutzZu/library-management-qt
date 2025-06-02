//
// Created by AleXutzZu on 02/06/2025.
//

#include "JsonPublicationRepository.h"
#include "../model/Book.h"
#include "../model/Article.h"
#include <QJsonArray>
#include <QFile>

void JsonPublicationRepository::load(const std::string &filePath) {
    QFile input(QString::fromStdString(filePath));
    if (!input.open(QIODevice::ReadOnly)) throw std::runtime_error("Could not open file: " + filePath);
    QJsonDocument doc = QJsonDocument::fromJson(input.readAll());
    input.close();
    if (!doc.isArray()) throw std::runtime_error("Malformed JSON input: Expected array and got object");
    QJsonArray array = doc.array();

    for (const auto &value: array) {
        if (!value.isObject()) throw std::runtime_error("Malformed JSON input: Expected object");
        auto object = value.toObject();
        auto publication = publicationFromJSON(object);
        this->add(publication);
    }
}

void JsonPublicationRepository::save(const std::string &filePath) {
    QJsonArray array;
    for (const auto &publication: publications) {
        array.push_back(publication->toJSON());
    }

    QFile output(QString::fromStdString(filePath));

    if (output.open(QIODevice::WriteOnly)) {
        output.write(QJsonDocument(array).toJson());
        output.close();
    } else throw std::runtime_error("Could not open file: " + filePath);
}

std::shared_ptr<Publication> JsonPublicationRepository::publicationFromJSON(QJsonObject object) {
    std::string title = object["title"].toString().toStdString();
    Date date = Date(object["date"].toString().toStdString());
    std::vector<std::string> authors;

    auto authorsVec = object["authors"].toArray();
    for (const auto &value: authorsVec) {
        authors.push_back(value.toString().toStdString());
    }

    if (object["type"] == "Book") {
        std::string publisher = object["publisher"].toString().toStdString();
        int pages = object["numberOfPages"].toInt();
        return std::make_shared<Book>(authors, title, date, pages, publisher);
    } else if (object["type"] == "Article") {
        std::string journal = object["journal"].toString().toStdString();
        int citations = object["citations"].toInt();
        return std::make_shared<Article>(authors, title, date, journal, citations);
    } else throw std::runtime_error("Malformed JSON object: No type field");
}
