#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Product
{
public:
    int id;
    string name;
    float price;
    int quantity;

    // id is passed in already validated/unique by the caller
    void addProduct(int newId)
    {
        id = newId;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Product Name: ";
        getline(cin, name);

        while (true)
        {
            cout << "Enter Price: ";
            if (cin >> price && price >= 0)
                break;

            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid price! Please enter a positive number.\n";
        }

        while (true)
        {
            cout << "Enter Quantity: ";
            if (cin >> quantity && quantity >= 0)
                break;

            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid quantity! Please enter a positive number.\n";
        }
    }

    void displayProduct()
    {
        cout << "\nID       : " << id;
        cout << "\nName     : " << name;
        cout << "\nPrice    : " << price;
        cout << "\nQuantity : " << quantity << endl;
    }
};

// Returns true if the ID already exists in the inventory
bool idExists(Product p[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (p[i].id == id)
            return true;
    }
    return false;
}

int readValidId(const string &prompt)
{
    int id;
    cout << prompt;

    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number: ";
    }

    return id;
}

int main()
{
    Product p[100];
    int count = 0;
    int choice;
    int id;
    bool found;

    do
    {
        cout << "\n\n===== INVENTORY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Product";
        cout << "\n2. Display Products";
        cout << "\n3. Search Product";
        cout << "\n4. Update Product";
        cout << "\n5. Delete Product";
        cout << "\n6. Sell Product";
        cout << "\n7. Exit";

        cout << "\n\nEnter your choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number (1-7): ";
        }

        if (choice < 1 || choice > 7)
        {
            cout << "Invalid choice! Please enter a number from 1 to 7.";
            continue;
        }

        // Every operation below except Add/Display needs at least one product
        if (choice >= 3 && choice <= 6 && count == 0)
        {
            cout << "\nNo products available. Add a product first.";
            continue;
        }

        switch(choice)
        {
            case 1:
                if (count < 100)
                {
                    int newId = readValidId("\nEnter Product ID: ");

                    if (idExists(p, count, newId))
                    {
                        cout << "\nA product with this ID already exists! Use Update instead.";
                        break;
                    }

                    // Single source of truth for add-product input logic
                    p[count].addProduct(newId);
                    count++;
                    cout << "\nProduct added successfully!";
                }
                else
                {
                    cout << "\nInventory is full!";
                }
                break;

            case 2:
                if (count == 0)
                {
                    cout << "\nNo products available.";
                }
                else
                {
                    float totalValue = 0;

                    for (int i = 0; i < count; i++)
                    {
                        cout << "\n--- Product " << i + 1 << " ---";
                        p[i].displayProduct();
                        totalValue += p[i].price * p[i].quantity;

                        if (p[i].quantity <= 5)
                            cout << "*** LOW STOCK WARNING ***\n";
                    }

                    cout << "\nTotal inventory value: " << totalValue << endl;
                }
                break;

            case 3:
                id = readValidId("\nEnter Product ID: ");
                found = false;

                for (int i = 0; i < count; i++)
                {
                    if (p[i].id == id)
                    {
                        p[i].displayProduct();
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "\nProduct not found.";

                break;

            case 4:
                id = readValidId("\nEnter Product ID to update: ");
                found = false;

                for (int i = 0; i < count; i++)
                {
                    if (p[i].id == id)
                    {
                        while (true)
                        {
                            cout << "\nEnter New Price: ";

                            if (cin >> p[i].price && p[i].price >= 0)
                                break;

                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid price! Please enter a positive number.\n";
                        }

                        while (true)
                        {
                            cout << "Enter New Quantity: ";

                            if (cin >> p[i].quantity && p[i].quantity >= 0)
                                break;

                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid quantity! Please enter a positive number.\n";
                        }

                        cout << "\nProduct updated successfully!";
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "\nProduct not found.";

                break;

            case 5:
                id = readValidId("\nEnter Product ID to delete: ");
                found = false;

                for (int i = 0; i < count; i++)
                {
                    if (p[i].id == id)
                    {
                        for (int j = i; j < count - 1; j++)
                        {
                            p[j] = p[j + 1];
                        }

                        count--;
                        found = true;

                        cout << "\nProduct deleted successfully!";
                        break;
                    }
                }

                if (!found)
                    cout << "\nProduct not found.";

                break;

            case 6:
                id = readValidId("\nEnter Product ID to sell: ");
                found = false;

                for (int i = 0; i < count; i++)
                {
                    if (p[i].id == id)
                    {
                        int sellQuantity;

                        // Zero is rejected here now, not downstream
                        while (true)
                        {
                            cout << "Enter quantity to sell: ";

                            if (cin >> sellQuantity && sellQuantity > 0)
                                break;

                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input! Please enter a positive number greater than zero.\n";
                        }

                        if (sellQuantity <= p[i].quantity)
                        {
                            p[i].quantity -= sellQuantity;

                            cout << "\nSale successful!";
                            cout << "\nRemaining Stock: "
                                 << p[i].quantity;
                        }
                        else
                        {
                            cout << "\nNot enough stock!";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "\nProduct not found.";

                break;

            case 7:
                cout << "\nThank you for using the system!";
                break;
        }

    } while (choice != 7);

    return 0;
}
