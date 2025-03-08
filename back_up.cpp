#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include<cstring>
#include <windows.h>
using namespace std;
// DES算法中用到的初始置换IP表
const int IP[64] = {
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8, 0,
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6
};

// 结束置换表FP
const int FP[64] = {
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25,
        32, 0, 40,  8, 48, 16, 56, 24
};

// S盒
const int S_BOX[8][4][16] =
        {
                {
                        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                },
                {
                        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
                },
                {
                        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
                },
                {
                        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
                },
                {
                        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
                },
                {
                        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
                },
                {
                        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
                },
                {
                        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
                }
        };

// 密钥置换选择1
const int PC1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
};

// 密钥置换选择2
const int PC2[48] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
};

// 左移次数表
const int SHIFTS[16] = {
        1, 1, 2, 2,
        2, 2, 2, 2,
        1, 2, 2, 2,
        2, 2, 2, 1
};

const int EXPANSION_TABLE[48] = {
        31, 0, 1, 2, 3, 4, 3, 4,
        5, 6, 7, 8, 7, 8, 9, 10,
        11, 12, 11, 12, 13, 14, 15, 16,
        15, 16, 17, 18, 19, 20, 19, 20,
        21, 22, 23, 24, 23, 24, 25, 26,
        27, 28, 27, 28, 29, 30, 31, 0
};

// P盒置换表
const int P_BOX[32] = {
        15, 6, 19, 20, 28, 11, 27, 16,
        0, 14, 22, 25, 4, 17, 30, 9,
        1, 7, 23, 13, 31, 26, 2, 8,
        18, 12, 29, 5, 21, 10, 3, 24
};
template <size_t N>
void PRINT(const std::bitset<N>& bits) {
    // 计算十六进制所需的最小宽度，每4位二进制对应1位十六进制
    const int hexWidth = (N + 3) / 4;

    // 将bitset转换为无符号长整型（注意这是有长度限制的，通常适用于N<=64）
    unsigned long long value = bits.to_ullong();

    // 使用ostringstream和iomanip来格式化输出
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0') << std::setw(hexWidth) << value;

    // 打印结果
    std::cout << oss.str() << std::endl;
}


std::bitset<64> stringToBitset(const std::string& hex) {
    std::bitset<64> bits;
    for(int i=0;i<16;i++){
        int vv=(hex[i]>='A'&&hex[i]<='F'?hex[i]-'A'+10:hex[i]-'0');
        for(int j=0;j<4;j++){
            if((vv>>j)&1){
                bits.set(60-4*i+j);
            }
        }
    }
    return bits;
}

string bitsetToString(const bitset<64>& bits){
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << bits.to_ullong();
    return oss.str();
}
std::string plainfile, keyfile, ivfile, cipherfile, mode;
bool hasIV = false;
bool isEncrypting=true;
bitset<64> iv;
std::vector<std::bitset<48>> roundKeys;
std::vector<std::bitset<64>> inputDataBlocks;
vector<bitset<64>> outDataBlocks;
void keySchedule(const std::bitset<64>& key) {
    std::bitset<56> permutedKey;

    // 初始密钥置换PC1
    for (int i = 0; i < 56; ++i) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }

    std::bitset<28> left = (permutedKey.to_ullong() >> 28) & 0x0FFFFFFF;
    std::bitset<28> right = permutedKey.to_ullong() & 0x0FFFFFFF;

    // 生成16轮子密钥
    for (int i = 0; i < 16; ++i) {
        // 循环左移
        left = left << SHIFTS[i] | left >> (28 - SHIFTS[i]);
        right = right << SHIFTS[i] | right >> (28 - SHIFTS[i]);

        std::bitset<56> combined = (left.to_ullong() << 28) | right.to_ullong();
        std::bitset<48> roundKey;
        for (int j = 0; j < 48; ++j) {
            roundKey[47 - j] = combined[56 - PC2[j]];
        }
        roundKeys.push_back(roundKey);
    }
}

