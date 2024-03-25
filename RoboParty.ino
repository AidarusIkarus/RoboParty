#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR
#endif

#define MATRIX_PIN 1
#define POWER 200

#define R_m2_PIN 0  // D3        D0
#define R_m1_PIN 2  // D4        D1
#define L_m2_PIN 13 // D7        D2
#define L_m1_PIN 15 // D8        D3

#define STEP_PER_TURN 2800
#define STEP_MM ((43 * PI) / STEP_PER_TURN)
int L_enc = 0;
int R_enc = 0;

bool dance_1 = false;
bool dance_2 = false;
bool light_on = false;

const byte L_encInt_PIN = D1; // D1 5
const byte L_encVal_PIN = D2; // D2 4
const byte R_encInt_PIN = D5; // D5 14
const byte R_encVal_PIN = D6; // D6 12

#define ssid      "HONOR-16 2651"
#define password  "amongussss"
#define host "192.168.137.157"
const int sendUdpPort = 4210;
const int receiveUdpPort = 2000;
char incomingPacket[255];
char Old_incomingPacket[255];
WiFiUDP Udp;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 39, MATRIX_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ZIGZAG + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
  
int x1, x2;
int y2;
int rate = 5;
int value[3] = {255, 0, 0};
int pos = 0;
int color_pos = 0;
int x = matrix.width();
int pass = 0;
int colors[][3] = {
{255, 0, 0}, {255, 1, 0}, {255, 2, 0}, {255, 3, 0}, {255, 4, 0}, {255, 5, 0}, {255, 6, 0}, {255, 7, 0}, {255, 8, 0}, {255, 9, 0}, {255, 10, 0}, {255, 11, 0}, {255, 12, 0}, {255, 13, 0}, {255, 14, 0}, {255, 15, 0}, {255, 16, 0}, {255, 17, 0}, {255, 18, 0}, {255, 19, 0}, {255, 20, 0}, {255, 21, 0}, {255, 22, 0}, {255, 23, 0}, {255, 24, 0}, {255, 25, 0}, {255, 26, 0}, {255, 27, 0}, {255, 28, 0}, {255, 29, 0}, {255, 30, 0}, {255, 31, 0}, {255, 32, 0}, {255, 33, 0}, {255, 34, 0}, {255, 35, 0}, {255, 36, 0}, {255, 37, 0}, {255, 38, 0}, {255, 39, 0}, {255, 40, 0}, {255, 41, 0}, {255, 42, 0}, {255, 43, 0}, {255, 44, 0}, {255, 45, 0}, {255, 46, 0}, {255, 47, 0}, {255, 48, 0}, {255, 49, 0}, {255, 50, 0}, {255, 51, 0}, {255, 52, 0}, {255, 53, 0}, {255, 54, 0}, {255, 55, 0}, {255, 56, 0}, {255, 57, 0}, {255, 58, 0}, {255, 59, 0}, {255, 60, 0}, {255, 61, 0}, {255, 62, 0}, {255, 63, 0}, {255, 64, 0}, {255, 65, 0}, {255, 66, 0}, {255, 67, 0}, {255, 68, 0}, {255, 69, 0}, {255, 70, 0}, {255, 71, 0}, {255, 72, 0}, {255, 73, 0}, {255, 74, 0}, {255, 75, 0}, {255, 76, 0}, {255, 77, 0}, {255, 78, 0}, {255, 79, 0}, {255, 80, 0}, {255, 81, 0}, {255, 82, 0}, {255, 83, 0}, {255, 84, 0}, {255, 85, 0}, {255, 86, 0}, {255, 87, 0}, {255, 88, 0}, {255, 89, 0}, {255, 90, 0}, {255, 91, 0}, {255, 92, 0}, {255, 93, 0}, {255, 94, 0}, {255, 95, 0}, {255, 96, 0}, {255, 97, 0}, {255, 98, 0}, {255, 99, 0}, {255, 100, 0}, {255, 101, 0}, {255, 102, 0}, {255, 103, 0}, {255, 104, 0}, {255, 105, 0}, {255, 106, 0}, {255, 107, 0}, {255, 108, 0}, {255, 109, 0}, {255, 110, 0}, {255, 111, 0}, {255, 112, 0}, {255, 113, 0}, {255, 114, 0}, {255, 115, 0}, {255, 116, 0}, {255, 117, 0}, {255, 118, 0}, {255, 119, 0}, {255, 120, 0}, {255, 121, 0}, {255, 122, 0}, {255, 123, 0}, {255, 124, 0}, {255, 125, 0}, {255, 126, 0}, {255, 127, 0}, {255, 128, 0}, {255, 129, 0}, {255, 130, 0}, {255, 131, 0}, {255, 132, 0}, {255, 133, 0}, {255, 134, 0}, {255, 135, 0}, {255, 136, 0}, {255, 137, 0}, {255, 138, 0}, {255, 139, 0}, {255, 140, 0}, {255, 141, 0}, {255, 142, 0}, {255, 143, 0}, {255, 144, 0}, {255, 145, 0}, {255, 146, 0}, {255, 147, 0}, {255, 148, 0}, {255, 149, 0}, {255, 150, 0}, {255, 151, 0}, {255, 152, 0}, {255, 153, 0}, {255, 154, 0}, {255, 155, 0}, {255, 156, 0}, {255, 157, 0}, {255, 158, 0}, {255, 159, 0}, {255, 160, 0}, {255, 161, 0}, {255, 162, 0}, {255, 163, 0}, {255, 164, 0}, {255, 165, 0}, {255, 166, 0}, {255, 167, 0}, {255, 168, 0}, {255, 169, 0}, {255, 170, 0}, {255, 171, 0}, {255, 172, 0}, {255, 173, 0}, {255, 174, 0}, {255, 175, 0}, {255, 176, 0}, {255, 177, 0}, {255, 178, 0}, {255, 179, 0}, {255, 180, 0}, {255, 181, 0}, {255, 182, 0}, {255, 183, 0}, {255, 184, 0}, {255, 185, 0}, {255, 186, 0}, {255, 187, 0}, {255, 188, 0}, {255, 189, 0}, {255, 190, 0}, {255, 191, 0}, {255, 192, 0}, {255, 193, 0}, {255, 194, 0}, {255, 195, 0}, {255, 196, 0}, {255, 197, 0}, {255, 198, 0}, {255, 199, 0}, {255, 200, 0}, {255, 201, 0}, {255, 202, 0}, {255, 203, 0}, {255, 204, 0}, {255, 205, 0}, {255, 206, 0}, {255, 207, 0}, {255, 208, 0}, {255, 209, 0}, {255, 210, 0}, {255, 211, 0}, {255, 212, 0}, {255, 213, 0}, {255, 214, 0}, {255, 215, 0}, {255, 216, 0}, {255, 217, 0}, {255, 218, 0}, {255, 219, 0}, {255, 220, 0}, {255, 221, 0}, {255, 222, 0}, {255, 223, 0}, {255, 224, 0}, {255, 225, 0}, {255, 226, 0}, {255, 227, 0}, {255, 228, 0}, {255, 229, 0}, {255, 230, 0}, {255, 231, 0}, {255, 232, 0}, {255, 233, 0}, {255, 234, 0}, {255, 235, 0}, {255, 236, 0}, {255, 237, 0}, {255, 238, 0}, {255, 239, 0}, {255, 240, 0}, {255, 241, 0}, {255, 242, 0}, {255, 243, 0}, {255, 244, 0}, {255, 245, 0}, {255, 246, 0}, {255, 247, 0}, {255, 248, 0}, {255, 249, 0}, {255, 250, 0}, {255, 251, 0}, {255, 252, 0}, {255, 253, 0}, {255, 254, 0}, 
{255, 255, 0}, {254, 255, 0}, {253, 255, 0}, {252, 255, 0}, {251, 255, 0}, {250, 255, 0}, {249, 255, 0}, {248, 255, 0}, {247, 255, 0}, {246, 255, 0}, {245, 255, 0}, {244, 255, 0}, {243, 255, 0}, {242, 255, 0}, {241, 255, 0}, {240, 255, 0}, {239, 255, 0}, {238, 255, 0}, {237, 255, 0}, {236, 255, 0}, {235, 255, 0}, {234, 255, 0}, {233, 255, 0}, {232, 255, 0}, {231, 255, 0}, {230, 255, 0}, {229, 255, 0}, {228, 255, 0}, {227, 255, 0}, {226, 255, 0}, {225, 255, 0}, {224, 255, 0}, {223, 255, 0}, {222, 255, 0}, {221, 255, 0}, {220, 255, 0}, {219, 255, 0}, {218, 255, 0}, {217, 255, 0}, {216, 255, 0}, {215, 255, 0}, {214, 255, 0}, {213, 255, 0}, {212, 255, 0}, {211, 255, 0}, {210, 255, 0}, {209, 255, 0}, {208, 255, 0}, {207, 255, 0}, {206, 255, 0}, {205, 255, 0}, {204, 255, 0}, {203, 255, 0}, {202, 255, 0}, {201, 255, 0}, {200, 255, 0}, {199, 255, 0}, {198, 255, 0}, {197, 255, 0}, {196, 255, 0}, {195, 255, 0}, {194, 255, 0}, {193, 255, 0}, {192, 255, 0}, {191, 255, 0}, {190, 255, 0}, {189, 255, 0}, {188, 255, 0}, {187, 255, 0}, {186, 255, 0}, {185, 255, 0}, {184, 255, 0}, {183, 255, 0}, {182, 255, 0}, {181, 255, 0}, {180, 255, 0}, {179, 255, 0}, {178, 255, 0}, {177, 255, 0}, {176, 255, 0}, {175, 255, 0}, {174, 255, 0}, {173, 255, 0}, {172, 255, 0}, {171, 255, 0}, {170, 255, 0}, {169, 255, 0}, {168, 255, 0}, {167, 255, 0}, {166, 255, 0}, {165, 255, 0}, {164, 255, 0}, {163, 255, 0}, {162, 255, 0}, {161, 255, 0}, {160, 255, 0}, {159, 255, 0}, {158, 255, 0}, {157, 255, 0}, {156, 255, 0}, {155, 255, 0}, {154, 255, 0}, {153, 255, 0}, {152, 255, 0}, {151, 255, 0}, {150, 255, 0}, {149, 255, 0}, {148, 255, 0}, {147, 255, 0}, {146, 255, 0}, {145, 255, 0}, {144, 255, 0}, {143, 255, 0}, {142, 255, 0}, {141, 255, 0}, {140, 255, 0}, {139, 255, 0}, {138, 255, 0}, {137, 255, 0}, {136, 255, 0}, {135, 255, 0}, {134, 255, 0}, {133, 255, 0}, {132, 255, 0}, {131, 255, 0}, {130, 255, 0}, {129, 255, 0}, {128, 255, 0}, {127, 255, 0}, {126, 255, 0}, {125, 255, 0}, {124, 255, 0}, {123, 255, 0}, {122, 255, 0}, {121, 255, 0}, {120, 255, 0}, {119, 255, 0}, {118, 255, 0}, {117, 255, 0}, {116, 255, 0}, {115, 255, 0}, {114, 255, 0}, {113, 255, 0}, {112, 255, 0}, {111, 255, 0}, {110, 255, 0}, {109, 255, 0}, {108, 255, 0}, {107, 255, 0}, {106, 255, 0}, {105, 255, 0}, {104, 255, 0}, {103, 255, 0}, {102, 255, 0}, {101, 255, 0}, {100, 255, 0}, {99, 255, 0}, {98, 255, 0}, {97, 255, 0}, {96, 255, 0}, {95, 255, 0}, {94, 255, 0}, {93, 255, 0}, {92, 255, 0}, {91, 255, 0}, {90, 255, 0}, {89, 255, 0}, {88, 255, 0}, {87, 255, 0}, {86, 255, 0}, {85, 255, 0}, {84, 255, 0}, {83, 255, 0}, {82, 255, 0}, {81, 255, 0}, {80, 255, 0}, {79, 255, 0}, {78, 255, 0}, {77, 255, 0}, {76, 255, 0}, {75, 255, 0}, {74, 255, 0}, {73, 255, 0}, {72, 255, 0}, {71, 255, 0}, {70, 255, 0}, {69, 255, 0}, {68, 255, 0}, {67, 255, 0}, {66, 255, 0}, {65, 255, 0}, {64, 255, 0}, {63, 255, 0}, {62, 255, 0}, {61, 255, 0}, {60, 255, 0}, {59, 255, 0}, {58, 255, 0}, {57, 255, 0}, {56, 255, 0}, {55, 255, 0}, {54, 255, 0}, {53, 255, 0}, {52, 255, 0}, {51, 255, 0}, {50, 255, 0}, {49, 255, 0}, {48, 255, 0}, {47, 255, 0}, {46, 255, 0}, {45, 255, 0}, {44, 255, 0}, {43, 255, 0}, {42, 255, 0}, {41, 255, 0}, {40, 255, 0}, {39, 255, 0}, {38, 255, 0}, {37, 255, 0}, {36, 255, 0}, {35, 255, 0}, {34, 255, 0}, {33, 255, 0}, {32, 255, 0}, {31, 255, 0}, {30, 255, 0}, {29, 255, 0}, {28, 255, 0}, {27, 255, 0}, {26, 255, 0}, {25, 255, 0}, {24, 255, 0}, {23, 255, 0}, {22, 255, 0}, {21, 255, 0}, {20, 255, 0}, {19, 255, 0}, {18, 255, 0}, {17, 255, 0}, {16, 255, 0}, {15, 255, 0}, {14, 255, 0}, {13, 255, 0}, {12, 255, 0}, {11, 255, 0}, {10, 255, 0}, {9, 255, 0}, {8, 255, 0}, {7, 255, 0}, {6, 255, 0}, {5, 255, 0}, {4, 255, 0}, {3, 255, 0}, {2, 255, 0}, {1, 255, 0}, 
{0, 255, 0}, {0, 255, 1}, {0, 255, 2}, {0, 255, 3}, {0, 255, 4}, {0, 255, 5}, {0, 255, 6}, {0, 255, 7}, {0, 255, 8}, {0, 255, 9}, {0, 255, 10}, {0, 255, 11}, {0, 255, 12}, {0, 255, 13}, {0, 255, 14}, {0, 255, 15}, {0, 255, 16}, {0, 255, 17}, {0, 255, 18}, {0, 255, 19}, {0, 255, 20}, {0, 255, 21}, {0, 255, 22}, {0, 255, 23}, {0, 255, 24}, {0, 255, 25}, {0, 255, 26}, {0, 255, 27}, {0, 255, 28}, {0, 255, 29}, {0, 255, 30}, {0, 255, 31}, {0, 255, 32}, {0, 255, 33}, {0, 255, 34}, {0, 255, 35}, {0, 255, 36}, {0, 255, 37}, {0, 255, 38}, {0, 255, 39}, {0, 255, 40}, {0, 255, 41}, {0, 255, 42}, {0, 255, 43}, {0, 255, 44}, {0, 255, 45}, {0, 255, 46}, {0, 255, 47}, {0, 255, 48}, {0, 255, 49}, {0, 255, 50}, {0, 255, 51}, {0, 255, 52}, {0, 255, 53}, {0, 255, 54}, {0, 255, 55}, {0, 255, 56}, {0, 255, 57}, {0, 255, 58}, {0, 255, 59}, {0, 255, 60}, {0, 255, 61}, {0, 255, 62}, {0, 255, 63}, {0, 255, 64}, {0, 255, 65}, {0, 255, 66}, {0, 255, 67}, {0, 255, 68}, {0, 255, 69}, {0, 255, 70}, {0, 255, 71}, {0, 255, 72}, {0, 255, 73}, {0, 255, 74}, {0, 255, 75}, {0, 255, 76}, {0, 255, 77}, {0, 255, 78}, {0, 255, 79}, {0, 255, 80}, {0, 255, 81}, {0, 255, 82}, {0, 255, 83}, {0, 255, 84}, {0, 255, 85}, {0, 255, 86}, {0, 255, 87}, {0, 255, 88}, {0, 255, 89}, {0, 255, 90}, {0, 255, 91}, {0, 255, 92}, {0, 255, 93}, {0, 255, 94}, {0, 255, 95}, {0, 255, 96}, {0, 255, 97}, {0, 255, 98}, {0, 255, 99}, {0, 255, 100}, {0, 255, 101}, {0, 255, 102}, {0, 255, 103}, {0, 255, 104}, {0, 255, 105}, {0, 255, 106}, {0, 255, 107}, {0, 255, 108}, {0, 255, 109}, {0, 255, 110}, {0, 255, 111}, {0, 255, 112}, {0, 255, 113}, {0, 255, 114}, {0, 255, 115}, {0, 255, 116}, {0, 255, 117}, {0, 255, 118}, {0, 255, 119}, {0, 255, 120}, {0, 255, 121}, {0, 255, 122}, {0, 255, 123}, {0, 255, 124}, {0, 255, 125}, {0, 255, 126}, {0, 255, 127}, {0, 255, 128}, {0, 255, 129}, {0, 255, 130}, {0, 255, 131}, {0, 255, 132}, {0, 255, 133}, {0, 255, 134}, {0, 255, 135}, {0, 255, 136}, {0, 255, 137}, {0, 255, 138}, {0, 255, 139}, {0, 255, 140}, {0, 255, 141}, {0, 255, 142}, {0, 255, 143}, {0, 255, 144}, {0, 255, 145}, {0, 255, 146}, {0, 255, 147}, {0, 255, 148}, {0, 255, 149}, {0, 255, 150}, {0, 255, 151}, {0, 255, 152}, {0, 255, 153}, {0, 255, 154}, {0, 255, 155}, {0, 255, 156}, {0, 255, 157}, {0, 255, 158}, {0, 255, 159}, {0, 255, 160}, {0, 255, 161}, {0, 255, 162}, {0, 255, 163}, {0, 255, 164}, {0, 255, 165}, {0, 255, 166}, {0, 255, 167}, {0, 255, 168}, {0, 255, 169}, {0, 255, 170}, {0, 255, 171}, {0, 255, 172}, {0, 255, 173}, {0, 255, 174}, {0, 255, 175}, {0, 255, 176}, {0, 255, 177}, {0, 255, 178}, {0, 255, 179}, {0, 255, 180}, {0, 255, 181}, {0, 255, 182}, {0, 255, 183}, {0, 255, 184}, {0, 255, 185}, {0, 255, 186}, {0, 255, 187}, {0, 255, 188}, {0, 255, 189}, {0, 255, 190}, {0, 255, 191}, {0, 255, 192}, {0, 255, 193}, {0, 255, 194}, {0, 255, 195}, {0, 255, 196}, {0, 255, 197}, {0, 255, 198}, {0, 255, 199}, {0, 255, 200}, {0, 255, 201}, {0, 255, 202}, {0, 255, 203}, {0, 255, 204}, {0, 255, 205}, {0, 255, 206}, {0, 255, 207}, {0, 255, 208}, {0, 255, 209}, {0, 255, 210}, {0, 255, 211}, {0, 255, 212}, {0, 255, 213}, {0, 255, 214}, {0, 255, 215}, {0, 255, 216}, {0, 255, 217}, {0, 255, 218}, {0, 255, 219}, {0, 255, 220}, {0, 255, 221}, {0, 255, 222}, {0, 255, 223}, {0, 255, 224}, {0, 255, 225}, {0, 255, 226}, {0, 255, 227}, {0, 255, 228}, {0, 255, 229}, {0, 255, 230}, {0, 255, 231}, {0, 255, 232}, {0, 255, 233}, {0, 255, 234}, {0, 255, 235}, {0, 255, 236}, {0, 255, 237}, {0, 255, 238}, {0, 255, 239}, {0, 255, 240}, {0, 255, 241}, {0, 255, 242}, {0, 255, 243}, {0, 255, 244}, {0, 255, 245}, {0, 255, 246}, {0, 255, 247}, {0, 255, 248}, {0, 255, 249}, {0, 255, 250}, {0, 255, 251}, {0, 255, 252}, {0, 255, 253}, {0, 255, 254}, 
{0, 255, 255}, {0, 254, 255}, {0, 253, 255}, {0, 252, 255}, {0, 251, 255}, {0, 250, 255}, {0, 249, 255}, {0, 248, 255}, {0, 247, 255}, {0, 246, 255}, {0, 245, 255}, {0, 244, 255}, {0, 243, 255}, {0, 242, 255}, {0, 241, 255}, {0, 240, 255}, {0, 239, 255}, {0, 238, 255}, {0, 237, 255}, {0, 236, 255}, {0, 235, 255}, {0, 234, 255}, {0, 233, 255}, {0, 232, 255}, {0, 231, 255}, {0, 230, 255}, {0, 229, 255}, {0, 228, 255}, {0, 227, 255}, {0, 226, 255}, {0, 225, 255}, {0, 224, 255}, {0, 223, 255}, {0, 222, 255}, {0, 221, 255}, {0, 220, 255}, {0, 219, 255}, {0, 218, 255}, {0, 217, 255}, {0, 216, 255}, {0, 215, 255}, {0, 214, 255}, {0, 213, 255}, {0, 212, 255}, {0, 211, 255}, {0, 210, 255}, {0, 209, 255}, {0, 208, 255}, {0, 207, 255}, {0, 206, 255}, {0, 205, 255}, {0, 204, 255}, {0, 203, 255}, {0, 202, 255}, {0, 201, 255}, {0, 200, 255}, {0, 199, 255}, {0, 198, 255}, {0, 197, 255}, {0, 196, 255}, {0, 195, 255}, {0, 194, 255}, {0, 193, 255}, {0, 192, 255}, {0, 191, 255}, {0, 190, 255}, {0, 189, 255}, {0, 188, 255}, {0, 187, 255}, {0, 186, 255}, {0, 185, 255}, {0, 184, 255}, {0, 183, 255}, {0, 182, 255}, {0, 181, 255}, {0, 180, 255}, {0, 179, 255}, {0, 178, 255}, {0, 177, 255}, {0, 176, 255}, {0, 175, 255}, {0, 174, 255}, {0, 173, 255}, {0, 172, 255}, {0, 171, 255}, {0, 170, 255}, {0, 169, 255}, {0, 168, 255}, {0, 167, 255}, {0, 166, 255}, {0, 165, 255}, {0, 164, 255}, {0, 163, 255}, {0, 162, 255}, {0, 161, 255}, {0, 160, 255}, {0, 159, 255}, {0, 158, 255}, {0, 157, 255}, {0, 156, 255}, {0, 155, 255}, {0, 154, 255}, {0, 153, 255}, {0, 152, 255}, {0, 151, 255}, {0, 150, 255}, {0, 149, 255}, {0, 148, 255}, {0, 147, 255}, {0, 146, 255}, {0, 145, 255}, {0, 144, 255}, {0, 143, 255}, {0, 142, 255}, {0, 141, 255}, {0, 140, 255}, {0, 139, 255}, {0, 138, 255}, {0, 137, 255}, {0, 136, 255}, {0, 135, 255}, {0, 134, 255}, {0, 133, 255}, {0, 132, 255}, {0, 131, 255}, {0, 130, 255}, {0, 129, 255}, {0, 128, 255}, {0, 127, 255}, {0, 126, 255}, {0, 125, 255}, {0, 124, 255}, {0, 123, 255}, {0, 122, 255}, {0, 121, 255}, {0, 120, 255}, {0, 119, 255}, {0, 118, 255}, {0, 117, 255}, {0, 116, 255}, {0, 115, 255}, {0, 114, 255}, {0, 113, 255}, {0, 112, 255}, {0, 111, 255}, {0, 110, 255}, {0, 109, 255}, {0, 108, 255}, {0, 107, 255}, {0, 106, 255}, {0, 105, 255}, {0, 104, 255}, {0, 103, 255}, {0, 102, 255}, {0, 101, 255}, {0, 100, 255}, {0, 99, 255}, {0, 98, 255}, {0, 97, 255}, {0, 96, 255}, {0, 95, 255}, {0, 94, 255}, {0, 93, 255}, {0, 92, 255}, {0, 91, 255}, {0, 90, 255}, {0, 89, 255}, {0, 88, 255}, {0, 87, 255}, {0, 86, 255}, {0, 85, 255}, {0, 84, 255}, {0, 83, 255}, {0, 82, 255}, {0, 81, 255}, {0, 80, 255}, {0, 79, 255}, {0, 78, 255}, {0, 77, 255}, {0, 76, 255}, {0, 75, 255}, {0, 74, 255}, {0, 73, 255}, {0, 72, 255}, {0, 71, 255}, {0, 70, 255}, {0, 69, 255}, {0, 68, 255}, {0, 67, 255}, {0, 66, 255}, {0, 65, 255}, {0, 64, 255}, {0, 63, 255}, {0, 62, 255}, {0, 61, 255}, {0, 60, 255}, {0, 59, 255}, {0, 58, 255}, {0, 57, 255}, {0, 56, 255}, {0, 55, 255}, {0, 54, 255}, {0, 53, 255}, {0, 52, 255}, {0, 51, 255}, {0, 50, 255}, {0, 49, 255}, {0, 48, 255}, {0, 47, 255}, {0, 46, 255}, {0, 45, 255}, {0, 44, 255}, {0, 43, 255}, {0, 42, 255}, {0, 41, 255}, {0, 40, 255}, {0, 39, 255}, {0, 38, 255}, {0, 37, 255}, {0, 36, 255}, {0, 35, 255}, {0, 34, 255}, {0, 33, 255}, {0, 32, 255}, {0, 31, 255}, {0, 30, 255}, {0, 29, 255}, {0, 28, 255}, {0, 27, 255}, {0, 26, 255}, {0, 25, 255}, {0, 24, 255}, {0, 23, 255}, {0, 22, 255}, {0, 21, 255}, {0, 20, 255}, {0, 19, 255}, {0, 18, 255}, {0, 17, 255}, {0, 16, 255}, {0, 15, 255}, {0, 14, 255}, {0, 13, 255}, {0, 12, 255}, {0, 11, 255}, {0, 10, 255}, {0, 9, 255}, {0, 8, 255}, {0, 7, 255}, {0, 6, 255}, {0, 5, 255}, {0, 4, 255}, {0, 3, 255}, {0, 2, 255}, {0, 1, 255}, 
{0, 0, 255}, {1, 0, 255}, {2, 0, 255}, {3, 0, 255}, {4, 0, 255}, {5, 0, 255}, {6, 0, 255}, {7, 0, 255}, {8, 0, 255}, {9, 0, 255}, {10, 0, 255}, {11, 0, 255}, {12, 0, 255}, {13, 0, 255}, {14, 0, 255}, {15, 0, 255}, {16, 0, 255}, {17, 0, 255}, {18, 0, 255}, {19, 0, 255}, {20, 0, 255}, {21, 0, 255}, {22, 0, 255}, {23, 0, 255}, {24, 0, 255}, {25, 0, 255}, {26, 0, 255}, {27, 0, 255}, {28, 0, 255}, {29, 0, 255}, {30, 0, 255}, {31, 0, 255}, {32, 0, 255}, {33, 0, 255}, {34, 0, 255}, {35, 0, 255}, {36, 0, 255}, {37, 0, 255}, {38, 0, 255}, {39, 0, 255}, {40, 0, 255}, {41, 0, 255}, {42, 0, 255}, {43, 0, 255}, {44, 0, 255}, {45, 0, 255}, {46, 0, 255}, {47, 0, 255}, {48, 0, 255}, {49, 0, 255}, {50, 0, 255}, {51, 0, 255}, {52, 0, 255}, {53, 0, 255}, {54, 0, 255}, {55, 0, 255}, {56, 0, 255}, {57, 0, 255}, {58, 0, 255}, {59, 0, 255}, {60, 0, 255}, {61, 0, 255}, {62, 0, 255}, {63, 0, 255}, {64, 0, 255}, {65, 0, 255}, {66, 0, 255}, {67, 0, 255}, {68, 0, 255}, {69, 0, 255}, {70, 0, 255}, {71, 0, 255}, {72, 0, 255}, {73, 0, 255}, {74, 0, 255}, {75, 0, 255}, {76, 0, 255}, {77, 0, 255}, {78, 0, 255}, {79, 0, 255}, {80, 0, 255}, {81, 0, 255}, {82, 0, 255}, {83, 0, 255}, {84, 0, 255}, {85, 0, 255}, {86, 0, 255}, {87, 0, 255}, {88, 0, 255}, {89, 0, 255}, {90, 0, 255}, {91, 0, 255}, {92, 0, 255}, {93, 0, 255}, {94, 0, 255}, {95, 0, 255}, {96, 0, 255}, {97, 0, 255}, {98, 0, 255}, {99, 0, 255}, {100, 0, 255}, {101, 0, 255}, {102, 0, 255}, {103, 0, 255}, {104, 0, 255}, {105, 0, 255}, {106, 0, 255}, {107, 0, 255}, {108, 0, 255}, {109, 0, 255}, {110, 0, 255}, {111, 0, 255}, {112, 0, 255}, {113, 0, 255}, {114, 0, 255}, {115, 0, 255}, {116, 0, 255}, {117, 0, 255}, {118, 0, 255}, {119, 0, 255}, {120, 0, 255}, {121, 0, 255}, {122, 0, 255}, {123, 0, 255}, {124, 0, 255}, {125, 0, 255}, {126, 0, 255}, {127, 0, 255}, {128, 0, 255}, {129, 0, 255}, {130, 0, 255}, {131, 0, 255}, {132, 0, 255}, {133, 0, 255}, {134, 0, 255}, {135, 0, 255}, {136, 0, 255}, {137, 0, 255}, {138, 0, 255}, {139, 0, 255}, {140, 0, 255}, {141, 0, 255}, {142, 0, 255}, {143, 0, 255}, {144, 0, 255}, {145, 0, 255}, {146, 0, 255}, {147, 0, 255}, {148, 0, 255}, {149, 0, 255}, {150, 0, 255}, {151, 0, 255}, {152, 0, 255}, {153, 0, 255}, {154, 0, 255}, {155, 0, 255}, {156, 0, 255}, {157, 0, 255}, {158, 0, 255}, {159, 0, 255}, {160, 0, 255}, {161, 0, 255}, {162, 0, 255}, {163, 0, 255}, {164, 0, 255}, {165, 0, 255}, {166, 0, 255}, {167, 0, 255}, {168, 0, 255}, {169, 0, 255}, {170, 0, 255}, {171, 0, 255}, {172, 0, 255}, {173, 0, 255}, {174, 0, 255}, {175, 0, 255}, {176, 0, 255}, {177, 0, 255}, {178, 0, 255}, {179, 0, 255}, {180, 0, 255}, {181, 0, 255}, {182, 0, 255}, {183, 0, 255}, {184, 0, 255}, {185, 0, 255}, {186, 0, 255}, {187, 0, 255}, {188, 0, 255}, {189, 0, 255}, {190, 0, 255}, {191, 0, 255}, {192, 0, 255}, {193, 0, 255}, {194, 0, 255}, {195, 0, 255}, {196, 0, 255}, {197, 0, 255}, {198, 0, 255}, {199, 0, 255}, {200, 0, 255}, {201, 0, 255}, {202, 0, 255}, {203, 0, 255}, {204, 0, 255}, {205, 0, 255}, {206, 0, 255}, {207, 0, 255}, {208, 0, 255}, {209, 0, 255}, {210, 0, 255}, {211, 0, 255}, {212, 0, 255}, {213, 0, 255}, {214, 0, 255}, {215, 0, 255}, {216, 0, 255}, {217, 0, 255}, {218, 0, 255}, {219, 0, 255}, {220, 0, 255}, {221, 0, 255}, {222, 0, 255}, {223, 0, 255}, {224, 0, 255}, {225, 0, 255}, {226, 0, 255}, {227, 0, 255}, {228, 0, 255}, {229, 0, 255}, {230, 0, 255}, {231, 0, 255}, {232, 0, 255}, {233, 0, 255}, {234, 0, 255}, {235, 0, 255}, {236, 0, 255}, {237, 0, 255}, {238, 0, 255}, {239, 0, 255}, {240, 0, 255}, {241, 0, 255}, {242, 0, 255}, {243, 0, 255}, {244, 0, 255}, {245, 0, 255}, {246, 0, 255}, {247, 0, 255}, {248, 0, 255}, {249, 0, 255}, {250, 0, 255}, {251, 0, 255}, {252, 0, 255}, {253, 0, 255}, {254, 0, 255}, 
{255, 0, 255}, {255, 0, 254}, {255, 0, 253}, {255, 0, 252}, {255, 0, 251}, {255, 0, 250}, {255, 0, 249}, {255, 0, 248}, {255, 0, 247}, {255, 0, 246}, {255, 0, 245}, {255, 0, 244}, {255, 0, 243}, {255, 0, 242}, {255, 0, 241}, {255, 0, 240}, {255, 0, 239}, {255, 0, 238}, {255, 0, 237}, {255, 0, 236}, {255, 0, 235}, {255, 0, 234}, {255, 0, 233}, {255, 0, 232}, {255, 0, 231}, {255, 0, 230}, {255, 0, 229}, {255, 0, 228}, {255, 0, 227}, {255, 0, 226}, {255, 0, 225}, {255, 0, 224}, {255, 0, 223}, {255, 0, 222}, {255, 0, 221}, {255, 0, 220}, {255, 0, 219}, {255, 0, 218}, {255, 0, 217}, {255, 0, 216}, {255, 0, 215}, {255, 0, 214}, {255, 0, 213}, {255, 0, 212}, {255, 0, 211}, {255, 0, 210}, {255, 0, 209}, {255, 0, 208}, {255, 0, 207}, {255, 0, 206}, {255, 0, 205}, {255, 0, 204}, {255, 0, 203}, {255, 0, 202}, {255, 0, 201}, {255, 0, 200}, {255, 0, 199}, {255, 0, 198}, {255, 0, 197}, {255, 0, 196}, {255, 0, 195}, {255, 0, 194}, {255, 0, 193}, {255, 0, 192}, {255, 0, 191}, {255, 0, 190}, {255, 0, 189}, {255, 0, 188}, {255, 0, 187}, {255, 0, 186}, {255, 0, 185}, {255, 0, 184}, {255, 0, 183}, {255, 0, 182}, {255, 0, 181}, {255, 0, 180}, {255, 0, 179}, {255, 0, 178}, {255, 0, 177}, {255, 0, 176}, {255, 0, 175}, {255, 0, 174}, {255, 0, 173}, {255, 0, 172}, {255, 0, 171}, {255, 0, 170}, {255, 0, 169}, {255, 0, 168}, {255, 0, 167}, {255, 0, 166}, {255, 0, 165}, {255, 0, 164}, {255, 0, 163}, {255, 0, 162}, {255, 0, 161}, {255, 0, 160}, {255, 0, 159}, {255, 0, 158}, {255, 0, 157}, {255, 0, 156}, {255, 0, 155}, {255, 0, 154}, {255, 0, 153}, {255, 0, 152}, {255, 0, 151}, {255, 0, 150}, {255, 0, 149}, {255, 0, 148}, {255, 0, 147}, {255, 0, 146}, {255, 0, 145}, {255, 0, 144}, {255, 0, 143}, {255, 0, 142}, {255, 0, 141}, {255, 0, 140}, {255, 0, 139}, {255, 0, 138}, {255, 0, 137}, {255, 0, 136}, {255, 0, 135}, {255, 0, 134}, {255, 0, 133}, {255, 0, 132}, {255, 0, 131}, {255, 0, 130}, {255, 0, 129}, {255, 0, 128}, {255, 0, 127}, {255, 0, 126}, {255, 0, 125}, {255, 0, 124}, {255, 0, 123}, {255, 0, 122}, {255, 0, 121}, {255, 0, 120}, {255, 0, 119}, {255, 0, 118}, {255, 0, 117}, {255, 0, 116}, {255, 0, 115}, {255, 0, 114}, {255, 0, 113}, {255, 0, 112}, {255, 0, 111}, {255, 0, 110}, {255, 0, 109}, {255, 0, 108}, {255, 0, 107}, {255, 0, 106}, {255, 0, 105}, {255, 0, 104}, {255, 0, 103}, {255, 0, 102}, {255, 0, 101}, {255, 0, 100}, {255, 0, 99}, {255, 0, 98}, {255, 0, 97}, {255, 0, 96}, {255, 0, 95}, {255, 0, 94}, {255, 0, 93}, {255, 0, 92}, {255, 0, 91}, {255, 0, 90}, {255, 0, 89}, {255, 0, 88}, {255, 0, 87}, {255, 0, 86}, {255, 0, 85}, {255, 0, 84}, {255, 0, 83}, {255, 0, 82}, {255, 0, 81}, {255, 0, 80}, {255, 0, 79}, {255, 0, 78}, {255, 0, 77}, {255, 0, 76}, {255, 0, 75}, {255, 0, 74}, {255, 0, 73}, {255, 0, 72}, {255, 0, 71}, {255, 0, 70}, {255, 0, 69}, {255, 0, 68}, {255, 0, 67}, {255, 0, 66}, {255, 0, 65}, {255, 0, 64}, {255, 0, 63}, {255, 0, 62}, {255, 0, 61}, {255, 0, 60}, {255, 0, 59}, {255, 0, 58}, {255, 0, 57}, {255, 0, 56}, {255, 0, 55}, {255, 0, 54}, {255, 0, 53}, {255, 0, 52}, {255, 0, 51}, {255, 0, 50}, {255, 0, 49}, {255, 0, 48}, {255, 0, 47}, {255, 0, 46}, {255, 0, 45}, {255, 0, 44}, {255, 0, 43}, {255, 0, 42}, {255, 0, 41}, {255, 0, 40}, {255, 0, 39}, {255, 0, 38}, {255, 0, 37}, {255, 0, 36}, {255, 0, 35}, {255, 0, 34}, {255, 0, 33}, {255, 0, 32}, {255, 0, 31}, {255, 0, 30}, {255, 0, 29}, {255, 0, 28}, {255, 0, 27}, {255, 0, 26}, {255, 0, 25}, {255, 0, 24}, {255, 0, 23}, {255, 0, 22}, {255, 0, 21}, {255, 0, 20}, {255, 0, 19}, {255, 0, 18}, {255, 0, 17}, {255, 0, 16}, {255, 0, 15}, {255, 0, 14}, {255, 0, 13}, {255, 0, 12}, {255, 0, 11}, {255, 0, 10}, {255, 0, 9}, {255, 0, 8}, {255, 0, 7}, {255, 0, 6}, {255, 0, 5}, {255, 0, 4}, {255, 0, 3}, {255, 0, 2}, {255, 0, 1},
};

