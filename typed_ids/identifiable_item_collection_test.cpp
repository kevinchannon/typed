
#include <typed/identifiable_item_collection.hpp>
#include <typed/identifiable.hpp>
#include <typed/io/idio.hpp>

#include <string>

///////////////////////////////////////////////////////////////////////////////

namespace {

///////////////////////////////////////////////////////////////////////////////

struct Duck : public typed::identifiable< Duck, std::string > {
  explicit Duck(std::string id) : typed::identifiable< Duck, std::string >{std::move(id)} {}
  explicit Duck(id_type id) : Duck{id.get()} {}
};

using Ducks = typed::identifiable_item_collection<Duck, uint8_t>;

class IdentifiableItemCollectionTests : public ::testing::Test {
  protected:
  Ducks ducks;
};
TEST_F(IdentifiableItemCollectionTests, DefaultConstructedHasZeroSize) {
  ASSERT_EQ(Ducks::size_type{0}, ducks.size());
}

TEST_F(IdentifiableItemCollectionTests, AddAnItem) {
  const auto [new_duck, added] = ducks.add(Duck{"duck-001"});
  ASSERT_NE(nullptr, new_duck);
  ASSERT_TRUE(added);
  ASSERT_EQ(Duck::id_type{"duck-001"}, new_duck->id());
}

TEST_F(IdentifiableItemCollectionTests, AddAnItemAsAUniquePtr) {
  const auto [new_duck, added] = ducks.add(std::make_unique< Duck >("duck-007"));
  ASSERT_NE(nullptr, new_duck);
  ASSERT_TRUE(added);
  ASSERT_EQ(Duck::id_type{"duck-007"}, new_duck->id());
}

TEST_F(IdentifiableItemCollectionTests, SizeIsCorrect) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});

  ASSERT_EQ(Ducks::size_type{2}, ducks.size());
}

TEST_F(IdentifiableItemCollectionTests, CountAndSizeReturnTheSameValue) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});

  ASSERT_EQ(ducks.size(), ducks.count());
}

TEST_F(IdentifiableItemCollectionTests, GetReturnsTheExpectedItem) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});
  ducks.add(Duck{"duck-003"});

  constexpr auto idx = Ducks::index_type{1};

  ASSERT_EQ(Duck::id_type{"duck-002"}, ducks.at(idx).id());
}

TEST_F(IdentifiableItemCollectionTests, FindReturnsTheCorrectItem) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});
  ducks.add(Duck{"duck-003"});

  const auto duck = ducks.find(Duck::id_type{"duck-002"});
  ASSERT_NE(nullptr, duck);
  ASSERT_EQ(Duck::id_type{"duck-002"}, duck->id());
}

TEST_F(IdentifiableItemCollectionTests, FindNonExistantItemReturnsNull) {
  ASSERT_EQ(nullptr, ducks.find(Duck::id_type{"duck-001"}));
}


TEST_F(IdentifiableItemCollectionTests, RemoveAnItem) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});

  const auto id_to_remove  = Duck::id_type{"duck-001"};
  auto released_duck = ducks.remove(id_to_remove);
  
  ASSERT_NE(nullptr, released_duck);
  ASSERT_EQ(id_to_remove, released_duck->id());
  ASSERT_EQ(Ducks::size_type{1}, ducks.size());
  ASSERT_EQ(nullptr, ducks.find(id_to_remove));
}

TEST_F(IdentifiableItemCollectionTests, RemoveNonExistentItemDoesNothing) {
  ducks.add(Duck{"duck-001"});
  ducks.add(Duck{"duck-002"});

  const auto id_to_remove = Duck::id_type{"duck-003"};
  auto released_duck      = ducks.remove(id_to_remove);

  ASSERT_EQ(nullptr, released_duck);
  ASSERT_EQ(Ducks::size_type{2}, ducks.size());
}

TEST_F(IdentifiableItemCollectionTests, AddWithTheSameIdReturnsFalse) {
  auto [d1, added_1] = ducks.add(Duck{"duck-001"});
  ASSERT_NE(nullptr, d1);
  ASSERT_TRUE(added_1);

  auto [d2, added_2] = ducks.add(Duck{"duck-001"});
  ASSERT_NE(nullptr, d1);
  ASSERT_FALSE(added_2);
}

TEST_F(IdentifiableItemCollectionTests, EmplaceAnItem) {
  auto [d, added] = ducks.emplace("duck-0");
  ASSERT_NE(nullptr, d);
  ASSERT_TRUE(added);

  auto d_find = ducks.find(Duck::id_type{"duck-0"});
  ASSERT_NE(nullptr, d_find);
  ASSERT_EQ(Duck::id_type{"duck-0"}, d_find->id());
}

///////////////////////////////////////////////////////////////////////////////

}  // namespace

///////////////////////////////////////////////////////////////////////////////
