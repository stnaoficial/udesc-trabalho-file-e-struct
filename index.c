#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ------------------------------------------------------------------------------------

#include "flib.h"

struct Artist {
    char* name;
    char* nationality;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Music {
    char* name;
    int duration;
    char* style;
    struct Artist artist;
    struct Date date;
};

// ------------------------------------------------------------------------------------

void insertMusic(struct Music *m, int q) {
    // int opt;
    // scanf("%d", &opt);

    FILE *f1 = fopen("database.txt","a+t");
    if (f1 == NULL) 
    {
        printf("An error has occurred while trying to open the file.\n");
        exit(0);
    }

    fprintf(
        f1, "%s\t%s\t%d\t%d\t%d\n", 
        m[q-1].name, m[q-1].duration, m[q-1].style,
        m[q-1].artist.name, m[q-1].artist.nationality, 
        m[q-1].date.day, m[q-1].date.month, m[q-1].date.year
    );

    fclose(f1);
}

// void deleteMusic(void *name, Music *m) {

// }

// void listMusics(Music *m) {

// }

// void readMusic(int *name, Music *m) {
    
// }

// ------------------------------------------------------------------------------------

struct Music* load_musics(struct Music *m, int *q);
struct Music* read_music(struct Music *m, int q);
void store_music(struct Music *m, int q);
void read_artist(struct Artist *a);

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

    struct Music *m;
    int q = 0;
    m = NULL;

    m = load_musics(m, &q); 
    
    int *req; while(1) { request(req); // Input a request value
        switch(*req) {
            case 1:
                // inserir uma nova musica
                q++;
                m = read_music(m, q); 
                store_music(m, q);

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
                return response("Bye!"); // Output a response message
            
            default:
                return error("Invalid option"); // Output an error message
        }
    }

    return EXIT_SUCCESS;
}

struct Music* load_musics(struct Music *m, int *q)
{
    int i = 0, x;

    printf("\nLoading file with stored musics.");
    FILE *f1 = fopen("database.txt","a+t");

    if (f1 == NULL)
    {
        printf("An error has occurred while trying to open the file.\n");
        exit(0);
    }

    m = (struct Music*)realloc(m, sizeof(struct Music));

    if (m == NULL) 
    {
        printf("An error has occurred while trying to reallocate.");
        exit(0);
    }

    x = fscanf(
        f1, "%s %s %d %d %d", 
        m[i].name, m[i].duration, m[i].style,
        m[i].artist.name, m[i].artist.nationality
    ); 

    while(x !=EOF)
    {
        i++;
        m = (struct Music*) realloc(m, sizeof(struct Music) * (i+1));

        if (m == NULL) 
        {
            printf("An error has occurred while trying to reallocate.");
            exit(0);
        }

        x = fscanf( 
            f1, "%s %s %d %d %d", 
            m[i].name, m[i].duration, m[i].style,
            m[i].artist.name, m[i].artist.nationality
        ); 
    }

    *q = i;

    printf("\n%d musics have been loaded.\n\n", *q);
    fclose(f1);

    return m;
}

struct Music* read_music(struct Music *m, int q)
{
    int i;
    m = (struct Music*) realloc(m, sizeof(struct Music) * q);

    if (m == NULL)
    {
        printf("An error has occurred while trying to reallocate.");
        exit(0);
    }
    else
    {
        fflush(stdin);
        printf("Please, insert information about the music: ");
        printf("Music's name: ");
        fgets(&m[q-1].name, 255, stdin);
        printf("Music's duration: ");
        scanf(m[q-1].duration);
        printf("Musical style: ");
        fgets(&m[q-1].style, 255, stdin);

        printf("Please, insert information about the music's artist:\n");
        read_artist(&m[q-1].artist);
    }

    return m;
}

void show_musics(struct Music *m, int q)
{
    int i;
    printf("\nDados das pessoas cadastradas:\n");
    for(i=0;i<q;i++){
        printf("Nome: %s - ", m[i].name);
        printf("Telefone: %s - ", m[i].duration);
        printf("Style: %s - ", m[i].style);
    }
}

void read_artist(struct Artist *a)
{
    printf("Artist's name: ");
    scanf("%d", &a->name );
    printf("Artist's nationality: ");
    scanf("%d", &a->nationality );
}

// void mostra_data( struct data x ){
//     printf("Nascimento: %2d/%2d/%4d\n", x.dia, x.mes, x.ano);
// }

void store_music(struct Music *m, int q)
{
    FILE *f1 = fopen( "database.txt", "a+t");

    if (f1 == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(0);
    }

    fprintf(
        f1, "%s\t%s\t%d\t%d\t%d\n", 
        m[q-1].name, m[q-1].duration, m[q-1].style,
        m[q-1].artist.name, m[q-1].artist.nationality
    );

    fclose(f1);
}