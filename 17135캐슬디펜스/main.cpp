#include <stdio.h>
#include <vector>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int nfiled[16][16];
int nfiled_copy[16][16];
int archer_pos[3];
int n, m, d, nRet;

typedef struct inf{
	int x, y, val;
};

int chan_abs(int a)
{
	if (a < 0)
		a = -a;
	return a;
}

int compare(inf x, inf y){
	return x.val < y.val;
}

int compare2(inf x, inf y){
	return x.x < y.x;
}

void dfs(int cnt, int num)
{
	if (cnt == 3)
	{
		int enemy = 0;
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				nfiled_copy[i][j] = nfiled[i][j];

		int temp = 0;
		int min_temp = 0;
		vector <inf> inf_v;
		vector <inf> inf_v_2;
		vector <inf> inf_v_3;
		for (int t = n - 1; t >= 0; t--){ // time
			inf_v_3.clear();
			for (int k = 0; k < 3; k++){ // archer
				inf_v.clear();
				for (int i = t; i > t - d; i--){ // y
					if (i >= 0){
						for (int j = archer_pos[k] - d + 1; j <= archer_pos[k] + d - 1; j++){ // x
							if (j >= 0 && j < m){
								if (nfiled_copy[i][j]){
									min_temp = chan_abs(j - archer_pos[k]) + chan_abs(i - t);
									inf_v.push_back({ j, i, min_temp });
									temp = 1;
								}
							}
						}
					}
					if (temp)
					{	
						if (inf_v.size() == 1){
							inf_v_3.push_back(inf_v[0]);
						}
						
						if (inf_v.size() > 1 && inf_v[0].val == inf_v[1].val){
							sort(inf_v.begin(), inf_v.end(), compare);
							inf_v_2.clear();
							if (inf_v.size() == 2){
								inf_v_2.push_back(inf_v[0]);
								inf_v_2.push_back(inf_v[1]);
							}
							else{
								for (int i = 0; i < inf_v.size() - 1; i++){
									if (inf_v[i].val == inf_v[i + 1].val){
										inf_v_2.push_back(inf_v[i]);
									}
									else{
										inf_v_2.push_back(inf_v[i]);
										break;
									}
								}
							}
							sort(inf_v_2.begin(), inf_v_2.end(), compare2);
							inf_v_3.push_back(inf_v_2[0]);
						}
						
						if (inf_v.size() > 1 && inf_v[0].val != inf_v[1].val){
							sort(inf_v.begin(), inf_v.end(), compare);
							inf_v_3.push_back(inf_v[0]);
						}
						temp = 0;
						break;
					}
				}

			}
			for (int i = 0; i < inf_v_3.size(); i++){
				if (nfiled_copy[inf_v_3[i].y][inf_v_3[i].x]){
					nfiled_copy[inf_v_3[i].y][inf_v_3[i].x] = 0;
					enemy++; 
				}
			}
		}

		if (enemy > nRet)
			nRet = enemy;
		
		return;
	}

	for (int i = num; i < m; i++)
	{
		archer_pos[cnt] = i;
		dfs(cnt + 1, i + 1);
	}
}

int main()
{
	int t;
	int test_case;

	freopen("input.txt", "r", stdin);

	scanf("%d", &t);
	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d %d", &n, &m, &d);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &nfiled[i][j]);

		nRet = 0;
		dfs(0,0);

		printf("%d\n", nRet);
	}
	return 0;
}