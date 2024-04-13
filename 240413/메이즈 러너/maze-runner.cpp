#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

/*
00 01 02
10 11 12
20 21 22


상 하 좌 우
-1 1 0 0
0 0 -1 1
*/

struct Square {
	int y; int x; int n;
};

struct POS {
	int y, x;
	int isNotValid ;
	int number;
};
vector<POS> v;

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

int arr[14][14];
int N, M, K;
POS exitPos;

//회전 구현
void rotation(int y, int x, int w) {
	int copyArr[50][50] = { 0 ,};

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			copyArr[i][j] = arr[y + i][x + j];
		}
	}

	int rotationArr[50][50] = { 0, };

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++)
		{
			if (copyArr[i][j] <10&&copyArr[i][j] != -1 && copyArr[i][j] != 0) copyArr[i][j]--;
			rotationArr[j][w - i - 1] = copyArr[i][j];
		} 
	}

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			arr[y + i][x + j] = rotationArr[i][j];
			if (arr[y + i][x + j] >= 10) {
				v[(arr[y + i][x + j] / 10) - 1].y = y + i;
				v[(arr[y + i][x + j] / 10) - 1].x = x + j;
			}
			if (arr[y + i][x + j] == -1) {
				exitPos.y = y + i;
				exitPos.x = x + j;
			}
		}
	}


	
}


//정사각형 뽑기
Square squareSelect() {

	for (int n = 2; n <= 10; n++) {

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int isExit = 0;
				int isPeople = 0;
				int flag = 0;
				for (int ii = i; ii < i + n; ii++) {
					for (int jj = j; jj < j + n; jj++) {
						if (ii < 0 || ii == N || jj < 0 || jj == N) {
							flag = 1;
							break;
						}
						if (arr[ii][jj] == -1) isExit = 1;
						for (int p = 0; p < v.size(); p++) {
							if (v[p].isNotValid == 1) continue;
							if (ii == v[p].y&&jj == v[p].x) {
								isPeople++;
							}
						}
					}
					if (flag)break;
				}

				if (isExit&&isPeople) {
					Square s;
					s.y = i;
					s.x = j;
					s.n = n;
					return s;
					break;
				}
			}
		}
	}
	
}

void check() {
	for (int n = 2; n <= 2; n++) {


		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int isExit = 0;
				int isPeople = 0;
				for (int ii = i; ii < i + n; ii++) {
					for (int jj = j; jj < j + n; jj++) {
						printf("[%d, %d] ", ii,jj);
					}
					printf("\n");
				}
				
			}
		}
	}

}

//초기화
void init() {
	memset(arr, 0, sizeof(arr));
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	
	for (int i = 0; i < M; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		arr[y - 1][x - 1] = (i+1)*10;
		v.push_back({ y-1,x-1,0,(i+1)*10 });
	}


	scanf("%d %d", &exitPos.y, &exitPos.x);
	exitPos.y--;
	exitPos.x--;
	arr[exitPos.y][exitPos.x] = -1;
}
int ret = 0;

int distanceCal(int y, int x) {
	return abs(exitPos.y - y) + abs(exitPos.x - x);
}

bool safeZone(int y, int x) {
	return 0 < y || y < N || 0 < x||x < N;
}
void play() {
	//이동
	
	while (K--) {
		int outCount = 0;
		for (int i = 0; i < v.size(); i++) {


			int cy = v[i].y;
			int cx = v[i].x;
			if (v[i].isNotValid == 1) {
				outCount++;
				continue;
			}
			if (outCount == v.size()) break;
			int beforeShortDistance = distanceCal(cy, cx);

			for (int d = 0; d < 4; d++) {

				int ny = cy + dy[d];
				int nx = cx + dx[d];
				if (!safeZone(ny, nx)) continue;
				if (arr[ny][nx] == 0||arr[ny][nx]==-1) {
					int afterShortDistance = distanceCal(ny, nx);
					if (beforeShortDistance > afterShortDistance) {
						if (arr[ny][nx] == -1) {
							v[i].isNotValid = 1;
							arr[v[i].y][v[i].x] = 0;
							ret++;
							break;
						}
						arr[ny][nx] = arr[cy][cx];
						arr[cy][cx] = 0;
						v[i].y = ny;
						v[i].x = nx;
						ret++;
						break;
					}
				}
			}
		}

		//




		Square square = squareSelect();
		rotation(square.y, square.x, square.n);

		int a = 0;
	}

}
int main(void) {
	
	int TC = 1;
	for (int tc = 1; tc <= TC; tc++) {
		init();


		play();

		printf("%d\n", ret);
		printf("%d %d\n", exitPos.y+1, exitPos.x+1);
	}
	return 0;
}