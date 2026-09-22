# Inventory Management System (C++)

A simple console-based Inventory Management System built in C++ using OOP (class-based) principles. Supports adding, viewing, searching, updating, deleting, and selling products — all in-memory, no database.

## Features

- Add new products (ID, name, price, quantity)
- Display all products
- Search product by ID
- Update price/quantity of an existing product
- Delete a product
- Sell a product (with stock validation)

## Tech Stack

- **Language:** C++
- **Concepts used:** Classes & Objects, Arrays of Objects, Loops, Switch-case, Basic I/O

## Project Structure

```
inventory-management-system/
├── src/
│   └── main.cpp
├── README.md
├── LICENSE
└── .gitignore
```

## How to Run

```bash
git clone https://github.com/<your-username>/inventory-management-system.git
cd inventory-management-system
g++ src/main.cpp -o ims
./ims          # use ims.exe on Windows
```

## Sample Menu

```
===== INVENTORY MANAGEMENT SYSTEM =====
1. Add Product
2. Display Products
3. Search Product
4. Update Product
5. Delete Product
6. Sell Product
7. Exit
```

## Limitations / Future Improvements

- Fixed-size array (max 100 products) — could switch to `vector<Product>`
- No file/database persistence — data resets on exit
- No input validation (e.g., negative price/quantity, duplicate IDs)
- Could split into multiple files (`Product.h`, `Product.cpp`, `main.cpp`)

## Author

Shrey — CSIT student, Tribhuvan University

## License

This project is licensed under the MIT License — see [LICENSE](LICENSE) for details.
