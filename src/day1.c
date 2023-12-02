#include "common.c"

static file_t input;

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int to_digit(char c) {
    return c - '0';
}

void part_1(void) {
    char first = 0;
    char last  = 0;

    int sum = 0;

    for (usize i = 0; i < input.size; i++) {
        char c = input.data[i];

        if (c == '\n') {
            sum += (int)(first) * 10 + (int)(last);
            first = 0;
            continue;
        }

        if (is_digit(c)) {
            if (first == 0) {
                first = to_digit(c);
            }

            last = to_digit(c);
        }
    }

    printf("Output (Part 1): %i\n", sum);
}

static const char* spelled_digits[9] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

void part_2(void) {
    char first = 0;
    char last  = 0;

    int sum = 0;

    for (usize i = 0; i < input.size; i++) {
        char c = input.data[i];

        if (c == '\n') {
            sum += (int)(first) * 10 + (int)(last);
            first = 0;
            last  = 0;
            continue;
        }

        if (is_digit(c)) {
            if (first == 0) {
                first = to_digit(c);
            }

            last = to_digit(c);

            continue;
        }

        for (usize j = 0; j < 9; j++) {
            const char* sd = spelled_digits[j];
            usize len = strlen(sd);

            if (i + len > input.size) continue;

            if (strncmp(input.data + i, sd, len) == 0) {
                if (first == 0) {
                    first = j + 1;
                }

                last = j + 1;

                break;
            }
        }
    }

    printf("Output (Part 2): %i\n", sum);
}

int main(void) {
    int read_err = file_load(&input, "input/day1");
    if (read_err) return 1;

    i64 start, end;

    start = time_tick_now();
    part_1();
    end = time_tick_now();
    printf("Time (Part 1): %.1fus\n", time_microseconds(end - start));

    start = time_tick_now();
    part_2();
    end = time_tick_now();
    printf("Time (Part 2): %.1fus\n", time_microseconds(end - start));

    file_free(&input);

    return 0;
}
