#include <string>
#include <map>
#include <iostream>
using  namespace std;
namespace ariel {
    class NumberWithUnits{

    private:
        double v;
        string unit;

    public:
        NumberWithUnits(double v, const std::string& unit);
        static void read_units(std::ifstream& units_file);
        friend int compare(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend std::istream& operator>>(std::istream& in, NumberWithUnits& t);
        friend std::ostream& operator<<(std::ostream& out, const NumberWithUnits& t);
        NumberWithUnits operator+(const NumberWithUnits& num2);
        NumberWithUnits operator-(const NumberWithUnits& num2);
        NumberWithUnits operator+();
        NumberWithUnits operator-();
        NumberWithUnits& operator-=(const NumberWithUnits& num2);
        NumberWithUnits& operator+=(const NumberWithUnits& num2);
        NumberWithUnits& operator*=(const double num);
        NumberWithUnits& operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);
        NumberWithUnits& operator++();
        friend NumberWithUnits operator*(const NumberWithUnits& n, const double num);
        friend NumberWithUnits operator*(const double num, const NumberWithUnits& n);
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& num2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& num2);
    };
}