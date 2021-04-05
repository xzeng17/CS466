#include "fastaloader.h"

FastaLoader::FastaLoader(string& filename) {
    filename_ = filename;
    load();
}