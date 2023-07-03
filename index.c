#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// ------------------------------------------------------------------------------------

// }
// { Structs

struct Artist {
    char name[100];
    char nationality[100];
};

struct Date {
    int day;
    int month;
    int year;
};

struct Music {
    char name[100];
    int duration;
    char style[100];
    struct Artist artist;
    struct Date date;
};

// ------------------------------------------------------------------------------------

// }
// { Interfaces

void read_artist(struct Artist *a);
void read_date(struct Date *d);
struct Music* load_musics(int *c);
struct Music* read_music(struct Music *m, int *c);
void show_musics(struct Music *m, int c);
void store_music(struct Music *m, int c);
bool is_duplicate(struct Music *m, int count, const char *name);

// ------------------------------------------------------------------------------------

// }
// { Messsages & Dialogs

void ask(int *opt) {
    printf("\nAVAILABLE OPTIONS\n\n");
    printf("1 - Create music\n");
    printf("2 - Delete music\n");
    printf("3 - List musics\n");
    printf("4 - Read music\n");
    printf("5 - Quit\n");

    printf("\nOPTION:: ");
    scanf("%d", opt);
}

// Function to read an artist
void read_artist(struct Artist *a) {
    printf("Enter artist name: ");
    scanf("%s", a->name);

    printf("Enter artist nationality: ");
    scanf("%s", a->nationality);
}

// Function to read a date
void read_date(struct Date *d) {
    printf("Enter day: ");
    scanf("%d", &(d->day));

    printf("Enter month: ");
    scanf("%d", &(d->month));

    printf("Enter year: ");
    scanf("%d", &(d->year));
}

// ------------------------------------------------------------------------------------

// }
// { Methods

// Function to load music data from the binary file
struct Music* load_musics(int *c) {
    FILE *file = fopen("database.bin", "rb");

    if (file == NULL) {
        *c = 0;
        return NULL;
    }

    fread(c, sizeof(int), 1, file);

    struct Music *m = (struct Music*)malloc((*c) * sizeof(struct Music));
    fread(m, sizeof(struct Music), *c, file);

    fclose(file);

    return m;
}

// Function to read a music entry
struct Music* read_music(struct Music *m, int *c) {
    m = (struct Music*)realloc(m, (*c + 1) * sizeof(struct Music));

    char name[100];

    printf("\nEnter music name: ");
    scanf("%s", name);

    // Verifique se o nome da música já existe
    if (is_duplicate(m, *c, name)) {
        printf("Error: Music with the same name already exists.\n");
        return m;
    }

    strcpy(m[*c].name, name);

    printf("Enter music duration (in seconds): ");
    scanf("%d", &(m[*c].duration));

    printf("Enter music style: ");
    scanf("%s", m[*c].style);

    read_artist(&(m[*c].artist));
    read_date(&(m[*c].date));

    (*c)++;

    return m;
}

// Function to display all music entries
void show_musics(struct Music *m, int c) {
    if (c == 0) {
        printf("There are no stored musics\n");
        return;
    }

    printf("\nList of stored musics\n\n");
    printf("Music\t\t\tArtist\t\t\tNacionality\tCreated at\n");
    printf("-------------------\t-----------------------\t---------------\t-------------\n");

    for (int i = 0; i < c; i++) {
        printf("%-20s\t%-23s\t%-15s\t%02d/%02d/%04d\n", m[i].name, m[i].artist.name, m[i].artist.nationality, m[i].date.day, m[i].date.month, m[i].date.year);
    }
}

// Function to store music data in the binary file
void store_music(struct Music *m, int c) {
    FILE *file = fopen("database.bin", "wb");

    if (file == NULL) {
        printf("Failed to open file for writing.");
        return;
    }

    fwrite(&c, sizeof(int), 1, file);
    fwrite(m, sizeof(struct Music), c, file);

    fclose(file);
}

void delete_music(struct Music *m, int *c) {
    char name[100];

    printf("Enter the name of the music to delete: ");
    scanf("%s", name);

    int index = -1;

    for (int i = 0; i < *c; i++) {
        if (strcmp(m[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Music not found.\n");
        return;
    }

    for (int i = index; i < *c - 1; i++) {
        m[i] = m[i + 1];
    }

    (*c)--;

    printf("Music deleted successfully.\n");
}

void read_music_details(struct Music *m, int c) {
    char name[100];

    printf("Enter the name of the music to read: ");
    scanf("%s", name);

    int index = -1;

    for (int i = 0; i < c; i++) {
        if (strcmp(m[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Music not found.\n");
        return;
    }

    printf("\nMusic %d\n\n", index + 1);
    printf("Music\t\t\tArtist\t\t\tNacionality\tCreated at\n");
    printf("-------------------\t-----------------------\t---------------\t-------------\n");
    printf("%-20s\t%-23s\t%-15s\t%02d/%02d/%04d\n", m[index].name, m[index].artist.name, m[index].artist.nationality, m[index].date.day, m[index].date.month, m[index].date.year);
}

bool is_duplicate(struct Music *m, int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(m[i].name, name) == 0) {
            return true; // Já existe uma música com o mesmo nome
        }
    }
    return false; // O nome da música é único
}

// ------------------------------------------------------------------------------------

// }
// { Main

int main(int argc, char const *argv[]) {

    int count = 0;

    struct Music *musics = NULL;

    musics = load_musics(&count);

    int opt; while (true) { ask(&opt);
        switch (opt) {
            case 1:
                musics = read_music(musics, &count);
                break;

            case 2:
                delete_music(musics, &count);
                break;

            case 3:
                show_musics(musics, count);
                break;

            case 4:
                read_music_details(musics, count);
                break;

            case 5:
                store_music(musics, count);
                free(musics);
                return EXIT_SUCCESS;

            default:
                printf("\nERROR:: Invalid option\n\n");
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
