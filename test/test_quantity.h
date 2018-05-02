//
//  test_quantity.h
//  krypton
//
//  Created by Jack Zou on 2018/3/8.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef test_quantity_h
#define test_quantity_h

#include <cmath>
#include <gtest/gtest.h>
#include "core/dimension.hpp"
#include "core/quantity.hpp"
#include "length.hpp"
#include "velocity.hpp"
#include "time.hpp"

void quantity_static_check() {

    // this should no compile, initializing a quantity<int> with a
    // floating point number is not allowed
    //kr::quantity<int, kr::length> q1(1.0);
    
    // these should compile
    kr::quantity<float, kr::length> q2(2);
    kr::quantity<float, kr::length> q3(3.0);
    
    using Q1 = kr::quantity<int, kr::length, std::ratio<100, 1>>;
    using Q2 = kr::quantity<double, kr::length, std::ratio<1000, 1>>;
    using common_type = kr::common_type<Q1, Q2>::type;
    static_assert(kr::is_quantity<common_type>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type = common_type::ratio_type;
    static_assert(ratio_type::num == 100, "there are errors in kr::common_type implementation");
    static_assert(ratio_type::den == 1, "there are errors in kr::common_type implementation");
    
    using Q3 = kr::quantity<int, kr::length, std::ratio<100, 33>>;
    using Q4 = kr::quantity<double, kr::length, std::ratio<100, 99>>;
    using common_type_2 = kr::common_type<Q3, Q4>::type;
    static_assert(kr::is_quantity<common_type_2>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type_2 = common_type_2::ratio_type;
    static_assert(ratio_type_2::num == 100, "there are errors in kr::common_type implementation");
    static_assert(ratio_type_2::den == 99, "there are errors in kr::common_type implementation");
    
    using Q5 = kr::quantity<int, kr::length, std::ratio<100, 66>>;
    using Q6 = kr::quantity<double, kr::length, std::ratio<100, 99>>;
    using common_type_3 = kr::common_type<Q5, Q6>::type;
    static_assert(kr::is_quantity<common_type_3>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type_3 = common_type_3::ratio_type;
    static_assert(ratio_type_3::num == 50, "there are errors in kr::common_type implementation");
    static_assert(ratio_type_3::den == 99, "there are errors in kr::common_type implementation");
    
    using Q7 = kr::quantity<int, kr::length, std::ratio<100, 66>, kr::metric_system<kr::length>>;
    using Q8 = kr::quantity<int, kr::length, std::ratio<100, 99>, kr::british_system<kr::length>>;
    using common_type_4 = kr::common_type<Q7, Q8>::type;
}

TEST(test_quantity, test_quantity_cast) {
    using from_type = kr::quantity<int, kr::length, std::ratio<1>>;
    using to_type = kr::quantity<double, kr::length, std::ratio<1>>;
    
    static_assert(kr::is_quantity<to_type>::value, "type is not quantity");
    static_assert(kr::equals<from_type::dim_type, to_type::dim_type>::value, "dimension not equal");
    
    from_type from{1};
    to_type to = kr::quantity_cast<to_type>(from);
    EXPECT_EQ(to.value, 1.0);

    // convert feet to meter
    kr::meter<double> m1{1.0};
    kr::foot<double> f1 = kr::quantity_cast<kr::foot<double>>(m1);
    double diff = std::abs(f1.value - 3.28);
    EXPECT_LE(diff,0.01);
    
    // convert meter to feet
    kr::foot<double> f2{1.0};
    kr::meter<double> m2 = kr::quantity_cast<kr::meter<double>>(f2);
    diff = std::abs(m2.value - 1.0 / 3.28);
    EXPECT_LE(diff, 0.01);
    
    // convert meter to kilometer
    kr::meter<double> m3{1.0};
    kr::kilometer<double> km3 = kr::quantity_cast<kr::kilometer<double>>(m3);
    EXPECT_EQ(km3.value, 0.001);
    
    kr::meter<int> m4{1};
    kr::kilometer<int> km4 = kr::quantity_cast<kr::kilometer<int>>(m4);
    EXPECT_EQ(km4.value, 0);
    
    // convert kilometer to meter
    kr::kilometer<int> km5{1};
    kr::meter<int> m5 = kr::quantity_cast<kr::meter<int>>(km5);
    EXPECT_EQ(m5.value, 1000);
    
    // convert feet to kilometer
    kr::foot<double> f6{1.0};
    kr::kilometer<double> km6 = kr::quantity_cast<kr::kilometer<double>>(f6);
    diff = std::abs(km6.value - 0.0003048);
    EXPECT_LE(diff, 0.00000001);
    
    // convert kilometer to feet
    kr::kilometer<double> km7{1.0};
    kr::foot<double> f7 = kr::quantity_cast<kr::foot<double>>(km7);
    diff = std::abs(f7.value - 3280.8399);
    EXPECT_LE(diff, 0.00001);
    
    // convert kilometer to centimeter
    kr::kilometer<int> km8{1};
    kr::centimeter<int> cm8 = kr::quantity_cast<kr::centimeter<int>>(km8);
    EXPECT_EQ(cm8.value, 100000);
    
    // convert centimeter to kilometer
    kr::centimeter<double> cm9{10000.0};
    kr::kilometer<double> km9 = kr::quantity_cast<kr::kilometer<double>>(cm9);
    diff = std::abs(km9.value - 0.1);
    EXPECT_EQ(diff, 0.0);
    
    // convert kilometer to inch
    kr::kilometer<double> km10{1.0};
    kr::inch<double> inch9 = kr::quantity_cast<kr::inch<double>>(km10);
    diff = std::abs(inch9.value - 39370.0788);
    EXPECT_LE(diff, 0.00001);
    
    // convert inch to kilometer
    kr::inch<double> inch10{10000.0};
    kr::kilometer<double> km11 = kr::quantity_cast<kr::kilometer<double>>(inch10);
    diff = std::abs(km11.value - 0.254);
    EXPECT_LE(diff, 0.0001);
}


TEST(test_quantity, test_construct) {
    kr::quantity<int, kr::length> q1(3);
    EXPECT_EQ(q1.value, 3);

    // this should not compile
    //kr::quantity<int, kr::mass> q2(3.0);
    //EXPECT_EQ(q1.value, 3.0);

    kr::quantity<double, kr::length> q3(3);
    EXPECT_EQ(q3.value, 3.0);

    // construct kilometer from meter
    kr::meter<double> m4{1000.0};
    kr::kilometer<double> km4(m4);
    EXPECT_EQ(km4.value, 1.0);

    // construct meter from kilometer
    kr::kilometer<double> km5{1.0};
    kr::meter<double> m5 = km5;
    EXPECT_EQ(m5.value, 1000.0);

    // construct feet from meter
    kr::meter<double> m6{1.0};
    kr::foot<double> foot6{m6};
    double diff = std::abs(foot6.value - 3.2808399);
    EXPECT_LE(diff, 0.00000001);

    // construct meeter from feet
    kr::foot<double> foot7{1.0};
    kr::meter<double> m7 = foot7;
    diff = std::abs(m7.value - 0.3048);
    EXPECT_LE(diff, 0.0001);

    // this should not compile
    //kr::meter<double> m8{1.0};
    //kr::second<double> sec9{m8};
}

TEST(test_quantity, test_add) {
    kr::meter<int> m1{ 1 };
    kr::meter<int> m2{ 2 };
    kr::meter<int> m3 = m1.add(m2);
    EXPECT_EQ(m3.value, 3);

    kr::kilometer<int> m4{ 1 };
    kr::meter<int> m5 = m1.add(m4);
    EXPECT_EQ(m5.value, 1001);

    kr::centimeter<double> cm5{ 1.0 };
    kr::kilometer<double> km6{ 1.0 };
    EXPECT_EQ(cm5.add(km6).value, 100001);

    kr::meter<double> m7{ 1.0 };
    kr::foot<double> foot8{ 1.0 };
    double diff = std::abs(m7.add(foot8).value - 1.3048);
    EXPECT_LE(diff, 0.00001);

    kr::centimeter<double> cm8{ 1.0 };
    kr::inch<double> inch9{ 1.0 };
    diff = std::abs(inch9.add(cm8).value - 1.3937);
    EXPECT_LE(diff, 0.00001);

    // this should not compile
    //kr::meter<int> m10{ 10 };
    //kr::second<int> s10{ 10 };
    //m10.add(s10);
}

TEST(test_quantity, test_operator_add) {
	kr::meter<int> m1{ 1 };
	kr::meter<double> m2{ 2.0 };
	auto m3 = m1 + m2;
	EXPECT_EQ(m3.value, 3.0);

    kr::kilometer<double> m4{ 1.0 };
    auto m5 = m1 + m4;
    EXPECT_EQ(m5.value, 1001);
    auto m6 = m4 + m1;
    EXPECT_EQ(m6.value, 1.001);

    kr::meter<double> m7{ 1.0 };
    kr::foot<double> foot8{ 1.0 };
    auto res = m7 + foot8;
    double diff = std::abs(res.value - 1.3048);
    EXPECT_LE(diff, 0.00001);
    auto res2 = foot8 + m7;
    diff = std::abs(res2.value - 4.2808);
    EXPECT_LE(diff, 0.0001);

	// this should not compile
    //3 + m2;
    //m2 + 3
}

TEST(test_quantity, test_operator_sub) {
    kr::meter<int> m1{ 1 };
    kr::meter<double> m2{ 2.0 };
    auto m3 = m1 - m2;
    EXPECT_EQ(m3.value, -1.0);
    
    kr::kilometer<double> m4{ 1.0 };
    auto m5 = m1 - m4;
    EXPECT_EQ(m5.value, -999.0);
    auto m6 = m4 - m1;
    EXPECT_EQ(m6.value, 0.999);

    kr::meter<double> m7{ 1.0 };
    kr::foot<double> foot8{ 1.0 };
    auto res = m7 - foot8;
    double diff = std::abs(res.value - 0.6952);
    EXPECT_LE(diff, 0.00001);
    auto res2 = foot8 - m7;
    diff = std::abs(res2.value + 2.2808);
    EXPECT_LE(diff, 0.0001);
}

//TEST(test_quantity, test_normalized) {
//    kr::kilometer<int> km1{ 1 };
//    using normal_type = kr::kilometer<int>::normalized_type;
//    normal_type normal = km1.normalized();
//    EXPECT_EQ(normal.value, 1000);
//}

TEST(test_quantity, test_multiplication) {
    kr::m_per_s<double> v1{5.0};
    kr::second<int> s1{1};

    // this should not compile
    //kr::kilogram<double> kg1 = kr::quantity_multiply(v1, s1);

    kr::meter<double> m1 = kr::quantity_multiply(v1, s1);
    kr::foot<double> f1 = kr::quantity_multiply(v1, s1);
    EXPECT_EQ(m1.value, 5.0);
    double diff = std::abs(f1.value - 16.4042);
    EXPECT_LE(diff, 0.0001);
    
    kr::meter<double> m11{v1.multiply(s1)};
    EXPECT_EQ(m11.value, 5.0);
    
    kr::foot<double> f11{v1.multiply(s1)};
    diff = std::abs(f11.value - 16.4042);
    EXPECT_LE(diff, 0.0001);

    kr::kilometer<double> km1 = kr::quantity_multiply(v1, s1);
    EXPECT_EQ(km1.value, 0.005);

    kr::km_per_h<double> v2{3.6};
    kr::meter<double> m2 = kr::quantity_multiply(v2, s1);
    kr::kilometer<double> km2 = kr::quantity_multiply(v2, s1);
    EXPECT_EQ(m2.value, 1.0);
    EXPECT_EQ(km2.value, 0.001);

    kr::hour<int> h3{1};
    kr::meter<double> m3 = kr::quantity_multiply(v2, h3);
    kr::kilometer<double> km3 = kr::quantity_multiply(v2, h3);
    EXPECT_EQ(m3.value, 3600.0);
    EXPECT_EQ(km3.value, 3.6);

    //kr::ml_per_h<double> v4{ 1.0 };
    //kr::hour<double> h4{ 1.0 };
    //kr::mile<double> ml4 = kr::quantity_multiply(v4, h4);
    //EXPECT_EQ(ml4.value, 1.0);
    //kr::second<double> sec4{ 1.0 };
    //kr::feet<double> ft4 = kr::quantity_multiply(v4, sec4);
    //diff = std::abs(ft4.value - 1.47);
    //EXPECT_LT(diff, 0.01);
}


TEST(test_quantity, test_division) {
    kr::meter<double> m1{1.0};
    kr::second<double> sec1{1.0};
    kr::m_per_s<double> v1 = kr::quantity_divide(m1, sec1);
    EXPECT_EQ(v1.value, 1.0);
    
    kr::m_per_s<double> v11{m1.divide(sec1)};
    EXPECT_EQ(v11.value, 1.0);
    
    kr::f_per_s<double> bv1 = kr::quantity_divide(m1, sec1);
    double diff = std::abs(bv1.value - 3.2808);
    EXPECT_LE(diff, 0.0001);

    // this should not compile
    //kr::kilogram<double> kg1 = kr::quantity_divide(v1, sec1);

    kr::hour<int> h2{1};
    kr::kilometer<double> km2{1.0};
    kr::km_per_h<double> v2 = kr::quantity_divide(km2, h2);
    kr::m_per_s<double> v21 = kr::quantity_divide(km2, h2);
    diff = std::abs(v21.value - 0.28);
    EXPECT_EQ(v2.value, 1.0);
    EXPECT_LE(diff, 0.01);
}

TEST(test_quantity, test_operator_multiplication) {
	kr::m_per_s<double> v1{ 5.0 };
	kr::second<int> s1{ 1 };

    auto hs1 = s1 * 0.5;
    EXPECT_EQ(hs1.value, 0.5);
    auto hs2 = 0.5 * s1;
    EXPECT_EQ(hs2.value, 0.5);

	kr::meter<double> m1 = v1 * s1;
	EXPECT_EQ(m1.value, 5.0);
	kr::foot<double> f1 = v1 * s1;
	double diff = std::abs(f1.value - 16.4042);
	EXPECT_LE(diff, 0.0001);

	kr::meter<double> m11{ s1 * v1 };
	EXPECT_EQ(m11.value, 5.0);

	kr::foot<double> f11{ v1 * s1 };
	diff = std::abs(f11.value - 16.4042);
	EXPECT_LE(diff, 0.0001);

	kr::kilometer<double> km1 = s1 * v1;
	EXPECT_EQ(km1.value, 0.005);

	kr::km_per_h<double> v2{ 3.6 };
	kr::meter<double> m2 = v2 * s1;
	kr::kilometer<double> km2 = s1 * v2;
	EXPECT_EQ(m2.value, 1.0);
	EXPECT_EQ(km2.value, 0.001);

	kr::hour<int> h3{ 1 };
	kr::meter<double> m3 = v2 * h3;
	kr::kilometer<double> km3 = v2 * h3;
	EXPECT_EQ(m3.value, 3600.0);
	EXPECT_EQ(km3.value, 3.6);
}

TEST(test_quantity, test_operator_division) {
	kr::meter<double> m1{ 1.0 };
	kr::second<double> sec1{ 1.0 };
	kr::m_per_s<double> v1 = m1 / sec1;
	EXPECT_EQ(v1.value, 1.0);

	kr::meter<double> m11 = m1 / 2;
	EXPECT_EQ(m11.value, 0.5);

	kr::m_per_s<double> v11{ m1 / sec1 };
	EXPECT_EQ(v11.value, 1.0);

	kr::f_per_s<double> bv1 = m1 / sec1;
	double diff = std::abs(bv1.value - 3.2808);
	EXPECT_LE(diff, 0.0001);

	kr::hour<int> h2{ 1 };
	kr::kilometer<double> km2{ 1.0 };
	kr::km_per_h<double> v2 = km2 / h2;
	kr::m_per_s<double> v21 = km2 / h2;
	diff = std::abs(v21.value - 0.28);
	EXPECT_EQ(v2.value, 1.0);
	EXPECT_LE(diff, 0.01);
}

#endif /* test_quantity_h */
