#include <iostream>
#include <vector>

using std::vector;

// 세그먼트 트리: 특정 구간의 합/곱/최소값/최댓값 등을 구하는데 사용하는 자료구조
// 업데이트 O(logN), 구간합 O(logN)
// 트리의 크기
// 트리의 높이 = ceil(log2(n)) + 1
// 총 노드의 수 = 2 ^ (height + 1) - 1
// 세그먼트 트리의 크기는 항상 상한값으로 4*N의 크기를 가지기 때문에 보통 4*N으로 할당한다.
class SegmentTree {
    private:
        vector<int> tree;
        int size;

        void _build(vector<int>& arr, int idx, int left, int right){
            if(left == right) {
                tree[idx] = arr[left];
                return;
            }
            int mid = left + (right - left) / 2;
            _build(arr, idx * 2 + 1, left, mid);
            _build(arr, idx * 2 + 2, mid + 1, right);
            tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        }

        int _query(int idx, int left, int right, int queryLeft, int queryRight) {
            if(queryLeft <= left && right <= queryRight) {
                return tree[idx];
            }
            if(queryRight < left || right < queryLeft){
                return 0;
            }
            int mid = left + (right - left) / 2;
            int leftSum = _query(idx * 2 + 1, left, mid, queryLeft, queryRight);
            int rightSum = _query(idx * 2 + 2, mid + 1, right, queryLeft, queryRight);

            return leftSum + rightSum;
        }

        void _update(int idx, int left, int right, int targetIdx, int newValue){
            if(left == right){
                tree[idx] = newValue;
                return;
            }

            // 재귀로 해당 리프노드 까지 찾아감
            int mid = left + (right - left) / 2;
            if(targetIdx <= mid) {
                _update(idx * 2 + 1, left, mid, targetIdx, newValue);
            }else {
                _update(idx * 2 + 2, mid + 1, right, targetIdx, newValue);
            }
            // 빠져나오면서 자식노드의 합을 업데이트 시킴
            tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        }

    public:
        SegmentTree(vector<int>& arr){
            size = arr.size();
            tree.resize(size * 4);
            _build(arr, 0, 0, size - 1);
        }

        int query(int left, int right) {
            return _query(0, 0, size - 1, left, right);
        }

        void update(int idx, int newValue) {
            _update(0, 0, size - 1, idx, newValue);
        }
};


int main() {
    vector<int> arr = {1, 3, 5, 4, 12, -1, 6, 8, -7, 20, 7};
    SegmentTree segTree(arr);

    std::cout << "1 ~ 4의 구간합: " << segTree.query(1, 4) << '\n'; // Output: 24
    std::cout << "3 ~ 7의 구간합: " << segTree.query(3, 7) << '\n'; // Output: 29

    segTree.update(4, 100);

    std::cout << "1 ~ 4의 구간합: " << segTree.query(1, 4) << '\n'; // Output: 112
    std::cout << "3 ~ 7의 구간합: " << segTree.query(3, 7) << '\n'; // Output: 117

    return 0;
}
