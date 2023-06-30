void print_file(FILE *file)
{
    int c;

    while(1)
    {
        c = fgetc(file);
        
        if(feof(file))
        { 
            break;
        }
        
        printf("%c", c);
    }
}