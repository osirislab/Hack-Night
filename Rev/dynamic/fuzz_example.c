/*
 * fuzz_pseudocode.c
 *
 *      Example test harness for a fuzzer, demonstrating
 *      how we would implement a test case that can help
 *      our fuzzer maximize program coverage.
 *
 */

#include <my_json_impl.h>


/*
 * JSON file -> Object -> JSON dump 1
 *
 *  Check if JSON file == JSON dump
 *
 */

int main(int argc, char *argv[])
{
    /* `argv[1]` is a JSON input test we read from */
    char *input = readFromFile(argv[1]);
    size_t size = getFileInputSize(argv[1]);

    /* Parse our input, and an initial validation check */
    json_t *object = json_parse(input, size);
    object.validate();

    /* Dump back as a string */
    char *dump_output = object.dump();
    size_t dump_size = object.dump_size();

    /* Check against our original input! */
    CHECK(input, dump_output);
    exitSuccessfully();
}
