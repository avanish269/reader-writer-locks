# Reader-Writer Locks
Implemented two versions of reader-writer locks(reader-preference lock and writer-preference lock). The writer has exclusive access to the data.

There are two scripts (run_reader_pref.sh and run_writer_pref.sh) that run these programs with with some arguments. Inside the .sh files, the executables are followed by two arguments which represents number of reader and writer threads created. For example, ./rwlock-writer-pref 5 2 creates 5 reader threads followed by 2 writer threads and then lastly by additional 5 reader threads.
