#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

class Address
{
private:
    string country;
    string city;
    string street;
    string house;

public:
    Address(string country = "", string city = "", string street = "", string house = "") // constructor
    {
        this->country = country;
        this->city = city;
        this->street = street;
        this->house = house;
    };
    string GetCountry()
    {
        return country;
    };
    string GetCity()
    {
        return city;
    };
    string GetStreet()
    {
        return street;
    };
    string GetHouse()
    {
        return house;
    };
    void SetCountry(string country)
    {
        this->country = country;
    };
    void SetCity(string city)
    {
        this->city = city;
    };
    void SetStreet(string street)
    {
        this->street = street;
    };
    void SetHouse(string house)
    {
        this->house = house;
    };
};

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    };
    int GetDay()
    {
        return day;
    };
    int GetMonth()
    {
        return month;
    };
    int GetYear()
    {
        return year;
    };
    void set_day(int day)
    {
        if ((day <= 0) || (day >= 32))
        {
            cerr << "Day is limited between 1 and 31, you entered: " << day << endl;
            return;
        }
        this->day = day;
    };
    void set_month(int month)
    {
        if ((month <= 0) || (month >= 13))
        {
            cerr << "Month is limited between 1 and 12, you entered: " << month << endl;
            return;
        }
        this->month = month;
    };
    void set_year(int year)
    {
        if ((year <= 1899) || (year >= 2018))
        {
            cerr << "year is limited between 1900 and 2017, you entered: " << year << endl;
            return;
        }
        this->year = year;
    };
};

class Product
{
private:
    string name;
    float price;
    int amount;
    string manufacturer;

public:
    Product(string name = "", string manufacturer = "", float price = 0, int amount = 0)
    {
        this->name = name;
        this->price = price;
        this->amount = amount;
        this->manufacturer = manufacturer;
    };

    void SetName(string name)
    {
        this->name = name;
    };
    void SetPrice(float price)
    {
        this->price = price;
    };
    void SetAmount(int amount)
    {
        this->amount = amount;
    };
    void SetManufacturer(string manufacturer)
    {
        this->manufacturer = manufacturer;
    };
    string GetName()
    {
        return name;
    };
    float GetPrice()
    {
        return price * amount;
    };
    int GetAmount()
    {
        return amount;
    };
    string GetManufacturer()
    {
        return manufacturer;
    };

    bool operator>(Product &p)
    {
        return GetPrice() > p.GetPrice();
    };
    bool operator>=(Product &p)
    {
        return GetPrice() >= p.GetPrice();
    };
    bool operator<(Product &p)
    {
        return GetPrice() < p.GetPrice();
    };
    bool operator<=(const Product &p) const
    {
        return price <= p.price;
    };
    bool operator==(const Product &p) const
    {
        return name == p.name && manufacturer == p.manufacturer;
    };
    bool operator!=(Product &p)
    {
        return !(GetName() == p.GetName() && GetManufacturer() == p.GetManufacturer());
    };
};

class Person
{
private:
    string name;
    Address address;
    string mail;

public:
    Person(string name = "", Address address = Address(), string mail = "")
    {
        this->name = name;
        this->address = address;
        this->mail = mail;
    };

    void SetName(string name)
    {
        this->name = name;
    };
    void SetMail(string mail)
    {
        this->mail = mail;
    };
    void SetAddress(Address address)
    {
        this->address = address;
    };
    string GetName()
    {
        return name;
    };
    Address GetAddress()
    {
        return address;
    };
    string GetMail()
    {
        return mail;
    };
};

class Sender : public Person
{
private:
    int numberNIP;

public:
    Sender(string name = "", Address address = Address(), string mail = "", int numberNIP = 0) : Person{name, address, mail}
    {
        this->numberNIP = numberNIP;
    };
    void SetNumberNIP(int numberNIP)
    {
        this->numberNIP = numberNIP;
    };
    int GetNumberNIP()
    {
        return numberNIP;
    };
};

class InvoiceForm
{
private:
    Person reciever;
    Sender sender;
    Address place;
    vector<Product> products;

public:
    InvoiceForm(Person reciever, Sender sender, Address place, vector<Product> products) // constructor
    {
        this->reciever = reciever;
        this->sender = sender;
        this->place = place;
        this->products = products;
    };

    void SetReciever(Person reciever)
    {
        this->reciever = reciever;
    };
    Person GetReciever()
    {
        return reciever;
    };

    void SetSender(Sender sender)
    {
        this->sender = sender;
    };
    Sender GetSender()
    {
        return sender;
    };

    void SetPlace(Address place)
    {
        this->place = place;
    };
    Address GetPlace()
    {
        return place;
    };

