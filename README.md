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

## Recommended Improvements

### High priority

1. **Rename the source file** to `Inventory-mgm-sys-code.cpp`.
2. **Prevent duplicate product IDs** before adding a new product.
3. **Use `std::getline()`** for product names so names such as `Wireless Mouse` are accepted.
4. **Separate responsibilities** into functions or classes such as:
   - `addProduct()`
   - `displayProducts()`
   - `searchProduct()`
   - `updateProduct()`
   - `deleteProduct()`
   - `sellProduct()`
5. **Replace the fixed array** with `std::vector<Product>` for safer and more flexible storage.
6. **Add file persistence** using CSV, JSON, or a simple text file so inventory survives program restarts.

### Code quality and correctness

- Make product fields private and expose controlled methods instead of keeping all fields public.
- Use `const` for display and lookup functions that do not modify products.
- Replace repeated input-validation loops with reusable helper functions.
- Use `double` or an integer number of cents instead of `float` for prices.
- Use `std::numeric_limits<std::streamsize>::max()` when clearing input instead of a hard-coded `1000` character limit.
- Add clear comments and consistent formatting.
- Handle end-of-file or closed input streams gracefully.

### Features to add

- Low-stock warnings
- Product categories and suppliers
- Restock operation
- Sort products by name, price, quantity, or ID
- Search by name as well as ID
- Inventory value calculation
- Sales history and transaction records
- Confirmation prompts before deleting products
- Export inventory reports
- Login or role-based access for larger versions

### Repository improvements

- Add a `.gitignore` for compiled binaries and IDE files.
- Add a `LICENSE` file.
- Add a `CONTRIBUTING.md` file if collaboration is expected.
- Add a `Makefile` or CMake configuration for repeatable builds.
- Add a `tests/` directory with tests for adding, searching, updating, deleting, and selling products.
- Add GitHub Actions to compile the project automatically on every push and pull request.
- Move the implementation into a `src/` directory and keep documentation in the repository root.

## Suggested Future Structure

```text
Inventory-Management-System/
├── README.md
├── LICENSE
├── .gitignore
├── CMakeLists.txt
├── include/
│   ├── Product.hpp
│   └── Inventory.hpp
├── src/
│   ├── Product.cpp
│   ├── Inventory.cpp
│   └── main.cpp
├── data/
│   └── inventory.csv
└── tests/
    └── inventory_tests.cpp
```

## Contributing

Contributions and suggestions are welcome. A useful contribution should:

1. Explain the purpose of the change.
2. Keep the code readable and focused.
3. Include tests when adding or changing behavior.
4. Update this README when usage or project structure changes.

## License

No license has been added yet. Add a license before distributing or accepting external contributions. The MIT License is a common choice for small educational projects.

## Author

Created by [RacWagg](https://github.com/RacWagg).
