## TRandom
### A wrapper class around the std::random library

This simple library allow developer to generate random values easily, both built-in types and custom types, using one single header and one simple function call. Currently to generate good random values we need several lines of codes and several classes (distribution, engines etc.). Additionally, there is support for random custom types generation. 

The **TRandom** library solves this problem by providing 2 classes, one for built-in types and one for custom types. Each class implements 3 functions: Value, ValueParam, and Range.

#### Example
*Generate random built-in types*
```cpp
// Generate a random std::int32t
std::int32t INum32 = random::gen::IntGen<>::Value();

// Generate a random std::uint64t between [0,1000]
std::uint64t INum64 = random::gen::IntGen<std::uint64t>::Range(0u, 1000u);

// Generate a random bool with a probability of 50% (
bool Bool = random::gen::BoolGen<>::ValueParam(random::gen::BoolGen<>::ParamType(0.5));
```

*Generate random std::string*
```cpp
// A utility to create a random string with a personalized char set
struct RandomString
{
	// Function used by the number generator to generate a random foo class base on two parameter
	static std::string RandomValue(int Length, const std::string& CharSet = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" })
	{
		// string that will hold the random string
		std::string ReturnStr;

		// Store the size of the passed charset
		const auto CharSetSize = CharSet.size() - 1;

		while (Length-- > 0)
			ReturnStr += CharSet[random::gen::IntGen<>::Range(0, CharSetSize)];

		return ReturnStr;
	}
};

// Add our custom StringGenerator to the random namespace using the CustomGenerator class for consistent use in the rest of the program
namespace random
{
	namespace gen
	{
		// The Foo generator use the RandomString class and returns a std::string 
		using StringGen = random::impl::CustomGenerator<RandomString, std::string>;
	}
}

// Random 10 character string using the charset specified by the RandomString class
auto Str = random::gen::StringGen::ValueParam(10);

// Rnadom 20 character string using just numbers as charset
auto StrChar = random::gen::StringGen::ValueParam(20, "0123456789");
```
