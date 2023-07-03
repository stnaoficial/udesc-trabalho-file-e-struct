#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define TARGET_FILE "database.bin"
#define MAX_NAME_SIZE 100
#define MAX_STYLE_SIZE 100
#define MAX_ARTIST_NAME_SIZE 100
#define MAX_ARTIST_NATIONALITY_SIZE 100

// ------------------------------------------------------------------------------------

// }
// { Structs

struct Artist {
    char name[MAX_ARTIST_NAME_SIZE];
    char nationality[MAX_ARTIST_NATIONALITY_SIZE];
};

struct Date {
    int day;
    int month;
    int year;
};

struct Music {
    char name[MAX_NAME_SIZE];
    int duration;
    char style[MAX_STYLE_SIZE];
    struct Artist artist;
    struct Date date;
};

// ------------------------------------------------------------------------------------

// }
// { Interfaces

void read_artist(struct Artist *a);
void read_date(struct Date *d);
struct Music* load_musics(int *c);
struct Music* read_music(struct Music *m, int c);
void show_musics(struct Music *m, int c);
void store_music(struct Music *m, int c);

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
    FILE *file = fopen(TARGET_FILE, "rb");

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
struct Music* read_music(struct Music *m, int c) {
    m = (struct Music*)realloc(m, (c + 1) * sizeof(struct Music));

    printf("\nEnter music name: ");
    scanf("%s", m[c].name);

    printf("Enter music duration (in seconds): ");
    scanf("%d", &(m[c].duration));

    printf("Enter music style: ");
    scanf("%s", m[c].style);

    read_artist(&(m[c].artist));
    read_date(&(m[c].date));

    return m;
}

// Function to display all music entries
void show_musics(struct Music *m, int c) {
    printf("\nMUSIC LIST\n\n");

    for (int i = 0; i < c; i++) {
        printf("Music %d\n", i + 1);
        printf("Name: %s\n", m[i].name);
        printf("Duration: %d seconds\n", m[i].duration);
        printf("Style: %s\n", m[i].style);
        printf("Artist: %s\n", m[i].artist.name);
        printf("Nationality: %s\n", m[i].artist.nationality);
        printf("Date: %d/%d/%d\n\n", m[i].date.day, m[i].date.month, m[i].date.year);
    }
}

// Function to store music data in the binary file
void store_music(struct Music *m, int c) {
    FILE *file = fopen(TARGET_FILE, "wb");

    if (file == NULL) {
        printf("Failed to open file for writing.");
        return;
    }

    fwrite(&c, sizeof(int), 1, file);
    fwrite(m, sizeof(struct Music), c, file);

    fclose(file);
}

void delete_music(struct Music *m, int *c) {
    int index;
    
    printf("Enter the index of the music to delete: ");
    scanf("%d", &index);
    
    if (index < 1 || index > *c) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index - 1; i < *c - 1; i++) {
        m[i] = m[i + 1];
    }
    
    (*c)--;
    
    printf("Music deleted successfully.\n");
}

void read_music_details(struct Music *m, int c) {
    int index;
    
    printf("Enter the index of the music to read: ");
    scanf("%d", &index);
    
    if (index < 1 || index > c) {
        printf("Invalid index.\n");
        return;
    }
    
    index--;
    
    printf("\nMusic %d\n", index + 1);
    printf("Name: %s\n", m[index].name);
    printf("Duration: %d seconds\n", m[index].duration);
    printf("Style: %s\n", m[index].style);
    printf("Artist: %s\n", m[index].artist.name);
    printf("Nationality: %s\n", m[index].artist.nationality);
    printf("Date: %d/%d/%d\n\n", m[index].date.day, m[index].date.month, m[index].date.year);
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
                musics = read_music(musics, count);
                count++;
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
