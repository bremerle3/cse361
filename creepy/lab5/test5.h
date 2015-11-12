/* Test5.h - Fifth data file for CSE 361S Lab 5 */

#define NUM_STUDENTS	100

static student_rec students[NUM_STUDENTS] =
	{ { "ID 0",    8,  70,   0,  17,  13, 0, 'F', 0 },
	  { "ID 1",   34,  81,  67,  70,  75, 0, 'F', 0 },
	  { "ID 2",   13,  30,  39,  11,  43, 0, 'F', 0 },
	  { "ID 3",    6,  57,  30,  29,  73, 0, 'F', 0 },
	  { "ID 4",   35,  94,  90,  20,  95, 0, 'F', 0 },
	  { "ID 5",    2,  43,  19,   7,  78, 0, 'F', 0 },
	  { "ID 6",   22,  91,  67,  39,  14, 0, 'F', 0 },
	  { "ID 7",   90,  79,   3,  52,  14, 0, 'F', 0 },
	  { "ID 8",   37,  48,  73,  14,  23, 0, 'F', 0 },
	  { "ID 9",   69,   2,  31,  17,  54, 0, 'F', 0 },
	  { "ID 10",   1,  41,  69,  67,  15, 0, 'F', 0 },
	  { "ID 11",  15,  99,  53,  53,  41, 0, 'F', 0 },
	  { "ID 12",  48,  19,  91,  74,  91, 0, 'F', 0 },
	  { "ID 13",   5,  68,  82,  81,  13, 0, 'F', 0 },
	  { "ID 14",  84,  56,  18,  37,  86, 0, 'F', 0 },
	  { "ID 15",  62,  42,  87,  11,  66, 0, 'F', 0 },
	  { "ID 16",  81,  30,  75,  54,  44, 0, 'F', 0 },
	  { "ID 17",  96,  67,  37,  89,  42, 0, 'F', 0 },
	  { "ID 18",  30,  58,  20,  53,  39, 0, 'F', 0 },
	  { "ID 19",   5,  96,  73,  93,   6, 0, 'F', 0 },
	  { "ID 20",  16,  51,  67,  93,  17, 0, 'F', 0 },
	  { "ID 21",  67,  16,  41,  99,  84, 0, 'F', 0 },
	  { "ID 22",   4,  91,  12,  24,  64, 0, 'F', 0 },
	  { "ID 23",  67,  63,  36,  56,  89, 0, 'F', 0 },
	  { "ID 24",  37,  57,  18,  54,  75, 0, 'F', 0 },
	  { "ID 25",  12,  13,  20,  29,  22, 0, 'F', 0 },
	  { "ID 26",  42,  28,  99,  10,   5, 0, 'F', 0 },
	  { "ID 27",  81,  59,  95,  19,  99, 0, 'F', 0 },
	  { "ID 28",  90,  78,  38,  77,  71, 0, 'F', 0 },
	  { "ID 29",  93,  59,  87,  42,   0, 0, 'F', 0 },
	  { "ID 30",  96,  93,  94,  45,  46, 0, 'F', 0 },
	  { "ID 31",  58,  38,  92,  19,  72, 0, 'F', 0 },
	  { "ID 32",  90,  66,  76,  94,  28, 0, 'F', 0 },
	  { "ID 33",  17,  82,  80,  91,  98, 0, 'F', 0 },
	  { "ID 34",  99,  32,  48,  51,  44, 0, 'F', 0 },
	  { "ID 35",  72,  11,   9,  66,  64, 0, 'F', 0 },
	  { "ID 36",  36,  45,  40,  93,  60, 0, 'F', 0 },
	  { "ID 37",  70,  45,  79,  17,  79, 0, 'F', 0 },
	  { "ID 38",  36,  77,  85,  48,  68, 0, 'F', 0 },
	  { "ID 39",  89,  75,  88,  63,  29, 0, 'F', 0 },
	  { "ID 40",  13,  96,   4,  72,  15, 0, 'F', 0 },
	  { "ID 41",  28,  12,  99,  83,  10, 0, 'F', 0 },
	  { "ID 42",  81,  15,  87,  91,  46, 0, 'F', 0 },
	  { "ID 43",  94,  76,  91,   3,  51, 0, 'F', 0 },
	  { "ID 44",  38,  92,  61,  76,  94, 0, 'F', 0 },
	  { "ID 45",  45,  33,  21,   0,   6, 0, 'F', 0 },
	  { "ID 46",  15,  41,  35,  92,  31, 0, 'F', 0 },
	  { "ID 47",   0,  37,  91,  88,  90, 0, 'F', 0 },
	  { "ID 48",  73,  72,  81,  65,   5, 0, 'F', 0 },
	  { "ID 49",  56,  52,  24,  42,  71, 0, 'F', 0 },
	  { "ID 50",  41,  12,  97,  59,  73, 0, 'F', 0 },
	  { "ID 51",  28,  77,   7,  90,  28, 0, 'F', 0 },
	  { "ID 52",  87,  21,  55,  29,  57, 0, 'F', 0 },
	  { "ID 53",  40,  71,  86,  86,  10, 0, 'F', 0 },
	  { "ID 54",   6,  37,  66,  11,  46, 0, 'F', 0 },
	  { "ID 55",  23,  69,  30,  97,  17, 0, 'F', 0 },
	  { "ID 56",  57,   9,  10,   6,  52, 0, 'F', 0 },
	  { "ID 57",   8,  26,  29,  90,  23, 0, 'F', 0 },
	  { "ID 58",  40,  10,  15,  80,  22, 0, 'F', 0 },
	  { "ID 59",  50,  72,  45,  69,  54, 0, 'F', 0 },
	  { "ID 60",   3,   4,  42,  74,  31, 0, 'F', 0 },
	  { "ID 61",   9,  99,  70,  53,  56, 0, 'F', 0 },
	  { "ID 62",  45,  25,  92,  89,  17, 0, 'F', 0 },
	  { "ID 63",   6,  24,  92,  61,  51, 0, 'F', 0 },
	  { "ID 64",  41,   2,  73,  85,  43, 0, 'F', 0 },
	  { "ID 65",  79,  75,  86,  99,  71, 0, 'F', 0 },
	  { "ID 66",  10,  65,  75,  22,  90, 0, 'F', 0 },
	  { "ID 67",  80,  32,  58,  79,  82, 0, 'F', 0 },
	  { "ID 68",  79,  52,  53,  54,  77, 0, 'F', 0 },
	  { "ID 69",  71,  81,  69,  34,  35, 0, 'F', 0 },
	  { "ID 70",  51,  13,  60,  92,   0, 0, 'F', 0 },
	  { "ID 71",  76,  26,  40,  13,  32, 0, 'F', 0 },
	  { "ID 72",  36,  94,  35,  40,  22, 0, 'F', 0 },
	  { "ID 73",  56,  68,   9,  65,  42, 0, 'F', 0 },
	  { "ID 74",  35,  79,  94,  47,  52, 0, 'F', 0 },
	  { "ID 75",  23,  22,  88,   0,  10, 0, 'F', 0 },
	  { "ID 76",  61,   5,  67,  67,   0, 0, 'F', 0 },
	  { "ID 77",  11,  11,  13,  53,  19, 0, 'F', 0 },
	  { "ID 78",  27,  27,  41,  66,  78, 0, 'F', 0 },
	  { "ID 79",  89,  25,  72,  46,  43, 0, 'F', 0 },
	  { "ID 80",  19,  32,  42,  87,  72, 0, 'F', 0 },
	  { "ID 81",  50,  58,  52,  61,  82, 0, 'F', 0 },
	  { "ID 82",  59,   4,  23,   7,  65, 0, 'F', 0 },
	  { "ID 83",  20,  58,  14,  54,  70, 0, 'F', 0 },
	  { "ID 84",  14,  24,  66,   0,  37, 0, 'F', 0 },
	  { "ID 85",   8,  30,  82,  69,  71, 0, 'F', 0 },
	  { "ID 86",  99,  73,  64,  11,  49, 0, 'F', 0 },
	  { "ID 87",  39,  42,  39,   6,  71, 0, 'F', 0 },
	  { "ID 88",  13,  59,  50,  11,  89, 0, 'F', 0 },
	  { "ID 89",   8,   9,  75,  27,  76, 0, 'F', 0 },
	  { "ID 90",  45,  20,  88,  78,  41, 0, 'F', 0 },
	  { "ID 91",  41,  42,  29,  23,  34, 0, 'F', 0 },
	  { "ID 92",  14,  72,  86,   4,  59, 0, 'F', 0 },
	  { "ID 93",  27,  47,  96,  36,  72, 0, 'F', 0 },
	  { "ID 94",  11,  56,  84,  69,  26, 0, 'F', 0 },
	  { "ID 95",  30,  10,  80,   5,  94, 0, 'F', 0 },
	  { "ID 96",  69,   8,  98,  19,  59, 0, 'F', 0 },
	  { "ID 97",  92,  43,   1,  26,  73, 0, 'F', 0 },
	  { "ID 98",  48,  21,  91,  21,  53, 0, 'F', 0 },
	  { "ID 99",  82,  92,  62,  62,  85, 0, 'F', 0 } };
