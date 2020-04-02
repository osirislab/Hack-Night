/*
 *  Symbolic Execution Pseudocode Example
 *
 *      Demonstrates how a symbolic executor would
 *      represents symbolic expressions and path constraints during
 *      its execution.
 */


void foo(int z)
{
    fail("%d is less than 10! Bad!", z);
}


void bar(int z)
{
    doSomething(z);
    exitSuccessfully();
}


int main(int argc, char *argv[])
{
    int x = int(argv[0]);
    int y = int(argv[1]);

    int z = x + y
    if (x < 5 && y < 5)
        foo(z)
    else
        bar(z)
}
