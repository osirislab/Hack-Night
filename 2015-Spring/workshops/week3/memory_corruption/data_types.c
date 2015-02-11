
void primitive_data_types() {
    // Signed data types
    char a_char;            // 1 byte [-128 to 128]
    short a_short;          // 2 bytes [-256 to 256]
    long a_long;            // 4 bytes [-(2^32)/2 to (2^32)/2]
    long long a_long_long;  // 8 bytes [-(2^64)/2 to (2^64)/2]
    float a_float;          // 4 bytes [number and a decimal (single precision)]
    double a_double;        // 8 bytes [number and a decimal (double precision)]

    // Same number of bytes as signed numbers
    // but you do not get negative numbers
    unsigned char a_unsigned_char;           // 1 byte [0 to 256]
    unsigned short a_unsigned_short;         // 2 bytes [0 to 512]
    unsigned long a_unsigned_long;           // 4 bytes [0 to 2^32]
    unsigned long long a_unsigned_long_long; // etc.
    unsigned float a_unsigned_float;
    unsigned double a_unsigned_double;

    // Collections of primitive data types
    struct a_struct;
    enum a_enum;
    union a_union;

    void a_void;

    // typedef of unsigned int
    size_t a_size_t;
}

void arrays() {
    // A bunch of characters next to each other
    char[] a_char_array;
    a_char_array = "Some words go here";
}

void pointers() {
    // x points to an integer 
    int* x;
}
