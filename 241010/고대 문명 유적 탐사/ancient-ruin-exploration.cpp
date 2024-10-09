#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };

int K, M;
int ret;
int arr[7][7];
int crr[7][7];

struct Data {
	int y, x, rotation, removeCount;
};

struct Pos {
	int y;
	int x;
	int cnt;
};

queue<int> keys;
vector<Data> v;
queue<Pos>q;

void copyBoard(int crr[7][7], int arr[7][7]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			crr[i][j] = arr[i][j];
		}
	}
}

void rotation(int y, int x) {

	int si = y - 1;
	int ei = y + 2;
	int sj = x - 1;
	int ej = x + 1;
	
	


	int brr[7][7] = { 0, };
	for (int i =si; i < si+3 ; i++) {
		for (int j = sj; j <sj+3 ; j++) {
			brr[i][j] = arr[3+x-1-1-j+y-1][i+x-1-(y-1)];
		}
	}

	for (int i = si; i < si + 3; i++) {
		for(int j = sj; j < sj + 3; j++) {
			arr[i][j] = brr[i][j];
		}
	}
}

int bfsCount(bool on) {
	int retCount = 0;;
	int visit[7][7] = { 0 };
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (visit[i][j] == 0) {
				visit[i][j] = 1;
				int number = arr[i][j];
				while (!q.empty()) q.pop();
				q.push({ i,j,1 });
				int cnt = 0;
				while (!q.empty()){
					Pos c = q.front(); q.pop();

					if (cnt < c.cnt)cnt = c.cnt;

					for (int dir = 0; dir < 4; dir++) {
						Pos n;
						n.y = c.y + dy[dir];
						n.x = c.x + dx[dir];
						n.cnt = c.cnt + 1;
						if (n.y < 0 || n.y == 5 || n.x < 0 || n.x== 5) continue;
						if (visit[n.y][n.x] == 0 && arr[n.y][n.x] == number) {
							cnt++;
							visit[n.y][n.x] = 1;
							q.push(n);
						}
					}
				}//while end
				if (cnt <3) {
					visit[i][j] = 0;
				}
				else
					retCount += cnt;
			}
		}
	}

	if (on) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (visit[i][j] == 1) {
					arr[i][j] = 0;
				}
			}
		}
	}


	return  retCount;
}

int addMaterial() {
	int size = keys.size();
	for (int j = 0; j <= 4; j++) {
		for (int i = 4; i >= 0; i--) {
			if (arr[i][j] == 0) {
				arr[i][j] = keys.front(); keys.pop();
				if (keys.size() == 0) break;
			}
			if (keys.size() == 0) break;
		}
	}

	if (size == 0) return -1;
	else return 1;
}

bool cmp(Data a, Data b) {
	if (a.removeCount > b.removeCount)return true;
	else if(a.removeCount== b.removeCount) {
		if (a.rotation < b.rotation) {
			return true;
		}
		else if (a.rotation == b.rotation) {
			if (a.y < b.y) {
				return true;
			}
			else if (a.y == b.y) {
				if (a.x < b.x) return true;
				else return false;
			}
		}
	}
	return false;
}

int main(void) {

	cin >> K >> M;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
		}
	}
	for (int m = 0; m < M; m++) {
		int number;
		cin >> number;
		keys.push(number);
	}

	while (K--) {
		for (int i = 1; i <= 3; i++) {//선택
			for (int j = 1; j <= 3; j++) {
				for (int r = 1; r <= 4; r++) {
					Data c;
					rotation(i, j);
					if (r == 4) continue;
					copyBoard(crr, arr);
					c.y = i, c.x = j, c.rotation = r; c.removeCount = bfsCount(false);
					v.push_back(c);
					copyBoard(arr, crr);
				}
			}
		}
		sort(v.begin(), v.end(), cmp);

		//방문 제거 하고 
		for (int r = 0; r < v[0].rotation;r++) {
			rotation(v[0].y, v[0].x);
		}
		ret +=bfsCount(true);
		while (1) {
			//유물에 있는 것 넣고
			int aMaterial = addMaterial();
			if (aMaterial == -1) break;
			//다시 유물 확인 하고 
			int count = bfsCount(true);
			if (count == 0) break;
			ret += count;
			//제거 할놈 있으면 제거 하면서 ret+=count;
		}
	}

	cout << ret << endl;
	return 0;
}