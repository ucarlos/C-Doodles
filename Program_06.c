//
// Created by ulysses on 5/20/17.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
typedef struct {
    unsigned int font_id: 8;
    unsigned int font_size: 4;
    unsigned int alignment: 2;
    unsigned int bold: 1;
    unsigned int italic: 1;
    unsigned int underline: 1;

}Font;
const char *menu_options = "f)Change Font\ts)Change Size\t\ta)Change Alignment\n"
                           "b)Toggle Bold\ti)Toggle Italics\tu)Toggle Underline\n"
                            "q)Quit\n";
void main_menu(Font font);
void change_font(Font font);
void change_alignment(Font font);
void change_size(Font font);
void change_bold(Font font);
void change_italic(Font font);
void change_underline(Font font);
void display_font_attributes(Font font);
void clear_buffer(void);
void print_dash_line(void);

// Driver Function
int main(void){ //Use a terminal.
    Font font1 = {1, 12, 0, 0, 0, 0};
    main_menu(font1);
    return 0;
}

// Structure Functions

void print_dash_line(void){
    for (int i = 0; i < 80; i++)
        putchar('-');
    printf("\n");
};

void display_font_attributes(Font font){
    printf("Font_id\t Size\tAlignment\tBold\t\tItalic\t\tUnderline\n");
    printf("%u\t %u\t", font.font_id, font.font_size);
    printf((font.alignment == 2)?"Right\t\t":
           (font.alignment == 1)?"Center\t\t": "Left\t\t");
    printf((font.bold)? "On\t\t" : "Off\t\t");
    printf((font.italic)? "On\t\t": "Off\t\t");
    printf((font.underline)? "On\n\n": "Off\n\n");

}
void main_menu(Font font){
    system("clear");
    char input;
    void (*fpointer)(Font font1);
    
    print_dash_line();
    display_font_attributes(font);
    print_dash_line();
    
    puts("Press the appropriate key to select an option.");
    puts(menu_options);

    scanf("%c", &input);
    switch(input){
        case 'f': fpointer = change_font;break;
        case 's': fpointer = change_size;break;
        case 'a': fpointer = change_alignment;break;
        case 'b': fpointer = change_bold;break;
        case 'i': fpointer = change_italic;break;
        case 'u': fpointer = change_underline;break;
        case 'q': exit(EXIT_SUCCESS);
    default: // Can't display invalid input
            fpointer = main_menu;
            break;
    }
    fpointer(font);

}

void change_font(Font font){
    system("clear");
    clear_buffer();
    void (*fpointer)(Font font1) = main_menu;
    unsigned int tempfont_id;
    printf("Enter the new font id. The number must be in between 0 and 255.");
    scanf("%u", &tempfont_id);

    if (!(0 <= tempfont_id && tempfont_id <= 255))
        tempfont_id &= 255; // For example, if my number is 257(1 0000 0001), AND with 255 will produce
        //1 0000 0001 AND
        //0 1111 1111
    //==  0 0000 0001 , which is 1.

    font.font_id = tempfont_id;

    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void change_size(Font font){
    system("clear");
    clear_buffer();
    void (*fpointer)(Font font) = main_menu;
    unsigned int tempfont_size;
    printf("Enter the new font size. The number must in between 0 and 128.");
    scanf("%u", &tempfont_size);

    if (!(0 <= tempfont_size && tempfont_size <= 127))
        tempfont_size &= 127;
    font.font_size = tempfont_size;

    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void change_alignment(Font font){
    system("clear");
    clear_buffer();
    void (*fpointer)(Font font) = main_menu;
    unsigned int tempalign;
    printf("Choose Alignment: Left(0)\tCenter(1)\tRight(2)\n");
    scanf("%u", &tempalign);
    while (!(0 <= tempalign && tempalign <= 2)){
        printf("Invalid Alignment number. Try again.");
        scanf("%u", &tempalign);
    }
    font.alignment = tempalign;
    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void change_bold(Font font){
    system("clear");
    clear_buffer();
    void (*fpointer)(Font font) = main_menu;
    unsigned int bold;
    puts("Bold Options:\tOn(1)\tOff(0)");
    scanf("%u", &bold);
    if (!(bold == 0 || bold == 1)){
        printf("Invalid Number. Defaulting to Off.");
        bold &= 0;
    }
    font.bold = bold;
    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void change_italic(Font font){
    system("clear");
    clear_buffer();
    unsigned int italic;
    void (*fpointer)(Font font) = main_menu;
    puts("Italics Options:\tOn(1)\tOff(0)");
    scanf("%u", &italic);
    if (!(italic == 0 || italic == 1)) {
        printf("Invalid number. Defaulting to Off.");
        italic &= 0;
    }
    font.italic = italic;
    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void change_underline(Font font){
    system("clear");
    clear_buffer();
    unsigned int underline;
    void (*fpointer)(Font font) = main_menu;
    printf("Underline options:\tOn(1)\tOff(0)\n");
    scanf("%u", &underline);
    if (!(underline == 0 || underline == 1)){
        printf("Invalid number. Defaulting on Off.");
        underline &= 0;
    }
    font.underline = underline;
    printf("Returning to main menu.\n");
    sleep(1);
    fpointer(font);
}

void clear_buffer(void){
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
