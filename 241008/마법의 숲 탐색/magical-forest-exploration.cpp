#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
#include <string>
#define RSIZE 70
#define CSIZE 70 
using namespace std;

int arr[RSIZE+5][CSIZE+3];
int R, C, K;
int ret = 0;
/*
 00 01 02
 10 11 12
 20 21 22

 위	오	아	왼
 북	동	남	서
 0	1	2	3
 */ 
int dy[] = {-1,0,1,0};
int dx[] = {0,1,0,-1};

struct Data {
	int y, x, cnt;
};


void cleanArr() {//울타리 및 배열 초기화
	memset(arr, 0, sizeof(arr));

	for (int i = 0; i < R+4-1; i++) {
		arr[i][0] = arr[i][C + 1] = 1;
	}

	for (int j = 0; j < C + 2; j++) {
		arr[R + 4 - 1][j] = 1;
	}
}

int main() {

	cin >> R >> C >> K;
	cleanArr();
	int unit = 2;
	for (int k = 0; k < K; k++) {
		int j, dir;
		cin >> j >> dir;
		int ci = 1;
		int cj = j;

		while (1) {
			if (arr[ci + 1][cj - 1] + arr[ci + 2][cj] + arr[ci + 1][cj + 1] == 0) {//남쪽으로 이동
				ci++;
			}
			else if (arr[ci - 1][cj - 1] + arr[ci][cj - 2] + arr[ci + 1][cj - 2] + arr[ci][cj - 1] + arr[ci + 2][cj - 1] == 0) {
				dir = ((dir - 1) + 4) % 4;
				ci = ci + 1;
				cj = cj - 1;
			}
			else if (arr[ci - 1][cj + 1] + arr[ci][cj + 2] + arr[ci + 1][cj + 1] + arr[ci + 1][cj + 2] + arr[ci + 2][cj + 1] == 0) {
				dir = ((dir - 1) + 4) % 4;
				ci = ci + 1;
				cj = cj + 1;
			}
			else {
				break;
			}
		}
		if (ci <= 3) {
			cleanArr();
		}
		else {// bfs
/*
 00 01 02
 10 11 12
 20 21 22
 */
			arr[ci][cj] = arr[ci-1][cj] = arr[ci][cj+1] = arr[ci+1][cj] = arr[ci][cj-1] = unit;
			arr[ci+dy[dir]][cj + dx[dir]] = 1000 * arr[ci + dy[dir]][cj + dx[dir]];
			int visit[RSIZE][CSIZE] = { 0, };
			queue<Data> q;
			int maxR = -987654321; 
			int maxY = -987654321;
			q.push({ ci,cj,1});
			visit[ci][cj] = 1;


			while (!q.empty()) {
				Data c = q.front(); q.pop();
				if (c.cnt>maxR&& c.y>maxY){
					maxR = c.cnt;
					maxY = c.y;
					
				}
			
				for (int d = 0; d < 4; d++) {
					Data n;
					n.y = c.y + dy[d];
					n.x = c.x + dx[d];
					if (arr[n.y][n.x] != 1&& visit[n.y][n.x] == 0) {
						if (arr[c.y][c.x] >1000 && arr[n.y][n.x]*1000!= arr[c.y][c.x]) {
							n.cnt = c.cnt + 1;
							visit[n.y][n.x] = 1;
							q.push(n);
						}
						if(arr[c.y][c.x]==arr[n.y][n.x] || arr[c.y][c.x]*1000 == arr[n.y][n.x]) {
							n.cnt = c.cnt + 1;
							visit[n.y][n.x] = 1;
							q.push(n);
						}
					}
				}
			}
			ret += maxY - 2;
		}
		unit++;

	}

	cout << ret << endl;
	return 0;
}