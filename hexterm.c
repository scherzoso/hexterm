#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEXTERM_SEMVER "0.1.0"

const char hexterm_help_string[] =
	"usage: hexterm [-h|-v] [-H|-T] <args>\n"
	"\n"
	"Options:\n"
	" -H    - Treat arguments as hex colours to find similar indices for\n"
	" -T    - Treat arguments as colour indicies to output as hex\n"
	" -h    - Print this help text\n"
	" -v    - Print version information\n"
	"\n";


typedef struct hex_colour_s hex_colour;
typedef uint8_t             term_colour;

struct hex_colour_s {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct xterm_entry_s {
	char         name[18];
	hex_colour   h;
	term_colour  t;
};

struct xterm_entry_s termcols[256] = {
	{"Black",             {  0,   0,   0},   0},
	{"Maroon",            {128,   0,   0},   1},
	{"Green",             {  0, 128,   0},   2},
	{"Olive",             {128, 128,   0},   3},
	{"Navy",              {  0,   0, 128},   4},
	{"Purple",            {128,   0, 128},   5},
	{"Teal",              {  0, 128, 128},   6},
	{"Silver",            {192, 192, 192},   7},
	{"Grey",              {128, 128, 128},   8},
	{"Red",               {255,   0,   0},   9},
	{"Lime",              {  0, 255,   0},  10},
	{"Yellow",            {255, 255,   0},  11},
	{"Blue",              {  0,   0, 255},  12},
	{"Fuchsia",           {255,   0, 255},  13},
	{"Aqua",              {  0, 255, 255},  14},
	{"White",             {255, 255, 255},  15},
	{"Grey0",             {  0,   0,   0},  16},
	{"NavyBlue",          {  0,   0,  95},  17},
	{"DarkBlue",          {  0,   0, 135},  18},
	{"Blue3",             {  0,   0, 175},  19},
	{"Blue3",             {  0,   0, 215},  20},
	{"Blue1",             {  0,   0, 255},  21},
	{"DarkGreen",         {  0,  95,   0},  22},
	{"DeepSkyBlue4",      {  0,  95,  95},  23},
	{"DeepSkyBlue4",      {  0,  95, 135},  24},
	{"DeepSkyBlue4",      {  0,  95, 175},  25},
	{"DodgerBlue3",       {  0,  95, 215},  26},
	{"DodgerBlue2",       {  0,  95, 255},  27},
	{"Green4",            {  0, 135,   0},  28},
	{"SpringGreen4",      {  0, 135,  95},  29},
	{"Turquoise4",        {  0, 135, 135},  30},
	{"DeepSkyBlue3",      {  0, 135, 175},  31},
	{"DeepSkyBlue3",      {  0, 135, 215},  32},
	{"DodgerBlue1",       {  0, 135, 255},  33},
	{"Green3",            {  0, 175,   0},  34},
	{"SpringGreen3",      {  0, 175,  95},  35},
	{"DarkCyan",          {  0, 175, 135},  36},
	{"LightSeaGreen",     {  0, 175, 175},  37},
	{"DeepSkyBlue2",      {  0, 175, 215},  38},
	{"DeepSkyBlue1",      {  0, 175, 255},  39},
	{"Green3",            {  0, 215,   0},  40},
	{"SpringGreen3",      {  0, 215,  95},  41},
	{"SpringGreen2",      {  0, 215, 135},  42},
	{"Cyan3",             {  0, 215, 175},  43},
	{"DarkTurquoise",     {  0, 215, 215},  44},
	{"Turquoise2",        {  0, 215, 255},  45},
	{"Green1",            {  0, 255,   0},  46},
	{"SpringGreen2",      {  0, 255,  95},  47},
	{"SpringGreen1",      {  0, 255, 135},  48},
	{"MediumSpringGreen", {  0, 255, 175},  49},
	{"Cyan2",             {  0, 255, 215},  50},
	{"Cyan1",             {  0, 255, 255},  51},
	{"DarkRed",           { 95,   0,   0},  52},
	{"DeepPink4",         { 95,   0,  95},  53},
	{"Purple4",           { 95,   0, 135},  54},
	{"Purple4",           { 95,   0, 175},  55},
	{"Purple3",           { 95,   0, 215},  56},
	{"BlueViolet",        { 95,   0, 255},  57},
	{"Orange4",           { 95,  95,   0},  58},
	{"Grey37",            { 95,  95,  95},  59},
	{"MediumPurple4",     { 95,  95, 135},  60},
	{"SlateBlue3",        { 95,  95, 175},  61},
	{"SlateBlue3",        { 95,  95, 215},  62},
	{"RoyalBlue1",        { 95,  95, 255},  63},
	{"Chartreuse4",       { 95, 135,   0},  64},
	{"DarkSeaGreen4",     { 95, 135,  95},  65},
	{"PaleTurquoise4",    { 95, 135, 135},  66},
	{"SteelBlue",         { 95, 135, 175},  67},
	{"SteelBlue3",        { 95, 135, 215},  68},
	{"CornflowerBlue",    { 95, 135, 255},  69},
	{"Chartreuse3",       { 95, 175,   0},  70},
	{"DarkSeaGreen4",     { 95, 175,  95},  71},
	{"CadetBlue",         { 95, 175, 135},  72},
	{"CadetBlue",         { 95, 175, 175},  73},
	{"SkyBlue3",          { 95, 175, 215},  74},
	{"SteelBlue1",        { 95, 175, 255},  75},
	{"Chartreuse3",       { 95, 215,   0},  76},
	{"PaleGreen3",        { 95, 215,  95},  77},
	{"SeaGreen3",         { 95, 215, 135},  78},
	{"Aquamarine3",       { 95, 215, 175},  79},
	{"MediumTurquoise",   { 95, 215, 215},  80},
	{"SteelBlue1",        { 95, 215, 255},  81},
	{"Chartreuse2",       { 95, 255,   0},  82},
	{"SeaGreen2",         { 95, 255,  95},  83},
	{"SeaGreen1",         { 95, 255, 135},  84},
	{"SeaGreen1",         { 95, 255, 175},  85},
	{"Aquamarine1",       { 95, 255, 215},  86},
	{"DarkSlateGray2",    { 95, 255, 255},  87},
	{"DarkRed",           {135,   0,   0},  88},
	{"DeepPink4",         {135,   0,  95},  89},
	{"DarkMagenta",       {135,   0, 135},  90},
	{"DarkMagenta",       {135,   0, 175},  91},
	{"DarkViolet",        {135,   0, 215},  92},
	{"Purple",            {135,   0, 255},  93},
	{"Orange4",           {135,  95,   0},  94},
	{"LightPink4",        {135,  95,  95},  95},
	{"Plum4",             {135,  95, 135},  96},
	{"MediumPurple3",     {135,  95, 175},  97},
	{"MediumPurple3",     {135,  95, 215},  98},
	{"SlateBlue1",        {135,  95, 255},  99},
	{"Yellow4",           {135, 135,   0}, 100},
	{"Wheat4",            {135, 135,  95}, 101},
	{"Grey53",            {135, 135, 135}, 102},
	{"LightSlateGrey",    {135, 135, 175}, 103},
	{"MediumPurple",      {135, 135, 215}, 104},
	{"LightSlateBlue",    {135, 135, 255}, 105},
	{"Yellow4",           {135, 175,   0}, 106},
	{"DarkOliveGreen3",   {135, 175,  95}, 107},
	{"DarkSeaGreen",      {135, 175, 135}, 108},
	{"LightSkyBlue3",     {135, 175, 175}, 109},
	{"LightSkyBlue3",     {135, 175, 215}, 110},
	{"SkyBlue2",          {135, 175, 255}, 111},
	{"Chartreuse2",       {135, 215,   0}, 112},
	{"DarkOliveGreen3",   {135, 215,  95}, 113},
	{"PaleGreen3",        {135, 215, 135}, 114},
	{"DarkSeaGreen3",     {135, 215, 175}, 115},
	{"DarkSlateGray3",    {135, 215, 215}, 116},
	{"SkyBlue1",          {135, 215, 255}, 117},
	{"Chartreuse1",       {135, 255,   0}, 118},
	{"LightGreen",        {135, 255,  95}, 119},
	{"LightGreen",        {135, 255, 135}, 120},
	{"PaleGreen1",        {135, 255, 175}, 121},
	{"Aquamarine1",       {135, 255, 215}, 122},
	{"DarkSlateGray1",    {135, 255, 255}, 123},
	{"Red3",              {175,   0,   0}, 124},
	{"DeepPink4",         {175,   0,  95}, 125},
	{"MediumVioletRed",   {175,   0, 135}, 126},
	{"Magenta3",          {175,   0, 175}, 127},
	{"DarkViolet",        {175,   0, 215}, 128},
	{"Purple",            {175,   0, 255}, 129},
	{"DarkOrange3",       {175,  95,   0}, 130},
	{"IndianRed",         {175,  95,  95}, 131},
	{"HotPink3",          {175,  95, 135}, 132},
	{"MediumOrchid3",     {175,  95, 175}, 133},
	{"MediumOrchid",      {175,  95, 215}, 134},
	{"MediumPurple2",     {175,  95, 255}, 135},
	{"DarkGoldenrod",     {175, 135,   0}, 136},
	{"LightSalmon3",      {175, 135,  95}, 137},
	{"RosyBrown",         {175, 135, 135}, 138},
	{"Grey63",            {175, 135, 175}, 139},
	{"MediumPurple2",     {175, 135, 215}, 140},
	{"MediumPurple1",     {175, 135, 255}, 141},
	{"Gold3",             {175, 175,   0}, 142},
	{"DarkKhaki",         {175, 175,  95}, 143},
	{"NavajoWhite3",      {175, 175, 135}, 144},
	{"Grey69",            {175, 175, 175}, 145},
	{"LightSteelBlue3",   {175, 175, 215}, 146},
	{"LightSteelBlue",    {175, 175, 255}, 147},
	{"Yellow3",           {175, 215,   0}, 148},
	{"DarkOliveGreen3",   {175, 215,  95}, 149},
	{"DarkSeaGreen3",     {175, 215, 135}, 150},
	{"DarkSeaGreen2",     {175, 215, 175}, 151},
	{"LightCyan3",        {175, 215, 215}, 152},
	{"LightSkyBlue1",     {175, 215, 255}, 153},
	{"GreenYellow",       {175, 255,   0}, 154},
	{"DarkOliveGreen2",   {175, 255,  95}, 155},
	{"PaleGreen1",        {175, 255, 135}, 156},
	{"DarkSeaGreen2",     {175, 255, 175}, 157},
	{"DarkSeaGreen1",     {175, 255, 215}, 158},
	{"PaleTurquoise1",    {175, 255, 255}, 159},
	{"Red3",              {215,   0,   0}, 160},
	{"DeepPink3",         {215,   0,  95}, 161},
	{"DeepPink3",         {215,   0, 135}, 162},
	{"Magenta3",          {215,   0, 175}, 163},
	{"Magenta3",          {215,   0, 215}, 164},
	{"Magenta2",          {215,   0, 255}, 165},
	{"DarkOrange3",       {215,  95,   0}, 166},
	{"IndianRed",         {215,  95,  95}, 167},
	{"HotPink3",          {215,  95, 135}, 168},
	{"HotPink2",          {215,  95, 175}, 169},
	{"Orchid",            {215,  95, 215}, 170},
	{"MediumOrchid1",     {215,  95, 255}, 171},
	{"Orange3",           {215, 135,   0}, 172},
	{"LightSalmon3",      {215, 135,  95}, 173},
	{"LightPink3",        {215, 135, 135}, 174},
	{"Pink3",             {215, 135, 175}, 175},
	{"Plum3",             {215, 135, 215}, 176},
	{"Violet",            {215, 135, 255}, 177},
	{"Gold3",             {215, 175,   0}, 178},
	{"LightGoldenrod3",   {215, 175,  95}, 179},
	{"Tan",               {215, 175, 135}, 180},
	{"MistyRose3",        {215, 175, 175}, 181},
	{"Thistle3",          {215, 175, 215}, 182},
	{"Plum2",             {215, 175, 255}, 183},
	{"Yellow3",           {215, 215,   0}, 184},
	{"Khaki3",            {215, 215,  95}, 185},
	{"LightGoldenrod2",   {215, 215, 135}, 186},
	{"LightYellow3",      {215, 215, 175}, 187},
	{"Grey84",            {215, 215, 215}, 188},
	{"LightSteelBlue1",   {215, 215, 255}, 189},
	{"Yellow2",           {215, 255,   0}, 190},
	{"DarkOliveGreen1",   {215, 255,  95}, 191},
	{"DarkOliveGreen1",   {215, 255, 135}, 192},
	{"DarkSeaGreen1",     {215, 255, 175}, 193},
	{"Honeydew2",         {215, 255, 215}, 194},
	{"LightCyan1",        {215, 255, 255}, 195},
	{"Red1",              {255,   0,   0}, 196},
	{"DeepPink2",         {255,   0,  95}, 197},
	{"DeepPink1",         {255,   0, 135}, 198},
	{"DeepPink1",         {255,   0, 175}, 199},
	{"Magenta2",          {255,   0, 215}, 200},
	{"Magenta1",          {255,   0, 255}, 201},
	{"OrangeRed1",        {255,  95,   0}, 202},
	{"IndianRed1",        {255,  95,  95}, 203},
	{"IndianRed1",        {255,  95, 135}, 204},
	{"HotPink",           {255,  95, 175}, 205},
	{"HotPink",           {255,  95, 215}, 206},
	{"MediumOrchid1",     {255,  95, 255}, 207},
	{"DarkOrange",        {255, 135,   0}, 208},
	{"Salmon1",           {255, 135,  95}, 209},
	{"LightCoral",        {255, 135, 135}, 210},
	{"PaleVioletRed1",    {255, 135, 175}, 211},
	{"Orchid2",           {255, 135, 215}, 212},
	{"Orchid1",           {255, 135, 255}, 213},
	{"Orange1",           {255, 175,   0}, 214},
	{"SandyBrown",        {255, 175,  95}, 215},
	{"LightSalmon1",      {255, 175, 135}, 216},
	{"LightPink1",        {255, 175, 175}, 217},
	{"Pink1",             {255, 175, 215}, 218},
	{"Plum1",             {255, 175, 255}, 219},
	{"Gold1",             {255, 215,   0}, 220},
	{"LightGoldenrod2",   {255, 215,  95}, 221},
	{"LightGoldenrod2",   {255, 215, 135}, 222},
	{"NavajoWhite1",      {255, 215, 175}, 223},
	{"MistyRose1",        {255, 215, 215}, 224},
	{"Thistle1",          {255, 215, 255}, 225},
	{"Yellow1",           {255, 255,   0}, 226},
	{"LightGoldenrod1",   {255, 255,  95}, 227},
	{"Khaki1",            {255, 255, 135}, 228},
	{"Wheat1",            {255, 255, 175}, 229},
	{"Cornsilk1",         {255, 255, 215}, 230},
	{"Grey100",           {255, 255, 255}, 231},
	{"Grey3",             {  8,   8,   8}, 232},
	{"Grey7",             { 18,  18,  18}, 233},
	{"Grey11",            { 28,  28,  28}, 234},
	{"Grey15",            { 38,  38,  38}, 235},
	{"Grey19",            { 48,  48,  48}, 236},
	{"Grey23",            { 58,  58,  58}, 237},
	{"Grey27",            { 68,  68,  68}, 238},
	{"Grey30",            { 78,  78,  78}, 239},
	{"Grey35",            { 88,  88,  88}, 240},
	{"Grey39",            { 98,  98,  98}, 241},
	{"Grey42",            {108, 108, 108}, 242},
	{"Grey46",            {118, 118, 118}, 243},
	{"Grey50",            {128, 128, 128}, 244},
	{"Grey54",            {138, 138, 138}, 245},
	{"Grey58",            {148, 148, 148}, 246},
	{"Grey62",            {158, 158, 158}, 247},
	{"Grey66",            {168, 168, 168}, 248},
	{"Grey70",            {178, 178, 178}, 249},
	{"Grey74",            {188, 188, 188}, 250},
	{"Grey78",            {198, 198, 198}, 251},
	{"Grey82",            {208, 208, 208}, 252},
	{"Grey85",            {218, 218, 218}, 253},
	{"Grey89",            {228, 228, 228}, 254},
	{"Grey93",            {238, 238, 238}, 255}
};


static hex_colour strhex(const char *s)
{
	hex_colour h = {0, 0, 0};
	size_t     l = strnlen(s, 7);

	if (l == 6) {
		sscanf(s, "%2hhx", &h.r);
		sscanf(s + 2, "%2hhx", &h.g);
		sscanf(s + 4, "%2hhx", &h.b);
	} else if (l == 3) {
		char realhex[7];
		memset(realhex, 0, 7);
		memcpy(realhex, s, 3);
		memcpy(realhex + 3, s, 3);

		return strhex(realhex);
	}

	/* Just return black if we have an invalid hex string */
	return h;
}

static hex_colour termhex(const term_colour t)
{
	return termcols[t].h;
}

static double hex_term_dsquared(hex_colour h, term_colour t)
{
	double x2 = pow((double)termcols[t].h.r - h.r , 2.0);
	double y2 = pow((double)termcols[t].h.g - h.g , 2.0);
	double z2 = pow((double)termcols[t].h.b - h.b , 2.0);

	return (x2 + y2 + z2);
}

static term_colour hexterm(const hex_colour h)
{
	for (size_t i = 0; i < 256; i++) {
		if (h.r == termcols[i].h.r
		&& h.g == termcols[i].h.g
		&& h.b == termcols[i].h.b)
			return i;
	}

	/*
	 * Can't find exact match in table, so now we need to check distance
	 * against each entry and return the term colour with the smallest
	 * distance from the hex colour we received
	 */
	double min_d2 = INFINITY;
	term_colour t = 0;

	for (size_t i = 0; i < 256; i++) {
		double this_d2 = hex_term_dsquared(h, termcols[i].t);
		if (this_d2 < min_d2) {
			min_d2 = this_d2;
			t = i;
		}
	}

	return t;
}

static term_colour strterm(const char *s)
{
	return (term_colour)(strtoul(s, NULL, 0) % 256);
}


enum exec_mode {
	EXIT_IMMEDIATELY,
	HEX_TO_TERM,
	TERM_TO_HEX
};

int main(int argc, char **argv)
{
	enum exec_mode mode = HEX_TO_TERM;

	while (1) {
		static int opt = 0;
		static const char sopts[] = "HThv";

		opt = getopt(argc, argv, sopts);

		if (opt == -1)
			break;

		switch (opt) {
		case 'H':
			mode = HEX_TO_TERM;
			break;
		case 'T':
			mode = TERM_TO_HEX;
			break;
		case 'h':
			printf(hexterm_help_string);
			mode = EXIT_IMMEDIATELY;
			break;
		case 'v':
			printf("hexterm version " HEXTERM_SEMVER "\n");
			mode = EXIT_IMMEDIATELY;
			break;
		default:
			return 1;
		}
	}

	if (mode == HEX_TO_TERM) {
		for (; optind < argc; optind++) {
			hex_colour  h = strhex(argv[optind]);
			term_colour t = hexterm(h);
			printf("%02x%02x%02x (hex) = %3d (term: \"%s\")\n",
				h.r, h.g, h.b, t, termcols[t].name);
		}
	} else if (mode == TERM_TO_HEX) {
		for (; optind < argc; optind++) {
			term_colour t = strterm(argv[optind]);
			hex_colour  h = termhex(t);
			printf("%3d (term: \"%s\") = %02x%02x%02x (hex)\n",
				t, termcols[t].name, h.r, h.g, h.b);
		}
	}

	return 0;
}
