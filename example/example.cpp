// example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <typed/identifiable.hpp>
#include <typed/identifiable_item_collection.hpp>
#include <typed/io/idio.hpp>
#include <typed/io/indexio.hpp>

#include <iostream>
#include <string>

/// <summary>
/// A Dog has an ID, and it picks up all its ID-related behaviours from the "identifiable" mixin. The first template
/// argument is added into the type of the ID and ensures that IDs from different things can't accidentally be compared.
/// The second template argument is the actual type of the ID that you want to use. Can be anything, really.  It needs to
/// have well-behaved comparison operators though.
/// </summary>
class Dog : public typed::identifiable_mixin< Dog, size_t > {
 public:
  Dog(size_t id) : typed::identifiable_mixin< Dog, size_t >{id} {}
};

/// <summary>
/// You can just alias an identifiable_item_collection of your type to use as the collection for that type.  You can specify
/// the type of index used for the type. Again, indicies from collections of different types are not comparable.
/// </summary>
using Dogs = typed::identifiable_item_collection< Dog, size_t >;

/// <summary>
/// Another identifiable type. Its ID is not comparable with that of a Dog.
/// </summary>
class Duck : public typed::identifiable_mixin< Duck, size_t > {
 public:
  Duck(size_t id) : typed::identifiable_mixin< Duck, size_t >{id} {}
};

using Ducks = typed::identifiable_item_collection< Duck, size_t >;

/// <summary>
/// This type uses a std::string as the ID type. Pretty much any sensible type should be OK to use an ID.
/// </summary>
class Cat : public typed::identifiable_mixin< Cat, std::string > {
 public:
  Cat(typename id_type::value_type id) : typed::identifiable_mixin< Cat, std::string >{std::move(id)} {}
};

using Cats = typed::identifiable_item_collection< Cat, size_t >;

/// <summary>
/// A serial number is a bit more of a complicated type.  In is comparable though, so you can use it as an ID, if you like.
/// </summary>
struct SerialNumber {
  uint8_t region;
  uint8_t version;
  uint16_t facility;

  auto operator<=>(const SerialNumber&) const = default;

  friend std::ostream& operator<<(std::ostream& os, const SerialNumber& sn) {
    os << static_cast< uint32_t >(sn.version) << "." << static_cast< uint32_t >(sn.region) << "."
       << static_cast< uint32_t >(sn.facility);

    return os;
  }
};

class Printer : public typed::identifiable_mixin<Printer, SerialNumber> {
 public:
  Printer(SerialNumber id) : typed::identifiable_mixin< Printer, SerialNumber >{id} {}
};

using Printers = typed::identifiable_item_collection<Printer, size_t>;

int main() {
  /////////////////////////////////////////////////////////////////////////////
  //
  // Dogs and ducks
  //
  /////////////////////////////////////////////////////////////////////////////
  auto dogs  = Dogs{};
  auto ducks = Ducks{};

  const auto d1 = dogs.add(Dog{1}).first;
  const auto d2 = Dog{1};
  const auto d3 = ducks.add(Duck{1}).first;

  if (d1->id() == d2.id()) {
    std::cout << "IDs match" << std::endl;
  }

  // This will fail to build if uncommented, since Dog and Duck IDs are not comparable.
  //
  // if (d1->id() == d3->id()) {
  //   std::cout << "IDs match?!" << std::endl;
  // }

  const auto d4 = dogs.find(d1->id());
  if (nullptr != d4) {
    std::cout << "Found dog with ID" << d4->id() << std::endl;
  }

  dogs.add(Dog{2});

  const auto& d5 = dogs.at(Dogs::index_type{0});
  std::cout << "The 0-th dog has ID " << d5.id() << std::endl;

  for (auto i = Ducks::index_type{0}; i < ducks.count(); ++i) {
    std::cout << "Duck " << i << " has ID " << ducks.at(i).id() << std::endl;
  }

  // This will fail to build if uncommented, since a dog-index can't be used to get an item from a
  // collection of ducks.
  //
  // for (auto i = Dogs::index_type{0}; i < dogs.count(); ++i) {
  //   std::cout << "Dog " << i << " has ID " << ducks.at(i).id() << std::endl;
  // }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Cats
  //
  /////////////////////////////////////////////////////////////////////////////
  auto cats     = Cats{};
  const auto c1 = cats.add(Cat{"Cat-2022-04-27-01"}).first;

  std::cout << "Cat 1 has ID " << c1->id() << std::endl;

  cats.add(Cat("Cat-2022-04-27-02"));
  const auto c2 = cats.find(Cat::id_type{"Cat-2022-04-27-02"});

  std::cout << "Cat 2 has ID " << c2->id() << std::endl;

  // This will fail to build if uncommmented, since you can't use the un-typed, underlying ID type to find things,
  // it has to be the right ID type for the thing you're looking up.
  //
  // const auto c3 = cats.find("Cat-2022-04-27-01");

  /////////////////////////////////////////////////////////////////////////////
  //
  // Printers
  //
  /////////////////////////////////////////////////////////////////////////////

  auto printers = Printers{};
  printers.add(Printer{{10, 02, 2553}});
  printers.add(Printer{{10, 02, 2555}});
  printers.add(Printer{{10, 02, 2753}});

  std::cout << "We've got " << printers.count() << " printers." << std::endl;

  const auto p1 = printers.find(Printer::id_type{{10, 02, 2555}});
  std::cout << "Found printer with serial number " << p1->id() << std::endl;

  return 0;
}