std::bitset<32> feistelFunction(const std::bitset<32>& halfBlock, const std::bitset<48>& subKey) {
    std::bitset<48> expandedBlock;

    // 执行扩展置换 E
    for (int i = 0; i < 48; i++) {
        expandedBlock[47 - i] = halfBlock[31 - EXPANSION_TABLE[i]];
    }
    // 将扩展后的块与子密钥进行 XOR 操作
    expandedBlock ^= subKey;

    std::bitset<32> output;
    int sBoxOutput;

    // S盒处理
    for (int i = 0; i < 8; i++) {
        int row = (expandedBlock[47 - i*6] << 1) + expandedBlock[47 - i*6 - 5];
        int col = (expandedBlock[47 - i*6 - 1] << 3) + (expandedBlock[47 - i*6 - 2] << 2) +
                  (expandedBlock[47 - i*6 - 3] << 1) + expandedBlock[47 - i*6 - 4];
        sBoxOutput = S_BOX[i][row][col];
        output[31 - i*4] = (sBoxOutput >> 3) & 1;
        output[31 - i*4 - 1] = (sBoxOutput >> 2) & 1;
        output[31 - i*4 - 2] = (sBoxOutput >> 1) & 1;
        output[31 - i*4 - 3] = sBoxOutput & 1;
    }
    // P盒置换
    std::bitset<32> permutedOutput;
    for (int i = 0; i < 32; i++) {
        permutedOutput[31 - i] = output[31 - P_BOX[i]];
    }
    return permutedOutput;
}

std::bitset<64> DES(const std::bitset<64>& input,bool isEncrypto) {
    std::bitset<64> permutedInput;

    // 初始置换
    for (int i = 0; i < 64; ++i) {
        permutedInput[63 - i] = input[63 - IP[i]];
    }
    std::bitset<32> left = (permutedInput.to_ullong() >> 32) & 0xFFFFFFFF;
    std::bitset<32> right = permutedInput.to_ullong() & 0xFFFFFFFF;

    // 16轮Feistel网络
    for (int i = 0; i < 16; ++i) {
        int round = isEncrypto ? i : 15 - i;  // 解密时子密钥顺序相反
        std::bitset<32> tempRight = right;
        right = left ^ feistelFunction(right, roundKeys[round]);
        left = tempRight;
    }

    // 交换左右半块之前不进行交换，因为最终轮已经交换
    std::bitset<64> preOutput((right.to_ullong() << 32) | left.to_ullong());
    // 最终置换FP
    std::bitset<64> finalOutput;
    for (int i = 0; i < 64; ++i) {
        finalOutput[63 - i] = preOutput[63 - FP[i]];
    }
    return finalOutput;
}

std::vector<std::bitset<64>> encryptCBC(const std::vector<std::bitset<64>>& plaintextBlocks) {
    std::vector<std::bitset<64>> ciphertextBlocks;
    std::bitset<64> previousBlock = iv;

    for (const auto& block : plaintextBlocks) {
        std::bitset<64> xorBlock = block ^ previousBlock;
        std::bitset<64> encryptedBlock = DES(xorBlock,true);
        ciphertextBlocks.push_back(encryptedBlock);
        previousBlock = encryptedBlock;
    }

    return ciphertextBlocks;
}

std::vector<std::bitset<64>> decryptCBC(const std::vector<std::bitset<64>>& ciphertextBlocks) {
    std::vector<std::bitset<64>> plaintextBlocks;
    std::bitset<64> previousBlock = iv;

    for (const auto& block : ciphertextBlocks) {
        std::bitset<64> decryptedBlock = DES(block,false);
        std::bitset<64> plaintextBlock = decryptedBlock ^ previousBlock;
        plaintextBlocks.push_back(plaintextBlock);
        previousBlock = block;
    }

    return plaintextBlocks;
}

vector<bitset<64>> DES_ECB(const vector<bitset<64>>& dataBlocks) {
    vector<bitset<64>> processedBlocks;
    for (const auto& block : dataBlocks) {
        bitset<64> processedBlock = DES(block,isEncrypting);
        processedBlocks.push_back(processedBlock);
    }
    return processedBlocks;
}

void DES_CBC(const vector<bitset<64>>& dataBlocks) {
    outDataBlocks.clear();
    outDataBlocks.reserve(dataBlocks.size());
    bitset<64> previousBlock = iv;
    if (isEncrypting) {
        for (const auto& block : dataBlocks) {
            bitset<64> xorBlock = block ^ previousBlock;
            bitset<64> encryptedBlock = DES(xorBlock, true);
            outDataBlocks.push_back(encryptedBlock);
            previousBlock = encryptedBlock;
        }
    } else {
        for (const auto& block : dataBlocks) {
            bitset<64> decryptedBlock = DES(block, false);
            bitset<64> originalBlock = decryptedBlock ^ previousBlock;
            outDataBlocks.push_back(originalBlock);
            previousBlock = block;
        }
    }
}


