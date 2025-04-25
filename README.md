**Get next line**

get_next_line is a function that reads from a file descriptor and returns the next line each time it is called. It reads the input one line at a time, keeping track of what has already been read. It handles files of any size, supports multiple file descriptors simultaneously, and manages partial reads using a buffer. The function continues returning lines until there is nothing left to read, at which point it returns NULL.
