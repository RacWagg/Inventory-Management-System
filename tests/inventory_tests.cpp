#include "Inventory.hpp"

#include <cassert>
#include <cstdio>
#include <string>

void testAddAndSearch()
{
    Inventory inventory;
    std::string error;
    const bool added = inventory.addProduct(Product(1, "Wireless Mouse", 25.5, 10), &error);
    assert(added);
    assert(error.empty());

    const Product* product = inventory.findProductById(1);
    assert(product != nullptr);
    assert(product->getName() == "Wireless Mouse");
}

void testDuplicateIdsRejected()
{
    Inventory inventory;
    std::string error;
    assert(inventory.addProduct(Product(7, "Keyboard", 40.0, 4), &error));
    error.clear();
    assert(!inventory.addProduct(Product(7, "Keyboard 2", 50.0, 5), &error));
    assert(error == "Product ID already exists.");
}

void testUpdateDeleteAndSell()
{
    Inventory inventory;
    std::string error;
    assert(inventory.addProduct(Product(5, "Monitor", 199.99, 8), &error));

    assert(inventory.updateProduct(5, 149.99, 6, &error));
    const Product* updated = inventory.findProductById(5);
    assert(updated != nullptr);
    assert(updated->getPrice() == 149.99);
    assert(updated->getQuantity() == 6);

    assert(inventory.sellProduct(5, 2, &error));
    const Product* sold = inventory.findProductById(5);
    assert(sold != nullptr);
    assert(sold->getQuantity() == 4);

    error.clear();
    assert(!inventory.sellProduct(5, 0, &error));
    assert(error == "Invalid quantity. Quantity must be greater than zero.");

    error.clear();
    assert(!inventory.sellProduct(5, 100, &error));
    assert(error == "Insufficient stock.");

    assert(inventory.deleteProduct(5, &error));
    assert(inventory.findProductById(5) == nullptr);
}

void testPersistence()
{
    const std::string path = "/tmp/inventory_tests_data.csv";
    std::remove(path.c_str());

    {
        Inventory inventory;
        std::string error;
        assert(inventory.addProduct(Product(11, "USB Cable", 9.5, 15), &error));
        assert(inventory.saveToCsv(path, &error));
    }

    {
        Inventory loaded;
        std::string error;
        assert(loaded.loadFromCsv(path, &error));
        const Product* product = loaded.findProductById(11);
        assert(product != nullptr);
        assert(product->getName() == "USB Cable");
        assert(product->getPrice() == 9.5);
        assert(product->getQuantity() == 15);
    }

    std::remove(path.c_str());
}

int main()
{
    testAddAndSearch();
    testDuplicateIdsRejected();
    testUpdateDeleteAndSell();
    testPersistence();
    return 0;
}
