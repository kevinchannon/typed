# Typed: Help prevent accidental look-up of items with the ID of another item of a different type

## A motivating example

Say you're writing something that involves using multiple collections of different types of things. So, maybe something that's managing widgets, or something.  You might have a list of buttons, a list of scrollbars, a list of menu items, _etc_:
```
class Button { ... };
using Buttons = std::vector<Button>;

class ScrollBar { ... };
using ScrollBars = std::vector<ScrollBar>;

class MenuItem { ... };
using MenuItems = std::vector<MenuItem>;
```

Cool. In your code, you probably want to do things with particular items in these collections.  So, each will have some kind of ID and you want to find the things by their ID in order to use them. You could replace the vectors above with maps from ID to the item, or something, or you could make some convenience function that gives you the thing, given it's ID:
```
template<typename Container_T>
const typename Container_T::value_type* const* find_item(const Container_T& items, const int id) {
    const auto item = std::find_if(items.begin(), items.end(), [id](auto&& item){
        return id == item.id();
    });

    return items.end() != item ? &(*item) : nullptr; 
}
```

Great!  Now we can find the things we need using their ID :)  However, in a larger codebase, it's not too difficult to make this kind of mistake:
```
const auto id = button1.id();

/*
    ... Insert lots of code here, so that you don't easily see the definition of `id`.
*/

auto menu_item = find(menu_items, id);  // D'oh! This is not the menu item you a looking for.
```

This is a bit of a noddy example, but these kinds of error can be annoying and difficult to diagnose if you have lots of collections of lots of types.

## Using types to generate compile-time errors

The code in this repo includes a bunch of templates to allow you to easily stamp IDs and array indices with a particular type, preventing accidental use of an ID to look-up something of the wrong type. First of all, you derive the type that you want to have an ID from `typed::identifiable`:
```
#include <typed/identifiable.hpp>


class Button : public typed::identifiable<Button, int> {
public:
    Buttong(int id) : typed::identifiable<Button, int>{ std::move(id)} {}
};
```

The mixin provides an `id()` method for our class and manages a variable that stores the ID; as well as some type aliases to allow use to find out the type of the ID.  The ID has the type:
```
using id_type = id< _base_type, Id_T >;
```
where the `_base_type` is whatever the first template argument to `identifiable` is and `Id_T` is the underlying ID type, `Button` and `int`, respectively, in the example above. The type of the ID can be anything that's comparable.  So, it could be an `int`, as above, or a `float`, if you were a bit mad, or a `std:string`, or `GUID`, or you could define your own comparable type, like a serial number, or something.

Once you've mixed-in the identifiable type, then you can do something like:
```
constexpr auto button = Button{1};

constexpr auto id = button.id();
```
The ID that comes back out, is now only comparable with the Id's of other buttons.  So, if you'd also defined `MenuItem` and `ScrollBar` classes, with their respective collections, then the find function could be mofidied to something like:
```
template<typename Container_T, typename Id_T>
const typename Container_T::value_type* const* find_item(const Container_T& items, const Id_T id) {
    const auto item = std::find_if(items.begin(), items.end(), [id](auto&& item){
        return id == item.id();
    });

    return items.end() != item ? &(*item) : nullptr; 
}
```
Now, attempting to do the comparison that previously resulted in a run-time bug is now a compilation error:
```
const auto id = button1.id();

/*
    ... Insert lots of code here, so that you don't easily see the definition of `id`.
*/

auto menu_item = find(menu_items, id);  // Compilation failure here! Button::id_type is not comparable with MenuItem::id_type!
```

## Typed indices

As well as looking things up in a container by ID, it's also common to use an index value to get at a value in a container.
It's also possible to confuse the index of one container with another in the same way as an ID.
If you use a `std` container, like a vector or list is used, then you're kind of restriced in the kind of value that you use for an index into the array.
Here, we provide a container that stores identifiable items and defines its own type for indices, which is stamped with the type of the thing in the container: `typed::identifiable_item_container`.
This is easiest to use _via_ an alias, like this:
```
using Buttons = typed::identifiable_item_container<Button, size_t>;
```
This defines a container that contains `Button` objects and is indexed using an index that's based on a `size_t`.
This container has `at` methods for access by index and `find` methods for finding things by their ID.

## More...
OK, the basics of the thing are here.
There are some other things that would be nice to do, but I don't have time right now.
If you're reading this and want to do something from below, then go for it and send a pull-request :)

### Iterators
Every good container has iterators and it would be good to have them for `identifiable_item_collection`, then it could be used with all the STL algorithms and ranges and all that goodness.

### Template on container type
At the moment, the `identifiable_item_collection` stores things in a `std::vector`.
This is good for iterating and indexed access, but not so good for finding things.
If you were doing something that involved lots of insertions and deletions and looking things up by ID, then this vector-based thing might be sub-optimal.
To get the best of both worlds, it could be nice to have the container type inside the `identifiable_item_collection` as a template parameter and then alias things like this:
```
template<typename Base_T, typename Id_T, typename Container_T>
class basic_identifiable_item_collection { ... };

template<typename Base_T, typename Id_T>
using identifiable_item_vector = identifiable_item_collection<Base_T, Id_T, std::vector<std::unique_ptr<Item_T>>;

template<typename Base_T, typename Id_T>
using identifiable_item_set = identifiable_item_collection<Base_T, Id_T, std::set<std::unique_ptr<Item_T>>;
```
Then, the user could alias the right one of the two aliases for the application that they have in mind.

### Interfaces
There's a system of interfaces that could be layered on top of the existing templates. This could be useful for some applications.