#include <msp430.h>
#include <stdio.h>
#include <string.h>

typedef unsigned spm_id;

extern spm_id hash_spm(const char* expected_hash, const void* spm_entry);

typedef struct
{
    char hash[64];
    const char* expected_hash;
    long secret;
    const char* public;
    size_t size;
} Spm __attribute__((aligned(2)));

#define INIT_SPM(x, p, h) \
    static const char x##_public[sizeof(p) - 1] __attribute__((aligned(2), section(".data"))) = p; \
    static const char x##_hash[64] __attribute__((aligned(2))) = h; \
    Spm x = {{0}, x##_hash, 0, x##_public, sizeof(x##_public)}

#define TEST_SPM(x) do {puts("Testing SPM " #x); test_spm(&x);} while (0)

// PS(simple, "\xde\xad\xbe\xef");

INIT_SPM(simple,
         "\xde\xad\xbe\xef",
         "\x88\x39\xe9\x9f\xb1\xbb\xb5\x55\x99\xf5\x49\x3e\xdc\x4c\xff\xaa\x53\xf1\xf4\x5f\x7f\xc9\xb8\xa2\x5f\x12\x06\xa6\x12\x80\xe8\x0d\x59\x7c\x84\x46\x36\x63\xcf\x6b\xeb\x77\x4f\x32\xc4\x26\xd0\xa4\xde\x56\x06\xf2\x76\x05\xe2\x5f\x28\xb2\xa6\x71\x94\x85\x0b\xa9");

INIT_SPM(full_block,
         "\x9f\x81\x9a\x67\xce\x36\x22\xa6\xb0\x61\xd7\xc6\x83\x7e\x59\xed\xa7\x3b\x81\x19\x34\xc4\x06\x5a\x4c\x1b\x5c\x73\x5b\x56\x69\x97\x78\x20\xfd\x7a\x66\x1b\xe3\xed\xae\xbd\xfd\xf7\xce\x48\x2c\xdf\xec\xc0\x6b\xfd\x3f\xc0\x41\xe5\x99\x67\x8f\x91\x3e\x14\x0f\x3f\xb7\x7b\xf0\xd5\x2a\x9b\x93\x18\xfe\x11\xb5\x5f\xc1\xdb\x7a\x18\xd1\xb0\x32\x7e\xda\xb2\xcb\xb9\xf2\x77\x44\x39\x48\x69\x11\xb1\x76\xdf\x4e\x02\xd5\x3a\xd1\x7a\x37\x77\xc8\xcd\xab\xeb",
         "\xd5\xf2\x98\x77\xf5\x8d\x91\x9d\x89\xe6\x6b\x8a\x39\x06\x36\x28\xf1\x2a\x3a\xbb\xc1\x83\xba\xb0\x24\x83\x07\x59\x69\x2e\xd2\x1a\xfb\xb0\x50\x01\xef\x4d\x37\x8d\xe9\x26\x56\xb4\x0f\xbd\xd7\x41\xa3\x5b\x81\xb9\xe4\xbf\xb0\x9d\x68\xd9\x11\x25\x66\x9e\xc8\x10");

INIT_SPM(wait_write_mem_last_word,
         "\x10\x2a\x80\xd3\x36\x0b\x77\x98\x5b\x67\xa9\x8b\x5f\xf5\xb8\x88\x22\x3a\x15\xdc\xc4\x9e\xf6\x00\x46\x27\x1c\x3b\x72\xcb\x1e\x09\x18\xf5\x15\xc4\xe4\xcd\x87\xfd\x46\x93\x81\x02\xfc\xb5\x02\x1e\x9f\x54\xcf\xaa\xc7\x0a\x5e\x2b\x3c\x8a\x95\xd7\x5b\xdd\x35\x7c\xf6\xd5\x07\x0e\x57\xc4\xae\xa5\x44\x09\x72\x7d\x60\x26\x5e\x48\x44\xf8\x91\x4c\x67\x61\xb7\x34\x0b\x5b\x56\x7e\xfa\xe5\xf8\x05\xd4\xe7\xc3\xae\x95\x84\x98\x1f\x34\xe6\x87\xe3\xae\xcd\xf6\x9a\x0c\x59\x48\x9b\x1d\x7b\xd5\xf5\xbc\xd4\xaa\x90\xd7\x91\x7e\x5f\x38\x5d",
         "\xa5\xe5\x30\xd4\xd0\x69\xf6\xd4\xd6\x10\x22\xa0\x2f\x2f\xdb\xc3\x7c\x8f\xc9\x05\x3f\x50\xf9\x53\x0d\xcd\xc6\x6d\x96\x0c\x3e\x84\x5c\x62\x19\x2a\xac\xb1\x64\xf5\xd3\x34\x07\x25\x13\x02\xe8\xaf\xa4\xa1\x85\xc1\x0d\x15\xe8\x49\x64\x89\xe6\x4b\xbd\x83\x1d\x6a");

INIT_SPM(wait_after_last_mem,
         "\xac\x68\x7a\x85\xaf\x1a\x99\x1b\x2d\x80\xde\xd8\x5c\x06\x85\xd6\x40\x17\x4e\x56\xa4\xf4\xff\x9d\xe6\xb6\x35\x40\xae\x6b\x34\xe9\x52\x68\x42\xd7\xeb\x16\x0f\x27\xe8\xfc\xa2\x47\xe1\x4f\xad\x9d\x49\x4b\xe2\xd5\xbb\x77\x4c\xc4\x17\x82\x5a\xa6\xf3\x45\xab\x7d\x21\xf8\x0a\x97\x58\x80\x21\x56\xe0\x06\xe4\x07\xc8\x44\x26\xce\xc2\x00\x1f\xa1\x35\x38\xa2\xf2\xdd\x4d\xf7\x85\xc9\xaa\x24\x42\x78\xb5\xfa\xb0\x91\xe6\xe4\x7f\x91\x7d\x71\xfb\x62\xc1\x5e\x6b\x2b\xe8\xb4\x26\xd5\xe2\xec\x49\x70\x18\xc0\x1f\x28\x35\x78\x7f",
         "\x09\x00\xb3\xa9\x34\xee\xa2\x42\xf4\x0e\x06\xdb\x7c\x49\x1c\x33\x8f\x44\x23\x3c\x84\xa7\x6a\xd5\x5d\x79\x7b\x1e\x78\x27\xd2\xf0\x1f\x45\xbd\x37\xfa\xd8\xd2\xd5\x61\xdd\x67\x92\x57\x0b\xa9\x7a\x1e\x7b\x42\x45\x4c\x16\x58\xb8\x13\xa7\x04\x8a\x1f\x67\x94\x4f");

INIT_SPM(wait_write_mem,
         "\xff\x06\x43\x98\xb5\xf1\x62\x07\x52\xa8\x5a\x8f\x73\xe3\x55\x52\x9b\x87\x13\x70\x6a\xc1\x62\xfd\xad\xfa\x89\x69\x0c\xa9\x22\x8b\x97\x3c\x90\x58\x8b\xb2\xa6\x39\x79\x43\xbf\xb1\x44\xe1\x0e\x96\x28\xbf\x9f\x49\x2b\xdf\x70\x08\xd1\x10\x37\xba\xe4\xe5\xd3\xc3\x42\x2d\x66\x0a\x5f\xca\xaa\x9a\xca\xc8\x66\xf4\x57\x6e\x56\xcc\xbd\x09\x2f\xdb\x37\x4c\x17\x34\x1e\x69\x86\xb7\xdf\x97\xec\x1b\x17\xfc\x13\x9a\x33\x3b\x23\xbc\xa1\xf0\xad\xf1\xb2\x46\xe8\xbe\xa3\xf0\x7e\xa0\xb1\xd3\x1b\x1b\xb5\xca\x06\xbd\x7b\xe2\x4c\xc8\xa7\xe5\xe8\xb9\x70\xa4\x93\x34\x80\xeb\x17\x7b",
         "\xff\xba\x41\xae\xa6\x1c\xd9\x0a\x37\xfd\xb1\x6b\xed\x4b\x38\xb0\xf5\xca\xe8\x2e\xf3\xeb\x9e\x31\x17\xd1\x14\xc2\x4b\x04\x3a\xdd\x28\xb2\x2f\xc9\xea\x2a\x9a\xbd\x76\x36\x13\x18\x72\xd4\x6e\xe5\x15\x14\x02\x73\x52\xba\x65\x09\x7c\xb2\x90\x43\x9c\x04\xb8\xd0");

INIT_SPM(wait_after_ps,
         "\xc0\xe9\x3c\x89\x83\xeb\x8b\x29\x51\xd4\x15\x72\xdb\x4e\xad\x56\x13\xc0\x05\x88\xc1\xf1\x1a\x58\x5b\x4b\x39\xbd\xae\xa3\x55\x7a\x71\xbc\x66\xa3\x4a\x18\x20\x03\x75\x10\xd8\x05\x32\x4a\xfb\x68\x87\x46\x2f\x9b\xe4\xae\xd6\x90\x57\x09\xd6\xea\x47\x99\x3e\x17\x9f\x4f\x5e\x4b\x61\x88\x05\xcb\xe8\x94\x34\x51\xab\xd2\x40\x11\x9a\x7d\x21\xf5\x4b\x7d\x1f\x6f\x22\x31\x96\x12\xd9\xe4\x50\xdf\x4e\xa4\x85\xa2\xb6\x92\x00\x76\x37\x9b\xc4\xc5\x5e\xdc\x8a\xba\xe2\x38\x3d\xff\x50\x40\x78\x2e\xd8\xad\x45\xcc\x8b\x27",
         "\x4e\xa0\xf5\xf5\x25\xa9\xe1\x14\x5c\xe0\x30\xed\xb2\xfc\xc3\xdf\x25\xfe\x88\x16\x78\x65\x47\xc3\x17\xd5\x05\x5e\x6b\x34\x73\xd4\x88\x0b\x1f\x95\x54\x07\xad\x87\xa3\xd0\x9e\x71\xc1\x1c\x1e\xee\x01\xf8\x0a\x8f\x24\xc5\x50\x75\x88\xb7\xdf\xbe\xd7\xdb\x96\xe4");

INIT_SPM(wait_after_pe,
         "\xd7\xa6\x07\x3c\x0c\x07\x2b\x2e\xfa\x80\x9b\xd3\xc0\x8e\x4c\x93\x7f\x13\xdc\xf0\x9e\x79\x10\x5a\x0f\x3b\xe4\x34\x31\x74\x39\xa7\xda\x7f\xbe\x98\x29\xdc\x81\xb7\x5a\x36\x95\x10\xcf\xd8\x0c\x0f\x5e\xe1\xba\x8d\x60\x85\xca\xa7\x6e\x9e\x56\x32\xd5\xb8\x3a\x79\x58\xd6\xee\x7b\xf0\xc5\x8d\xc2\x8e\xc1\xe1\xdb\x73\xf0\x76\xd9\x27\x34\x30\x55\xe8\x9f\x27\x1e\x22\x60\x1a\xdd\x65\x21\x8a\x52\x86\xee\x55\x67\x97\x0c\xfb\x14\x20\xd7\x4c\xeb\xca\xa1\x9c\xc1\x7d\x45\xbd\x3e\xad\x1a\xa2\xff\x2c\x0b\xc9\x34",
         "\x23\x81\xbf\xe4\x6c\xff\xea\x97\x02\x34\x47\x95\x17\xb2\x72\xb9\xb6\x2c\x9a\xfd\x67\xe6\xd5\x0d\x9d\xda\x58\xca\x91\x87\x7f\x0b\xa0\xee\xb0\xff\xf1\x01\x57\xd0\x58\xb3\x6b\x73\xc5\x9b\x65\x82\x82\x46\x20\x68\xbc\xf3\x59\x71\xb6\x4a\x41\x1d\x30\x43\xda\x94");

INIT_SPM(wait_after_ss,
         "\x2e\x8d\xc8\xea\xff\xef\x12\x01\xb5\x83\x80\xde\x89\xef\x54\x05\x7f\x55\x25\x09\x23\x4c\xef\xf2\x25\xb2\x3e\xd7\x9a\xd7\x4d\x1a\xcc\xbb\x90\x01\xe0\xdc\x96\xa7\xf8\x89\xd7\x06\x7d\x27\x1c\x40\x5e\xc6\x0b\x66\x79\x85\x37\x51\xad\x70\x79\x20\x4b\x0b\x39\xe4\xd5\x63\x36\xb1\xe3\x05\x9b\xa7\x58\xf2\x79\x0e\xb6\xbc\x91\xa8\x41\x59\xf7\x24\xae\xfb\x7d\x04\xb2\x58\xf6\xcd\x94\xaa\x3d\x1d\x69\xe6\xe5\x0f\xd4\xd0\xa0\x25\xb1\x19\x46\x69\x9c\x9c\xc9\xb5\xf6\xf7\xc2\xbc\x53\x0c\x8a\xe9\x9f\xe9",
         "\x1e\x2c\x51\x3a\x6d\x52\xb4\xab\x33\x53\x7e\xf6\x39\xda\xa1\x20\xd2\x2d\xa4\xba\xe5\x06\x13\xb0\x30\x72\x36\x3f\x15\x4c\x9a\x0f\xba\xb6\xd4\x17\x9f\x74\x5a\xdc\x1b\xde\x6e\x47\xce\x30\x4c\xbc\x52\x22\x86\xb3\x68\xc0\xe0\x44\x49\x36\xc7\x32\x00\x87\xff\x72");

INIT_SPM(big_one,
         "\x9c\x49\xc6\x06\x9e\xae\x71\x9c\x87\x83\x0e\x18\xdf\xfb\xd2\x1e\x71\x73\x88\x61\x66\xdc\xcb\x24\xcc\x46\x0a\x47\xa2\x9d\x2b\x5d\x15\x54\x1f\x4d\xab\x55\xa6\xea\xdf\x41\xdf\xe0\x96\x3e\x74\xd0\x0e\x77\xe0\xc8\x91\x40\x4f\xe5\xec\x1f\x1d\x2d\xc8\xce\x12\x7c\x15\xce\xf0\x69\x43\x83\xf1\x55\x35\xe5\x31\x9b\xd6\x4b\x34\x28\x38\xc5\xc7\x39\xf1\x3c\xdb\x03\x7e\xbe\x3d\xe3\xd8\xfe\x9b\xa2\x55\xe1\x2a\x0d\xcf\x42\x85\x2b\x57\x05\xdf\x13\xce\xdf\x31\x59\x2e\x52\x2e\x4c\x95\xfa\x2f\x28\xf5\x57\x56\x52\xc3\x9e\x94\x55\xa5\x41\x37\x08\x5a\xe7\xd5\xeb\xd1\x37\xb9\x9a\xe5\x7d\xf2\x41\x2d\xc7\x44\x13\xbb\x1e\x7c\x2c\xba\x5a\x5f\x43\x47\x69\x65\x66\x79\x5d\x33\x5a\xa2\xba\xf5\x18\x4d\xc9\x89\x21\xc0\xd1\x2a\x89\x9d\x48\x15\x46\x60\x8e\x2c\xd9\xd1\x23\x29\x72\x9b\x0b\xdc\x1e\x04\x95\x01\x3f\x91\xc3\xed\xb5\x55\x07\xbb\xa4\x94\xbc\x07\x2a\xa5\xd1\xdf\x45\xcc\x10\x58\xda\xdd\x6a\x65\xf8\x07\x7f\xf6\xd7\x07\x25\x3f\xe8\x48\x04\x22\x08\xbe\xd4\x13\xf2\xae\xaa\x81\xbb\x7f\xb5\xd0\x0e\xab\x01\x8f\x89\x9b\x9c\xf3\xad\x1c\xc9\x91\x41",
         "\x2f\xc6\xa6\x2c\x7b\x3f\x25\x35\x6e\xa2\x62\xa3\x17\xc5\x42\x14\x52\x2c\xcf\x16\xf3\x50\x07\x68\x2a\x31\x97\xb4\xe4\x07\x0c\x4e\x46\x08\xcc\x8f\x59\xfb\x3b\x5a\x70\x87\x91\x98\x89\x6b\xc7\x3f\x1f\x94\x6a\x80\x69\xe0\x46\xc6\x72\xe8\xcb\x79\xbd\x41\x0d\x9e");

void print_nibble(unsigned char n)
{
    if (n > 0xf)
        putchar('?');
    else if (n < 0xa)
        putchar(n + '0');
    else
        putchar(n - 0xa + 'a');
}

void print_mem(const unsigned char* start, size_t size, int swap)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        unsigned char b = start[swap ? (i % 2 ? i - 1 : i + 1) : i];
        print_nibble(b >> 4);
        print_nibble(b & 0x0f);
    }
}