unsigned long startTime = 0;
int state = 0;
long timer = millis();

void stop_all() {
  dance_1 = false;  dance_2 = false;  light_on = false;
  analogWrite(R_m1_PIN, POWER);
  analogWrite(R_m2_PIN, POWER);
  analogWrite(L_m1_PIN, POWER);
  analogWrite(L_m2_PIN, POWER);
  delay(500);
  analogWrite(R_m1_PIN, 0);
  analogWrite(R_m2_PIN, 0);
  analogWrite(L_m1_PIN, 0);
  analogWrite(L_m2_PIN, 0);
}

void stop_R() {
  analogWrite(R_m1_PIN, POWER);
  analogWrite(R_m2_PIN, POWER);
}

void stop_L() {
  analogWrite(L_m1_PIN, POWER);
  analogWrite(L_m2_PIN, POWER);
}

void L_forw(int power) {
  analogWrite(L_m1_PIN,  0);
  analogWrite(L_m2_PIN, POWER);
}

void R_forw(int power) {
  analogWrite(R_m1_PIN, POWER);
  analogWrite(R_m2_PIN,  0);
}

void L_back(int power) {
  analogWrite(L_m1_PIN, POWER);
  analogWrite(L_m2_PIN, 0);
}

void R_back(int power) {
  analogWrite(R_m1_PIN, 0);
  analogWrite(R_m2_PIN, POWER);
}

