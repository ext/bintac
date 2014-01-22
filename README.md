Like `tac` (cat reverse) and `rev` but works on bytestream instead of line-by-line.

Usage: `bintac FILES..`

## Example

    % cat test
    foo
    bar
    abc
    % bintac test | hexdump -C
    00000000  0a 0a 63 62 61 0a 72 61  62 0a 6f 6f 66           |..cba.rab.oof|
    0000000d

## TODO

* work with stdin (need to buffer entire stream, cannot work on chunks)
