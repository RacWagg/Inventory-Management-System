#pragma once

#include "Product.hpp"

#include <string>
#include <vector>

class Inventory
{
public:
    bool addProduct(const Product& product, std::string* error = nullptr);
    Product* findProductById(int id);
    const Product* findProductById(int id) const;
    bool updateProduct(int id, double newPrice, int newQuantity, std::string* error = nullptr);
    bool deleteProduct(int id, std::string* error = nullptr);
    bool sellProduct(int id, int sellQuantity, std::string* error = nullptr);

    const std::vector<Product>& getProducts() const;

    bool loadFromCsv(const std::string& filePath, std::string* error = nullptr);
    bool saveToCsv(const std::string& filePath, std::string* error = nullptr) const;

private:
    std::vector<Product> products_;
};
