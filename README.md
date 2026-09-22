# Inventory Management System (C++)

A simple command-line inventory management system written in **C++**. This project demonstrates basic object-oriented programming, arrays, input validation, and CRUD-style inventory operations.

> **Project status:** Beginner/student project. The current version stores data in memory only, so all products are lost when the program exits.

## Features

- Add products with:
  - Product ID (must be unique — duplicate IDs are rejected)
  - Product name (supports multi-word names, e.g. "Red Shoes")
  - Price
  - Quantity
- Display all products, including:
  - Total inventory value (price × quantity summed across all products)
  - Low-stock warning for any product with quantity ≤ 5
- Search for a product by ID
- Update product price and quantity
- Delete products by ID
- Sell products and reduce available stock
- Validate numeric menu, price, quantity, and product ID input
- Prevent sales when the requested quantity exceeds available stock
- Skip ID-based operations gracefully when the inventory is empty
- Limit the inventory to 100 products

## Requirements

- A C++ compiler supporting C++11 or later
- A terminal or command prompt

Recommended tools:

- GCC / G++
- Clang
- Visual Studio
- Code::Blocks
- Visual Studio Code with a C++ extension

## Project Structure

```
Inventory-Management-System/
├── src/
│   └── main.cpp
├── .gitignore
├── LICENSE
└── README.md
```

## How to Compile

### GCC / G++

```bash
g++ -std=c++11 -Wall -Wextra -pedantic src/main.cpp -o inventory
```

### Clang

```bash
clang++ -std=c++11 -Wall -Wextra -pedantic src/main.cpp -o inventory
```

## How to Run

### Linux / macOS

```
./inventory
```

### Windows

```
.\inventory.exe
```

## Usage

After starting the program, choose an option from the menu:

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

A typical workflow is:

1. Select **Add Product** to create an inventory item.
2. Select **Display Products** to view all stored items, total value, and low-stock warnings.
3. Select **Search Product** to find an item by ID.
4. Select **Update Product** to change its price or quantity.
5. Select **Sell Product** to decrease its stock.
6. Select **Delete Product** to remove it from the inventory.

## Technical Overview

The application uses a `Product` class containing:

- `id` — integer product identifier
- `name` — product name (string, supports spaces)
- `price` — product price
- `quantity` — available stock quantity

Products are stored in a fixed-size array with capacity for 100 items. Duplicate product IDs are rejected at add-time via an `idExists()` check. The `main()` function provides the menu and performs operations such as searching, updating, deleting, and selling products, using a shared `readValidId()` helper for consistent ID input validation.

## Current Limitations

- Product data is not saved to a file or database.
- The inventory is limited to 100 products.
- The program uses `float` for prices, which can cause currency precision problems.
- Most application logic is contained in `main()`, making the code harder to maintain as features grow.
- There are no automated tests or continuous integration checks.
- The program does not show sales history or generate reports.

## Contributing

Pull requests are welcome.

Created by [RacWagg](https://github.com/RacWagg).