vector<bitset<64>> DES_CFB(const vector<bitset<64>>& dataBlocks) {
    vector<bitset<64>> processedBlocks;
    bitset<64> previousBlock = iv;

    for (const auto& block : dataBlocks) {
        bitset<64> outputBlock = DES(previousBlock, true); // Always encrypt IV or previous output
        bitset<64> processedBlock = block ^ outputBlock;
        processedBlocks.push_back(processedBlock);
        previousBlock = isEncrypting ? processedBlock : block;
    }
    return processedBlocks;
}


vector<bitset<64>> DES_OFB(const vector<bitset<64>>& dataBlocks) {
    vector<bitset<64>> processedBlocks;
    bitset<64> previousBlock = iv;

    for (const auto& block : dataBlocks) {
        previousBlock= DES(previousBlock, true); // Always encrypt IV or previous output
        bitset<64> processedBlock = block ^ previousBlock;
        processedBlocks.push_back(processedBlock);
    }
    return processedBlocks;
}

void readFromFile(const string& fileName,vector<bitset<64>>& res){
    res.clear();
    ifstream file(fileName,ios::binary);
    if(!file){
        cout<<"文件: "<<fileName<<" 打开失败"<<endl;
        exit(-1);
    }
    vector<string> strings;
    const size_t length=16;
    char buffer[length + 1] = {};  // +1 为了能够在末尾加上空字符

    while (file.read(buffer, length)) {
        buffer[length] = '\0'; // 确保字符串是正确终止的
        strings.emplace_back(buffer);
    }
    size_t bytesRead = file.gcount();
    if (bytesRead > 0) {
        buffer[length]=0;
        for(size_t h=bytesRead;h<length;h++)buffer[h]='0';
        std::string last(buffer);
        strings.push_back(last);
    }

    file.close();

    res.reserve(strings.size());
    for(const auto& s:strings)res.push_back(stringToBitset(s));
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-p") == 0) {
            plainfile = argv[++i];
        } else if (std::strcmp(argv[i], "-k") == 0) {
            keyfile = argv[++i];
        } else if (std::strcmp(argv[i], "-v") == 0) {
            ivfile = argv[++i];
            hasIV = true;//若不指定初始向量,初始向量为全零
        } else if (std::strcmp(argv[i], "-m") == 0) {
            mode = argv[++i];
        } else if (std::strcmp(argv[i], "-c") == 0) {
            cipherfile = argv[++i];
        }else if(std::strcmp(argv[i], "-d") == 0){
            isEncrypting=false;
        }
    }
    vector<bitset<64>> tp;
    readFromFile(keyfile,tp);
    auto Key_= tp[0];
    keySchedule(Key_);
    if(hasIV){
        readFromFile(ivfile,tp);
        iv= tp[0];
    }
    if(isEncrypting)readFromFile(plainfile,inputDataBlocks);
    else readFromFile(cipherfile,inputDataBlocks);
    if(mode!="ECB"&&mode!="CBC"&&mode!="CFB"&&mode!="OFB"){
        cout<<"加(解)密方式有误!"<<endl;
        exit(-1);
    }
    std::ofstream outFile;
    if(isEncrypting)outFile.open(cipherfile, std::ios::out | std::ios::binary);
    else outFile.open(plainfile,std::ios::out | std::ios::binary);
    if(!outFile){
        cout<<"创建输出文件失败!"<<endl;
        exit(-1);
    }
    //ECB、CBC、CFB、OFB

    if(mode=="ECB"){
        outDataBlocks= DES_ECB(inputDataBlocks);
    }else if(mode=="CBC"){
        DES_CBC(inputDataBlocks);
    }else if(mode=="CFB"){
        outDataBlocks= DES_CFB(inputDataBlocks);
    }else if(mode=="OFB"){
        outDataBlocks= DES_OFB(inputDataBlocks);
    }

    vector<string> content;
    content.reserve((outDataBlocks.size()));
    for(const auto& bits:outDataBlocks){
        content.push_back(bitsetToString(bits));
    }
    for(const auto& s:content){
        outFile<<s;
    }

    cout<<"加(解)密完毕"<<endl;
//    //加密
//    std::vector<std::bitset<64>> ciphertextBlocks = encryptCBC(inputDataBlocks);
//
//    // 解密
//    std::vector<std::bitset<64>> decryptedBlocks = decryptCBC(ciphertextBlocks);
//
//    std::cout << "Ciphertext Blocks:\n";
//    for (const auto& block : ciphertextBlocks) {
//        std::cout << std::hex << std::uppercase << block.to_ullong() << std::endl;
//    }
//
//    std::cout << "Decrypted Blocks:\n";
//    for (const auto& block : decryptedBlocks) {
//        std::cout << std::hex << std::uppercase << block.to_ullong() << std::endl;
//    }

    return 0;
}
