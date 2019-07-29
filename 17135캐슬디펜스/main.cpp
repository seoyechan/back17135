#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int nfiled[16][16];
int nfiled_copy[16][16];
int nvisit[17][17];
int archer_pos[3];
int n, m, d, nRet;

int dirx[] = { -1, 0, 1 };
int diry[] = { 0, -1, 0 };

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
		vector<inf>temp_v;
		
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				nfiled_copy[i][j] = nfiled[i][j];
			}
		}

		for (int t = n; t >= 0; t--){
			temp_v.clear();
			for (int k = 0; k < 3; k++){
				queue <inf> bfs_q;
				inf cur_pos = { 0, };
				int nextx, nexty = 0;
				bool flag = false;
				bfs_q.push({ archer_pos[k], t, 0 });
				nvisit[t][archer_pos[k]] = 1;
				
				for (int i = 0; i <= n; i++){
					for (int j = 0; j <= m; j++){
						nvisit[i][j] = 0;
					}
				}

				while (!bfs_q.empty()){
					cur_pos = bfs_q.front();
					bfs_q.pop();

					if (cur_pos.val >= d) continue;

					for (int dir = 0; dir < 3; dir++){
						nextx = cur_pos.x + dirx[dir];
						nexty = cur_pos.y + diry[dir];

						if (nexty == t) continue;

						if (nextx >= 0 && nextx < m && nexty >= 0 && nexty < m && !nvisit[nexty][nextx]){
							if (nfiled_copy[nexty][nextx])
							{
								temp_v.push_back({ nextx, nexty, ++cur_pos.val });
								cur_pos.val--;
								flag = true;
								break;
							}
							else
							{
								bfs_q.push({ nextx, nexty, ++cur_pos.val });
								nvisit[nexty][nextx] = 1;
								cur_pos.val--;
							}

						}

					}
					if (flag) break;
				}
			}

			for (int e = 0; e < temp_v.size(); e++){
				if (nfiled_copy[temp_v[e].y][temp_v[e].x]){
					nfiled_copy[temp_v[e].y][temp_v[e].x] = 0;
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