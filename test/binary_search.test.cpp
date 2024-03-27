#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "binary_search.h"
}

TEST_GROUP(BinarySearch){};

TEST(BinarySearch, InitFifoFull)
{
    uint32_t arr[] = { 12, 13, 45, 51, 0xFFFFFFFFU, 1, 3};

    Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

    CHECK_EQUAL(5U, fifo_indexes.tail);
    CHECK_EQUAL(4U, fifo_indexes.head);
}

TEST(BinarySearch, InitFifoNotFullWithoutZeros)
{
    uint32_t arr[] = { 12, 13, 45, 51, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 1, 3};

    Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

    CHECK_EQUAL(7U, fifo_indexes.tail);
    CHECK_EQUAL(4U, fifo_indexes.head);
}

TEST(BinarySearch, InitFifoNotFullWithMultipleZeros)
{
    uint32_t arr[] = { 12, 13, 45, 51, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0, 0, 0, 0, 1, 3};

    Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

    CHECK_EQUAL(11U, fifo_indexes.tail);
    CHECK_EQUAL(4U, fifo_indexes.head);
}

TEST(BinarySearch, InitFifoNeverFullyWritten)
{
    uint32_t arr[] = { 0, 0, 0, 12, 13, 45, 51, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU};

    Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

    CHECK_EQUAL(3U, fifo_indexes.tail);
    CHECK_EQUAL(7U, fifo_indexes.head);
}

// TEST(BinarySearch, InitFifoEmptyNeverWritten)
// {
//     uint32_t arr[] = { 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU};

//     Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

//     CHECK_EQUAL(0U, fifo_indexes.tail);
//     CHECK_EQUAL(0U, fifo_indexes.head);
// }

TEST(BinarySearch, InitFifoEmptyAllWritten)
{
    uint32_t arr[] = { 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U};

    Fifo_Indexes_t fifo_indexes =  init_fifo_indexes(arr, sizeof(arr)/sizeof(arr[0]));

    CHECK_EQUAL(0U, fifo_indexes.tail);
    CHECK_EQUAL(0U, fifo_indexes.head);
}