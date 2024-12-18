#include <assert.h>
#include <stdio.h>

int sample_function(int a, int b) {
    return a + b; 
}

void test_sample_function() {
    assert(sample_function(2, 3) == 5); 
    assert(sample_function(-1, 1) == 0); 
    printf("All tests passed successfully!\n");
}

int main() {
    test_sample_function();
    return 0;
}

