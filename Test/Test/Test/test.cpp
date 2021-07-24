// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
	
    add_entries(1);
    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);

	// Assert that 5 elements existing within the collection vector.
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyMaxSizeIsGreaterThanOrEqualToEntrySize)
{
	// Collection will be empty on SetUp so no need to attempt to add 0.
	// Plus, Assert(count > 0) will prevent from moving further.
    ASSERT_GE(collection->max_size(), 0);

    // Add a single entry, then tear down before the next test.
    add_entries(1);
    ASSERT_GE(collection->max_size(), 1);
    TearDown();

    // Before next entry, setup collection to prevent null reference
    SetUp();

    // Add a five entries, then tear down before the next test.
    add_entries(5);
    ASSERT_GE(collection->max_size(), 5);
    TearDown();

    // Add ten entries, do not tear down because that will be handled as the test ends.
    SetUp();
    add_entries(10);
    ASSERT_GE(collection->max_size(), 10);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyCapacityIsGreaterThanOrEqualToEntrySize)
{
	// Assert that collection's capacity is greater than or equal to 0 immediately.
    ASSERT_GE(collection->capacity(), 0);

	// Add a single entry, assert capacity is greater than or equal to 1, finally tear down before next test.
    add_entries(1);
    ASSERT_GE(collection->capacity(), 1);
    TearDown();

	// Before next entry, setup collection to prevent null reference.
    SetUp();

	// Add five entries, assert capacity is greater than or equal to 5, finally tear down before next test.
    add_entries(5);
    ASSERT_GE(collection->capacity(), 5);
    TearDown();

	// Before next entry, setup collection to prevent null reference.
    SetUp();

	// Add ten entries, assert capacity is greater than or equal to 10, and do not tear down.
    add_entries(10);
    ASSERT_GE(collection->capacity(), 10);
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, VerifyResizeIncreasesCollection)
{
	
}

// TODO: Create a test to verify resizing decreases the collection

// TODO: Create a test to verify resizing decreases the collection to zero

// TODO: Create a test to verify clear erases the collection

// TODO: Create a test to verify erase(begin,end) erases the collection

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative