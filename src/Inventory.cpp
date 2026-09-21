#include "Inventory.hpp"

#include <fstream>
#include <sstream>

namespace
{
std::string trim(const std::string& value)
{
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
    {
        return "";
    }

    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, (last - first + 1));
}
} // namespace

bool Inventory::addProduct(const Product& product, std::string* error)
{
    if (findProductById(product.getId()) != nullptr)
    {
        if (error != nullptr)
        {
            *error = "Product ID already exists.";
        }
        return false;
    }

    products_.push_back(product);
    return true;
}

Product* Inventory::findProductById(int id)
{
    for (auto& product : products_)
    {
        if (product.getId() == id)
        {
            return &product;
        }
    }

    return nullptr;
}

const Product* Inventory::findProductById(int id) const
{
    for (const auto& product : products_)
    {
        if (product.getId() == id)
        {
            return &product;
        }
    }

    return nullptr;
}

bool Inventory::updateProduct(int id, double newPrice, int newQuantity, std::string* error)
{
    Product* product = findProductById(id);
    if (product == nullptr)
    {
        if (error != nullptr)
        {
            *error = "Product not found.";
        }
        return false;
    }

    if (!product->setPrice(newPrice))
    {
        if (error != nullptr)
        {
            *error = "Invalid price. Price must be non-negative.";
        }
        return false;
    }

    if (!product->setQuantity(newQuantity))
    {
        if (error != nullptr)
        {
            *error = "Invalid quantity. Quantity must be non-negative.";
        }
        return false;
    }

    return true;
}

bool Inventory::deleteProduct(int id, std::string* error)
{
    for (auto iterator = products_.begin(); iterator != products_.end(); ++iterator)
    {
        if (iterator->getId() == id)
        {
            products_.erase(iterator);
            return true;
        }
    }

    if (error != nullptr)
    {
        *error = "Product not found.";
    }
    return false;
}

bool Inventory::sellProduct(int id, int sellQuantity, std::string* error)
{
    Product* product = findProductById(id);
    if (product == nullptr)
    {
        if (error != nullptr)
        {
            *error = "Product not found.";
        }
        return false;
    }

    if (sellQuantity <= 0)
    {
        if (error != nullptr)
        {
            *error = "Invalid quantity. Quantity must be greater than zero.";
        }
        return false;
    }

    if (sellQuantity > product->getQuantity())
    {
        if (error != nullptr)
        {
            *error = "Insufficient stock.";
        }
        return false;
    }

    product->setQuantity(product->getQuantity() - sellQuantity);
    return true;
}

const std::vector<Product>& Inventory::getProducts() const
{
    return products_;
}

bool Inventory::loadFromCsv(const std::string& filePath, std::string* error)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        if (error != nullptr)
        {
            *error = "Inventory file not found. Starting with empty inventory.";
        }
        return true;
    }

    products_.clear();

    std::string line;
    int lineNumber = 0;
    std::string parseErrors;

    while (std::getline(file, line))
    {
        ++lineNumber;
        if (trim(line).empty())
        {
            continue;
        }

        std::stringstream lineStream(line);
        std::string idString;
        std::string nameString;
        std::string priceString;
        std::string quantityString;

        if (!std::getline(lineStream, idString, ',') ||
            !std::getline(lineStream, nameString, ',') ||
            !std::getline(lineStream, priceString, ',') ||
            !std::getline(lineStream, quantityString))
        {
            parseErrors += "Line " + std::to_string(lineNumber) + " is malformed.\n";
            continue;
        }

        idString = trim(idString);
        nameString = trim(nameString);
        priceString = trim(priceString);
        quantityString = trim(quantityString);

        if ((lineNumber == 1) &&
            (idString == "id" || idString == "ID") &&
            (nameString == "name" || nameString == "Name"))
        {
            continue;
        }

        try
        {
            const int id = std::stoi(idString);
            const double price = std::stod(priceString);
            const int quantity = std::stoi(quantityString);

            Product product(id, nameString, price, quantity);
            if (nameString.empty() || price < 0.0 || quantity < 0)
            {
                parseErrors += "Line " + std::to_string(lineNumber) + " has invalid values.\n";
                continue;
            }

            std::string addError;
            if (!addProduct(product, &addError))
            {
                parseErrors += "Line " + std::to_string(lineNumber) + ": " + addError + "\n";
            }
        }
        catch (const std::exception&)
        {
            parseErrors += "Line " + std::to_string(lineNumber) + " has invalid number format.\n";
        }
    }

    if (!parseErrors.empty())
    {
        if (error != nullptr)
        {
            *error = "Some inventory rows were skipped:\n" + parseErrors;
        }
        return false;
    }

    return true;
}

bool Inventory::saveToCsv(const std::string& filePath, std::string* error) const
{
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open())
    {
        if (error != nullptr)
        {
            *error = "Unable to open inventory file for writing.";
        }
        return false;
    }

    file << "id,name,price,quantity\n";
    for (const auto& product : products_)
    {
        file << product.getId() << ","
             << product.getName() << ","
             << product.getPrice() << ","
             << product.getQuantity() << "\n";
    }

    return true;
}
