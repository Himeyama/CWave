typedef struct{
    char riff_chunk_ID[4] = {'R', 'I', 'F', 'F'};
    uint32_t riff_chunk_size;
    char file_format_type[4] = {'W', 'A', 'V', 'E'};

    char fmt_chunk_ID[4] = {'f', 'm', 't'};
    uint32_t fmt_fhunk_size = 16;
    uint16_t wave_format_type = 1;
    uint16_t channel = 1;
    uint32_t samples_per_sec = 44100;
    uint32_t bytes_per_sec;
    uint16_t block_size;
    uint16_t bits_per_sample = 16;

    char data_chunk_ID[4] = {'d', 'a', 't', 'a'};
    uint32_t data_chunk_size[4];
    int16_t* data;
} WavFormat;