#include "procfamily.h"
#include "gradation.h"

const uint16_t GradationTable[GRADATIONTABLE] = {
		0,//0
		2,//1
		5,//2
		7,//3
		10,//4
		12,//5
		15,//6
		17,//7
		20,//8
		22,//9
		24,//10
		27,//11
		29,//12
		32,//13
		34,//14
		37,//15
		39,//16
		42,//17
		44,//18
		46,//19
		49,//20
		51,//21
		54,//22
		56,//23
		59,//24
		61,//25
		63,//26
		66,//27
		68,//28
		71,//29
		73,//30
		76,//31
		78,//32
		81,//33
		83,//34
		85,//35
		88,//36
		90,//37
		93,//38
		95,//39
		98,//40
		100,//41
		103,//42
		105,//43
		107,//44
		110,//45
		112,//46
		115,//47
		117,//48
		120,//49
		122,//50
		125,//51
		127,//52
		129,//53
		132,//54
		134,//55
		137,//56
		139,//57
		142,//58
		144,//59
		146,//60
		149,//61
		151,//62
		154,//63
		156,//64
		161,//65
		166,//66
		171,//67
		176,//68
		181,//69
		186,//70
		190,//71
		195,//72
		200,//73
		205,//74
		210,//75
		215,//76
		220,//77
		225,//78
		229,//79
		234,//80
		239,//81
		244,//82
		249,//83
		254,//84
		259,//85
		264,//86
		269,//87
		273,//88
		278,//89
		283,//90
		288,//91
		293,//92
		298,//93
		303,//94
		308,//95
		313,//96
		322,//97
		332,//98
		342,//99
		352,//100
		361,//01
		371,//02
		381,//03
		391,//04
		400,//05
		410,//06
		420,//07
		430,//08
		439,//09
		449,//110
		459,//11
		469,//12
		479,//13
		488,//14
		498,//15
		508,//16
		518,//17
		527,//18
		537,//19
		547,//120
		557,//21
		566,//22
		576,//23
		586,//24
		596,//25
		605,//26
		615,//27
		625,//28
		645,//29
		664,//130
		684,//31
		703,//32
		723,//33
		742,//34
		762,//35
		781,//36
		801,//37
		820,//38
		840,//39
		859,//140
		879,//41
		898,//42
		918,//43
		938,//44
		957,//45
		977,//46
		996,//47
		1016,//48
		1035,//49
		1055,//150
		1074,//51
		1094,//52
		1113,//53
		1133,//54
		1152,//55
		1172,//56
		1191,//57
		1211,//58
		1230,//59
		1250,//160
		1289,//61
		1328,//62
		1367,//63
		1406,//64
		1445,//65
		1484,//66
		1523,//67
		1563,//68
		1602,//69
		1641,//170
		1680,//71
		1719,//72
		1758,//73
		1797,//74
		1836,//75
		1875,//76
		1914,//77
		1953,//78
		1992,//79
		2031,//180
		2070,//81
		2109,//82
		2148,//83
		2188,//84
		2227,//85
		2266,//86
		2305,//87
		2344,//88
		2383,//89
		2422,//190
		2461,//91
		2500,//92
		2578,//93
		2656,//94
		2734,//95
		2813,//96
		2891,//97
		2969,//98
		3047,//99
		3125,//200
		3203,//01
		3281,//02
		3359,//03
		3438,//04
		3516,//05
		3594,//06
		3672,//07
		3750,//08
		3828,//09
		3906,//210
		3984,//11
		4063,//12
		4141,//13
		4219,//14
		4297,//15
		4375,//16
		4453,//17
		4531,//18
		4609,//19
		4688,//220
		4766,//21
		4844,//22
		4922,//23
		5000,//24
		5156,//25
		5313,//26
		5469,//27
		5625,//28
		5781,//29
		5938,//230
		6094,//31
		6250,//32
		6406,//33
		6563,//34
		6719,//35
		6875,//36
		7031,//37
		7188,//38
		7344,//39
		7500,
		7556,
		7813,
		7969,
		8125,
		8281,
		8438,
		8594,
		8750,
		8906,
		9063,
		9219,
		9375,
		9531,
		9688,
		9844,
};

const uint8_t sinusTable1[256]={
		127,	130,	133,	136,	140,	143,	146,	149,
		152,	155,	158,	161,	164,	167,	170,	173,
		176,	179,	182,	185,	187,	190,	193,	195,
		198,	201,	203,	206,	208,	211,	213,	215,
		218,	220,	222,	224,	226,	228,	230,	232,
		233,	235,	237,	238,	240,	241,	243,	244,
		245,	246,	248,	249,	249,	250,	251,	253,
		253,	253,	254,	254,	254,	255,	255,	255,
		255,	255,	255,	255,	254,	254,	254,	253,
		253,	252,	251,	250,	249,	249,	248,	246,
		245,	244,	243,	241,	240,	238,	237,	235,
		233,	232,	230,	228,	226,	224,	222,	220,
		218,	215,	213,	211,	208,	206,	203,	201,
		198,	195,	193,	190,	187,	185,	182,	179,
		176,	173,	170,	167,	164,	161,	158,	155,
		152,	149,	146,	143,	140,	136,	133,	130,
		127,	124,	121,	118,	114,	111,	108,	105,
		102,	99,		96,		93,		90,		87,		84,		81,
		78,		75,		72,		69,		67,		64,		61,		59,
		56,		53,		51,		48,		46,		43,		41,		39,
		36,		34,		32,		30,		28,		26,		24,		22,
		21,		19,		17,		16,		14,		13,		11,		10,
		9,		8,		6,		5,		5,		4,		3,		2,
		1,		1,		0,		0,		0,		1,		1,		1,
		1,		1,		1,		1,		0,		0,		0,		1,
		1,		2,		3,		4,		5,		5,		6,		8,
		9,		10,		11,		13,		14,		16,		17,		19,
		21,		22,		24,		26,		28,		30,		32,		34,
		36,		39,		41,		43,		46,		48,		51,		53,
		56,		59,		61,		64,		67,		69,		72,		75,
		78,		81,		84,		87,		90,		93,		96,		99,
		102,	105,	108,	111,	114,	118,	121,	124,

};

const uint8_t sinusTable2[128]={
		102,	99,		96,		93,		90,		87,		84,		81,
		78,		75,		72,		69,		67,		64,		61,		59,
		56,		53,		51,		48,		46,		43,		41,		39,
		36,		34,		32,		30,		28,		26,		24,		22,
		21,		19,		17,		16,		14,		13,		11,		10,
		9,		8,		6,		5,		5,		4,		3,		2,
		1,		1,		0,		0,		0,		1,		1,		1,
		1,		1,		1,		1,		1,		1,		1,		1,
		1,		2,		3,		4,		5,		5,		6,		8,
		9,		10,		11,		13,		14,		16,		17,		19,
		21,		22,		24,		26,		28,		30,		32,		34,
		36,		39,		41,		43,		46,		48,		51,		53,
		56,		59,		61,		64,		67,		69,		72,		75,
		78,		81,		84,		87,		90,		93,		96,		99,
		102,	105,	108,	111,	114,	118,	121,	124,
		127,	124,	121,	118,	114,	111,	108,	105,
};
