#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

class WavFormat{
    private:
        char riff_chunk_ID[4] = {'R', 'I', 'F', 'F'};
        uint32_t riff_chunk_size = 0;
        char file_format_type[4] = {'W', 'A', 'V', 'E'};

        char fmt_chunk_ID[4] = {'f', 'm', 't', ' '};
        uint32_t fmt_chunk_size = 16;
        uint16_t wave_format_type = 1;
        uint16_t channel = 1;
        uint32_t samples_per_sec = 44100;
        uint32_t bytes_per_sec = 0;
        uint16_t block_size = 0;
        uint16_t bits_per_sample = 16;

        char data_chunk_ID[4] = {'d', 'a', 't', 'a'};
        uint32_t data_chunk_size = 0;
        int16_t* data = NULL;

    public:
        void save(){
            FILE *fp;

            if((fp = fopen("test.wav", "w")) != NULL){
                char* p = this->riff_chunk_ID;
                uint64_t i;
                for(i = 0; i < 44; i++){
                    fwrite(p+i, 1, 1, fp);
                }
                p = (char*)this->data;
                uint64_t datalen = this->data_chunk_size / this->channel;
                // cout << datalen << endl;
                for(i = 0; i < datalen * 2; i++){
                    fwrite(p+i, 1, 1, fp);
                }
                fclose(fp);
            }else{
                cout << "書き込み失敗" << endl;
            }
        }

        void makeSound(uint64_t n){
            freeMemory();
            this->data = (int16_t*)calloc(sizeof(int16_t), n);
            this->data_chunk_size = this->channel * n;
            this->riff_chunk_size = this->data_chunk_size + 36;
            this->block_size = (this->bits_per_sample * this->channel) / 8;
            this->bytes_per_sec = (this->block_size * this->samples_per_sec) / 8;
        }

        void makeSin(uint64_t n){
            makeSound(n);
            for(uint64_t i=0; i<n; i++){
                *(this->data + i) = sin(440 * 3.1416 * i / (1.0 * this->samples_per_sec / 2)) * 32767;
            }
        }

        void freeMemory(){
            if(this->data != NULL){
                free(this->data);
            }
        }
};


int main(void){
    WavFormat wav;
    wav.makeSin(100000);
    wav.save();
    wav.freeMemory();

    return 0;
}