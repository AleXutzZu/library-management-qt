//
// Created by AleXutzZu on 21/05/2025.
//
#include <gtest/gtest.h>
#include "../controller/PublicationController.h"
#include "../repository/JsonPublicationRepository.h"

Date makeDate(int d, int m, int y) {
    return Date(y, m, d);
}

// Fixture
class PublicationControllerTest : public ::testing::Test {
protected:
    std::unique_ptr<BasePublicationRepository> repo;
    std::unique_ptr<PublicationController> controller;

    void SetUp() override {
        repo = std::make_unique<JsonPublicationRepository>();

        controller = std::make_unique<PublicationController>(*repo);
    }

    void TearDown() override {
        repo.reset();
        controller.reset();
    }
};

TEST_F(PublicationControllerTest, AddBookSuccess) {
    controller->addBook("Book1", {"Author1", "Author2"}, makeDate(1, 1, 2020), 300, "PublisherX");

    const auto &pubs = controller->getPublications();
    ASSERT_EQ(pubs.size(), 1);
    auto book = std::dynamic_pointer_cast<Book>(pubs[0]);
    ASSERT_NE(book, nullptr);
    EXPECT_EQ(book->getTitle(), "Book1");
}

TEST_F(PublicationControllerTest, AddArticleSuccess) {
    controller->addArticle("Article1", {"AuthorX"}, makeDate(2, 2, 2021), 50, "JournalY");

    const auto &pubs = controller->getPublications();
    ASSERT_EQ(pubs.size(), 1);
    auto article = std::dynamic_pointer_cast<Article>(pubs[0]);
    ASSERT_NE(article, nullptr);
    EXPECT_EQ(article->getTitle(), "Article1");
}

TEST_F(PublicationControllerTest, AddBookDuplicateThrows) {
    controller->addBook("SameTitle", {"Author"}, makeDate(1, 1, 2000), 100, "Publisher");

    EXPECT_THROW(
            controller->addBook("SameTitle", {"Author2"}, makeDate(1, 1, 2000), 200, "Publisher2"),
            std::invalid_argument
    );
}

TEST_F(PublicationControllerTest, AddArticleDuplicateThrows) {
    controller->addArticle("SameArticle", {"Author"}, makeDate(1, 1, 2000), 10, "Journal");

    EXPECT_THROW(
            controller->addArticle("SameArticle", {"Author2"}, makeDate(1, 1, 2000), 20, "OtherJournal"),
            std::invalid_argument
    );
}

TEST_F(PublicationControllerTest, RemoveByTitleSuccess) {
    controller->addBook("BookToRemove", {"A"}, makeDate(1, 1, 2000), 100, "P");
    controller->removeByTitle("BookToRemove");
    EXPECT_TRUE(controller->getPublications().empty());
}

TEST_F(PublicationControllerTest, RemoveByNonExistentTitleThrows) {
    EXPECT_THROW(controller->removeByTitle("MissingTitle"), std::invalid_argument);
}

TEST_F(PublicationControllerTest, UpdateBookSuccess) {
    controller->addBook("OriginalBook", {"A"}, makeDate(1, 1, 2020), 150, "Pub");

    BookUpdate update;
    update.title = "UpdatedBook";
    update.authors = {"New Author"};
    update.publicationDate = makeDate(10, 10, 2022);
    update.numberOfPages = 200;
    update.publisher = "NewPublisher";

    controller->updateBook("OriginalBook", std::move(update));

    auto pubs = controller->getPublications();
    ASSERT_EQ(pubs.size(), 1);
    EXPECT_EQ(pubs[0]->getTitle(), "UpdatedBook");
}

TEST_F(PublicationControllerTest, UpdateArticleSuccess) {
    controller->addArticle("OrigArt", {"X"}, makeDate(3, 3, 2020), 33, "JournalA");

    ArticleUpdate update;
    update.title = "UpdatedArt";
    update.authors = {"Z"};
    update.publicationDate = makeDate(4, 4, 2021);
    update.citations = 100;
    update.journal = "UpdatedJournal";

    controller->updateArticle("OrigArt", std::move(update));

    auto pubs = controller->getPublications();
    ASSERT_EQ(pubs.size(), 1);
    EXPECT_EQ(pubs[0]->getTitle(), "UpdatedArt");
}

TEST_F(PublicationControllerTest, UpdateBookThrowsIfNotBook) {
    controller->addArticle("Mixed", {"X"}, makeDate(1, 1, 2000), 20, "J");

    BookUpdate update;
    update.title = "WrongUpdate";
    update.authors = {"A"};
    update.publicationDate = makeDate(2, 2, 2022);
    update.numberOfPages = 300;
    update.publisher = "P";

    EXPECT_THROW(controller->updateBook("Mixed", std::move(update)), std::invalid_argument);
}

TEST_F(PublicationControllerTest, UpdateArticleThrowsIfNotArticle) {
    controller->addBook("Mixed2", {"Y"}, makeDate(1, 1, 2000), 100, "Pub");

    ArticleUpdate update;
    update.title = "WrongArt";
    update.authors = {"Z"};
    update.publicationDate = makeDate(3, 3, 2023);
    update.citations = 50;
    update.journal = "JournalZ";

    EXPECT_THROW(controller->updateArticle("Mixed2", std::move(update)), std::invalid_argument);
}

TEST_F(PublicationControllerTest, UpdateThrowsIfTitleMissing) {
    BookUpdate update;
    update.title = "New";
    update.authors = {"A"};
    update.publicationDate = makeDate(1, 1, 2001);
    update.numberOfPages = 123;
    update.publisher = "Pub";

    EXPECT_THROW(controller->updateBook("NoTitle", std::move(update)), std::invalid_argument);
}

TEST_F(PublicationControllerTest, UpdateThrowsIfNewTitleAlreadyExists) {
    controller->addBook("Book1", {"A"}, makeDate(1, 1, 2000), 100, "P");
    controller->addBook("Book2", {"B"}, makeDate(2, 2, 2000), 150, "Q");

    BookUpdate update;
    update.title = "Book2"; // Already exists
    update.authors = {"C"};
    update.publicationDate = makeDate(3, 3, 2001);
    update.numberOfPages = 200;
    update.publisher = "R";

    EXPECT_THROW(controller->updateBook("Book1", std::move(update)), std::invalid_argument);
}

TEST_F(PublicationControllerTest, UndoRevertsLastAdd) {
    controller->addBook("UndoBook", {"A"}, makeDate(1, 1, 2000), 100, "P");
    controller->undo();

    EXPECT_TRUE(controller->getPublications().empty());
}

TEST_F(PublicationControllerTest, UndoRevertsLastRemove) {
    controller->addBook("UndoRemove", {"A"}, makeDate(1, 1, 2000), 100, "P");
    controller->removeByTitle("UndoRemove");
    controller->undo();

    EXPECT_EQ(controller->getPublications().size(), 1);
}

