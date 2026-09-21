#include "Inventory.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace
{
int readInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a number.\n";
    }
}

int readNonNegativeInt(const std::string& prompt)
{
    while (true)
    {
        const int value = readInt(prompt);
        if (value >= 0)
        {
            return value;
        }
        std::cout << "Invalid quantity! Please enter a non-negative number.\n";
    }
}

double readNonNegativeDouble(const std::string& prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= 0.0)
            {
                return value;
            }
            std::cout << "Invalid price! Please enter a non-negative number.\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
        }
    }
}

std::string readNonEmptyLine(const std::string& prompt)
{
    std::string value;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty())
        {
            return value;
        }

        std::cout << "Product name cannot be empty.\n";
    }
}

void displayProduct(const Product& product)
{
    std::cout << "\nID       : " << product.getId();
    std::cout << "\nName     : " << product.getName();
    std::cout << "\nPrice    : " << product.getPrice();
    std::cout << "\nQuantity : " << product.getQuantity() << "\n";
}

std::string resolveInventoryPath()
{
    const std::string defaultPath = "data/inventory.csv";
    std::ifstream local(defaultPath);
    if (local.good())
    {
        return defaultPath;
    }

    const std::string buildPath = "../data/inventory.csv";
    std::ifstream fromBuildDir(buildPath);
    if (fromBuildDir.good())
    {
        return buildPath;
    }

    return defaultPath;
}

void saveInventory(const Inventory& inventory, const std::string& inventoryPath)
{
    std::string saveError;
    if (!inventory.saveToCsv(inventoryPath, &saveError))
    {
        std::cout << "\nWarning: " << saveError << "\n";
    }
}
} // namespace

int main()
{
    Inventory inventory;
    const std::string inventoryPath = resolveInventoryPath();
    std::string loadMessage;
    if (!inventory.loadFromCsv(inventoryPath, &loadMessage))
    {
        std::cout << "Warning: " << loadMessage << "\n";
    }
    else if (!loadMessage.empty())
    {
        std::cout << loadMessage << "\n";
    }

    int choice = 0;
    do
    {
        std::cout << "\n\n===== INVENTORY MANAGEMENT SYSTEM =====";
        std::cout << "\n1. Add Product";
        std::cout << "\n2. Display Products";
        std::cout << "\n3. Search Product";
        std::cout << "\n4. Update Product";
        std::cout << "\n5. Delete Product";
        std::cout << "\n6. Sell Product";
        std::cout << "\n7. Exit";

        choice = readInt("\n\nEnter your choice: ");

        if (choice < 1 || choice > 7)
        {
            std::cout << "Invalid choice! Please enter a number from 1 to 7.";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            const int id = readInt("\nEnter Product ID: ");
            const std::string name = readNonEmptyLine("Enter Product Name: ");
            const double price = readNonNegativeDouble("Enter Price: ");
            const int quantity = readNonNegativeInt("Enter Quantity: ");

            std::string error;
            if (inventory.addProduct(Product(id, name, price, quantity), &error))
            {
                std::cout << "\nProduct added successfully!";
                saveInventory(inventory, inventoryPath);
            }
            else
            {
                std::cout << "\n" << error;
            }
            break;
        }
        case 2:
        {
            const auto& products = inventory.getProducts();
            if (products.empty())
            {
                std::cout << "\nNo products available.";
            }
            else
            {
                for (std::size_t i = 0; i < products.size(); ++i)
                {
                    std::cout << "\n--- Product " << i + 1 << " ---";
                    displayProduct(products[i]);
                }
            }
            break;
        }
        case 3:
        {
            const int id = readInt("\nEnter Product ID: ");
            const Product* product = inventory.findProductById(id);
            if (product == nullptr)
            {
                std::cout << "\nProduct not found.";
            }
            else
            {
                displayProduct(*product);
            }
            break;
        }
        case 4:
        {
            const int id = readInt("\nEnter Product ID to update: ");
            const double newPrice = readNonNegativeDouble("Enter New Price: ");
            const int newQuantity = readNonNegativeInt("Enter New Quantity: ");

            std::string error;
            if (inventory.updateProduct(id, newPrice, newQuantity, &error))
            {
                std::cout << "\nProduct updated successfully!";
                saveInventory(inventory, inventoryPath);
            }
            else
            {
                std::cout << "\n" << error;
            }
            break;
        }
        case 5:
        {
            const int id = readInt("\nEnter Product ID to delete: ");
            std::string error;
            if (inventory.deleteProduct(id, &error))
            {
                std::cout << "\nProduct deleted successfully!";
                saveInventory(inventory, inventoryPath);
            }
            else
            {
                std::cout << "\n" << error;
            }
            break;
        }
        case 6:
        {
            const int id = readInt("\nEnter Product ID to sell: ");
            const int sellQuantity = readInt("Enter quantity to sell: ");

            std::string error;
            if (inventory.sellProduct(id, sellQuantity, &error))
            {
                const Product* product = inventory.findProductById(id);
                std::cout << "\nSale successful!";
                if (product != nullptr)
                {
                    std::cout << "\nRemaining Stock: " << product->getQuantity();
                }
                saveInventory(inventory, inventoryPath);
            }
            else
            {
                std::cout << "\n" << error;
            }
            break;
        }
        case 7:
            saveInventory(inventory, inventoryPath);
            std::cout << "\nThank you for using the system!";
            break;
        default:
            break;
        }

    } while (choice != 7);

    return 0;
}
