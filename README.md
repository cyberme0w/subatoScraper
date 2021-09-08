# subatoScraper
This scraper was made with the intention of learning a bit about bash. I'm currently porting it to C though, since I would like to make it portable to both Windows and Linux.

The scraper loops over a given range of numbers and cURLs the respective Subato Sheet.
The scraper then checks if the content matches a valid sheet and saves it in its cache (just text entries in a file). The output of the scraper is currently only:
* Module Name
* Exercise Name
* Exercise Number

but might be extended in the future.


# Arguments
It is possible to pass certain arguments to change the scraper's behaviour:
* `-h (--help)` Show this help message.
* `-n (--min)` Set the lower limit for scraping (inclusive)
  * Usage: `subatoScraper -n 5` (scrapes sheets 5 - infinity)
* `-x (--max)` Set the upper limit for scraping (inclusive)
  * Usage: `subatoScraper -x 10` (scrapes sheets 0-10)
* `-p (--path)` Set the path to the 'sheets' folder
  * Usage: `subatoScraper -p ./scraper/` will create the folder `./scraper/sheets/` and store results in there. (TODO)
* `-c (--no-cache)` Ignore cached sheets in `PATH/sheets/` folder. 
  * Standard behaviour is to **not** check cached sheets.
* `-d (--delay)` Set the delay in milliseconds between each request.
  * Usage: `subatoScraper -d 500` (set delay to 500ms).
  * Standard is no delay, which might be too spammy when looping over large ranges.
* `-v (--verbose)` Set verbose output.
* `-s (--savecontent)` Download the .zip files from the exercise sheet.
