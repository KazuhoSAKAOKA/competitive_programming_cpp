


class KDTree {
public:

    struct Point {
        int64_t x, y;
        size_t id;
    };

    struct KDNode {
        Point point;
        KDNode* left = nullptr, * right = nullptr;
        KDNode(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
    };

private:
    KDNode* root = nullptr;

    KDNode* build(vector<Point>& pts, int depth) {
        if (pts.empty()) return nullptr;
        int axis = depth % 2;
        sort(pts.begin(), pts.end(), [&](const Point& a, const Point& b) {
            return axis == 0 ? a.x < b.x : a.y < b.y;
            });
        int mid = pts.size() / 2;
        KDNode* node = new KDNode{ pts[mid] };
        vector<Point> left(pts.begin(), pts.begin() + mid);
        vector<Point> right(pts.begin() + mid + 1, pts.end());
        node->left = build(left, depth + 1);
        node->right = build(right, depth + 1);
        return node;
    }

    void nearest(KDNode* node, const Point& target, int depth,
        Point& best, double& bestDist) {
        if (!node) return;
        double d = distance(target, node->point);
        if (d < bestDist) {
            bestDist = d;
            best = node->point;
        }

        int axis = depth % 2;
        KDNode* near = nullptr, * far = nullptr;
        if ((axis == 0 && target.x < node->point.x) ||
            (axis == 1 && target.y < node->point.y)) {
            near = node->left;
            far = node->right;
        }
        else {
            near = node->right;
            far = node->left;
        }

        nearest(near, target, depth + 1, best, bestDist);

        double delta = axis == 0 ? fabs(target.x - node->point.x)
            : fabs(target.y - node->point.y);
        if (delta < bestDist) {
            nearest(far, target, depth + 1, best, bestDist);
        }
    }

    double distance(const Point& a, const Point& b) {
        return hypot(a.x - b.x, a.y - b.y);
    }

    void rangeSearch(KDNode* node, int depth,
        int64_t xmin, int64_t xmax,
        int64_t ymin, int64_t ymax,
        vector<Point>& result) {
        if (!node) return;
        const Point& p = node->point;
        if (p.x >= xmin && p.x <= xmax && p.y >= ymin && p.y <= ymax) {
            result.push_back(p);
        }

        int axis = depth % 2;
        if ((axis == 0 && xmin <= p.x) || (axis == 1 && ymin <= p.y)) {
            rangeSearch(node->left, depth + 1, xmin, xmax, ymin, ymax, result);
        }
        if ((axis == 0 && xmax >= p.x) || (axis == 1 && ymax >= p.y)) {
            rangeSearch(node->right, depth + 1, xmin, xmax, ymin, ymax, result);
        }
    }



public:
    KDTree(const vector<Point>& points) {
        vector<Point> pts = points;
        root = build(pts, 0);
    }

    Point nearestNeighbor(const Point& target) {
        Point best = { LLONG_MAX, LLONG_MAX, SIZE_MAX };
        double bestDist = 1e18;
        nearest(root, target, 0, best, bestDist);
        return best;
    }

    vector<Point> rangeQuery(int64_t xmin, int64_t xmax,
        int64_t ymin, int64_t ymax) {
        vector<Point> result;
        rangeSearch(root, 0, xmin, xmax, ymin, ymax, result);
        return result;
    }


};
