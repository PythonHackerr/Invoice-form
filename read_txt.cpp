#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Invoice.cpp"
using namespace std;

class InvoiceCreation
{
private:
    vector<InvoiceForm> invoices = {};
    string file_name;

public:
    InvoiceCreation(string file_name)
    {
        this->file_name = file_name;
    };
    vector<string> split(string s, string delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    };
    vector<InvoiceForm> CreateInvoicesFromFile()
    {
        vector<InvoiceForm> invoices;
        ifstream file;
        file.open(file_name);
        if (file.is_open())
        {
            Address recieverAddress;
            Address senderAddress;
            Person reciever;
            Sender sender;
            Address place;
            vector<Product> products;

            int iterator = 0;
            string line;
            while (getline(file, line))
            {
                if (iterator == 0)
                {
                    reciever.SetName(line);
                }
                else if (iterator == 1)
                {
                    vector<string> words = split(line, " ");
                    recieverAddress.SetCountry(words[0]);
                    recieverAddress.SetCity(words[1]);
                    recieverAddress.SetStreet(words[2]);
                    recieverAddress.SetHouse(words[3]);
                    reciever.SetAddress(recieverAddress);
                }
                else if (iterator == 2)
                {
                    reciever.SetMail(line);
                }

                else if (iterator == 4)
                {
                    sender.SetName(line);
                }
                else if (iterator == 5)
                {
                    vector<string> words = split(line, " ");
                    senderAddress.SetCountry(words[0]);
                    senderAddress.SetCity(words[1]);
                    senderAddress.SetStreet(words[2]);
                    senderAddress.SetHouse(words[3]);
                    sender.SetAddress(senderAddress);
                }
                else if (iterator == 6)
                {
                    sender.SetMail(line);
                }
                else if (iterator == 8)
                {
                    vector<string> words = split(line, " ");
                    place.SetCountry(words[0]);
                    place.SetCity(words[1]);
                    place.SetStreet(words[2]);
                    place.SetHouse(words[3]);
                }
                else if (iterator >= 10 && line != "")
                {
                    // istringstream iss(line);
                    // vector<string> results((istream_iterator<WordDelimitedBy<','>>(iss)),
                    //                        istream_iterator<WordDelimitedBy<','>>());
                    Product product;
                    vector<string> words = split(line, ",");
                    product.SetName(words[0]);
                    product.SetManufacturer(words[1]);
                    product.SetPrice(stof(words[2]));
                    product.SetAmount(stoi(words[3]));
                    products.push_back(product);
                }
                else if (line == "--------------------------------")
                {
                    InvoiceForm invoice = InvoiceForm(reciever, sender, place, products);
                    iterator = -2;
                    invoices.push_back(invoice);
                }
                iterator += 1;
            }
            file.close();
        }
        else
        {
            throw "No such file!!!";
        }
        return invoices;
    };
};

// int main()
// {
//     InvoiceCreation IC("Invoices.txt");
//     vector<InvoiceForm> forms = IC.CreateInvoicesFromFile();
// };
