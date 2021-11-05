//
// Created by samuel on 03/11/2021.
//

#include <gtest/gtest.h>

#include <memory>
#include "Property.hpp"

TEST(Property, GetValue)
{
    fox::Property<int> myProp;
    EXPECT_TRUE(myProp.get() == 0);
}

TEST(Property, SetValueByCopy)
{
    fox::Property<int> myProp;
    myProp.set(12);
    EXPECT_TRUE(myProp.get() == 12);
}

TEST(Property, SetValueByMove)
{
    fox::Property<std::unique_ptr<int>> myProp;
    myProp.set(std::make_unique<int>(12));
    EXPECT_TRUE(*myProp.get() == 12);
}

TEST(Property, ImplicitGetConversion)
{
    fox::Property<int> myProp;
    myProp.set(12);
    EXPECT_TRUE(myProp == 12);
}

TEST(Property, SetValueOpByCopy)
{
    fox::Property<int> myProp;
    myProp = 12;
    EXPECT_TRUE(myProp == 12);
}

TEST(Property, SetValueOpByMove)
{
    fox::Property<std::unique_ptr<int>> myProp;
    myProp = std::make_unique<int>(12);
    EXPECT_TRUE(*myProp.get() == 12);
}

TEST(Property, ConstructorPassValueByCopy)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp.get() == 45);
}

TEST(Property, ConstructorPassValueByMove)
{
    fox::Property<std::unique_ptr<int>> myProp(std::make_unique<int>(45));
    EXPECT_TRUE(*myProp.get() == 45);
}

TEST(Property, GetPointerValue)
{
    fox::Property<std::unique_ptr<int>> myProp(std::make_unique<int>(45));
    EXPECT_TRUE(*myProp == 45);
}

TEST(Property, GetValueFromPointer)
{
    struct TestData
    {
        TestData(int d) : data(d) {}
        int data;
    };
    fox::Property<std::unique_ptr<TestData>> myProp(std::make_unique<TestData>(45));
    EXPECT_TRUE(myProp->data == 45);
}

TEST(Property, ValueEqualComparator)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp == 45);
}

TEST(Property, ValueNotEqualComparator)
{
    fox::Property<int> myProp(0);
    EXPECT_TRUE(myProp != 45);
}

TEST(Property, ValueLessComparator)
{
    fox::Property<int> myProp(0);
    EXPECT_TRUE(myProp < 45);
}

TEST(Property, ValueLessEqualComparator)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp <= 45);
}

TEST(Property, ValueGreaterComparator)
{
    fox::Property<int> myProp(47);
    EXPECT_TRUE(myProp > 45);
}

TEST(Property, ValueGreaterEqualComparator)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp >= 45);
}

TEST(Property, ValueIncrement)
{
    fox::Property<int> myProp(45);
    myProp++;
    EXPECT_TRUE(myProp == 46);
}

TEST(Property, ValueDecrement)
{
    fox::Property<int> myProp(45);
    myProp--;
    EXPECT_TRUE(myProp == 44);
}

TEST(Property, ValueAddition)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp + 5 == 50);
}

TEST(Property, ValueSubstraction)
{
    fox::Property<int> myProp(45);
    EXPECT_TRUE(myProp - 5 == 40);
}

TEST(Property, ValueMultiplication)
{
    fox::Property<int> myProp(2);
    EXPECT_TRUE(myProp * 5 == 10);
}

TEST(Property, ValueDivision)
{
    fox::Property<int> myProp(10);
    EXPECT_TRUE(myProp / 2 == 5);
}

TEST(Property, ValueAdditionAssign)
{
    fox::Property<int> myProp(45);
    myProp += 5;
    EXPECT_TRUE(myProp == 50);
}

TEST(Property, ValueSubstractionAssign)
{
    fox::Property<int> myProp(45);
    myProp -= 5;
    EXPECT_TRUE(myProp == 40);
}

TEST(Property, ValueMutiplicationAssign)
{
    fox::Property<int> myProp(2);
    myProp *= 5;
    EXPECT_TRUE(myProp == 10);
}

TEST(Property, ValueDivisionAssign)
{
    fox::Property<int> myProp(10);
    myProp /= 2;
    EXPECT_TRUE(myProp == 5);
}

TEST(Property, Output)
{
    fox::Property<int> myProp(10);

    testing::internal::CaptureStdout();
    std::cout << "My Props: " << myProp;
    EXPECT_TRUE(testing::internal::GetCapturedStdout() == "My Props: 10");
}

TEST(Property, Input)
{
    fox::Property<int> myProp(10);

    std::istringstream str("10");
    str >> myProp;
    EXPECT_TRUE(myProp == 10);
}

TEST(Property, OnChangeEvent)
{
    int iRes = 0;
    fox::Property<int> myProp;
    myProp.OnChange().connect([&](int v) {
        iRes = v;
        std::cout << "OnValueChange Event triggered with value: " << v << std::endl;
    });
    myProp = 10;
    EXPECT_TRUE(iRes == 10);
}

TEST(Property, OnBeforeChangeEvent)
{
    int iRes = 0;
    fox::Property<int> myProp;
    myProp.OnBeforeChange().connect([&](int v) {
        iRes = v;
        std::cout << "OnBeforeValueChange Event triggered with value: " << v << std::endl;
    });

    // The old value of myProp should be 0
    EXPECT_TRUE(iRes == 0);

    // When we set the prop to 10, the old value still 0
    myProp = 10;
    EXPECT_TRUE(iRes == 0);

    // The old value of myProp should be 10
    // so when the signal will be send, iRes should be 10
    myProp = 20;
    EXPECT_TRUE(iRes == 10);
}
