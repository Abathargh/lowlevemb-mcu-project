#include "ay38910a.h"

struct note {
	int note;
	int duration;
};

const struct note parallax[42] = {
	{NOTE(C_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(C_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(C_NOTE, 2), 250},
	{NOTE(F_SHARP_NOTE, 2), 250},

	{NOTE(C_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(C_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(C_NOTE, 2), 250},
	{NOTE(C_SHARP_NOTE, 2), 250},

	{NOTE(D_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_NOTE, 2), 250},
	{NOTE(F_SHARP_NOTE, 2), 250},

	{NOTE(D_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 550},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_NOTE, 2), 500},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(A_SHARP_NOTE, 2), 250},
	{NOTE(D_NOTE, 2), 250},
	{NOTE(D_SHARP_NOTE, 2), 250},
	{NOTE(D_NOTE, 2), 250},
	{NOTE(C_NOTE, 2), 250},
	{NOTE(D_NOTE, 2), 250},
};

const struct note verse[48] = {
	{NOTE(G_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(G_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(G_NOTE, 3), 250},
	{NOTE(C_NOTE, 3), 250},
	{NOTE(G_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(G_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(G_NOTE, 3), 250},
	{NOTE(C_NOTE, 3), 250},

	{NOTE(F_SHARP_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(F_SHARP_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(F_SHARP_NOTE, 3), 250},
	{NOTE(C_NOTE, 3), 250},
	{NOTE(F_SHARP_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(F_SHARP_NOTE, 3), 300},
	{NOTE(C_NOTE, 3), 500},
	{NOTE(F_SHARP_NOTE, 3), 250},
	{NOTE(C_NOTE, 3), 250},

	{NOTE(F_NOTE, 3), 300},
	{NOTE(G_NOTE, 2), 500},
	{NOTE(F_NOTE, 3), 300},
	{NOTE(G_NOTE, 2), 500},
	{NOTE(F_NOTE, 3), 250},
	{NOTE(G_NOTE, 2), 250},
	{NOTE(F_NOTE, 3), 300},
	{NOTE(G_NOTE, 2), 500},
	{NOTE(F_NOTE, 3), 300},
	{NOTE(G_NOTE, 2), 500},
	{NOTE(F_NOTE, 3), 250},
	{NOTE(G_NOTE, 2), 250},

	{NOTE(D_SHARP_NOTE, 3), 300},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_SHARP_NOTE, 3), 300},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_SHARP_NOTE, 3), 250},
	{NOTE(F_SHARP_NOTE, 2), 250},
	{NOTE(D_SHARP_NOTE, 3), 300},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_SHARP_NOTE, 3), 300},
	{NOTE(F_SHARP_NOTE, 2), 500},
	{NOTE(D_SHARP_NOTE, 3), 250},
	{NOTE(F_SHARP_NOTE, 2), 250},




//	{NOTE(G_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(G_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(G_NOTE, 2), 250},
//	{NOTE(C_NOTE, 2), 250},
//	{NOTE(G_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(G_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(G_NOTE, 2), 250},
//	{NOTE(C_NOTE, 2), 250},
//
//	{NOTE(F_SHARP_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(F_SHARP_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(F_SHARP_NOTE, 2), 250},
//	{NOTE(C_NOTE, 2), 250},
//	{NOTE(F_SHARP_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
//	{NOTE(F_SHARP_NOTE, 2), 300},
//	{NOTE(C_NOTE, 2), 500},
// 	{NOTE(F_SHARP_NOTE, 2), 250},
//	{NOTE(C_NOTE, 2), 250},
};