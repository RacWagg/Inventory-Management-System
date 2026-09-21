#include "Product.hpp"

Product::Product(int id, std::string name, double price, int quantity)
    : id_(id), name_(std::move(name))
{
    setPrice(price);
    setQuantity(quantity);
}

int Product::getId() const
{
    return id_;
}

const std::string& Product::getName() const
{
    return name_;
}

double Product::getPrice() const
{
    return price_;
}

int Product::getQuantity() const
{
    return quantity_;
}

bool Product::setName(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    name_ = name;
    return true;
}

bool Product::setPrice(double price)
{
    if (price < 0.0)
    {
        return false;
    }

    price_ = price;
    return true;
}

bool Product::setQuantity(int quantity)
{
    if (quantity < 0)
    {
        return false;
    }

    quantity_ = quantity;
    return true;
}
