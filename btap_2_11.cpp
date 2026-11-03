#include <bits/stdc++.h>
class sanpham
{
protected:
    std::string name;
    double price;

public:
    sanpham() = default;
    sanpham(std::string name, double price) : price{price}, name{std::move(name)} {}
    virtual void getdata()
    {
        std::cout << "Nhap ten: ";
        std::cin >> name;
        std::cout << "Nhap gia: ";
        std::cin >> price;
    }

    virtual void putdata() const
    {
        std::cout << "Ten: " << name << std::endl;
        std::cout << "Gia: " << price << std::endl;
    }
    virtual bool isOverSize() const = 0;
    virtual ~sanpham() = default;
};
// book
class book : public sanpham
{
    int pagenumber;

public:
    book() = default;
    book(std::string name, double price, int pagenumber)
        : sanpham{std::move(name), price}, pagenumber{pagenumber} {}
    void getdata() override
    {
        sanpham::getdata();
        std::cout << "Nhap so trang: ";
        std::cin >> pagenumber;
    }

    void putdata() const override
    {
        sanpham::putdata();
        std::cout << "So trang: " << pagenumber << std::endl;
    }
    // isoversize
    bool isOverSize() const override
    {
        if (pagenumber > 800)
            return 1;
        else
            return 0;
    }
    ~book() override;
};
// casset
class acassette : public sanpham
{
    float playingtime;

public:
    acassette() = default;
    acassette(std::string name, double price, float playingtime)
        : sanpham{std::move(name), price}, playingtime{playingtime} {}
    void getdata() override
    {
        sanpham::getdata();
        std::cout << "Nhap thoi luong: ";
        std::cin >> playingtime;
    }
    // putdata
    void putdata() const override
    {
        sanpham::putdata();
        std::cout << "Thoi luong: " << playingtime << std::endl;
    }
    // isoversize
    bool isOverSize() const override
    {
        if (playingtime > 90)
            return 1;
        else
            return 0;
    }
    ~acassette() override;
};

// main
int main()
{
    book b1{"Tam quoc", 100000, 500};
    book b2{"Tam quoc 2", 2000000, 1000};
    acassette ac1{"Playlist nhac buon", 10000, 67};
    acassette ac2{"Plalist houselak", 200000, 91};
    std::vector<sanpham *> ds;
    std::vector<sanpham *> ds_ovs;
    ds.push_back(&b1);
    ds.push_back(&b2);
    ds.push_back(&ac2);
    ds.push_back(&ac1);
}