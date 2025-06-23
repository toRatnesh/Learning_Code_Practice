/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/header/concepts

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.15 Existing Concepts

The STL comes with pre-defined common concepts. They are part of the <concepts> header.
Most of them are concept definitions for existing type-traits, uses same_as std::is_same_v. 

These pre-defined concepts consider subsumption rules, and have the requires helpers to avoid different results due to parameter swapping.

Arithmetic concepts
	integral				specifies that a type is an integral type
	signed_integral			specifies that a type is an integral type that is signed
	unsigned_integral		specifies that a type is an integral type that is unsigned
	floating_point			specifies that a type is a floating-point type

Type concepts
	same_as					specifies that a type is the same as another type
	derived_from			specifies that a type is derived from another type
	convertible_to			specifies that a type is implicitly convertible to another type
	common_reference_with	specifies that two types share a common reference type
	common_with				specifies that two types share a common type

Construction concepts
	assignable_from			specifies that a type is assignable from another type
	swappable
	swappable_with			specifies that a type can be swapped or that two types can be swapped with each other
	destructible			specifies that an object of the type can be destroyed
	constructible_from		specifies that a variable of the type can be constructed from or bound to a set of argument types
	default_initializable	specifies that an object of a type can be default constructed
	move_constructible		specifies that an object of a type can be move constructed
	copy_constructible		specifies that an object of a type can be copy constructed and move constructed

Object concepts
	movable					specifies that an object of a type can be moved and swapped
	copyable				specifies that an object of a type can be copied, moved, and swapped
	semiregular				specifies that an object of a type can be copied, moved, swapped, and default constructed
	regular					specifies that a type is regular, that is, it is both semiregular and equality_comparable

Callable concepts
	invocable
	regular_invocable		specifies that a callable type can be invoked with a given set of argument types
	predicate				specifies that a callable type is a Boolean predicate
	relation				specifies that a callable type is a binary relation
	equivalence_relation	specifies that a relation imposes an equivalence relation
	strict_weak_order		specifies that a relation imposes a strict weak ordering

Comparison concepts
	boolean-testable			specifies that a type can be used in Boolean contexts
								(exposition-only concept*)
	equality_comparable
	equality_comparable_with	specifies that operator == is an equivalence relation

	totally_ordered
	totally_ordered_with		specifies that the comparison operators on the type yield a total order
								Defined in header <compare>

	three_way_comparable
	three_way_comparable_with	specifies that operator <=> produces consistent result on given types

**********/

int main() {

    return 0; 
}

/*****
    END OF FILE
**********/


