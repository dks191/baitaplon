#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <limits>
#include <conio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
const std::string xanh = "\033[32m";
const std::string reset = "\033[0m";
const std::string vang = "\033[33m";
class product
{
protected:
    std::string name{""}, sku{""};
    double price{0.0};
    int stock{0};

public:
    product() = default;
    product(std::string n, std::string s, double p, int st)
        : sku{std::move(n)}, name{std::move(s)}, price{p}, stock{st} {}

    virtual void input()
    {
        std::cout << "Ma: ";
        std::getline(std::cin >> std::ws, sku);
        std::cout << "Ten: ";
        std::getline(std::cin, name);
        std::cout << "Gia: ";
        std::cin >> price;
        std::cout << "So luong: ";
        std::cin >> stock;
    }

    virtual void xuatthongtin()
    {
        std::cout << std::fixed << std::setprecision(0) << "[" << sku << "]" << " " << name << " " << price << "VND - " << stock << std::endl;
    }
    virtual ~product()
    {
        std::ofstream outfile("bai5output.txt", std::ios::out);
        if (outfile.is_open())
        {
            outfile << "da huy" << std::endl;
        }
        outfile.close();
    }
    std::string getsku()
    {
        return sku;
    }
};

class book : public product
{
    std::string author{""};

public:
    book() = default;
    book(std::string n, std::string s, double p, int st, std::string au)
        : product{n, s, p, st}, author{std::move(au)} {}
    void input() override
    {
        product::input();
        std::cout << "Ten tgia: ";
        std::getline(std::cin >> std::ws, author);
    }

    void xuatthongtin() override
    {
        product::xuatthongtin();
        std::cout << "tac gia: " << author << std::endl;
    }
};

class dientu : public product
{
    double phibaohanh{0.0};

public:
    dientu() = default;
    dientu(std::string n, std::string s, double p, int st, double fee)
        : product{n, s, p, st}, phibaohanh{fee} {}
    void input() override
    {
        product::input();
        std::cout << "phi bao hanh: ";
        std::cin >> phibaohanh;
    }

    void xuatthongtin() override
    {
        product::xuatthongtin();
        std::cout << std::fixed << std::setprecision(0) << "phi bao hanh: " << phibaohanh << std::endl;
    }
};
//
//
//
//
//
//
//
//
//
//
bool cmp(std::unique_ptr<product> &a, std::unique_ptr<product> &b)
{
    return a->getsku() < b->getsku();
}
void inmenu(std::vector<std::string> &menu, int select)
{
    system("cls");
    for (int i = 0; i < menu.size(); i++)
    {
        if (select == i)
        {
            std::cout << xanh << menu[i] << reset << std::endl;
        }

        else
            std::cout << menu[i] << std::endl;
    }
}

int getchoice(std::vector<std::string> &menu)
{
    int select = 0;
    bool open = 1;
    int key;
    while (open)
    {

        inmenu(menu, select);
        while (key != 13)
        {
            inmenu(menu, select);
            key = _getch();
            if (key == 224)
            {
                key = _getch();
                if (key == 72)
                {
                    if (select <= 0)
                        continue;
                    else
                        select--;
                }

                else if (key == 80)
                {
                    if (select >= menu.size() - 1)
                        continue;
                    else
                        select++;
                }
                else if (key == 13)
                    break;
            }
            else
                continue;
        }
        open = 0;
    }
    return select;
}

void docfile(std::vector<std::unique_ptr<product>> &ds)
{
    std::ifstream infile("bai5input.csv", std::ios::in);
    std::string line;
    std::string linehientai;
    while (std::getline(infile, line))
    {
        std::unique_ptr<product> p;

        if (line == "dientu" || line == "book")
        {
            linehientai = line;
            continue;
        }
        if (linehientai == "book" || linehientai == "dientu")
        {
            std::stringstream ss(line);
            std::string sku, name, price, stock;

            std::getline(ss, sku, ',');
            std::getline(ss, name, ',');
            std::getline(ss, price, ',');
            std::getline(ss, stock, ',');
            if (linehientai == "book")
            {
                std::string author;
                std::getline(ss, author, ',');

                p = std::make_unique<book>(sku, name, std::stod(price), std::stoi(stock), author);
            }
            else if (linehientai == "dientu")
            {
                std::string fee;
                std::getline(ss, fee, ',');

                p = std::make_unique<dientu>(sku, name, std::stod(price), std::stoi(stock), std::stod(fee));
            }
            ds.push_back(std::move(p));
        }
    }
    infile.close();
}

void nhap(std::vector<std::unique_ptr<product>> &ds)
{

    std::vector<std::string> menu = {"1.Book", "2.Dien tu", "3.Cap nhat tu file", "4.quay lai"};
    std::unique_ptr<product> p = nullptr;
    int select = getchoice(menu);
    if (select == 0)
    {
        system("cls");
        std::cout << "Nhap vao thong tin" << std::endl;
        p = std::make_unique<book>();
        p->input();
        ds.push_back(std::move(p));
    }
    else if (select == 1)
    {
        system("cls");
        std::cout << "Nhap vao thong tin" << std::endl;
        p = std::make_unique<dientu>();
        p->input();
        ds.push_back(std::move(p));
    }
    else if (select == 2)
    {
        docfile(ds);
    }
    else
        return;
    std::sort(ds.begin(), ds.end(), cmp);
}
int main()
{
    std::vector<std::string> menu = {"1. Them", "2. Xuat tt", "3. Sua"};
    std::vector<std::unique_ptr<product>> ds;
    bool open = 1;
    int select;
    while (open)
    {
        select = getchoice(menu);
        if (select == 0)
        {
            nhap(ds);
        }
        else if (select == 1)
        {
            system("cls");
            for (auto const &i : ds)
            {
                i->xuatthongtin();
                std::cout << std::endl;
            }
            _getch();
        }
        else if (select == 2)
        {
        }
        else
        {
            break;
        }
    }

    system("pause");
}