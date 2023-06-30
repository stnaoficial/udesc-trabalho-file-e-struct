#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ------------------------------------------------------------------------------------

#include "flib.h"

struct Artist {
    char name[255];
    char nationality[255];
};

struct Date {
    int day;
    int month;
    int year;
};

struct Music {
    char name[255];
    int duration;
    char style[255];
    struct Artist artist;
    struct Date date;
};

// ------------------------------------------------------------------------------------

// void insertMusic(Music *m) {
//     int opt;
//     scanf("%d", &opt);
// }

// void deleteMusic(void *name, Music *m) {

// }

// void listMusics(Music *m) {

// }

// void readMusic(int *name, Music *m) {
    
// }

// ------------------------------------------------------------------------------------

void request(int *req) {
    printf("\nAVAILABLE OPTIONS\n\n");
    printf("1 - Create music\n");
    printf("2 - Delete music\n");
    printf("3 - List musics\n");
    printf("4 - Read music\n");
    printf("5 - Quit\n");

    printf("\nREQUEST:: ");
    scanf("%d", req);
}

int error(const char *message) {
    printf("\nERROR:: %s\n\n", message);
    return EXIT_FAILURE;
}

int response(const char *message) {
    printf("\nRESPONSE:: %s\n\n", message);
    return EXIT_SUCCESS;
}

// ------------------------------------------------------------------------------------

int main(int argc, char const *argv[]) {
    // FILE *file;

    // file = fopen("./database.txt", "r+");

    // if (file == NULL)
    // {
    //     return EXIT_FAILURE;
    // }

    // struct Date date = { 30, 6, 2023 };

    // fwrite(&date, sizeof(struct Date), 1, file);

    // fclose(file);

    // print_file(file);

    int *req; while(1) { request(req); // Input a request value
        switch(*req) {
            case 1:
                /* code */
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;

            case 5:
                return response("bye!"); // Output a response message
            
            default:
                return error("invalid option"); // Output an error message
        }
    }

    return EXIT_SUCCESS;
}
