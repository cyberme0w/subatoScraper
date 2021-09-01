#include "htmlExtractor.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *modNameTag = "<span id=\"course\">";
char *sheetNumTag = "<span id=\"number\">";
char *sheetTitleTag = "<span id=\"exerciseSheet\">";
char *closingTag = "</span>";

bool isValidSubatoHTML(char *html) {
    /*
        Since all invalid resources return the same
        error message in subato ("Exception (...)")
        we can check if the page is valid or not by
        checking the first word of the html string.
    */
    
    int pos = 0;
    char* bad = "Exception";

    for(pos = 0; pos < 9; pos++) {
        if(html[pos + 29] != bad[pos]) return true;
    }

    return false;
}

ExerciseSheet extractSheetFromHTML(char *html, bool verbose) {
    /*
        There are three elements that need to be
        extracted from the html string. Each of 
        these elements can be found by parsing
        the html looking for specific nodes.
            ModuleName  : <span id="course">
            SheetNumber : <span id="number">
            SheetTitle  : <span id="exerciseSheet">
    */
    
    // Module Name
    char *ptrToModName = strstr(html, modNameTag) + sizeof(char) * 18;
    int lengthModName = strstr(ptrToModName, closingTag) - ptrToModName;
    char modName[lengthModName + 1];
    memcpy(modName, ptrToModName, lengthModName * sizeof(char));
    modName[lengthModName] = '\0';

    if(verbose) printf("Module Name: %s\n", modName);

    // Sheet Number
    char *ptrToSheetNum = strstr(html, sheetNumTag) + sizeof(char) * 18;
    int lengthSheetNum = strstr(ptrToSheetNum, closingTag) - ptrToSheetNum;
    char sheetNum[lengthSheetNum + 1];
    memcpy(sheetNum, ptrToSheetNum, lengthSheetNum * sizeof(char));
    sheetNum[lengthSheetNum] = '\0';

    if(verbose) printf("Sheet Number: %s\n", sheetNum);

    // Sheet Title
    char *ptrToSheetTitle = strstr(html, sheetTitleTag) + sizeof(char) * 25;
    int lengthSheetTitle = strstr(ptrToSheetTitle, closingTag) - ptrToSheetTitle;
    char sheetTitle[lengthSheetTitle + 1];
    memcpy(sheetTitle, ptrToSheetTitle, lengthSheetTitle * sizeof(char));
    sheetTitle[lengthSheetTitle] = '\0';

    if(verbose) printf("Sheet Title: %s\n", sheetTitle);

    ExerciseSheet ex;
    ex.moduleName = modName;
    ex.sheetNumber = sheetNum;
    ex.sheetTitle = sheetTitle;
    return ex;
}
