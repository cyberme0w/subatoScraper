#include <stdbool.h>

typedef struct {
    char *moduleName;
    char *sheetTitle;
    char *sheetNumber;
} ExerciseSheet;

bool isValidSubatoHTML(char *html);

ExerciseSheet extractSheetFromHTML(char *html, bool verbose);

