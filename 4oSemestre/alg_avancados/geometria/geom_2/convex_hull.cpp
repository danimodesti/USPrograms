#include <iostream>
#include <algorithm> // Ordenar pontos
#include <vector>

#include "geom_computacional.h"

using namespace std;

typedef long long ll;
typedef vector<Point<ll>> vp;

double polygon_perimeter(vp points);
vp convex_hull(vp polygon_points);

int main() {
    int sheep_amt;
    cin >> sheep_amt;

    vp points(sheep_amt);
    int x, y;

    for (int i = 0; i < sheep_amt; i++) {
        cin >> x >> y;
        Point<ll> P(x, y);

        points[i] = P;    
    }

    vp hull = convex_hull(points);
    cout << fixed << setprecision(6) << polygon_perimeter(hull) << '\n';

    return EXIT_SUCCESS;
}

vp convex_hull(vp polygon_points) {
    // Ordenar pelos x, desempatando pelos y
    sort(polygon_points.begin(), polygon_points.end());

    // Tem que ter um vetor inicial com os 2 primeiros pontos
    vp lower_hull{polygon_points[0], polygon_points[1]};

    int point_amt = polygon_points.size();
    for (int i = 2; i < point_amt; i++) {
        while ((int)lower_hull.size() >= 2) {
            int lh_size = lower_hull.size();
            Point<ll> A = lower_hull[lh_size - 2];
            Point<ll> B = lower_hull[lh_size - 1];

            Point<ll> C = polygon_points[i];

            // Se o produto vetorial der negativo, ha uma concavidade. Retirar
            // aquele ponto.
            // Se der = 0, eh colinear
            if ((B - A).cross(C - B) <= 0) { // Prod. vet. entre vetores BC e AB
                lower_hull.pop_back();
            }

            // Aceitar o ponto (poligono eh convexo)
            else {
                break;
            }
        }

        lower_hull.push_back(polygon_points[i]);
    }

    // Tem que ter um vetor inicial com os 2 ultimos pontos
    vp upper_hull{polygon_points[point_amt - 1], polygon_points[point_amt - 2]};

    for (int i = point_amt - 3; i >= 0; i--) {
        while ((int)upper_hull.size() >= 2) {
            int uh_size = upper_hull.size();
            Point<ll> A = upper_hull[uh_size - 2];
            Point<ll> B = upper_hull[uh_size - 1];

            Point<ll> C = polygon_points[i];

            // Se o produto vetorial der negativo, ha uma concavidade. Retirar
            // aquele ponto.
            // Se der = 0, eh colinear
            if ((B - A).cross(C - B) <= 0) { // Prod. vet. entre vetores BC e AB
                upper_hull.pop_back();
            }

            // Aceitar o ponto (poligono eh convexo)
            else {
                break;
            }
        }

        upper_hull.push_back(polygon_points[i]);
    }

    // Juntar os hull
    vp hull = lower_hull;
    hull.insert(hull.end(), upper_hull.begin() + 1, upper_hull.begin() + upper_hull.size() - 1);

    return hull;
}

double polygon_perimeter(vp points) {
    double perimeter = 0;
    int point_amt = points.size();

    for (int i = 0; i < point_amt; i++) {
        Point<ll> A = points[i];
        Point<ll> B = points[(i + 1) % point_amt];

        perimeter += (B - A).len();
    }

    return perimeter;
}