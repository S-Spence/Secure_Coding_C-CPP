// Author: Sarah Spence
// Date: 07/25/2021
// Title: CS 405 Unit Testing Milestone

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
 * Uncomment this test to see a failure in the test explorer
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}*/

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{

    /* Using assert here because the test is to verify that the program can add to an empty vector. If the vector is not empty,
     * the test should not continue because it will not verify the proper test case.
     */
    // is the collection empty?
    ASSERT_TRUE(collection->empty()) << "The starting vector must be empty.";
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0) << "The size of the starting vector must be 0.";

    // Add entries if the above assertion tests passed
    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty()) << "The collection is still empty.";
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1) << "The value was not added to the collection.";
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    /* Get the starting size since this test is to verify that five values are added to a vector. Determining the starting size will 
     * ensure the test works for empty vectors and non-emoty vectors*/
    unsigned long long int starting_size = collection->size();
    add_entries(5);
    // Using assert because this is the end of this test case and the test will not continue after this line. 
    ASSERT_EQ(collection->size() - 5, starting_size) << "Something went wrong, five values were not added to the collection.";
}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifySizeDoesNotExceedMaxSize)
{
    // Ensure the vector is empty to start and of size zero using assertions
    ASSERT_TRUE(collection->empty()) << "The collection was not empty to start.";
    ASSERT_EQ(collection->size(), 0) << "The collection did no start at size 0.";
    // Check that the vector at size 0 does not exceed the max size. Using expect so test execution continues. 
    EXPECT_GE(collection->max_size(), collection->size()) << "The collection exceeded the manximum size at 0 entries.";

    // Add one entry to the vector
    add_entries(1);
    /* Assert that the vector contains 1 entries. If it doesn't, end the test because something went wrong and entries of 1, 5, and 10 will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 1) << "The collection does not contain 1 entry as expected.";
    // Check that the collection size does not exceed max size using expect so execution continues. 
    EXPECT_GE(collection->max_size(), collection->size()) << "The collection exceeded the maximum size at 1 entry.";

    // Add four entries for a total of 5 entries.
    add_entries(4);
    /* Assert that the vector contains 5 entries. If it doesn't, end the test because something went wrong and entries of 5 and 10 will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 5) << "The collection does not contain 5 entries as expected.";
    /* Verify that max size is greater than or equal to size for 5 entries. Using expect here because the test should continue to test
     * 10 entries added after this line.
     */
    EXPECT_GE(collection->max_size(), collection->size()) << "The collection exceeded the maximum size at 5 entries." ;

    // Add five entries for a total of 10 entries.
    add_entries(5);
    /* Assert that the vector contains 10 entries. If it doesn't, end the test because something went wrong 10 entries will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 10) << "The collection does not contain 10 entries as expected";
    // Verify that max size is greater than or equal to size for 10 entries. Using assert here because this is the end of this test case
    ASSERT_GE(collection->max_size(), collection->size()) << "The collection exceeded the maximum size at 10 entries.";
}

// Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyCapacityIsGreaterThanOrEqualToSize)
{
    // Ensure the vector is empty to start and of size 0 using assertions
    ASSERT_TRUE(collection->empty()) << "The collection was not empty to start";
    ASSERT_EQ(collection->size(), 0) << "The collection did not start at size zero";
    // Check that the vector's capacity is greater than or equal to it's size at 0 entries.  
    EXPECT_GE(collection->capacity(), collection->size()) << "The collection's capacity was not greater than or equal to its size at 0 entries";

    // Add one entry to the vector
    add_entries(1);
    /* Assert that the vector contains 1 entries. If it doesn't, end the test because something went wrong and entries of 1, 5, and 10 will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 1) << "The collection did not contain 1 entry as expected";
    // Verify that capacity is greater than or equal to size for 1 entries. Using expect so test execution continues. 
    EXPECT_GE(collection->capacity(), collection->size()) << "The collection's capacity was not greater than or equal to its size at 1 entry";

    // Add four entries for a total of 5 entries.
    add_entries(4);
    /* Assert that the vector contains 5 entries. If it doesn't, end the test because something went wrong and entries of 5 and 10 will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 5) << "The collection did not contain 5 entries as expected.";
    // Verify that capcity is greater than or equal to size for 5 entries. Using expect so test execution continues.
    EXPECT_GE(collection->capacity(), collection->size()) << "The collection's capacity was not greater than or equal to its size at 5 entries";

    // Add five entries for a total of 10 entries.
    add_entries(5);
    /* Assert that the vector contains 10 entries. If it doesn't, end the test because something went wrong and 10 entries will
     * not be tested as expected.
     */
    ASSERT_EQ(collection->size(), 10) << "The vector did not contain 10 entries as expected.";
    // Verify that capacity is greater than or equal to size for 10 entries. Using assert here because this is the end of this test case
    ASSERT_GE(collection->capacity(), collection->size()) << "The collection's capacity was not greater than or equal to it's size at 10 entries.";
}

