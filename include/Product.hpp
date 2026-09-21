#pragma once

#include <string>

class Product
{
public:
    Product() = default;
    Product(int id, std::string name, double price, int quantity);

    int getId() const;
    const std::string& getName() const;
    double getPrice() const;
    int getQuantity() const;

    bool setName(const std::string& name);
    bool setPrice(double price);
    bool setQuantity(int quantity);

private:
    int id_{0};
    std::string name_;
    double price_{0.0};
    int quantity_{0};
};
