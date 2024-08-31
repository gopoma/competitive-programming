//? https://codeforces.com/contest/2000/submission/276943782
//? 0-indexed
//? [l, r]

class SegmentTree {
private:
    std::vector<int> seg;
    std::vector<int> lazy;
    std::vector<int> arr;
    int n;

    void build(int node, int st, int en) {
        if (st == en) {
            seg[node] = arr[st];
            return;
        }

        int mid = (st + en) / 2;

        // Llamada recursiva para el hijo izquierdo
        build(2 * node, st, mid);

        // Llamada recursiva para el hijo derecho
        build(2 * node + 1, mid + 1, en);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    void update(int node, int st, int en, int l, int r, int val) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];

            if (st != en) { // Si los hijos existen, los marca como "lazy"
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return;
        }

        if (st >= l && en <= r) { // Caso 2: completamente dentro del rango
            seg[node] += (en - st + 1) * val;
            if (st != en) {
                lazy[2 * node] += val; // Marca a los hijos como "lazy"
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Caso 3: parcialmente dentro del rango
        int mid = (st + en) / 2;

        // Llamada recursiva para actualizar el hijo izquierdo
        update(2 * node, st, mid, l, r, val);
        // Llamada recursiva para actualizar el hijo derecho
        update(2 * node + 1, mid + 1, en, l, r, val);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    int query(int node, int st, int en, int l, int r) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];
            if (st != en) { // Verifica si los hijos existen
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return 0;
        }

        if (l <= st && en <= r) { // Caso 2: completamente dentro del rango
            return seg[node];
        }

        int mid = (st + en) / 2;

        // Consulta del hijo izquierdo
        int q1 = query(2 * node, st, mid, l, r);

        // Consulta del hijo derecho
        int q2 = query(2 * node + 1, mid + 1, en, l, r);

        return q1 + q2;
    }

public:
    SegmentTree(int size, std::vector<int>& elements) {
        n = size;
        arr = elements;
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
	// Constructor sin arreglo, inicializa todo a cero
    SegmentTree(int size) {
        n = size;
        arr.assign(n, 0); // Inicializa el arreglo con ceros
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
    void update(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
