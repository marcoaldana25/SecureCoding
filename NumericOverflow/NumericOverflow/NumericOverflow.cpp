// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

enum class string_type_values
{
	eChar,
	eWChar_T,
	eShortInt,
	eInt,
	eLong,
	eInt64,
	eUnsignedChar,
	eUnsignedShortInt,
	eUnsignedInt,
	eUnsignedLong,
	eUnsignedInt64,
	eFloat,
	eDouble,
	eLongDouble
};

string_type_values convert_to_enum(std::string type_value)
{
	if (type_value == "char")
	{
        return string_type_values::eChar;
	}
    else if(type_value == "wchar_t")
    {
        return string_type_values::eWChar_T;
    }
    else if (type_value == "short")
    {
        return string_type_values::eShortInt;
    }
    else if (type_value == "int")
    {
        return string_type_values::eInt;
    }
    else if (type_value == "long")
    {
        return string_type_values::eLong;
    }
    else if (type_value == "__int64")
    {
        return string_type_values::eInt64;
    }
    else if (type_value == "unsigned char")
    {
        return string_type_values::eUnsignedChar;
    }
    else if (type_value == "unsigned short")
    {
        return string_type_values::eUnsignedShortInt;
    }
    else if (type_value == "unsigned int")
    {
        return string_type_values::eUnsignedInt;
    }
    else if (type_value == "unsigned long")
    {
        return string_type_values::eUnsignedLong;
    }
    else if (type_value == "unsigned __int64")
    {
        return string_type_values::eUnsignedInt64;
    }
    else if (type_value == "float")
    {
        return string_type_values::eFloat;
    }
    else if (type_value == "double")
    {
        return string_type_values::eDouble;
    }
    else if (type_value == "long double")
    {
        return string_type_values::eLongDouble;
    }
}

template <typename T>
bool is_valid_maximum_value(T result, float max, T const& increment)
{
    return (result > 0) && (result > max - increment);
}

template <typename T>
bool is_valid_minimum_value(T result, float max, T const& increment)
{
    return (result < 0) && (result < max - increment);
}

/// <summary>
/// Responsible for checking the type of the given result and validating that the result
/// value will remain under the specified type's maximum value. 
/// </summary>
/// <typeparam name="T">Generic type T</typeparam>
/// <param name="result">Result value used to validate against</param>
/// <param name="increment">Constant increment value passed in from Main.</param>
/// <returns>True if result + increment will overflow. False if result + increment will not overflow.</returns>
template <typename T>
bool is_overflow(T result, T const& increment)
{
    string_type_values type_value = convert_to_enum(std::string(typeid(result).name()));

	switch (type_value)
	{
		case string_type_values::eChar:
            return is_valid_maximum_value(result, std::numeric_limits<char>::max(), increment);
        case string_type_values::eWChar_T:
            return is_valid_maximum_value(result, WCHAR_MAX, increment);
        case string_type_values::eShortInt:
            return is_valid_maximum_value(result, SHRT_MAX, increment);
        case string_type_values::eInt:
            return is_valid_maximum_value(result, INT_MAX, increment);
        case string_type_values::eLong:
            return is_valid_maximum_value(result, LONG_MAX, increment);
        case string_type_values::eInt64:
            return is_valid_maximum_value(result, LLONG_MAX, increment);
        case string_type_values::eUnsignedChar:
            return is_valid_maximum_value(result, UCHAR_MAX, increment);
        case string_type_values::eUnsignedShortInt:
            return is_valid_maximum_value(result, USHRT_MAX, increment);
        case string_type_values::eUnsignedInt:
            return is_valid_maximum_value(result, UINT_MAX, increment);
        case string_type_values::eUnsignedLong:
            return is_valid_maximum_value(result, ULONG_MAX, increment);
        case string_type_values::eUnsignedInt64:
            return is_valid_maximum_value(result, ULLONG_MAX, increment);
        case string_type_values::eFloat:
            return is_valid_maximum_value(result, FLT_MAX, increment);
        case string_type_values::eDouble:
            return is_valid_maximum_value(result, DBL_MAX, increment);
        case string_type_values::eLongDouble:
            return is_valid_maximum_value(result, LDBL_MAX, increment);
	    default:
	        break;
	}
}

template <typename T>
bool is_underflow(T result, T const& increment)
{
    string_type_values type_value = convert_to_enum(std::string(typeid(result).name()));

    switch (type_value)
    {
    case string_type_values::eChar:
        return is_valid_minimum_value(result, CHAR_MIN, increment);
    case string_type_values::eWChar_T:
        return is_valid_minimum_value(result, WCHAR_MIN, increment);
    case string_type_values::eShortInt:
        return is_valid_minimum_value(result, SHRT_MIN, increment);
    case string_type_values::eInt:
        return is_valid_minimum_value(result, INT_MIN, increment);
    case string_type_values::eLong:
        return is_valid_minimum_value(result, LONG_MIN, increment);
    case string_type_values::eInt64:
        return is_valid_minimum_value(result, LLONG_MIN, increment);
    case string_type_values::eUnsignedChar:
        return is_valid_minimum_value(result, 0, increment);
    case string_type_values::eUnsignedShortInt:
        return is_valid_minimum_value(result, 0, increment);
    case string_type_values::eUnsignedInt:
        return is_valid_minimum_value(result, 0, increment);
    case string_type_values::eUnsignedLong:
        return is_valid_minimum_value(result, 0, increment);
    case string_type_values::eUnsignedInt64:
        return is_valid_minimum_value(result, 0, increment);
    case string_type_values::eFloat:
        return is_valid_minimum_value(result, FLT_MIN, increment);
    case string_type_values::eDouble:
        return is_valid_minimum_value(result, DBL_MIN, increment);
    case string_type_values::eLongDouble:
        return is_valid_minimum_value(result, LDBL_MIN, increment);
    default:
        break;
    }
}


/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if (is_overflow(result, increment))
        {
            return false;
        }
        else
        {
            result += increment;
        }
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="decrement">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
    	if (is_underflow(result, decrement))
    	{
            return false;
    	}
        else
        {
            result -= decrement;
        }
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps);
    std::cout << +result << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1);
    if (result == 0)
    {
        std::cout << "Overflow prevented" <<std::endl;
    }
    else
    {
        std::cout << +result << std::endl; 
    }
}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps);
    std::cout << +result << std::endl;

    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);
    if (result == 0)
    {
        std::cout << "Underflow prevented" << std::endl;
    }
    else
    {
        std::cout << +result << std::endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu