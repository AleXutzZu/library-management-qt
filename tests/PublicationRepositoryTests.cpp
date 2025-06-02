//
// Created by AleXutzZu on 03/06/2025.
//

#include <gtest/gtest.h>
#include "../repository/JsonPublicationRepository.h"
#include "../model/Book.h"
#include "../model/Article.h"

class BaseRepositoryTest : public ::testing::Test {
protected:
    std::unique_ptr<JsonPublicationRepository> jsonRepo;

    void SetUp() override {
        jsonRepo = std::make_unique<JsonPublicationRepository>();
        jsonRepo->load("resources/dummy.json");
    }

    void TearDown() override {
        jsonRepo.reset();
    }
};


TEST_F(BaseRepositoryTest, LoadInitialData) {
    const auto &pubs = jsonRepo->getPublications();
    ASSERT_FALSE(pubs.empty()) << "Repository should not be empty after loading";
}

TEST_F(BaseRepositoryTest, AddValidBook) {
    auto book = std::make_shared<Book>(std::vector<std::string>{"Author1"}, "New Book", Date{2024, 1, 1}, 200,
                                       "PublisherX");
    jsonRepo->add(book);
    auto found = jsonRepo->findByTitle("New Book");
    ASSERT_EQ(found->getTitle(), "New Book");
}

TEST_F(BaseRepositoryTest, AddDuplicateThrows) {
    auto pub = jsonRepo->getPublications().at(0);
    ASSERT_THROW(jsonRepo->add(pub), std::invalid_argument);
}

TEST_F(BaseRepositoryTest, RemoveExistingPublication) {
    auto pub = std::make_shared<Article>(std::vector<std::string>{"A1"},
                                         "Unique Article", Date{2023, 2, 2},
                                         "JournalX",
                                         10);
    jsonRepo->add(pub);
    jsonRepo->removeByTitle("Unique Article");
    ASSERT_EQ(jsonRepo->findByTitle("Unique Article"), nullptr);
}

TEST_F(BaseRepositoryTest, RemoveNonexistentThrows) {
    ASSERT_THROW(jsonRepo->removeByTitle("NotInRepo"), std::invalid_argument);
}

TEST_F(BaseRepositoryTest, UpdateValidBook) {
    auto book = std::make_shared<Book>(std::vector<std::string>{"Author1"}, "Temp Book", Date{2024, 1, 1}, 200,
                                       "OldPublisher");
    jsonRepo->add(book);
    auto updated = std::make_shared<Book>(std::vector<std::string>{"Author1"}, "Temp Book", Date{2024, 1, 1}, 300,
                                          "NewPublisher");

    jsonRepo->update("Temp Book", updated);
    auto found = jsonRepo->findByTitle("Temp Book");

    ASSERT_EQ(std::dynamic_pointer_cast<Book>(found)->getPublisher(), "NewPublisher");
    ASSERT_EQ(std::dynamic_pointer_cast<Book>(found)->getNumberOfPages(), 300);
}

TEST_F(BaseRepositoryTest, UpdateWrongTypeThrows) {
    auto article = std::make_shared<Article>(std::vector<std::string>{"A1"}, "TypeConflict", Date{2023, 1, 1}, "JX",
                                             15);
    jsonRepo->add(article);
    auto book = std::make_shared<Book>(std::vector<std::string>{"A1"}, "TypeConflict", Date{2023, 1, 1}, 100, "PX");

    ASSERT_THROW(jsonRepo->update("TypeConflict", book), std::invalid_argument);
}

TEST_F(BaseRepositoryTest, UpdateToDuplicateTitleThrows) {
    auto a1 = std::make_shared<Article>(std::vector<std::string>{"A1"}, "Title1", Date{2022, 1, 1}, "J1", 5);
    auto a2 = std::make_shared<Article>(std::vector<std::string>{"A2"}, "Title2", Date{2022, 1, 1}, "J2", 5);
    jsonRepo->add(a1);
    jsonRepo->add(a2);

    auto update = std::make_shared<Article>(std::vector<std::string>{"A2"}, "Title1", Date{2022, 1, 1}, "J2", 5);
    ASSERT_THROW(jsonRepo->update("Title2", update), std::invalid_argument);
}

TEST_F(BaseRepositoryTest, TokenizeAuthorsString) {
    auto tokens = BasePublicationRepository::tokenize("Alice;Bob;Charlie", ';');
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "Alice");
    EXPECT_EQ(tokens[1], "Bob");
    EXPECT_EQ(tokens[2], "Charlie");
}
