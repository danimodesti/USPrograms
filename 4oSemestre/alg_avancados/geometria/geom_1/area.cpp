#include <iostream>
#include <vector>

#include "geom_computacional.h"

using namespace std;

typedef long long ll;
typedef vector<Point<ll>> vp;

ll shoe_lace_2(vp polygon);

int main() {
    int apex_amt;
    cin >> apex_amt;

    ll x, y;

    vp points(apex_amt);

    for (int i = 0; i < apex_amt; i++) {
        cin >> x >> y;
        Point<ll> p(x, y);

        points[i] = p;
    }

    cout << shoe_lace_2(points) << '\n';

    return EXIT_SUCCESS;
}

// Retorna 2 * area do poligono (para evitar trabalhar
// com numeros quebrados)
ll shoe_lace_2(vp polygon) {
    int apex_amt = polygon.size();
    ll double_area = 0;

    for (int i = 0; i < apex_amt; i++) {
        double_area += polygon[i].cross(polygon[(i + 1) % apex_amt]);
    }

    return abs(double_area);
}