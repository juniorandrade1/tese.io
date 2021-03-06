#include "SegmentTree.hpp"

namespace BST {
  SegmentTree::SegmentTree() {
    n = (int)1e5;
    tr.resize(4 * n);
  }
  SegmentTree::SegmentTree(int _n) {
    n = _n;
    tr.resize(4 * n);
  }
  void SegmentTree::insertSegment(int no, int l, int r, int l0, int l1, int y, int idx) {
    if(r < l0 || l > l1) return;
    if(l >= l0 && r <= l1) {
      tr[no].insert(make_pair(y, idx));
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    insertSegment(nxt, l, mid, l0, l1, y, idx);
    insertSegment(nxt + 1, mid + 1, r, l0, l1, y, idx);
  }
  void SegmentTree::eraseSegment(int no, int l, int r, int l0, int l1, int y, int idx) {
    if(r < l0 || l > l1) return;
    if(l >= l0 && r <= l1) {
      tr[no].erase(tr[no].find(make_pair(y, idx)));
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    eraseSegment(nxt, l, mid, l0, l1, y, idx);
    eraseSegment(nxt + 1, mid + 1, r, l0, l1, y, idx);
  }
  void SegmentTree::insertSegment(int l0, int l1, int y, int idx) {
    Hseg[l0] = make_pair(l1, y);
    Hins[y] = l0;
    printf("inserting horizontal segment %d %d %d\n", l0, l1, y);
    insertSegment(1, 0, n, l0, l1, y, idx);
  }
  void SegmentTree::eraseSegment(int l0, int l1, int y, int idx) {
    Hseg.erase(l0);
    Hins.erase(y);
    printf("removing horizontal segment %d %d %d\n", l0, l1, y);
    eraseSegment(1, 0, n, l0, l1, y, idx);
  }
  int SegmentTree::getMinY(int no, int l, int r, int t) {
    int ans = numeric_limits< int > :: max();
    if(tr[no].size() > 0) {
      pair<int, int> f = *tr[no].begin();
      ans = min(ans, f.first);
    }
    if(l != r) {
      int nxt = (no << 1), mid = (l + r) >> 1;
      if(t <= mid) ans = min(ans, getMinY(nxt, l, mid, t));
      else ans = min(ans, getMinY(nxt + 1, mid + 1, r, t));
    }
    return ans;
  }
  int SegmentTree::getMinY(int t) {
    return getMinY(1, 0, n, t);
  }
  int SegmentTree::getStartTimeFromKey(int x) {
    return Hins[x];
  }
  int SegmentTree::getFinishTimeFromKey(int x) {
    int tins = getStartTimeFromKey(x);
    return Hseg[tins].first;
  }
  int SegmentTree::getKeyFromStartTime(int startTime) {
    return Hseg[startTime].second;
  }
  int SegmentTree::getFinishTimeFromStartTime(int startTime) {
    return Hseg[startTime].first;
  }
};