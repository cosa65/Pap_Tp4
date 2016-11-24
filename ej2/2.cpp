#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
    vector<int> a(n), q(n);
	for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    // cuento cuantas veces aparece el iesimo

    int last = 0;
    int times_seen = 1;
    for (int i = 1; i < n; i++) {
        if (a[i - 1] != a[i]) {
            for (; last < i; last++)
                q[last] = times_seen;
            times_seen = 1;
        } else {
            times_seen++;
        }
    }
    for (;last < n; last++)
        q[last] = times_seen;

    // sumo numbers_left/times_left para cada uno

    times_seen=0;
    int times_left = q[0];
    int numbers_left = n;
    double res = numbers_left / (double) times_left;
    
    for (int i = 1; i < n; i++) {
        if (a[i - 1] != a[i])
            times_seen = 0;
        else times_seen++;
        times_left = q[i] - times_seen;
        numbers_left = n - i;
        res += numbers_left / (double) times_left;
    }

    cout << res - n + 1 << endl;
    
}
