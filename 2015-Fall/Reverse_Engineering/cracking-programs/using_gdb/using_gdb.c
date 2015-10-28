
int look_imma_function(int parameter1, char* parameter2) {
    return 0xdeadbeef;
}

int main() {
    int x = 0x42;
    char *string = "Cool beans\x00";

    look_imma_function(x, string);

    return 0;
}
