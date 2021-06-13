//
// Created by Almog on 18/04/2021.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include "NumberWithUnits.hpp"
#include "doctest.h"
using namespace ariel;
using namespace std;


TEST_CASE("TESTS") {
    ifstream units_file{"units.txt"};

    //checking the regular conversions
    NumberWithUnits km{1, "km"};
    CHECK_EQ(km, NumberWithUnits{1000, "m"});
    NumberWithUnits m{2, "m"};
    CHECK_EQ(m, NumberWithUnits{200, "cm"});
    NumberWithUnits kg{3, "kg"};
    CHECK_EQ(kg, NumberWithUnits{3000, "g"});
    NumberWithUnits ton{4, "ton"};
    CHECK_EQ(ton, NumberWithUnits{4000, "kg"});
    NumberWithUnits hour{5, "hour"};
    CHECK_EQ(hour, NumberWithUnits{300, "min"});
    NumberWithUnits min{6, "min"};
    CHECK_EQ(min, NumberWithUnits{360, "sec"});
    NumberWithUnits usd{1, "USD"};
    CHECK_EQ(usd, NumberWithUnits{3.33, "ILS"});

    //checking the ++,+= operator
    CHECK_EQ(km++, NumberWithUnits{2000, "m"});
    CHECK_EQ(++m, NumberWithUnits{200, "cm"});
    km+=km;//2000m+2000m
    m+=m;//400cm+400cm
    CHECK_EQ(km, NumberWithUnits{4000, "m"});
    CHECK_EQ(m, NumberWithUnits{800, "cm"});

    //checking +,-,* operators
    CHECK_EQ(km+m, NumberWithUnits{4008, "m"});//4km+8m
    CHECK_EQ(ton-kg, NumberWithUnits{3996, "m"});//4ton-4kg
    CHECK_EQ(hour*2, NumberWithUnits{600, "min"});//5hours*2

    //checking the >,>=,<,<= operators
    CHECK_FALSE(m>km);
    CHECK_FALSE(m>=km);
    CHECK_FALSE(km<m);
    CHECK_FALSE(km<=m);
    CHECK_FALSE(m>km);
    CHECK_FALSE(m>=km);
    CHECK_FALSE(km<m);
    CHECK_FALSE(km<=m);
    CHECK_FALSE(m>km);
    CHECK_FALSE(m>=km);
    CHECK_FALSE(km<m);
    CHECK_FALSE(km<=m);
    CHECK_FALSE(m>km);
    CHECK_FALSE(m>=km);
    CHECK_FALSE(km<m);
    CHECK_FALSE(km<=m);
}
