/* Author: Sarah Spence
 * Date: 07/19/2021
 * Title: Module Four Assignment -Exceptions 
 */

#include <iostream>
#include <exception>

// Create a custom exception class that inherits from std::exception
class Exception1 : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "This is a custom exception derived from std::exception";
    }
};

bool do_even_more_custom_application_logic()
{
    // Throw any standard exception
    // I threw a bad exception here because this type of exception handles unexpected exceptions in a C++ program. Since this function only
    // contains a print statement, this seemed like a good exception choice for this scenario. 
    throw std::bad_exception();
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    
    return true;
}
void do_custom_application_logic()
{
    // Wrap the call to do_even_more_custom_application_logic()
    //  With an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing

    std::cout << "Running Custom Application Logic." << std::endl;
 
    // Wrap the call to do_even_more_custom_application_logic() in a try/catch block
    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::bad_exception& ex)
    {
        // Catch the std::bad_exception thrown from the function call and display a message about the caught exception. 
        std::cerr << "Caught an exception of type: " << ex.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    throw Exception1();

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    // I used a runtime error to handle division by zero
    if (den == 0)
    {
        throw std::runtime_error("Illegal Operation: Cannot divide by zero.");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  Create an exception handler to capture ONLY the exception thrown
    //  by divide.
    float numerator = 10.0f;
    float denominator = 0;

    /* Wrap the division function call in a try block. The result message only prints if the division was not by zero.
     * I left the print message to display results in the try block because the result variable was also declared in the try block. 
     * The print statement would not be able to access result if it were not in the try block as well.*/
    try {
        auto result = divide(numerator, denominator); 
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::runtime_error& ex)
    {
        // I created the exception message in the throw clause for this exception. The message displays with the call to ex.what()
        std::cout << ex.what() << std::endl;
    }
}

int main()
{
    try {
        std::cout << "Exception Tests!" << std::endl;

        // Create exception handlers that catch (in this order):
        //  your custom exception
        //  std::exception
        //  uncaught exception 
        //  that wraps the whole main function, and displays a message to the console.
        do_division();
        do_custom_application_logic();
    }
    catch (const Exception1& ex1)
    {
        std::cerr << ex1.what() << std::endl;
    }
    // Catch std::exception as instructed in TODO above. This will handle any unexpected std::exceptions the program throws. 
    catch (const std::exception& ex2) {
        std::cerr << "Caught an std::exception of type: " << ex2.what() << std::endl;
    }
    // The catch all exception catches all unhandled exceptions in main. The SEI secure coding standards state "this ensures the
    // stack in unwound up to main."
    catch (...)
    {
        std::cerr << "An unexpected exception occured." << std::endl;
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu