# Syscalls

## Assumptions
### Question 1
* The process of closing files is considered non-fatal, and so the program is continued even if any of the `close(fd)` encounter error.
* The second assumption is that data is being written in chunks, and thus the progress should move accordingly(in chunks).
* The number of bytes in the file can fit in a `long long` variable.
* It is assumed that if the file/directory already exist, then their permissions haven't been tampered with.
* It is assumed that the pwd has 0700 permissions already, otherwise its sub-directories cannot get appropriate permissions.
* It is assumed that the file name would be present after the last `/` in the file path.
* Atleast 1 MB of RAM is available to the program.
* It is assumed that the program is run from the directory where `Assignment` directory is to be created.

### Question 2
* The process of closing files is considered non-fatal, and so the program is continued even if any of the `close(fd)` encounter error.
* The second assumption is that data is being written in chunks, and thus the progress should move accordingly(in chunks).
* The number of bytes in the file can fit in a `long long` variable.
* It is assumed that if the file/directory already exist, then their permissions haven't been tampered with.
* It is assumed that the pwd has 0700 permissions already, otherwise its sub-directories cannot get appropriate permissions.
* It is assumed that the file name would be present after the last `/` in the file path.
* Atleast 1 MB of RAM is available to the program.
* It is assumed that the two numbers given would be single digit.
* It is assumed that the part number would be >0.
* It is assumed that the program is run from the directory where `Assignment` directory is to be created.

### Question 3
* It is assumed that the `Assignment` directory is inside the directory from where the program is executed.
* It is assumed that the file name is after the last `/` in the path.
* It is assumed that the `1_` and `2_` files would have the same initial file used for creation.
* It is safe to assume that if the directory doesn't exist, then both files won't exist as well.

