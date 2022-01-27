#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<set>
#include<cstring>
#include<stack>
#include<algorithm>

struct Pair
{
    int s1; // prima stare
    int s2; // a doua stare
    std::vector<int> seq; // retine tranzitia care a dus spre cele 2 stari
};

using namespace std;

/**
 * @brief descopera toate starile accesibile ale automatului
 * 
 * Din fiecare stare initiala se porneste o parcurgere BFS pentru determinarea starilor
 * accesibile. Starile accesibile sunt reprezentate de toate nodurile vizitate din cadrul
 * parcurgerii.
 * 
 * @param n numarul de stari ale automatului
 * @param adj lista de adiacenta a automatului
 * @param initialStates starile initiale ale automatului
 */
void task1(int n, vector<int> adj[], vector<int> initialStates) {
    bool visited[n] = { false };

    // se iau starile initiale pe rand
    for (auto &initialState : initialStates) {

        if (visited[initialState]) {
            continue;
        }

        // se porneste parcurgerea BFS
        queue<int> queue;
        queue.push(initialState);
        visited[initialState] = true;

        while (!queue.empty())
        {
            // se ia nodul curent din timpul parcurgerii => stare accesibila
            int currState = queue.front();
            queue.pop();
            
            printf("%d\n", currState);

            for (auto &nextState : adj[currState]) {
                if (!visited[nextState]) {
                    queue.push(nextState);
                    visited[nextState] = true;
                }
            }
        }
        
    }
}

/**
 * @brief descopera toate starile productive ale automatului
 * 
 * Din fiecare stare a automatului se porneste o parcurgere BFS. Daca din starea 
 * din care s-a pornit parcurgerea s-a ajuns in una din starile initiale, atunci
 * acea stare este una productiva
 * 
 * @param n numarul de stari al automatului
 * @param adj lista de adiacenta la automatului
 * @param finalStates lista starilor finale
 */
void task2(int n, vector<int> adj[], int finalStates[]) {
   // se ia fiecare stare
   for (int i = 0; i < n; i++) {

       // se porneste un BFS
        bool visited[n] = { false };
        queue<int> queue;
        queue.push(i);

        while (!queue.empty())
        {
            int currState = queue.front();
            queue.pop();

            // se verifica daca starea curenta este una finala
            if (finalStates[currState] == 1) {
                printf("%d\n", i);
                break;
            }

            for (auto &nextState : adj[currState]) {
                if (!visited[nextState]) {
                    queue.push(nextState);
                    visited[nextState] = true;
                }
            }
        }
        
    }
}

/**
 * @brief determina starile utile ale automatului
 * 
 * Din fiecare stare initiala a automatului se porneste o parcurgere BFS pana
 * la starile finale la care poate ajunge. Starile utile ale automatului
 * sunt reprezentate nodurile ce formeaza drum de la starea initiala pana 
 * la una din starile finale.
 * 
 * @param n numarul de stari al automatului
 * @param adj lista adiacenta automat
 * @param initialStates starile intiale ale automatului
 * @param finalStates starile finale ale automatului
 */
void task3(int n, vector<int> adj[], vector<int> initialStates, int finalStates[]) {
    set<int> result; // retine starile utile
    
    // se ia fiecare stare intiala din automat
    for (auto &initialState : initialStates) {

        // se porneste parcurherea BFS
        queue<vector<int>> queue;
        vector<int> path;
        path.push_back(initialState);
        queue.push(path);

        while (!queue.empty())
        {
            path = queue.front(); // se ia ramura curenta
            queue.pop();

            int lastState = path.back(); // se ia ultimul nod din drum la care s-a ajuns

            // se verifica daca s-a ajuns intr-o stare finala
            if (finalStates[lastState] == 1) {
                for (auto &res : path) {            
                    result.insert(res);
                }
            }

            for (auto &nextState : adj[lastState]) {

                // verifca daca ramura curenta conine urmatorul nod
                if (find(path.begin(), path.end(), nextState) == path.end()) {

                    // se adauga nod in drum
                    vector<int> newPath;
                    newPath.assign(path.begin(), path.end());
                    newPath.push_back(nextState);
                    queue.push(newPath);
                }
            }
        }
        
    }

    // afisare rezultat
    for (auto &res : result) {
        cout << res << endl;
    }
}


