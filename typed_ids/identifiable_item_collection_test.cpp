
#include "identifiable_item_collection.hpp"
#include "identifiable.hpp"

#include <string>

///////////////////////////////////////////////////////////////////////////////

namespace {

///////////////////////////////////////////////////////////////////////////////

struct Duck : public typed::identifiable_mixin< Duck, std::string > {
  explicit Duck(std::string id) : typed::identifiable_mixin< Duck, std::string >{std::move(id)} {}
  explicit Duck(id_type id) : Duck{id.get()} {}
};

using Ducks = typed::identifiable_item_collection<Duck, uint8_t>;

TEST(IdentifiableItemCollectionTests, DefaultConstructedHasZeroSize) {
  ASSERT_EQ(Ducks::size_type{0}, Ducks{}.size());
}

TEST(IdentifiableItemCollectionTests, AddAnItem) {
  auto ducks = Ducks{};
  const auto new_duck = ducks.add(Duck{"duck-001"});
  ASSERT_NE(nullptr, new_duck);
  ASSERT_EQ(Duck::id_type{"duck-001"}, new_duck->id());
}

///////////////////////////////////////////////////////////////////////////////

}  // namespace

///////////////////////////////////////////////////////////////////////////////