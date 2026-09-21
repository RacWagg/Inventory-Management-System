# Inventory Management System

A command-line inventory manager in modern C++ with CRUD operations, sales handling, and CSV persistence.

## Features

- Add products (ID, name, price, quantity)
- Display all products
- Search products by ID
- Update product price and quantity
- Delete products by ID
- Sell products and decrease stock
- Prevent duplicate product IDs
- Support product names with spaces
- Validate invalid IDs, quantities, prices, and menu choices with clear messages
- Load inventory from `data/inventory.csv` on startup
- Save inventory back to CSV after mutations and on exit

## Project Structure

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

## Build Instructions (CMake)

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

This builds:

- `build/inventory` (main CLI application)
- `build/inventory_tests` (test executable)

## Run

```bash
./build/inventory
```

Menu options are:

1. Add Product
2. Display Products
3. Search Product
4. Update Product
5. Delete Product
6. Sell Product
7. Exit

## Testing

Run tests with CTest:

```bash
cd build
ctest --output-on-failure
```

Or run the test binary directly:

```bash
./build/inventory_tests
```

## CSV Persistence Format

File: `data/inventory.csv`

Format:

```csv
id,name,price,quantity
1001,Sample Product,19.99,25
```

Notes:

- The header row is optional but recommended.
- Missing file is handled gracefully (app starts with empty inventory).
- Malformed rows are skipped with a warning.
- Names with spaces are supported.
- To keep parsing simple, avoid commas in product names.

## Migration Note

The previous single-file beginner implementation has been migrated into:

- `Product` model class (`include/Product.hpp`, `src/Product.cpp`)
- `Inventory` domain class (`include/Inventory.hpp`, `src/Inventory.cpp`)
- CLI and input helpers (`src/main.cpp`)

This repository no longer keeps a duplicate legacy implementation at the root.

## Current Limitations

- CSV parsing is intentionally simple and does not support quoted commas in names.
- No category/reporting/history features yet.
- No database backend (CSV only).

## License

This project is licensed under the MIT License. See `LICENSE`.

## Author

Created by [RacWagg](https://github.com/RacWagg).
