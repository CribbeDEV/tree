#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BBLU "\e[1;34m"
#define CRESET "\e[0m"

void print_file(const char *name, const char *prefix, int is_dir, int is_last) {
    printf("%s", prefix);
    if (is_last == 1) {
        printf("└── ");
    } else {
        printf("├── ");
    }

    if (is_dir)
        printf("%s%s%s\n", BBLU, name, CRESET);
    else
        printf("%s\n", name);
}

int not_dot(const struct dirent *entry) {
    return strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0;
}

int walk(const char *path, const char *prefix) {
    struct dirent **namelist;
    int n;

    n = scandir(path, &namelist, not_dot, alphasort);
    if (n == -1) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        const char *name = namelist[i]->d_name;

        int is_last = (i == n-1);
        int is_dir = (namelist[i]->d_type == DT_DIR);
        print_file(name, prefix, is_dir, is_last);
        if (is_dir == 1) {

            int len = strlen(path) + strlen(name) + 2;
            char sub_path[len];

            snprintf(sub_path, len, "%s/%s", path, name);

            const char *branch = is_last ? "    " : "│   ";
            int prefix_len = strlen(prefix) + strlen(branch) + 1;
            char sub_prefix[prefix_len];

            snprintf(sub_prefix, prefix_len, "%s%s", prefix, branch);

            walk(sub_path, sub_prefix);
        }
        free(namelist[i]);
    }

    free(namelist);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *path = ".";

    if (argc > 1) {
        path = argv[1];
    }

    printf("%s\n", path);

    int err = walk(path, "");

    return err;
}