// Create a test to verify resizing increases the collection
TEST_F(CollectionTest, VerifySizeIncreasesWhenResizing)
{
    // Get the starting size before resizing the vector
    unsigned long long int starting_size = collection->size();
    // Increase the vector's size by one
    collection->resize(starting_size + 1);
    // Using assert because this is the end of this test case
    ASSERT_GT(collection->size(), starting_size) << "Resizing did not increase the collection's size.";
}

// Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, VerifySizeDecreasesWhenResizing)
{
    // Add some entries to the vector first so it's size is reducable
    add_entries(3);
    // Assert that the vector is not empty to start because the test will not be able to reduce the vector if it is already empty
    ASSERT_NE(collection->size(), 0) << "The collection was empty to start so it's size cannot be reduced.";
    // If the vector is not empty, get its start size before decreasing
    unsigned long long int starting_size = collection->size();
    // Decrease the vector's size by one
    collection->resize(starting_size - 1);
    // Using assert less than because this is the end of this test case
    ASSERT_LT(collection->size(), starting_size) << "Resizing did not reduce the collection's size.";
}

// Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, VerifySizeDecreasesToZeroWhenResizing)
{
    // Add some entries to the vector first so it's size is reducable
    add_entries(3);
    // Assert that the vector is not empty to start because the test will not be able to reduce the vector if it is already empty
    ASSERT_NE(collection->size(), 0) << "The collection was empty to start and cannot be reduced.";
    // Decrease the vector's size to zero
    collection->resize(0);
    // Using assert equals because this is the end of this test case
    ASSERT_EQ(collection->size(), 0) << "The vector's size did not reduce to zero by resizing.";
}

// Create a test to verify clear erases the collection
TEST_F(CollectionTest, VerifyClearErasesCollection)
{
    // Add some entries to the vector first so there are some entries to clear
    add_entries(3);
    // Assert that the vector is not empty to start so the test has some elements to clear
    ASSERT_NE(collection->size(), 0) << "The collection was empty to start.";
    // Decrease the vector's size to zero using clear()
    collection->clear();
    // Using assert equals because this is the end of this test case
    ASSERT_EQ(collection->size(), 0) << "The vector's size did not reuce to 0 using clear.";
}

// Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VerifyEraseBeginEndErasesCollection)
{
    // Add some entries to the vector first so there are some entries to erase
    add_entries(3);
    // Assert that the vector is not empty to start so the test has some elements to erase
    ASSERT_NE(collection->size(), 0) << "The collection was empty to start.";
    // Decrease the vector's size to zero using erase(begin, end)
    collection->erase(collection->begin(), collection->end());
    // Using assert equals because this is the end of this test case
    ASSERT_EQ(collection->size(), 0) << "erase(begin, end) did not erase the collection.";
}

// Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VerifyReserveIncreasesCapacityOnly)
{
    // Determine the vector's starting capacity
    unsigned long long int starting_cap = collection->capacity();
    // Determine the vector's starting size
    unsigned long long int starting_size = collection->size();
    // Increase the capacity by one
    collection->reserve(starting_cap + 1);
    // Expect that the collection size remained unchanged so execution coninues to check capacity
    EXPECT_EQ(starting_size, collection->size()) << "The collection's size was changed when changing capacity.";
    // Using assert greater than to test the capacity increase because this is the end of this test case
    ASSERT_GT(collection->capacity(), starting_cap) << "The collection's capacity was not increased with reserve.";
}

// Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, VerifyExceptionWithOutOfBoundsAccess)
{
    // Determine the vector's size
    unsigned long long int collection_size = collection->size();
    // Assert that the std::out_of_range exception is thrown when calling on an out of bounds index
    ASSERT_THROW(collection->at(collection_size + 1), std::out_of_range) << "An out of range exception was not thrown.";
}

// Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// A positive test to verify that shink_to_fit reduces the vector's capacity to be equivalent to it's size
TEST_F(CollectionTest, VerifyShrinkToFitMakesCapacityEqualToSize) {
    
    // Add one value to the vector so it is not empty
    add_entries(1);
    // Adjust capacity so it is greater than size
    collection->reserve(3);
    // Assert that the capacity is greater than the size because this is a necessary condition to test the shrink_to_fit funcitonality
    ASSERT_GT(collection->capacity(), collection->size()) << "The capacity was not larger than size to start.";
    // Call the shrink_to_fit method
    collection->shrink_to_fit();
    // Assert that shrink_to_fit makes the vector's capacity and size equivalent
    ASSERT_EQ(collection->size(), collection->capacity()) << "Shrink to fit did not fit the collection's capacity to its size.";
}

// A negative test to verify that an std::length_error exception is thrown when trying to resize a vector beyond its maximum size
TEST_F(CollectionTest, VerifyLengthErrorWhenResizingBeyondMaxSize)
{
    ASSERT_THROW(collection->resize(collection->max_size() + 1), std::length_error) << "A length error was not thrown.";
}
