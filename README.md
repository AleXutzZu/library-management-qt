# 📚 Library Management System

A Qt-based desktop application for managing a collection of **Books** and **Articles**, developed in C++. It features in-place editing, undo/redo operations, dynamic filtering, and persistence using JSON or CSV repositories.

## ✨ Features

- Add, update, and delete **Books** and **Articles**
- In-place editing directly in the table
- Custom delegates for field validation
- Filter and sort publications with **AND/OR** logic
- Undo last action (add, remove, update)
- Save and load publications from **JSON** or **CSV**
- Clean architecture using MVC + custom signals/slots

## 🏗️ Technologies

- **C++20**
- **Qt 6** (Widgets, Model/View Framework)
- **Google Test** for unit testing
- **CMake** for build configuration

## 📄 Example JSON entry

```json
{
  "type": "Book",
  "title": "Design Patterns",
  "date": "10/02/1995",
  "authors": ["Erich Gamma", "Richard Helm"],
  "pages": 395,
  "publisher": "Addison-Wesley"
}
```

## 🧠 TODO 
- Add search bar with live filtering
- Export filtered view to file
- Multi-language support (Qt Linguist)
- Redo functionality
