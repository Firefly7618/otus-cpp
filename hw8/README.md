Simple utility to identy equal Files.
Output: list of equal files, each group divided by an empty string.

Usage:
  -h [ --help ]                Show help
  -i [ --include-dir ] arg     Include directories
  -e [ --exclude-dir ] arg     Exclude directories that match
  -n [ --filename ] arg        Filename interpreted as a POSIX-basic regular 
                               expression
  -l [ --scan-level ] arg (=0) Level of scanning
  -s [ --file-size ] arg (=1)  Minimum file size
  -b [ --block-size ] arg      Block size for reading files
  -a [ --hash ] arg            Hash algorithm used for comparison. Possible 
                               values [crc32, default].


Usage example:
./bayan -b 32 -i test1 test2 -l 1 -e exclude -n "[0-9]*.TXT" -s 4 --hash crc32