    void SetProducts(vector<Product> products)
    {
        this->products = products;
    };
    vector<Product> GetProducts()
    {
        return products;
    };
    float GetProductsPrice()
    {
        int price = 0;
        for (Product p : GetProducts())
        {
            price += p.GetPrice();
        }
        return price;
    };

    bool CheckIfProductExists(Product product)
    {
        for (int i = 0; i < GetProducts().size(); i++)
        {
            if (GetProducts()[i] == product)
            {
                return true;
            }
        }
        return false;
    };

    void RemoveProduct(Product product)
    {
        if (CheckIfProductExists(product) == false)
        {
            throw "No such product!";
            return;
        }
        vector<Product> new_products;
        for (int i = 0; i < GetProducts().size(); i++)
        {
            if (product != GetProducts()[i])
            {
                new_products.push_back(product);
            }
        }
        SetProducts(new_products);
    };

    void AddProduct(Product product)
    {
        if (CheckIfProductExists(product) == true)
        {
            throw "Product already exists!";
            return;
        }
        products.push_back(product);
    };

    void SortProductByName()
    {
        vector<Product> products = GetProducts();
        sort(products.begin(), products.end(), [](Product lhs, Product rhs)
             { return lhs.GetName() < rhs.GetName(); });
        SetProducts(products);
    };

    void SortProductByPrice()
    {
        vector<Product> products = GetProducts();
        sort(products.begin(), products.end(), [](Product lhs, Product rhs)
             { return lhs.GetPrice() < rhs.GetPrice(); });
        SetProducts(products);
    };

    vector<Product> GetProductsWithValueLower(float maxPrice)
    {
        vector<Product> new_products;
        for (int i = 0; i < GetProducts().size(); i++)
        {
            if (GetProducts()[i].GetPrice() <= maxPrice)
            {
                new_products.push_back(GetProducts()[i]);
            };
        };
        return new_products;
    };

    bool operator>(InvoiceForm &i)
    {
        float my_price = GetProductsPrice();
        float other_price = i.GetProductsPrice();
        return my_price > other_price;
    };
    bool operator>=(InvoiceForm &i)
    {
        float my_price = GetProductsPrice();
        float other_price = i.GetProductsPrice();
        return my_price >= other_price;
    };
    bool operator<(InvoiceForm &i)
    {
        float my_price = GetProductsPrice();
        float other_price = i.GetProductsPrice();
        return my_price < other_price;
    };
    bool operator<=(InvoiceForm &i)
    {
        float my_price = GetProductsPrice();
        float other_price = i.GetProductsPrice();
        return my_price <= other_price;
    };

    InvoiceForm operator+=(InvoiceForm &i)
    {
        if (i.GetSender().GetName() != GetSender().GetName() ||
            i.GetReciever().GetName() != GetReciever().GetName())
        {
            throw "Can't combine invoice forms!";
        };
        Person reciever = GetReciever();
        Sender sender = GetSender();
        Address place = GetPlace();
        vector<Product> new_products = GetProducts();
        vector<Product> other_products = i.GetProducts();
        for (int i = 0; i < other_products.size(); ++i)
        {
            for (int j = 0; j < new_products.size(); ++j)
            {
                if (new_products[j] == other_products[i])
                {
                    new_products[j].SetAmount(new_products[j].GetAmount() + other_products[i].GetAmount());
                    other_products.erase(remove(other_products.begin(), other_products.end(), other_products[i]), other_products.end());
                };
            };
        };
        for (int i = 0; i < other_products.size(); ++i)
        {
            new_products.push_back(other_products[i]);
        };

        SetProducts(new_products);
        return *this;
    };

    InvoiceForm operator+(InvoiceForm &i)
    {
        if (i.GetSender().GetName() != GetSender().GetName() ||
            i.GetReciever().GetName() != GetReciever().GetName())
        {
            throw "Can't combine invoice forms!";
        }
        Person reciever = GetReciever();
        Sender sender = GetSender();
        Address place = GetPlace();
        vector<Product> new_products = GetProducts();
        vector<Product> other_products = i.GetProducts();
        for (int i = 0; i < other_products.size(); ++i)
        {
            for (int j = 0; j < new_products.size(); ++j)
            {
                if (new_products[j] == other_products[i])
                {
                    new_products[j].SetAmount(new_products[j].GetAmount() + other_products[i].GetAmount());
                    other_products.erase(remove(other_products.begin(), other_products.end(), other_products[i]), other_products.end());
                };
            };
        };
        for (int i = 0; i < other_products.size(); ++i)
        {
            new_products.push_back(other_products[i]);
        };

        InvoiceForm new_invoice(GetReciever(), GetSender(), GetPlace(), new_products);
        return new_invoice;
    };
};