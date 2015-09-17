/*
 * Scans ports on a given IP
 * */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <SFML/Network.hpp>
#include <sstream>
#include <string>
#include <vector>

static bool port_is_open(const std::string& address, int port)
{
    return (sf::SocketTCP().connect(address, port) == sf::Socket::Done);
}

static std::vector<std::string> split(const std::string& string,
                                      char delimiter = ' ',
                                      bool allow_empty = false)
{
    std::vector<std::string> tokens;
    std::stringstream sstream(string);
    std::string token;
    while (std::getline(sstream, token, delimiter)) {
        if (allow_empty || token.size() > 0)
            tokens.push_back(token);
    }
    return tokens;
}

static int string_to_int(const std::string& string)
{
    std::stringstream sstream(string);
    int i;
    sstream >> i;
    return i;
}

template <typename T>
static void swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

template <typename T>
static std::vector<T> range(T min, T max)
{
    if (min > max)
        swap(min, max);
    if (min == max)
        return std::vector<T>(1, min);
    std::vector<T> values;
    for (; min <= max; ++min)
        values.push_back(min);
    return values;
}

static std::vector<int> parse_ports_list(const std::string& list)
{
    std::vector<int> ports;
    for (const std::string& token : split(list, ',')) {
        std::vector<std::string> strrange = split(token, '-');
        switch (strrange.size()) {
            case 0: ports.push_back(string_to_int(token));       break;
            case 1: ports.push_back(string_to_int(strrange[0])); break;
            case 2:
            {
                int min = string_to_int(strrange[0]),
                    max = string_to_int(strrange[1]);
                for (int port : range(min, max))
                    ports.push_back(port);
                break;
            }
            default:
                break;
        }
    }
    return ports;
}

template <typename T>
static T maximum(const std::vector<T>& values)
{
    T max = values[0];
    for (T value : values) {
        if (value > max)
            max = value;
    }
    return max;
}

template <typename T>
static size_t digits(T value)
{
    size_t count = (value < 0) ? 1 : 0;
    if (value == 0)
        return 0;
    while (value) {
        value /= 10;
        ++count;
    };
    return count;
}

int main(int argc, char* argv[])
{
    std::string address;
    std::vector<int> ports;
    if (argc == 3) {
        address = argv[1];
        ports = parse_ports_list(std::string(argv[2]));
    } else {
        std::string port_list;
        std::cout << "Address: " << std::flush;
        std::getline(std::cin, address);
        std::cout << "Port: " << std::flush;
        std::getline(std::cin, port_list);
        ports = parse_ports_list(port_list);
    }
    std::cout << "Showing open ports on " << address << "...\n";
    size_t width = digits(maximum(ports));
    for (int port : ports) {
        if (port_is_open(address, port))
            std::cout << "Port " << std::setw(width) << port << " : OPEN\n";
    }
    std::cout << std::flush;
    return 0;
}
