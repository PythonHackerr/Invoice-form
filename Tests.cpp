#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
//#include "Invoice.cpp"
#include "read_txt.cpp"
using namespace std;

Product red_apple("Red apple", "Apple inc", 4, 500);          // 2000$
Product green_apple("Green apple", "Apple inc", 5, 1000);     // 5000$
Product yellow_apple("Yellow apple", "Apple inc", 4.5, 1500); // 6000$
Product golden_apple("Golden apple", "Notch", 1000, 50);      // 50000$
Product banana("Banana", "Banana maker", 9, 100);             // 900$
Product candy("Sweet candy!!!", "Candy factory", 20, 10000);  // 200000$
Product bread("Bread", "Bread factory!!!", 0.99, 10000);      // 9990$

Address sender_address("Poland", "Warsaw", "Akademicka", "5");
Sender sender("Bob", sender_address, "Bob@gmail.com", 63276);
Address reciever_address("USA", "NYC", "Central Park West", "15");
Person reciever("Misha", reciever_address, "Misha@ukr.net");
Address place("Ukraine!!!", "Kiyv", "Chreshatyk", "12");

vector<Product> products = {red_apple, green_apple, banana, candy};
InvoiceForm invoice(reciever, sender, place, products);

TEST_CASE("Testing invoice info")
{
    SECTION("invoice properties")
    {
        REQUIRE(invoice.GetProductsPrice() == 207900); // 900$ + 200000$ + 2000$ + 5000$
        REQUIRE(invoice.GetProducts()[1] == green_apple);
        vector<Product> low_cost_products = {red_apple, banana};
        REQUIRE(invoice.GetProductsWithValueLower(4000) == low_cost_products);
    }
}

TEST_CASE("Testing addition of invoices")
{
    InvoiceForm invoice_to_add = invoice;
    vector<Product> products_added = {bread, golden_apple, green_apple};
    InvoiceForm invoice_added(reciever, sender, place, products_added);
    SECTION("adding videos")
    {
        InvoiceForm new_invoice = invoice_to_add + invoice_added;
        REQUIRE(new_invoice.GetProducts().size() == 6); // 4+3-1
        invoice_to_add += invoice_added;
        REQUIRE(invoice_to_add.GetProducts().size() == 6);
        REQUIRE(new_invoice.GetProducts() == invoice_to_add.GetProducts());
    };
}

TEST_CASE("Comparing invoices")
{
    vector<Product> products2 = {candy, golden_apple};
    InvoiceForm invoice2(reciever, sender, place, products2);
    vector<Product> products3 = {bread};
    InvoiceForm invoice3(reciever, sender, place, products3);
    SECTION("comparison")
    {
        REQUIRE((invoice2 > invoice) == true);
        REQUIRE((invoice3 <= invoice) == true);
    }
}

TEST_CASE("Comparing products")
{
    Product banana2("Banana", "Banana maker", 90, 10); // 900$
    SECTION("comparison")
    {
        REQUIRE((red_apple >= banana) == true);
        REQUIRE((golden_apple < candy) == true);
        REQUIRE((banana == banana2) == true);
    }
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TEST_CASE("Testing sorting system of products")
{
    SECTION("sort by name")
    {
        vector<Product> unsorted_products = {red_apple, green_apple, candy, banana};
        vector<Product> sorted_products = {banana, green_apple, red_apple, candy};
        invoice.SetProducts(unsorted_products);
        invoice.SortProductByName();
        REQUIRE(invoice.GetProducts() == sorted_products);
    }
    SECTION("sort by price")
    {
        vector<Product> unsorted_products = {red_apple, green_apple, candy, banana};
        vector<Product> sorted_products = {candy, green_apple, red_apple, banana};
        vector<Product> sorted_products2 = {banana, red_apple, green_apple, candy};
        invoice.SetProducts(unsorted_products);
        invoice.SortProductByPrice();
        REQUIRE(invoice.GetProducts() == sorted_products2);
    }
}

TEST_CASE("Testing exceptions")
{
    Address sender_address("Poland", "Warsaw", "Akademicka", "5");
    Sender sender("Not Bob", sender_address, "Bob@gmail.com", 63276);
    Address reciever_address("USA", "NYC", "Central Park West", "15");
    Person reciever("Not Misha", reciever_address, "Misha@ukr.net");
    Address place("Not Ukraine!!!", "Not Kiyv", "Not Chreshatyk", "12");
    InvoiceForm invoice3(reciever, sender, place, products);
    SECTION("incorrect addition of invoices")
    {
        REQUIRE_THROWS(invoice3 + invoice, "Can't combine invoice forms!");
    }
    SECTION("removing product to invoice")
    {
        //! Already deleted
        REQUIRE_THROWS(invoice.RemoveProduct(golden_apple), "No such product!");
    }
    SECTION("adding product to invoice")
    {
        //! Already exists
        REQUIRE_THROWS(invoice.AddProduct(green_apple), "Product already exists!");
    }
}

TEST_CASE("Testing reading from txt file")
{
    InvoiceCreation IC("Invoices.txt");
    vector<InvoiceForm> forms = IC.CreateInvoicesFromFile();
    SECTION("aaa")
    {
        REQUIRE(forms.size() == 2);
        REQUIRE(forms[1].GetSender().GetName() == "Oggy");
        REQUIRE(forms[0].GetReciever().GetMail() == "Bob@gmail.com");
        REQUIRE(forms[0].GetProducts().size() == 2);
        REQUIRE(forms[1].GetProducts().size() == 4);
        REQUIRE(forms[1].GetProducts().size() == 4);
    }
}