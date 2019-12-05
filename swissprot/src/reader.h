#ifndef SWISSPROT_READER_H
#define SWISSPROT_READER_H

namespace swissprot {
    extern void read(const char* filename, void (*cb)(void*));
}
#endif