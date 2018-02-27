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

#pragma once

#include <random>
#include <type_traits>

namespace random
{
	// Contains an implementation for generals value generator
	namespace impl
	{

		// General generator function for builtin-types
		template <class _Type, class _Distribution, class _Engine, class _Seed>
		struct Generator
		{
			// Typedefs for the 
			using Type = _Type;
			using Distribution = _Distribution;
			using Engine = _Engine;
			using Seed = _Seed;
			using ParamType = typename _Distribution::param_type;
			using ReturnType = typename _Distribution::result_type;			
			
			// Return the distribution used
			static Distribution& GetDistribution()
			{
				static Distribution DInstance;
				return DInstance;
			}

			// Return the engine used
			static Engine& GetEngine()
			{
				static Engine DEngine(GetSeed()());
				return DEngine;
			}

			// Return the seed used
			static Seed& GetSeed()
			{
				static Seed DEngine;
				return DEngine;
			}
			
			// Return a value
			static ReturnType Value()
			{			
				// Return a random number
				return GetDistribution()(GetEngine());
			
			}

			// Return a value base on a parameter
			template <class... TArgs>
			static ReturnType ValueParam(TArgs&&... Params)
			{
				// Return a random number
				return GetDistribution()(GetEngine(), ParamType(std::forward<TArgs>(Params)...));
			}
						
			// Return a value that is between 2 parameters
			static ReturnType Range(Type Min, Type Max)
			{
				// Return a random number
				return GetDistribution()(GetEngine(), ParamType(Min, Max));
			}
			
		};

		// Useful for custom class
		// General generator function
		template <class _Type, class _ReturnType = _Type>
		struct CustomGenerator
		{
			using Type = _Type;
			using ReturnType = _ReturnType;
						
			// Return a value
			static ReturnType Value()
			{
				return Type::RandomValue();
			}
			
			// Return a value base on one or more parameters
			template <class... TArgs>
			static ReturnType ValueParam(TArgs&&... AdditionalParam)
			{
				return Type::RandomValue(std::forward<TArgs>(AdditionalParam)...);
			}

			// Return a value that is between 2 parameters
			template <class T = Type>
			static ReturnType Range(T Min, T Max)
			{
				return Type::RandomRange(Min, Max);
			}
		};
	}

	// List of distribution aliases
	namespace distr
	{
		// Alias for std::uniform_int_distribution
		// Produces integer values evenly distributed across a range 
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using UniformInt = std::uniform_int_distribution<T>;

		// Alias for std::uniform_int_distribution
		// Produces real values evenly distributed across a range 
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using UniformReal = std::uniform_real_distribution<T>;
		
		// Alias for std::bernoulli_distribution
		// Produces bool values on a Bernoulli distribution
		using Bernoulli = std::bernoulli_distribution;

		// Alias for std::binomial_distribution
		// Produces integer values on a binomial distribution.
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using Binomial = std::binomial_distribution<T>;

		// Alias for std::negative_binomial_distribution
		// Produces integer values on a negative binomial distribution.
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using NegBinomial = std::negative_binomial_distribution<T>;

		// Alias for std::geometric_distribution
		// Produces integer values on a geometric distribution.
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using Geometric = std::geometric_distribution<T>;

		// Alias for std::poisson_distribution
		// Produces integer values on a poisson distribution. 
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using Poisson = std::poisson_distribution<T>;

		// Alias for std::exponential_distribution
		// produces real values on an exponential distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using Exponential = std::exponential_distribution<T>;

		// Alias for std::gamma_distribution
		// Produces real values on an gamma distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using Gamma = std::gamma_distribution<T>;

		// Alias for std::weibull_distribution
		// Produces real values on a Weibull distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using Weibull = std::weibull_distribution<T>;

		// Alias for std::extreme_value_distribution
		// Produces real values on an extreme value distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using ExtremeValue = std::extreme_value_distribution<T>;

		// Alias for std::normal_distribution
		// produces real values on a standard normal (Gaussian) distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using Gaussian = std::normal_distribution<T>;

		// Alias for std::lognormal_distribution
		// Produces real values on a lognormal distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using LogNormal = std::lognormal_distribution<T>;

		// Alias for std::chi_squared_distribution
		// Produces real values on a chi-squared distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using ChiSquared = std::chi_squared_distribution<T>;

		// Alias for std::cauchy_distribution
		// Produces real values on a Cauchy distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using Cauchy = std::cauchy_distribution<T>;

		// Alias for std::fisher_f_distribution
		// Produces real values on a Fisher's F-distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using FisherF = std::fisher_f_distribution<T>;

		// Alias for std::student_t_distribution
		// Produces real values on a Student's t-distribution.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using StudentT = std::student_t_distribution<T>;

		// Alias for std::discrete_distribution
		// Produces random integers on a discrete distribution.
		template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
		using Discrete = std::discrete_distribution<T>;

		// Alias for std::piecewise_constant_distribution
		// Produces real values distributed on constant subintervals.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using PiecewiseConstant = std::piecewise_constant_distribution<T>;

		// Alias for std::piecewise_linear_distribution
		// Produces real values distributed on defined subintervals.
		template <class T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		using PiecewiseLinear = std::piecewise_linear_distribution<T>;
	}

	// List of generators
	namespace gen
	{
		// Default engine
		using DefaultEngine = std::mt19937;

		// Default seeder
		using DefaultSeeder = std::random_device;

		// Template specialization for integer generation
		template <class T = std::int32_t, class D = distr::UniformInt<T>, class E = DefaultEngine, class S = DefaultSeeder>
		using IntGen = impl::Generator<T, D, E, S>;

		// Template specialization for floating point generation
		template <class T = float, class D = distr::UniformReal<T>, class E = DefaultEngine, class S = DefaultSeeder>
		using FloatGen = impl::Generator<T, D, E, S>;

		// Template specialization for boolean
		template <class E = DefaultEngine, class S = DefaultSeeder>
		using BoolGen = impl::Generator<bool, distr::Bernoulli, E, S>;
	}
		
}