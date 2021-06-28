// Ray soundfile table - 8 bit 8 kHz

const int ray_length=2108;
const unsigned char ray_data[] PROGMEM = {
0x89,	0xab,	0xb7,	0xc1,	0xc3,	0xc3,	0xbd,	0xb4,	0x9c,	0x62,	0x4b,	0x42,	0x3c,	0x3c,	0x41,	0x4b,
0x63,	0x9f,	0xb3,	0xbf,	0xc2,	0xc4,	0xbd,	0xb5,	0x9a,	0x5e,	0x4a,	0x3f,	0x3c,	0x3c,	0x46,	0x50,
0x82,	0xb0,	0xba,	0xc2,	0xc4,	0xbe,	0xb6,	0x99,	0x5d,	0x48,	0x3f,	0x3a,	0x40,	0x47,	0x61,	0x9d,
0xb8,	0xbe,	0xc6,	0xbf,	0xba,	0x9f,	0x64,	0x46,	0x41,	0x39,	0x42,	0x47,	0x6e,	0xa9,	0xbb,	0xc2,
0xc4,	0xbb,	0xb1,	0x79,	0x4b,	0x43,	0x3a,	0x40,	0x47,	0x6b,	0xa9,	0xbb,	0xc3,	0xc3,	0xbb,	0xa6,
0x65,	0x46,	0x3e,	0x3b,	0x44,	0x55,	0x96,	0xb9,	0xc0,	0xc4,	0xbb,	0xab,	0x6a,	0x46,	0x3e,	0x3c,
0x44,	0x60,	0xa6,	0xba,	0xc5,	0xc0,	0xba,	0x8e,	0x4f,	0x42,	0x3a,	0x42,	0x51,	0x98,	0xb8,	0xc3,
0xc1,	0xbb,	0x92,	0x51,	0x3f,	0x3c,	0x41,	0x5d,	0xa3,	0xbd,	0xc3,	0xc0,	0xaf,	0x71,	0x42,	0x3e,
0x3d,	0x4e,	0x8a,	0xbd,	0xc0,	0xc3,	0xb2,	0x75,	0x42,	0x3f,	0x3c,	0x51,	0x92,	0xc0,	0xc0,	0xc3,
0xa5,	0x60,	0x3e,	0x3f,	0x3f,	0x6e,	0xb1,	0xc1,	0xc2,	0xb7,	0x7a,	0x41,	0x3f,	0x3c,	0x63,	0xa9,
0xc1,	0xc1,	0xb9,	0x7b,	0x41,	0x3f,	0x3e,	0x69,	0xb1,	0xc2,	0xc1,	0xae,	0x62,	0x3d,	0x3e,	0x49,
0x92,	0xc0,	0xc0,	0xbd,	0x80,	0x42,	0x3f,	0x40,	0x7b,	0xbd,	0xc0,	0xc1,	0x86,	0x44,	0x3e,	0x40,
0x7c,	0xbe,	0xbf,	0xbf,	0x7c,	0x40,	0x3e,	0x48,	0x97,	0xc1,	0xc1,	0xaf,	0x5b,	0x3d,	0x3e,	0x66,
0xb8,	0xbf,	0xc0,	0x79,	0x40,	0x3d,	0x51,	0xa8,	0xc1,	0xc1,	0x8d,	0x41,	0x3f,	0x4a,	0xa0,	0xc2,
0xc1,	0x8a,	0x3f,	0x40,	0x4f,	0xae,	0xbf,	0xc1,	0x72,	0x40,	0x3b,	0x6f,	0xbb,	0xc3,	0xaa,	0x51,
0x3d,	0x47,	0x9d,	0xc3,	0xbf,	0x78,	0x3c,	0x3e,	0x80,	0xc1,	0xc3,	0x8e,	0x41,	0x3b,	0x70,	0xbc,
0xc4,	0x98,	0x46,	0x38,	0x6c,	0xb9,	0xc7,	0x8e,	0x44,	0x39,	0x79,	0xbf,	0xc3,	0x7d,	0x3c,	0x42,
0x8f,	0xc8,	0xb4,	0x65,	0x33,	0x5e,	0xaf,	0xc9,	0x92,	0x42,	0x3e,	0x84,	0xc8,	0xb2,	0x5f,	0x33,
0x69,	0xb9,	0xc4,	0x7e,	0x37,	0x50,	0xa5,	0xcb,	0x8d,	0x3e,	0x45,	0x9c,	0xcb,	0x96,	0x41,	0x43,
0x98,	0xcc,	0x97,	0x41,	0x45,	0x9c,	0xcb,	0x88,	0x3a,	0x4f,	0xac,	0xc6,	0x71,	0x35,	0x65,	0xc1,
0xb3,	0x55,	0x38,	0x88,	0xcc,	0x93,	0x3a,	0x55,	0xb6,	0xbe,	0x62,	0x35,	0x83,	0xcb,	0x93,	0x39,
0x5a,	0xbc,	0xb5,	0x50,	0x40,	0x9f,	0xc8,	0x6d,	0x36,	0x8c,	0xcb,	0x7f,	0x34,	0x75,	0xca,	0x94,
0x37,	0x6c,	0xc9,	0x9a,	0x39,	0x68,	0xc8,	0x9b,	0x38,	0x6b,	0xc9,	0x95,	0x37,	0x74,	0xcc,	0x7e,
0x35,	0x82,	0xcb,	0x6e,	0x38,	0xa2,	0xbf,	0x4e,	0x4d,	0xbf,	0xa0,	0x39,	0x72,	0xcb,	0x78,	0x39,
0xa5,	0xb9,	0x44,	0x5d,	0xc9,	0x86,	0x34,	0x98,	0xc1,	0x4b,	0x5e,	0xca,	0x7b,	0x37,	0xa5,	0xb6,
0x3e,	0x76,	0xcc,	0x5e,	0x4e,	0xc8,	0x85,	0x3a,	0xb1,	0xa8,	0x37,	0x91,	0xc1,	0x43,	0x73,	0xc8,
0x50,	0x5a,	0xca,	0x62,	0x51,	0xca,	0x73,	0x44,	0xc5,	0x76,	0x44,	0xc5,	0x74,	0x46,	0xc8,	0x71,
0x4b,	0xbc,	0xb4,	0xbd,	0xc3,	0xc3,	0xc1,	0xb7,	0xad,	0x7b,	0x51,	0x47,	0x3d,	0x3c,	0x3d,	0x46,
0x52,	0x82,	0xaf,	0xb7,	0xc4,	0xc1,	0xc4,	0xb7,	0xb0,	0x7b,	0x51,	0x45,	0x3d,	0x3b,	0x40,	0x49,
0x61,	0x9e,	0xb5,	0xbf,	0xc3,	0xc3,	0xba,	0xb0,	0x83,	0x50,	0x45,	0x3c,	0x3b,	0x42,	0x4b,	0x79,
0xad,	0xb9,	0xc2,	0xc4,	0xbe,	0xb5,	0x8f,	0x55,	0x45,	0x3d,	0x3b,	0x43,	0x4e,	0x86,	0xb2,	0xbc,
0xc4,	0xc2,	0xba,	0xa7,	0x69,	0x47,	0x40,	0x3a,	0x42,	0x4b,	0x80,	0xb2,	0xbc,	0xc5,	0xc0,	0xb9,
0x9a,	0x59,	0x44,	0x3c,	0x3d,	0x45,	0x5f,	0xa2,	0xba,	0xc3,	0xc2,	0xbb,	0xa0,	0x5d,	0x45,	0x3c,
0x3e,	0x45,	0x6c,	0xae,	0xba,	0xc6,	0xbe,	0xb8,	0x82,	0x4b,	0x41,	0x3a,	0x43,	0x58,	0xa0,	0xb9,
0xc5,	0xbf,	0xb9,	0x88,	0x4d,	0x3e,	0x3d,	0x42,	0x65,	0xa9,	0xbd,	0xc3,	0xbf,	0xac,	0x69,	0x41,
0x3e,	0x3e,	0x50,	0x8f,	0xbe,	0xc0,	0xc2,	0xb1,	0x76,	0x41,	0x40,	0x3c,	0x54,	0x96,	0xbf,	0xc0,
0xc2,	0xa7,	0x63,	0x3d,	0x3f,	0x40,	0x6b,	0xae,	0xc2,	0xc1,	0xb8,	0x7b,	0x43,	0x3f,	0x3d,	0x5d,
0xa6,	0xc2,	0xc1,	0xba,	0x7b,	0x43,	0x3f,	0x3d,	0x68,	0xb0,	0xc1,	0xc2,	0xae,	0x64,	0x3e,	0x3e,
0x45,	0x88,	0xbf,	0xc0,	0xbf,	0x8b,	0x46,	0x3e,	0x3f,	0x6e,	0xb8,	0xc0,	0xc2,	0x94,	0x49,	0x3e,
0x3e,	0x6e,	0xb9,	0xc0,	0xc1,	0x8c,	0x44,	0x3e,	0x42,	0x87,	0xc0,	0xc0,	0xb8,	0x6b,	0x3d,	0x3e,
0x57,	0xae,	0xc0,	0xc2,	0x8b,	0x42,	0x3f,	0x47,	0x99,	0xc1,	0xc2,	0x9f,	0x4a,	0x3e,	0x43,	0x8d,
0xc3,	0xc0,	0x9e,	0x45,	0x41,	0x43,	0x9b,	0xc0,	0xc4,	0x89,	0x42,	0x3c,	0x59,	0xb3,	0xc1,	0xb9,
0x60,	0x3e,	0x3e,	0x89,	0xc1,	0xc3,	0x8d,	0x42,	0x3a,	0x6a,	0xb8,	0xc6,	0xa2,	0x4d,	0x38,	0x58,
0xaa,	0xc9,	0xa8,	0x59,	0x33,	0x5b,	0xa8,	0xcc,	0xa1,	0x56,	0x32,	0x65,	0xaf,	0xcb,	0x94,	0x4a,
0x36,	0x78,	0xbd,	0xc4,	0x7c,	0x3a,	0x45,	0x92,	0xcb,	0xa9,	0x57,	0x34,	0x68,	0xba,	0xc4,	0x79,
0x39,	0x4b,	0x9e,	0xcc,	0x98,	0x45,	0x3d,	0x8c,	0xca,	0xa7,	0x51,	0x37,	0x80,	0xc7,	0xb0,	0x57,
0x36,	0x7b,	0xc7,	0xaf,	0x56,	0x36,	0x7e,	0xc7,	0xac,	0x50,	0x3b,	0x93,	0xca,	0x9a,	0x3e,	0x4c,
0xaa,	0xc7,	0x7b,	0x33,	0x69,	0xc3,	0xaf,	0x50,	0x3b,	0x91,	0xcc,	0x87,	0x36,	0x61,	0xc0,	0xb1,
0x4d,	0x40,	0xa2,	0xc7,	0x70,	0x34,	0x7f,	0xcb,	0x92,	0x38,	0x5f,	0xc1,	0xad,	0x45,	0x50,	0xba,
0xb4,	0x4e,	0x42,	0xae,	0xba,	0x52,	0x41,	0xab,	0xbb,	0x51,	0x42,	0xae,	0xb8,	0x4b,	0x49,	0xb3,
0xb3,	0x42,	0x59,	0xc4,	0x9b,	0x38,	0x6b,	0xca,	0x84,	0x33,	0x8f,	0xc7,	0x5c,	0x42,	0xb6,	0xac,
0x3c,	0x6a,	0xcb,	0x7b,	0x36,	0xa0,	0xbd,	0x47,	0x5b,	0xc8,	0x7b,	0x37,	0xa6,	0xb7,	0x40,	0x68,
0xca,	0x67,	0x40,	0xb9,	0x9e,	0x36,	0x93,	0xc1,	0x45,	0x6c,	0xcc,	0x63,	0x4c,	0xc7,	0x81,	0x3b,
0xb5,	0x97,	0x32,	0xa3,	0xab,	0x37,	0x98,	0xb3,	0x35,	0x88,	0xbc,	0x3e,	0x84,	0xbf,	0x39,	0x8c,
0xb8,	0x39,	0x90,	0xb8,	0xab,	0xc7,	0xbf,	0xc6,	0xba,	0xb6,	0x9a,	0x64,	0x4a,	0x43,	0x3b,	0x3d,
0x40,	0x4a,	0x61,	0x9d,	0xb3,	0xbd,	0xc3,	0xc3,	0xbf,	0xb5,	0x9f,	0x62,	0x4c,	0x40,	0x3d,	0x3b,
0x45,	0x4c,	0x7b,	0xac,	0xb9,	0xc2,	0xc3,	0xc0,	0xb7,	0xa4,	0x69,	0x49,	0x42,	0x3a,	0x3e,	0x45,
0x58,	0x91,	0xb5,	0xbc,	0xc5,	0xc1,	0xbb,	0xac,	0x76,	0x4a,	0x43,	0x39,	0x3f,	0x45,	0x5d,	0x98,
0xb9,	0xbe,	0xc6,	0xbe,	0xb8,	0x92,	0x56,	0x45,	0x3c,	0x3c,	0x44,	0x56,	0x94,	0xb8,	0xbe,	0xc6,
0xbd,	0xb5,	0x81,	0x4c,	0x43,	0x3a,	0x41,	0x48,	0x77,	0xb1,	0xbc,	0xc5,	0xbf,	0xb8,	0x8f,	0x50,
0x42,	0x3a,	0x40,	0x4b,	0x7e,	0xb6,	0xbd,	0xc7,	0xbb,	0xb1,	0x6f,	0x47,	0x3d,	0x3d,	0x44,	0x69,
0xad,	0xbc,	0xc5,	0xbd,	0xb2,	0x70,	0x47,	0x3d,	0x3e,	0x45,	0x75,	0xb3,	0xc0,	0xc2,	0xbe,	0x9b,
0x57,	0x40,	0x3d,	0x3f,	0x60,	0xa4,	0xbf,	0xc1,	0xc1,	0xa3,	0x60,	0x3e,	0x3f,	0x3e,	0x61,	0xa4,
0xc2,	0xbf,	0xc1,	0x94,	0x52,	0x3d,	0x3f,	0x44,	0x81,	0xb9,	0xc1,	0xc2,	0xae,	0x68,	0x3e,	0x3f,
0x3f,	0x72,	0xb3,	0xc2,	0xc1,	0xb1,	0x6a,	0x3e,	0x3f,	0x41,	0x78,	0xba,	0xc1,	0xc2,	0xa1,	0x55,
0x3d,	0x3e,	0x50,	0x9a,	0xc2,	0xc0,	0xb9,	0x71,	0x3f,	0x3e,	0x44,	0x88,	0xbf,	0xc0,	0xbe,	0x81,
0x42,	0x3e,	0x43,	0x88,	0xbf,	0xc0,	0xbb,	0x71,	0x3e,	0x3e,	0x4a,	0x9a,	0xc2,	0xc2,	0xa8,	0x54,
0x3e,	0x3e,	0x6a,	0xb9,	0xc0,	0xbe,	0x79,	0x3e,	0x3e,	0x52,	0xa8,	0xc2,	0xc1,	0x8c,	0x42,	0x3e,
0x4e,	0xa5,	0xc1,	0xc1,	0x8c,	0x3f,	0x3f,	0x52,	0xb0,	0xbe,	0xc1,	0x76,	0x3f,	0x3c,	0x69,	0xba,
0xc2,	0xaf,	0x54,	0x3d,	0x44,	0x97,	0xc3,	0xc0,	0x7e,	0x3e,	0x3c,	0x79,	0xbf,	0xc4,	0x96,	0x46,
0x39,	0x68,	0xb7,	0xc6,	0x9f,	0x4e,	0x36,	0x64,	0xb2,	0xca,	0x96,	0x4b,	0x35,	0x70,	0xb9,	0xc8,
0x87,	0x41,	0x3b,	0x84,	0xc3,	0xbd,	0x70,	0x36,	0x4f,	0xa0,	0xcc,	0x9e,	0x4c,	0x38,	0x73,	0xc1,
0xbd,	0x6d,	0x35,	0x55,	0xaa,	0xca,	0x8e,	0x3e,	0x44,	0x97,	0xcc,	0x9c,	0x47,	0x3c,	0x8d,	0xca,
0xa5,	0x4c,	0x3a,	0x87,	0xca,	0xa6,	0x4c,	0x3b,	0x8a,	0xcb,	0x9b,	0x43,	0x43,	0x9c,	0xcb,	0x8e,
0x39,	0x54,	0xb2,	0xc4,	0x72,	0x33,	0x72,	0xc7,	0xa7,	0x48,	0x40,	0x9a,	0xcb,	0x7d,	0x34,	0x6b,
0xc5,	0xa9,	0x46,	0x47,	0xab,	0xc3,	0x66,	0x35,	0x89,	0xcc,	0x87,	0x35,	0x69,	0xc5,	0xa4,	0x3e,
0x59,	0xc1,	0xac,	0x47,	0x4a,	0xb6,	0xb3,	0x49,	0x48,	0xb4,	0xb4,	0x48,	0x4a,	0xb6,	0xb0,	0x43,
0x52,	0xbb,	0xa9,	0x3c,	0x63,	0xc8,	0x8e,	0x35,	0x77,	0xcb,	0x78,	0x35,	0x9b,	0xc2,	0x52,	0x4a,
0xbe,	0xa1,	0x37,	0x76,	0xcc,	0x6f,	0x3a,	0xab,	0xb5,	0x3f,	0x68,	0xca,	0x6e,	0x3c,	0xb1,	0xad,
0x3a,	0x76,	0xc9,	0x5a,	0x49,	0xc1,	0x8b,	0x35,	0xa1,	0xb7,	0x3e,	0x78,	0xcb,	0x56,	0x57,	0xca,
0x6d,	0x42,	0xbd,	0x89,	0x35,	0xb0,	0x9e,	0x36,	0xa5,	0xa7,	0x32,	0x97,	0xb3,	0x39,	0x92,	0xb6,
0x34,	0x9b,	0xad,	0x36,	0x9f,	0xad,	0xaa,	0xc8,	0xbe,	0xc7,	0xb8,	0xb6,	0x95,	0x60,	0x49,	0x42,
0x3b,	0x3d,	0x41,	0x4c,	0x66,	0xa1,	0xb3,	0xbf,	0xc2,	0xc4,	0xbe,	0xb5,	0x9a,	0x5e,	0x4b,	0x3f,
0x3d,	0x3b,	0x46,	0x4e,	0x81,	0xaf,	0xba,	0xc2,	0xc4,	0xbf,	0xb6,	0x9f,	0x64,	0x48,	0x41,	0x3a,
0x3f,	0x45,	0x5c,	0x97,	0xb6,	0xbd,	0xc5,	0xc1,	0xba,	0xa8,	0x70,	0x48,	0x43,	0x39,	0x40,	0x45,
0x62,	0x9e,	0xba,	0xbf,	0xc6,	0xbd,	0xb7,	0x8c,	0x52,	0x44,	0x3b,	0x3d,	0x45,	0x5a,	0x99,	0xb9,
0xbf,	0xc5,	0xbc,	0xb2,	0x7b,	0x4b,	0x43,	0x3a,	0x43,	0x4b,	0x7e,	0xb3,	0xbb,	0xc4,	0xbd,	0xb5,
0x88,	0x4e,	0x43,	0x3c,	0x43,	0x4f,	0x85,	0xb6,	0xbc,	0xc4,	0xb8,	0xab,	0x69,	0x48,	0x3f,	0x41,
0x48,	0x70,	0xae,	0xba,	0xc2,	0xba,	0xac,	0x6a,	0x48,	0x40,	0x43,	0x4b,	0x7d,	0xb2,	0xbd,	0xbe,
0xb8,	0x93,	0x55,	0x44,	0x42,	0x45,	0x68,	0xa6,	0xbb,	0xbc,	0xbb,	0x9b,	0x5d,	0x44,	0x44,	0x45,
0x69,	0xa5,	0xbd,	0xba,	0xb9,	0x8c,	0x52,	0x43,	0x45,	0x4d,	0x87,	0xb5,	0xba,	0xbb,	0xa5,	0x65,
0x45,	0x46,	0x48,	0x7b,	0xb1,	0xba,	0xba,	0xa7,	0x67,	0x45,	0x47,	0x4b,	0x80,	0xb5,	0xb8,	0xb8,
0x97,	0x56,	0x47,	0x46,	0x5d,	0x9f,	0xb8,	0xb8,	0xad,	0x6d,	0x48,	0x48,	0x50,	0x8e,	0xb7,	0xb6,
0xb2,	0x77,	0x4a,	0x48,	0x50,	0x8e,	0xb6,	0xb6,	0xad,	0x6d,	0x49,	0x49,	0x58,	0x9c,	0xb6,	0xb6,
0x9b,	0x57,	0x4a,	0x4a,	0x79,	0xb2,	0xb3,	0xb0,	0x73,	0x4a,	0x4a,	0x61,	0xa5,	0xb4,	0xb2,	0x80,
0x4c,	0x4c,	0x5d,	0xa3,	0xb3,	0xb3,	0x81,	0x4c,	0x4d,	0x62,	0xaa,	0xb0,	0xb1,	0x70,	0x4e,	0x4b,
0x76,	0xae,	0xb3,	0x9e,	0x5a,	0x4c,	0x56,	0x97,	0xb3,	0xae,	0x77,	0x4d,	0x4f,	0x81,	0xb1,	0xb1,
0x8a,	0x51,	0x4d,	0x74,	0xac,	0xb2,	0x92,	0x56,	0x4c,	0x70,	0xa9,	0xb3,	0x8b,	0x55,	0x4c,	0x7a,
0xac,	0xb0,	0x80,	0x50,	0x53,	0x88,	0xb1,	0xa7,	0x70,	0x4b,	0x65,	0x9d,	0xb3,	0x8f,	0x58,	0x51,
0x7d,	0xaf,	0xa5,	0x6e,	0x4c,	0x6b,	0xa2,	0xaf,	0x84,	0x51,	0x5c,	0x94,	0xb2,	0x8d,	0x57,	0x56,
0x8e,	0xb1,	0x93,	0x5a,	0x55,	0x8a,	0xb0,	0x93,	0x5b,	0x57,	0x8c,	0xb0,	0x8a,	0x56,	0x5e,	0x97,
0xad,	0x83,	0x52,	0x6a,	0xa2,	0xa6,	0x71,	0x52,	0x7d,	0xac,	0x92,	0x5b,	0x5e,	0x95,	0xaa,	0x78,
0x53,	0x79,	0xaa,	0x92,	0x5b,	0x63,	0x9d,	0xa3,	0x6c,	0x58,	0x8a,	0xa9,	0x7e,	0x56,	0x79,	0xa7,
0x8d,	0x5a,	0x70,	0xa5,	0x93,	0x5e,	0x68,	0xa0,	0x96,	0x60,	0x67,	0x9e,	0x96,	0x60,	0x69,	0x9f,
0x94,	0x5e,	0x70,	0xa1,	0x8e,	0x5d,	0x77,	0xa4,	0x81,	0x5c,	0x82,	0xa3,	0x76,	0x5f,	0x91,	0x9b,
0x67,	0x6c,	0x9e,	0x8a,	0x5e,	0x81,	0xa0,	0x73,	0x64,	0x96,	0x92,	0x62,	0x7e,	0x9e,	0x73,	0x67,
0x97,	0x8d,	0x63,	0x84,	0x9a,	0x6d,	0x6f,	0x9a,	0x7e,	0x65,	0x90,	0x8f,	0x67,	0x82,	0x98,	0x6d,
0x76,	0x98,	0x75,	0x6e,	0x95,	0x7e,	0x6c,	0x92,	0x84,	0x6b,	0x8d,	0x87,	0x6a,	0x8a,	0x8a,	0x6d,
0x87,	0x8a,	0x6d,	0x89,	0x86,	0x70,	0x88,	0x87,	0x88,	0x8d,	0x8a,	0x8b,	0x88,	0x87,	0x81,	0x7c,
0x7b,	0x7d,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,
0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,
0x7f,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,
0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x80,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x80,	0x7f,	0x80,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x7f,
0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,
0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x7f,	0x80,	0x7f,	0x80,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x80,	0x80,
0x7f,	0x80,	0x7f,	0x80,	0x80,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x7f,	0x80,	0x7f,	0x80,
0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x7f,
0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f,	0x80,	0x80,	0x7f,	0x80,	0x7f};