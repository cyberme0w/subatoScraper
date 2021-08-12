# subatoScraper
This scraper was made with the intention of learning a bit about bash. However, I would like to port it to C to increase portability.

The script loops over a given range of urls and checks if that url represents a valid exercise sheet, in which case it grabs the module name, exercise name and number and echoes them on the terminal.

No harm intended. 

# TODO:
* Each curl is taking quite some time - find out why.
* Look into multithreading to parallelize curls.
* Add flag `-o filename` to create text file with output.
* Add silent flag `-s` to stop output to stdout.
