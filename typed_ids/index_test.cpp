#include "index.hpp"

///////////////////////////////////////////////////////////////////////////////

using IndexTypes = ::testing::Types< uint8_t, uint16_t, uint32_t, uint64_t >;

class IndexTypeNames {
 public:
  template < typename T >
  static std::string GetName(int) {
    if constexpr (std::is_same< T, uint8_t >()) {
      return "uint8_t";
    }
    if constexpr (std::is_same< T, uint16_t >()) {
      return "uint16_t";
    }
    if constexpr (std::is_same< T, uint32_t >()) {
      return "uint32_t";
    }
    if constexpr (std::is_same< T, uint64_t >()) {
      return "uint64_t";
    }
  }
};

template < typename Tested_T >
struct IndexTests : public testing::Test {};

TYPED_TEST_CASE(IndexTests, IndexTypes, IndexTypeNames);

///////////////////////////////////////////////////////////////////////////////

namespace {
struct Cat {};
}  // namespace

///////////////////////////////////////////////////////////////////////////////

TYPED_TEST(IndexTests, DefaultConstructToZero) {
  const auto idx       = index_type< Cat, TypeParam >{};
  const auto expected = TypeParam{0};
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, ConstructWithValue) {
  constexpr auto expected = TypeParam{10};
  const auto idx = index_type< Cat, TypeParam >{expected};
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, AssignValue) {
  auto idx = index_type< Cat, TypeParam >{};
  constexpr auto expected = TypeParam{5};
  idx                     = index_type< Cat, TypeParam >{expected};
  
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, CompareValues) {
  const auto idx_0 = index_type< Cat, TypeParam >{};
  const auto idx_1 = index_type< Cat, TypeParam >{10};
  const auto idx_2 = index_type< Cat, TypeParam >{10};

  EXPECT_NE(idx_0, idx_1);
  EXPECT_EQ(idx_1, idx_2);
  EXPECT_GT(idx_1, idx_0);
  EXPECT_LT(idx_0, idx_1);
}

TYPED_TEST(IndexTests, PreIncrement) {
  auto idx = index_type< Cat, TypeParam >{};
  ++idx;
  ASSERT_EQ(1, idx.get());
}

TYPED_TEST(IndexTests, PostIncrement) {
  constexpr auto expected = TypeParam{10};
  auto idx = index_type< Cat, TypeParam >{expected};
  const auto val = idx++;
  ASSERT_EQ(expected, val.get());
  ASSERT_EQ(1 + expected, idx.get());
}

///////////////////////////////////////////////////////////////////////////////