void ICACHE_RAM_ATTR L_encFunc() {
  if (digitalRead(L_encVal_PIN) == 1)
    L_enc ++;
  else
    L_enc --;
}

void ICACHE_RAM_ATTR R_encFunc() {
  if (digitalRead(R_encVal_PIN) == 1)
    R_enc --;
  else
    R_enc ++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");    
  Udp.begin(receiveUdpPort);

  pinMode(R_m1_PIN, OUTPUT);
  pinMode(R_m2_PIN, OUTPUT);
  pinMode(L_m1_PIN, OUTPUT);
  pinMode(L_m2_PIN, OUTPUT);
  
  pinMode(R_encInt_PIN, INPUT);
  pinMode(R_encVal_PIN, INPUT);
  pinMode(L_encInt_PIN, INPUT);
  pinMode(L_encVal_PIN, INPUT);
  
  attachInterrupt(L_encInt_PIN, L_encFunc, RISING);
  attachInterrupt(R_encInt_PIN, R_encFunc, RISING);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  light_on = true;
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(incomingPacket, sizeof(incomingPacket));
    if (strcmp(incomingPacket, Old_incomingPacket) != 0){
      state = 0;
      if (incomingPacket[0] == '1'){
        dance_1 = true;
      } else if (incomingPacket[0] == '2') {
        dance_2 = true;
      } else if (incomingPacket[0] == 'S'){
        stop_all();
      }
    }
  }

  if (dance_1 == true) {
    dance_2 = false;
  
    if (millis() - startTime >= 450) {
      startTime = millis();
      if (state < 4) {
        if (state % 2 == 0) {
          R_forw(POWER);
          L_back(POWER);
        } else {
          R_back(POWER);
          L_forw(POWER);
        }
      } else if (state < 8) {
        if (state % 2 == 0) {
          R_back(POWER);
          stop_L();
        } else {
          L_back(POWER);
          stop_R();
        }
      } else if (state < 10) {
        R_forw(255);
        L_forw(255);
      } else {
        R_forw(POWER);
        L_back(POWER);
      }
      
      state++;
      if (state >= 12) {
        state = 0;
      }
    }
  }
  
  if (light_on = true) {
    for(int i = 0; i < 46; i++) {
        x1 = i;
        x2 = i - 14; y2 = 7;
        
        if (value[0] == colors[pos][0] && 
            value[1] == colors[pos][1] &&
            value[2] == colors[pos][2]){
          if (pos == 5){
            pos = 0;     
          }
          else{
            pos += 1;
          }
        }
        for (int n = 0; n < 3; n++){
          if (value[n] > colors[pos][n]){
           value[n] -= rate;
          }
          else {
            value[n] += rate;
          }
        }
        
        matrix.drawLine(0, x1, y2, x2, matrix.Color(colors[color_pos][0], colors[color_pos][1], colors[color_pos][2]));
        color_pos += 1;
        if (color_pos == ((255*6) - 1)){
          color_pos = 0;
        }
        
        matrix.show();
    }
  }
}
