#include <iostream>
#include <vector>


using std::cout;
using std::cin;
using std::endl;
using std::ios;

using std::vector;

#define MOD 1000
typedef vector<vector<int>> matrix;

// 행렬의 곱셈 O(NM^2)
matrix operator * (const matrix& a, const matrix& b){
    if(a[0].size() != b.size()) {
        cout << "행렬을 곱할 수 없습니다. \n";
        assert(nullptr);
    }
    int rows = a.size();
    int cols = b[0].size();
    matrix result(rows, vector<int>(cols));

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            for(int k = 0; k < cols; ++k){
                result[i][j] += (a[i][k] % MOD) * (b[k][j] % MOD);
            }
            result[i][j] %= MOD;
        }
    }
    return result;
}

// 분할정복을 통한 O(logN) 행렬 제곱
matrix matrixPow(matrix mat, int n){
    if(mat.size() != mat[0].size()) {
        cout << "정방행렬이 아닙니다.\n";
        assert(nullptr);
    }
    matrix result(mat.size(), vector<int>(mat.size(), 0));
    for(int i = 0; i < mat.size(); ++i){
        result[i][i] = 1;
    }

    while(0 < n) {
        if(n % 2 == 1){
            --n;
            result = mat * result;
        }else {
            n /= 2;
            mat = mat * mat;
        }
    }
    return result;
}

int main() {
    // Input
    int N; // 정방행렬 크기
    long long B; // 제곱 횟수
    cin >> N >> B;
    matrix mat(N, vector<int>(N));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> mat[i][j];
        }
    }

    matrix answer = matrixPow(mat, B);

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << answer[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}

/* Input
3 3
1 2 3
4 5 6
7 8 9
*/
/* Output
3 3
468 576 684
62 305 548
656 34 412
*/

