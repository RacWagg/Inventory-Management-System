# Inventory Management System

A simple command-line inventory management system written in **C++**. This project demonstrates basic object-oriented programming, arrays, input validation, and CRUD-style inventory operations.

> **Project status:** Beginner/student project. The current version stores data in memory only, so all products are lost when the program exits.

## Features

- Add products with:
  - Product ID
  - Product name
  - Price
  - Quantity
- Display all products
- Search for a product by ID
- Update product price and quantity
- Delete products by ID
- Sell products and reduce available stock
- Validate numeric menu, price, quantity, and product ID input
- Prevent sales when the requested quantity exceeds available stock
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

```text
Inventory-Management-System/
├── Inventory-mgm-sys-code              # Main C++ source file
├── Inventory_Management_System_Error_Handled.txt
└── README.md                           # Project documentation
```

The main source file currently has no `.cpp` extension. Renaming it to `Inventory-mgm-sys-code.cpp` is recommended so that IDEs, GitHub, and build tools recognize it as a C++ source file.

## How to Compile

### GCC / G++

Because the current source file has no `.cpp` extension, compile it by explicitly specifying the C++ language:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -x c++ Inventory-mgm-sys-code -o inventory
```

If the file has been renamed to `Inventory-mgm-sys-code.cpp`, use:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Inventory-mgm-sys-code.cpp -o inventory
```

### Clang

```bash
clang++ -std=c++11 -Wall -Wextra -pedantic -x c++ Inventory-mgm-sys-code -o inventory
```

## How to Run

### Linux / macOS

```bash
./inventory
```

### Windows

```powershell
.\inventory.exe
```

## Usage

After starting the program, choose an option from the menu:

```text
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
2. Select **Display Products** to view all stored items.
3. Select **Search Product** to find an item by ID.
4. Select **Update Product** to change its price or quantity.
5. Select **Sell Product** to decrease its stock.
6. Select **Delete Product** to remove it from the inventory.

## Technical Overview

The application uses a `Product` class containing:

- `id` — integer product identifier
- `name` — product name
- `price` — product price
- `quantity` — available stock quantity

Products are stored in a fixed-size array with capacity for 100 items. The `main()` function provides the menu and performs operations such as searching, updating, deleting, and selling products.

## Current Limitations

- Product data is not saved to a file or database.
- The inventory is limited to 100 products.
- Duplicate product IDs are currently allowed.
- Product names cannot contain spaces because input uses `cin >> name`.
- The program uses `float` for prices, which can cause currency precision problems.
- Most application logic is contained in `main()`, making the code harder to maintain as features grow.
- There are no automated tests or continuous integration checks.
- The source file does not currently use the conventional `.cpp` extension.
- The program does not show totals, low-stock alerts, sales history, or reports.

.


Created by [RacWagg](https://github.com/RacWagg).
