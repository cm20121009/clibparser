#include "/include/io"
#include "/include/fs"
#include "/include/memory"
int main(int argc, char **argv) {
    if (argc > 1) {
        switch (cd(argv[1])) {
            case 0:
                // put_string("[INFO] Success.\n");
                break;
            case -1:
                set_fg(240, 0, 0);
                put_string("[ERROR] Path not exists.\n");
                restore_fg();
                break;
            case -2:
                set_fg(240, 0, 0);
                put_string("[ERROR] Path is not directory.\n");
                restore_fg();
                break;
        }
    }
    return 0;
}