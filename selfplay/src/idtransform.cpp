#include "idtransform.h"

std::map<int, std::array<int, 4>> id_to_action;
std::map<std::array<int, 4>, int> action_to_id;

std::vector<int> GetActionById(int id) {
	std::array<int, 4> ans = id_to_action[id];
	return std::vector<int>(ans.begin(), ans.end());
}
int GetIdByAction(std::vector<int>& action) {
	std::array<int, 4> key({ action[0], action[1], action[2], action[3] });
	return action_to_id[key];
}

void InitIdTransform() {
	// {棋子类型，棋子编号，x偏移，y偏移}
	id_to_action[0] = { 4, 1, 0, -1 };
	id_to_action[1] = { 4, 1, 0, 1 };
	id_to_action[2] = { 4, 1, -1, 0 };
	id_to_action[3] = { 4, 1, 1, 0 };

	id_to_action[4] = { 3, 1, 1, -1 };
	id_to_action[5] = { 3, 1, -1, -1 };
	id_to_action[6] = { 3, 1, 1, 1 };
	id_to_action[7] = { 3, 1, -1, 1 };
	id_to_action[8] = { 3, 2, 1, -1 };
	id_to_action[9] = { 3, 2, -1, -1 };
	id_to_action[10] = { 3, 2, 1, 1 };
	id_to_action[11] = { 3, 2, -1, 1 };

	id_to_action[12] = { 2, 1, 2, -2 };
	id_to_action[13] = { 2, 1, -2, -2 };
	id_to_action[14] = { 2, 1, 2, 2 };
	id_to_action[15] = { 2, 1, -2, 2 };
	id_to_action[16] = { 2, 2, 2, -2 };
	id_to_action[17] = { 2, 2, -2, -2 };
	id_to_action[18] = { 2, 2, 2, 2 };
	id_to_action[19] = { 2, 2, -2, 2 };


	id_to_action[20] = { 1, 1, 1, 2 };
	id_to_action[21] = { 1, 1, 1, -2 };
	id_to_action[22] = { 1, 1, -1, 2 };
	id_to_action[23] = { 1, 1, -1, -2 };
	id_to_action[24] = { 1, 1, 2, 1 };
	id_to_action[25] = { 1, 1, 2, -1 };
	id_to_action[26] = { 1, 1, -2, 1 };
	id_to_action[27] = { 1, 1, -2, -1 };
	id_to_action[28] = { 1, 2, 1, 2 };
	id_to_action[29] = { 1, 2, 1, -2 };
	id_to_action[30] = { 1, 2, -1, 2 };
	id_to_action[31] = { 1, 2, -1, -2 };
	id_to_action[32] = { 1, 2, 2, 1 };
	id_to_action[33] = { 1, 2, 2, -1 };
	id_to_action[34] = { 1, 2, -2, 1 };
	id_to_action[35] = { 1, 2, -2, -1 };


	id_to_action[36] = { 0, 1, 0, 1 };
	id_to_action[37] = { 0, 1, 0, 2 };
	id_to_action[38] = { 0, 1, 0, 3 };
	id_to_action[39] = { 0, 1, 0, 4 };
	id_to_action[40] = { 0, 1, 0, 5 };
	id_to_action[41] = { 0, 1, 0, 6 };
	id_to_action[42] = { 0, 1, 0, 7 };
	id_to_action[43] = { 0, 1, 0, 8 };
	id_to_action[44] = { 0, 1, 0, -1 };
	id_to_action[45] = { 0, 1, 0, -2 };
	id_to_action[46] = { 0, 1, 0, -3 };
	id_to_action[47] = { 0, 1, 0, -4 };
	id_to_action[48] = { 0, 1, 0, -5 };
	id_to_action[49] = { 0, 1, 0, -6 };
	id_to_action[50] = { 0, 1, 0, -7 };
	id_to_action[51] = { 0, 1, 0, -8 };
		
	id_to_action[52] = { 0, 1, 1, 0 };
	id_to_action[53] = { 0, 1, 2, 0 };
	id_to_action[54] = { 0, 1, 3, 0 };
	id_to_action[55] = { 0, 1, 4, 0 };
	id_to_action[56] = { 0, 1, 5, 0 };
	id_to_action[57] = { 0, 1, 6, 0 };
	id_to_action[58] = { 0, 1, 7, 0 };
	id_to_action[59] = { 0, 1, 8, 0 };
	id_to_action[60] = { 0, 1, 9, 0 };
	id_to_action[61] = { 0, 1, -1, 0 };
	id_to_action[62] = { 0, 1, -2, 0 };
	id_to_action[63] = { 0, 1, -3, 0 };
	id_to_action[64] = { 0, 1, -4, 0 };
	id_to_action[65] = { 0, 1, -5, 0 };
	id_to_action[66] = { 0, 1, -6, 0 };
	id_to_action[67] = { 0, 1, -7, 0 };
	id_to_action[68] = { 0, 1, -8, 0 };
	id_to_action[69] = { 0, 1, -9, 0 };


	id_to_action[70] = { 0, 2, 0, 1 };
	id_to_action[71] = { 0, 2, 0, 2 };
	id_to_action[72] = { 0, 2, 0, 3 };
	id_to_action[73] = { 0, 2, 0, 4 };
	id_to_action[74] = { 0, 2, 0, 5 };
	id_to_action[75] = { 0, 2, 0, 6 };
	id_to_action[76] = { 0, 2, 0, 7 };
	id_to_action[77] = { 0, 2, 0, 8 };
	id_to_action[78] = { 0, 2, 0, -1 };
	id_to_action[79] = { 0, 2, 0, -2 };
	id_to_action[80] = { 0, 2, 0, -3 };
	id_to_action[81] = { 0, 2, 0, -4 };
	id_to_action[82] = { 0, 2, 0, -5 };
	id_to_action[83] = { 0, 2, 0, -6 };
	id_to_action[84] = { 0, 2, 0, -7 };
	id_to_action[85] = { 0, 2, 0, -8 };

	id_to_action[86] = { 0, 2, 1, 0 };
	id_to_action[87] = { 0, 2, 2, 0 };
	id_to_action[88] = { 0, 2, 3, 0 };
	id_to_action[89] = { 0, 2, 4, 0 };
	id_to_action[90] = { 0, 2, 5, 0 };
	id_to_action[91] = { 0, 2, 6, 0 };
	id_to_action[92] = { 0, 2, 7, 0 };
	id_to_action[93] = { 0, 2, 8, 0 };
	id_to_action[94] = { 0, 2, 9, 0 };
	id_to_action[95] = { 0, 2, -1, 0 };
	id_to_action[96] = { 0, 2, -2, 0 };
	id_to_action[97] = { 0, 2, -3, 0 };
	id_to_action[98] = { 0, 2, -4, 0 };
	id_to_action[99] = { 0, 2, -5, 0 };
	id_to_action[100] = { 0, 2, -6, 0 };
	id_to_action[101] = { 0, 2, -7, 0 };
	id_to_action[102] = { 0, 2, -8, 0 };
	id_to_action[103] = { 0, 2, -9, 0 };

	id_to_action[104] = { 5, 1, 0, 1 };
	id_to_action[105] = { 5, 1, 0, 2 };
	id_to_action[106] = { 5, 1, 0, 3 };
	id_to_action[107] = { 5, 1, 0, 4 };
	id_to_action[108] = { 5, 1, 0, 5 };
	id_to_action[109] = { 5, 1, 0, 6 };
	id_to_action[110] = { 5, 1, 0, 7 };
	id_to_action[111] = { 5, 1, 0, 8 };
	id_to_action[112] = { 5, 1, 0, -1 };
	id_to_action[113] = { 5, 1, 0, -2 };
	id_to_action[114] = { 5, 1, 0, -3 };
	id_to_action[115] = { 5, 1, 0, -4 };
	id_to_action[116] = { 5, 1, 0, -5 };
	id_to_action[117] = { 5, 1, 0, -6 };
	id_to_action[118] = { 5, 1, 0, -7 };
	id_to_action[119] = { 5, 1, 0, -8 };

	id_to_action[120] = { 5, 1, 1, 0 };
	id_to_action[121] = { 5, 1, 2, 0 };
	id_to_action[122] = { 5, 1, 3, 0 };
	id_to_action[123] = { 5, 1, 4, 0 };
	id_to_action[124] = { 5, 1, 5, 0 };
	id_to_action[125] = { 5, 1, 6, 0 };
	id_to_action[126] = { 5, 1, 7, 0 };
	id_to_action[127] = { 5, 1, 8, 0 };
	id_to_action[128] = { 5, 1, 9, 0 };
	id_to_action[129] = { 5, 1, -1, 0 };
	id_to_action[130] = { 5, 1, -2, 0 };
	id_to_action[131] = { 5, 1, -3, 0 };
	id_to_action[132] = { 5, 1, -4, 0 };
	id_to_action[133] = { 5, 1, -5, 0 };
	id_to_action[134] = { 5, 1, -6, 0 };
	id_to_action[135] = { 5, 1, -7, 0 };
	id_to_action[136] = { 5, 1, -8, 0 };
	id_to_action[137] = { 5, 1, -9, 0 };

	id_to_action[138] = { 5, 2, 0, 1 };
	id_to_action[139] = { 5, 2, 0, 2 };
	id_to_action[140] = { 5, 2, 0, 3 };
	id_to_action[141] = { 5, 2, 0, 4 };
	id_to_action[142] = { 5, 2, 0, 5 };
	id_to_action[143] = { 5, 2, 0, 6 };
	id_to_action[144] = { 5, 2, 0, 7 };
	id_to_action[145] = { 5, 2, 0, 8 };
	id_to_action[146] = { 5, 2, 0, -1 };
	id_to_action[147] = { 5, 2, 0, -2 };
	id_to_action[148] = { 5, 2, 0, -3 };
	id_to_action[149] = { 5, 2, 0, -4 };
	id_to_action[150] = { 5, 2, 0, -5 };
	id_to_action[151] = { 5, 2, 0, -6 };
	id_to_action[152] = { 5, 2, 0, -7 };
	id_to_action[153] = { 5, 2, 0, -8 };

	id_to_action[154] = { 5, 2, 1, 0 };
	id_to_action[155] = { 5, 2, 2, 0 };
	id_to_action[156] = { 5, 2, 3, 0 };
	id_to_action[157] = { 5, 2, 4, 0 };
	id_to_action[158] = { 5, 2, 5, 0 };
	id_to_action[159] = { 5, 2, 6, 0 };
	id_to_action[160] = { 5, 2, 7, 0 };
	id_to_action[161] = { 5, 2, 8, 0 };
	id_to_action[162] = { 5, 2, 9, 0 };
	id_to_action[163] = { 5, 2, -1, 0 };
	id_to_action[164] = { 5, 2, -2, 0 };
	id_to_action[165] = { 5, 2, -3, 0 };
	id_to_action[166] = { 5, 2, -4, 0 };
	id_to_action[167] = { 5, 2, -5, 0 };
	id_to_action[168] = { 5, 2, -6, 0 };
	id_to_action[169] = { 5, 2, -7, 0 };
	id_to_action[170] = { 5, 2, -8, 0 };
	id_to_action[171] = { 5, 2, -9, 0 };

	id_to_action[172] = { 6, 1, 0, 1 };
	id_to_action[173] = { 6, 1, 0, -1 };
	id_to_action[174] = { 6, 1, 1, 0 };
	id_to_action[175] = { 6, 1, -1, 0 };

	id_to_action[176] = { 6, 2, 0, 1 };
	id_to_action[177] = { 6, 2, 0, -1 };
	id_to_action[178] = { 6, 2, 1, 0 };
	id_to_action[179] = { 6, 2, -1, 0 };

	id_to_action[180] = { 6, 3, 0, 1 };
	id_to_action[181] = { 6, 3, 0, -1 };
	id_to_action[182] = { 6, 3, 1, 0 };
	id_to_action[183] = { 6, 3, -1, 0 };

	id_to_action[184] = { 6, 4, 0, 1 };
	id_to_action[185] = { 6, 4, 0, -1 };
	id_to_action[186] = { 6, 4, 1, 0 };
	id_to_action[187] = { 6, 4, -1, 0 };

	id_to_action[188] = { 6, 5, 0, 1 };
	id_to_action[189] = { 6, 5, 0, -1 };
	id_to_action[190] = { 6, 5, 1, 0 };
	id_to_action[191] = { 6, 5, -1, 0 };

	for (auto iter = id_to_action.begin(); iter != id_to_action.end(); ++iter) {
		action_to_id[iter->second] = iter->first;
	}
}
