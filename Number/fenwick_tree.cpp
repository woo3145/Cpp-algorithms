#include <iostream>
#include <vector>

using std::vector;

// 펜윅 트리: 하나의 인덱스를 업데이트할때 인덱스에 0이아닌 마지막 비트를 더하면서 구간별로 모두 업데이트
// 각 인덱스의 0이 아닌 마지막 비트는 자신이 저장하고 있는 값의 갯수를 나타냄
// ex) 6(0000 0110) => 2개(5~6) , 8(0000 1000) => 8개(1~8)
//     index5(0000 0101) 업데이트 -> index6(0000 0110) -> index8(0000 1000) ... indexN 까지
class FenwickTree {
    private:
        vector<int> tree;
        int size;
    public:
        FenwickTree(int n){
            size = n;
            tree.assign(n+1, 0);
        };

        void update(int i, int val){
            while(i <= size){
                tree[i] += val;
                i += i & -i;
            }
        }
        int sum(int i) {
            int ret = 0;
            while(0 < i){
                ret += tree[i];
                i -= i & -i;
            }
            return ret;
        }
        int rangeSum(int i, int j){
            return sum(j) - sum(i-1);
        }
};

int main() {
    FenwickTree fw(12);
    for(int i = 1; i <= 12; ++i){
        fw.update(i, i * 4);
    }

    std::cout << "1 ~ 4사이의 구간합 : " << fw.sum(4) << '\n'; // 40
    std::cout << "4 ~ 10사이의 구간합 : " << fw.rangeSum(4, 10) << '\n'; // 196
    return 0;
}
