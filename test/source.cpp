////////////////////////////////////////////////////////////
//
// https://github.com/assematt | assenza.matteo@gmail.com
// Copyright (C) - 2018 - Assenza Matteo
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files(the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial 
// portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

// Include the TRandom.hpp header to use the library
#include <TRandom.hpp>

// Example class to test the randomizer with custom class
struct Foo
{
	// Construct a Foo object using an ID and Price
	Foo(const int& _ID, const float& _Price)
	{
		ID = _ID;
		Price = _Price;
	}

	// For easy debugging in the console
	friend std::ostream& operator<<(std::ostream& Os, const Foo& _Foo)
	{
		Os << "Foo ID: " << _Foo.ID << ", Foo price: " << _Foo.Price;
		return Os;
	}

	// Function used by the number generator to generate a random foo class
	static Foo RandomValue()
	{
		return Foo(random::gen::IntGen<>::Range(0, 100), random::gen::FloatGen<>::Range(100.f, 1000.f));
	}

	// Function used by the number generator to generate a random foo class base on one parameter
	static Foo RandomValue(int Modifier)
	{
		return Foo(random::gen::IntGen<>::Range(0 * Modifier, 100 * Modifier), random::gen::FloatGen<>::Range(100.f * Modifier, 1000.f * Modifier));
	}

	// Function used by the number generator to generate a random foo class between two parameters
	static Foo RandomRange(const Foo& Min, const Foo& Max)
	{
		return Foo(random::gen::IntGen<>::Range(Min.ID, Max.ID), random::gen::FloatGen<>::Range(Max.Price, Max.Price));
	}

private:
	int ID;
	float Price;
};

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

// Add our custom Foo class and our StringGenerator to the random namespace using the CustomGenerator class for consistent use in the rest of the program
namespace random
{
	namespace gen
	{
		// The Foo generator use the RandomString class and returns a std::string
		using StringGen = random::impl::CustomGenerator<RandomString, std::string>;

		// The Foo generator use the Foo class and returns a Foo
		using FooGenerator = random::impl::CustomGenerator<Foo>;
	}
}

int main()
{
	// Welcome message
	std::cout << "RANDOM GENERATOR" << std::endl << std::endl;

	// Function aliases for our generators

	// Generate a random "int" between a user specified range
	auto Integer32Generator = random::gen::IntGen<>::Range;

	// Generate a random "int" between -2^64 and 2^64-1
	auto Integer64Generator = random::gen::IntGen<std::int64_t>::Value;

	// Generate a random "double" between a user specified range
	auto DoubleGenerator = random::gen::FloatGen<double>::Range;

	// Generate a random Foo object
	auto FooesGenerator = random::gen::FooGenerator::Value;

	// Generate a random bool based on a parameter (a float)
	auto BoolGenerator = random::gen::BoolGen<>::ValueParam<double>;

	// Generate a random string based on a parameter (an integer for the length, a string as a charset)
	auto StrGenerator = random::gen::StringGen::ValueParam<int>;
	auto StrGeneratorCharSet = random::gen::StringGen::ValueParam<int, std::string>;

	// Generate 10 Random values
	for (auto Index = 0u; Index < 10; ++Index)
	{
		// Generate a random int between 0 and 100
		std::cout << "Random std::int32_t: " << Integer32Generator(0, 100) << std::endl;

		// Generate a random int between 0 and 2^64-1
		std::cout << "Random std::int64_t: " << Integer64Generator() << std::endl;

		// Generate a random double between -500 and 500
		std::cout << "Random double: " << DoubleGenerator(-500, 500) << std::endl;

		// Generate a random parameter with a probability of 0.5
		std::cout << "Random bool: " << std::boolalpha << BoolGenerator(0.5) << std::endl;

		// Generate a random string of 10 character the default charset
		std::cout << "Random default string: " << StrGenerator(5) << std::endl;

		// Generate a random string of 5 character using "aeiou" as a charset
		std::cout << "Random string: " << StrGeneratorCharSet(10, "aeiou") << std::endl;

		// Generate a random Foo object
		std::cout << "Random Foo: " << FooesGenerator() << std::endl;

		// Generate a random Foo object based on a parameter without using a function alias
		std::cout << "Random Foo with modifier: " << random::gen::FooGenerator::ValueParam(5) << std::endl << std::endl;
	}

	// Everything went ok
	return 0;
}