/**
 * @brief determina secventa de sincronizare a automatului
 * 
 * Pentru a determina secventa de sincronizare se porneste o parcurgere BFS din 2 stari diferite.
 * Cele 2 stari sunt luate din multimea X, multime ce contine starile la care se ajung prin aplicarea
 * tranzitiilor determinate.
 * Daca in timpul parcurgerii cele 2 noduri ajung in acelasi nod, atunci s-a gasit o secventa de sincornizare.
 * Pentru fiecare stare din multimea X, se aplica secventa gasita si se salveaza starile finale.
 * 
 * @param n numarul de stari ale automatului
 * @param m numarul de simboluri pe care se fac tranzitiile
 * @param adj lista de adiacenta automat
 */
void task4(int n, int m, vector<int> adj[]) {
    vector<int> finalSeq; // retine cuvantul de sincronizare
    vector<int> X; // retine starile la care se ajunge prin aplicarea functiei de tranzitie
    int size = n;

    // la inceput contine toate starile din automat
    for (int i = 0; i < n; i++) {
        X.push_back(i);
    }

    // cat timp exista mai mult de o stare, se iau 2 stari si se incepe o parcurgere BFS
    while (size > 1)
    {
        vector<int> foundSeq; // secventa gasita pana la o stare singleton
        queue<Pair> queue;

        int s1 = X[0];
        int s2 = X[1];

        // se incepe BFS
        Pair pair;
        pair.s1 = s1;
        pair.s2 = s2;

        queue.push(pair);

        while (!queue.empty())
        {
            pair = queue.front();
            queue.pop();

            // se ia fiecare tranzitie
            for (int i = 0; i < m; i++) {

                // se iau urmatoarele stari pe care este aplicata tranzitia
                int nextS1 = adj[pair.s1][i];
                int nextS2 = adj[pair.s2][i];

                // se verifca daca cele 2 stari au ajuns in aceeasi stare prin tranzitia curenta
                if (nextS1 == nextS2) {

                    // s-a gasit secventa care duc cele 2 noduri in aceeasi stare
                    
                    foundSeq = pair.seq;
                    foundSeq.push_back(i);
                    break;
                
                } else {

                    // se adauga starile cu tranzitia ce duc spre ele
                    Pair nextState;
                    nextState.s1 = nextS1;
                    nextState.s2 = nextS2;
                    nextState.seq = pair.seq;
                    nextState.seq.push_back(i);

                    queue.push(nextState);
                }
            }

            if (!foundSeq.empty()) {
                break;
            }
        }

        set<int> finalNodes;

        // pentru fiecare stare din multimea X, se aplica tranzitia gasita
        for (int i = 0; i < size; i++) {
            int state = X[i];

            for (auto &symbol : foundSeq) {
                state = adj[state][symbol];
            }

            // se salvea starile finale determinate de tranzitie
            finalNodes.insert(state);
        }

        // concatenare la secventa finala
        for (auto &sym : foundSeq) {
            finalSeq.push_back(sym);
        }

        // se decrementeaza multimea X, avand doar starile finale determinate de tranzitia gasita
        X.clear();
        size = 0;

        for (auto& it : finalNodes) {
           X.push_back(it);
           size++;
        }

        finalNodes.clear();
    }

    for (auto &sym : finalSeq) {
        cout << sym << " ";
    }
    cout << endl;
    
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Wrong number of arguments!");
        exit(1);
    }

    // citire input
    int n, m, s, f;

    scanf("%d %d %d %d", &n, &m, &s, &f);

    vector<int> adj[n];

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {
            int state;
            scanf("%d", &state);

            adj[i].push_back(state);
        }

    }

    vector<int> initialStates;
    if (s != 0) {
        for (int i = 0; i < s; i++) {
            int state;
            scanf("%d", &state);

            initialStates.push_back(state);
        }
    }

    int finalStates[n] = { 0 };
    if (f != 0) {
        for (int i = 0; i < f; i++) {
            int state;
            scanf("%d", &state);

            finalStates[state] = 1;
        }
    }

    // se determina problema ce trebuie rezolvata
    if (strcmp("accessible", argv[1]) == 0) {
        task1(n, adj, initialStates);
    } else if (strcmp("productive", argv[1]) == 0) {
        task2(n, adj, finalStates);
    } else if (strcmp("useful", argv[1]) == 0) {
        task3(n, adj, initialStates, finalStates);
    } else if (strcmp("synchronize", argv[1]) == 0) {
        task4(n, m, adj);
    }


    return 0;
}