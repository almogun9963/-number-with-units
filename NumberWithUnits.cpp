#include <iostream>
#include "NumberWithUnits.hpp"
#include <fstream>
#include <map>
using namespace std;

const double ESPILON = 0.000001;
const int width = 200;

namespace ariel {
    
    static map<string, map<string, double> > map;
    NumberWithUnits::NumberWithUnits(double v, const string& unit){
        if(map.count(unit) == 0){
            throw invalid_argument{"invalid_argument"};
        }
        this->unit = unit;
        this->v = v;
    }
    void NumberWithUnits::read_units(ifstream& units_file) {
        string buff;
        string s1;
        string s2;
        double num1 = 0;
        double num2 = 0;
        while(units_file >> num1 >> s1 >> buff >> num2 >> s2) {
            map[s2][s1] = 1/num2;
            map[s1][s2] = num2;
            map[s2][s2] = 1;
            map[s1][s1] = 1;
            for (const auto &pair1 : map[s1]) {
                for (const auto &pair2 : map[s2]) {
                    map[pair1.first][pair2.first] = map[pair1.first][s1] * map[s1][s2] * map[s2][pair2.first];
                    map[pair2.first][pair1.first] = 1.0 / map[pair1.first][pair2.first];
                }
            }
        }
    }
    double converter(double t, const string& start, const string& end){
        if(start == end)
        {
            return t;
        }
        try
        {
            return t * map.at(start).at(end);
        }
        catch(const exception& e)
        {
            throw invalid_argument{"invalid_argument"};
        }
    }
    ostream& operator<<(ostream& out, const NumberWithUnits& t){
        out << t.v << "[" << t.unit << "]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& temp){
        double val;
        string buff;
        in >> val;
        getline(in, buff, ']');
        buff.erase(remove(buff.begin(), buff.end(), ' '), buff.end());
        buff = buff.substr(1, buff.size() - 1);
        temp = NumberWithUnits{val, buff};
        return in;
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& num2) {
        NumberWithUnits temp(this->v+converter(num2.v, num2.unit, this->unit), this->unit);
        return temp;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& num2) {
        NumberWithUnits temp(this->v-converter(num2.v, num2.unit, this->unit), this->unit);
        return temp;
    }
    NumberWithUnits NumberWithUnits::operator+() {
        NumberWithUnits temp(+this->v, this->unit);
        return temp;
    }
    NumberWithUnits NumberWithUnits::operator-() {
        NumberWithUnits temp(-this->v, this->unit);
        return temp;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& num2) {
        *this = *this + num2;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& num2) {
        *this = *this - num2;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator++() {
        ++(this->v);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) {
        return NumberWithUnits((this->v)++, this->unit);
    }
    NumberWithUnits& NumberWithUnits::operator--() {
        --(this->v);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) {
        return NumberWithUnits((this->v)--, this->unit);
    }
    NumberWithUnits operator*(const NumberWithUnits& n, const double num) {
        return NumberWithUnits(n.v*num, n.unit);
    }
    NumberWithUnits operator*(const double num, const NumberWithUnits& n) {
        return NumberWithUnits(n.v*num, n.unit);
    }
    NumberWithUnits& NumberWithUnits::operator*=(const double num) {
        this->v *= num;
        return *this;
    }
    int compare(const NumberWithUnits& num1, const NumberWithUnits& num2){
        
        double x = num1.v - converter(num2.v, num2.unit, num1.unit);
        int temp = 0;
        if(x > ESPILON){ temp = 1;}
        else if(-x > ESPILON) {temp = -1;}
        return temp;
    }
    bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) > 0;
    }
    bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) >= 0;
    }
    bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) < 0;
    }
    bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) <= 0;
    }
    bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) == 0;
    }
    bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2){
        return compare(num1, num2) != 0;
    }
}