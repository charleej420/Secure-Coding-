#include <iostream>
#include <stdexcept> // Include the header for std::exception

// Step 1: Create a custom exception derived from std::exception
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception: Something went wrong.";
    }
};

bool do_even_more_custom_application_logic() {
    // TODO: Throw any standard exception
    throw std::runtime_error("Standard Exception: An error occurred.");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic() {
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    // with an exception handler that catches std::exception, displays
    // a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    // and catch it explicitly in main
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den) {
    // TODO: Throw an exception to deal with divide by zero errors using
    // a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("Standard Exception: Divide by zero error.");
    }
    return (num / den);
}

void do_division() noexcept {
    // TODO: create an exception handler to capture ONLY the exception thrown
    // by divide.
    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        // TODO: Create exception handlers that catch (in this order):
        // your custom exception
        // std::exception
        // uncaught exception
        // that wraps the whole main function, and displays a message to the console.
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& e) {
        std::cerr << "Caught Custom Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught Unhandled Exception." << std::endl;
    }

    return 0;
}