void protect_spm(Spm* spm)
{
    puts("Protecting SPM...");

    asm("mov %0, r12\n\t"
        "mov %1, r13\n\t"
        "mov %2, r14\n\t"
        "mov %3, r15\n\t"
        ".word 0x1381"
        :
        : "m"(spm->public), "r"(spm->public + spm->size - 1),
          "r"(&spm->secret), "r"((char*)&spm->secret + sizeof(spm->secret) - 1)
        : "r12", "r13", "r14", "r15");
}

void test_spm(Spm* spm)
{
    static spm_id next_id = 0;
    spm_id id;
    protect_spm(spm);
    puts("Hashing SPM...");
    id = hash_spm(spm->expected_hash, spm->public);

    if (id != ++next_id)
        printf(" - Failed: expected id %u, got %u\n", next_id, id);
    else
        puts(" - Passed");
}

int __attribute__((section(".init9"), aligned(2))) main(void)
{
    puts("main() started");
    WDTCTL = WDTPW|WDTHOLD;

    asm("nop");
    TEST_SPM(simple);
    TEST_SPM(full_block);
    TEST_SPM(wait_write_mem_last_word);
    TEST_SPM(wait_after_last_mem);
    TEST_SPM(wait_write_mem);
    TEST_SPM(wait_after_ps);
    TEST_SPM(wait_after_pe);
    TEST_SPM(wait_after_ss);
    TEST_SPM(big_one);

    puts("main() done");
    P2OUT = 0x01;
    return 0;
}

int putchar(int c)
{
    P1OUT = c;
    P1OUT |= 0x80;
    return c;
}
