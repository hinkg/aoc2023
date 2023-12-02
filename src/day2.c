#include "common.c"

static file_t input;

const char *cube_colors[3] = {
    "red",
    "green",
    "blue",
};

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int to_digit(char c) {
    return c - '0';
}

int parse_number(char **c) {
    int out = 0;

    while (is_digit(**c)) {
        out *= 10;
        out += to_digit(**c);
        *c += 1;
    }

    return out;
}

int parse_color(char *c) {
    for (int i = 0; i < 3; i++) {
        int len = strlen(cube_colors[i]);

        if (c + len >= (input.data + input.size)) {
            continue;
        }

        if (strncmp(cube_colors[i], c, len) == 0) {
            return i;
        }
    }

    return -1;
}

void part_1(void) {
    int max_counts[3] = {
        12, // red
        13, // green
        14, // blue
    };

    int set_counts[3] = { 0, 0, 0 };

    int last_parsed_number = 0;
    int game_id = 0;
    int game_is_impossible = 0;

    int id_sum = 0;

    for (char *c = input.data; c < (input.data + input.size); c += 1) {
        if (is_digit(*c)) {
            // moves pointer to the char after the parsed number
            last_parsed_number = parse_number(&c);
        }

        if (*c == ':') {
            game_id = last_parsed_number;
            continue;
        }

        if (*c == ';' || *c == '\n') {
            if (set_counts[0] > max_counts[0] ||
                set_counts[1] > max_counts[1] ||
                set_counts[2] > max_counts[2]) {

                game_is_impossible = 1;
            }

            set_counts[0] = 0;
            set_counts[1] = 0;
            set_counts[2] = 0;
        }

        if (*c == '\n') {
            if (!game_is_impossible) {
                id_sum += game_id;
            }

            game_is_impossible = 0;

            continue;
        }

        int color = parse_color(c);

        if (color != -1) {
            set_counts[color] += last_parsed_number;
            continue;
        }

    }

    printf("Output (Part 1): %i\n", id_sum);
}

void part_2(void) {
    int set_counts[3] = { 0, 0, 0 };

    int last_parsed_number = 0;
    int pow_sum = 0;

    for (char *c = input.data; c < (input.data + input.size); c += 1) {
        if (is_digit(*c)) {
            // moves pointer to the char after the parsed number
            last_parsed_number = parse_number(&c);
        }

        if (*c == '\n') {
            pow_sum += set_counts[0] * set_counts[1] * set_counts[2];

            set_counts[0] = 0;
            set_counts[1] = 0;
            set_counts[2] = 0;

            continue;
        }

        int color = parse_color(c);

        if (color != -1) {
            set_counts[color] = MAX(set_counts[color], last_parsed_number);
            continue;
        }
    }

    printf("Output (Part 2): %i\n", pow_sum);
}

int main(void) {
    int read_err = file_load(&input, "input/day2");
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
