#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>

// Settings
int minnum;
int maxnum;
int curnum;
char strModule[64];
char strTitle[64];
char* pathToCWD;
int pathToCWD_len;

// Helpful vars
char* strURL = "https://procomp.cs.hs-rm.de/subato/ExerciseSheet/";
char* htmlStrCourse = "<span id=\"course\">";
char* htmlStrClose = "</span>";
char* htmlStrNum = "<span id=\"number\">";
char* htmlStrExSheet = "<span id=\"exerciseSheet\">";
int curArg;
CURL* curl;
CURLcode res;
bool ignoreCache;
bool verbose;

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  // from https://curl.se/libcurl/c/getinmemory.html
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct*) userp;

  char* ptr = realloc(mem->memory, mem->size + realsize + 1);

  if(!ptr) {
    // out of memory
    printf("Not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

bool isNumber (char* str) {
  while(*str != 0) {
    if(*str < 48 || *str > 57) return false;
    str++;
  }
  return true;
}

int stringToNumber (char* str) {
  int res = 0;
  while(*str != 0) {
    res *= 10;
    res += *str - 48;
    str++;
  }
  return res;
}

int main(int argc, char** argv) {

  // Set default settings
  getcwd(pathToCWD, pathToCWD_len);
  minnum = 0;
  maxnum = 0;
  curnum = 0;
  curArg = 1;
  verbose = false;
  ignoreCache = false;

  // Arguments
  while(curArg < argc) {
    if(verbose) printf("Handling option #%d with content (%s)\n", curArg, argv[curArg]);

    if(strcmp(argv[curArg], "-h") == 0 || strcmp(argv[curArg], "--help") == 0) {
      printf("\
Subato Scraper\n\
Scraper for the Subato Exercise Sheets available under subato.org\n\n\
Options:\n\
  -h (--help)     - Show this help message.\n\
  -n (--min)      - Set the lower limit for scraping (inclusive)\n\
                    Usage: subatoScraper -n 5 (scrape sheets 5 - infinity)\n\
  -x (--max)      - Set the upper limit for scraping (inclusive)\n\
                    Usage: subatoScraper -x 10 (scrape sheets 0-10)\n\
  -p (--path)     - Set the path to the 'sheets' folder\n\
                    Usage: subatoScraper -p ./scraper/ will create the folder ./scraper/sheets/ and store results in there.\n\
  -c (--no-cache) - Ignore cached sheets in sheets/ folder. Standard behaviour is to not check cached sheets.\n\
  -d (--delay)    - Set the delay in milliseconds between each request.\n\
                    Usage: subatoScraper -d 500 will set delay to 500ms. Standard is 1500ms which gives ~100 sheets per minute.\n\
  -v (--verbose)  - Set verbose output.\n");
      exit(0);
    }

    else if(strcmp(argv[curArg], "-n") == 0 || strcmp(argv[curArg], "--min") == 0) {
      curArg++;
      if(curArg < argc && isNumber(argv[curArg])) {
        minnum = stringToNumber(argv[curArg]);
        curnum = minnum;
        curArg++;
      }
      else {
        printf("ERR: Option -n / --min was used without providing a valid number. Aborting.\n");
        exit(101);
      }
    }

    else if(strcmp(argv[curArg], "-x") == 0 || strcmp(argv[curArg], "--max") == 0) {
      curArg++;
      if(curArg < argc && isNumber(argv[curArg])) {
        maxnum = stringToNumber(argv[curArg]);
        curArg++;
      }
      else {
        printf("ERR: Option -x / --max was used without providing a valid number. Aborting.\n");
        exit(101);
      }
    }

    else if(strcmp(argv[curArg], "-v") == 0 || strcmp(argv[curArg], "--verbose") == 0) {
      verbose = true;
      curArg++;
    }

    else if(strcmp(argv[curArg], "-c") == 0 || strcmp(argv[curArg], "--no-cache") == 0) {
      ignoreCache = true;
      curArg++;
    }

    else {
      printf("ERR: Unknown argument '%s'. Aborting.\n", argv[curArg]);
      exit(102);
    }
  }

  // Init memory chunk for curl results
  struct MemoryStruct chunk;
  chunk.memory = malloc(1); // will be grown as necessary with realloc
  chunk.size = 0; // no data yet

  // Scraping
  printf("Subato Scraper is starting...\n  min: %d\n  max: %d\n  delay: TODO\n  path: TODO\n  verbose: %d\n  ignoreCache: %d\n\n",
         minnum, maxnum, verbose, ignoreCache);

  if(verbose) printf("Entering for loop to curl\n");

  curl = curl_easy_init();

  if(curl) {
    if(verbose) printf("Starting curl\n");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    for(; curnum <= maxnum; curnum++) {
      //Allocating memory for current url
      int length = snprintf(NULL, 0, "%d", curnum);
      char str_curnum[length];

      //Converting curnum to string to append
      sprintf(str_curnum, "%d", curnum);

      //Appending curnum to url
      char url[50];
      strcpy(url, strURL);
      strcat(url, str_curnum);

      // run curl
      curl_easy_setopt(curl, CURLOPT_URL, url);
      res = curl_easy_perform(curl);

      // check for errors
      if(res != CURLE_OK) {
        printf("WAR: Curl returns non-ok status\n%s", curl_easy_strerror(res));
      } else {
        printf("%lu bytes retrieved\n from URL: %s\n", (unsigned long)chunk.size, url);
        //printf("%s", chunk.memory);

        /*
            do the html processing here
        */

      }
      free(chunk.memory);
    }
  }

  // cleanup
  curl_easy_cleanup(curl);
  free(pathToCWD);
  //free(strURL);
  //free(htmlStrCourse);
  //free(htmlStrClose);
  //free(htmlStrNum);
  //free(htmlStrExSheet);
  //free(curl);
}
