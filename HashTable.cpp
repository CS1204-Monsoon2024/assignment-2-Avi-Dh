#include <iostream>

using namespace std;

class Node {
    public:
        int key;
        // if true indicates that element is deleted but search function should 
        // continue search. if false search function should not continue searching
        int delete_flag;

        Node(int key) {
            this->key = key;
            delete_flag = false;
        }
};

class HashTable {
    Node** T;
    int m; 
    int n; 
    float alpha; 

    public:
        HashTable(int size) {
            m = size;
            n = 0;
            alpha = (float)n / (float)m;
            T = new Node*[m]; 
            for (int i = 0; i < m; i++) {
                T[i] = nullptr;
            }    
        }

        // void insert(int key) {
        //     alpha = (float)n / (float)m;

        //     if (alpha > 0.8) { 
        //         resize();
        //     }

        //     int index = hash(key);
        //     int i = 0;
        //     float limit = (float)(m+1) / (float)2;

        //     while (T[index] != nullptr && T[index]->delete_flag != true) {
        //         if (T[index]->key == key) {
        //             // T[index]->value = value; 
        //             cout << "Duplicate key insertion is not allowed" << endl;
        //             return;
        //         }
        //         i++;
        //         index = (hash(key) + i * i) % m; 
        //     }

        //     T[index] = new Node(key);
        //     n++; 
        //     alpha = (float)n / (float)m; 
        // }

        void insert(int key) {
            alpha = (float)n / (float)m;

            if (alpha > 0.8) { 
                resize();
            }

            int index = hash(key);
            int i = 0;
            float limit = (float)(m + 1) / (float)2;  // Max quadratic probing limit

            while (i < limit) {
                if (T[index] != nullptr && T[index]->delete_flag != true) {
                    if (T[index]->key == key) {
                        cout << "Duplicate key insertion is not allowed" << endl;
                        return;
                    }
                    i++;
                    index = (hash(key) + i * i) % m;
                } else {
                    T[index] = new Node(key);
                    n++; 
                    alpha = (float)n / (float)m;
                    return;
                }
            }

            cout << "Max probing limit reached!" << endl;
        }


        void insertWithTable(int key, Node** table) {
            int index = hash(key);
            int i = 0;
            float limit = (float)(m + 1) / (float)2;  // Max quadratic probing limit

            while (i < limit) {
                if (table[index] != nullptr && table[index]->delete_flag != true) {
                    if (table[index]->key == key) {
                        cout << "Duplicate key insertion is not allowed" << endl;
                        return;
                    }
                    i++;
                    index = (hash(key) + i * i) % m;
                } else {
                    table[index] = new Node(key);
                    return;
                }
            }

            cout << "Max probing limit reached!" << endl;
        }


        void remove(int key) {
            int index = hash(key);
            int i = 0;
            float limit = (float)(m+1) / (float)2;

            while (i < limit) {
                if (T[index] == nullptr) {
                    cout << "Element not found" << endl;
                    return;
                }

                if (T[index]->key == key) {
                    T[index]->delete_flag = true;
                    n--;
                    return;
                }
                i++;
                index = (hash(key) + i * i) % m; 
            }
            cout << "Element not found" << endl;
        }

        int search(int key) {
            int index = hash(key);
            int i = 0;
            float limit = (float)(m + 1) / 2;

            while (i < limit) {
                if (T[index] == nullptr) {
                    return -1;
                }
                if (T[index]->key == key && T[index]->delete_flag == false) {
                    return index;
                }
                i++;
                index = (hash(key) + i * i) % m;
            }
            return -1;
        }

        void resize() {
            int mPrev = m;
            // m = m * 2; 
            m = nextPrime(m * 2);

            Node** newT = new Node*[m]; 
            for (int i = 0; i < m; i++) {
                newT[i] = nullptr;
            }

            for (int i = 0; i < mPrev; i++) {
                if (T[i] != nullptr && T[i]->delete_flag != true) {
                    insertWithTable(T[i]->key, newT); 
                }
            }

            T = newT; 
        }
    
        void printTable() {
            for (int i = 0; i < m; i++) {
                if (T[i] == nullptr || T[i]->delete_flag == true) {
                    cout << "- ";
                } else {
                    cout << T[i]->key << " ";
                }
            }
            cout << endl;
        }

        bool isPrime(int num) {
            if (num < 2) {
                return false; 
            }
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) {
                    return false;
                }
            }
            return true;
        }

        int nextPrime(int num) {
            while (isPrime(num) == false) {
                num++;
            }
            return num;
        }

        int hash(int key) {
            return key % m;
        }
};

// int main() {
//     HashTable ht(5);  

//     ht.insert(3);
//     ht.printTable();
//     cout << endl;

//     ht.insert(21);
//     ht.printTable();
//     cout << endl;

//     ht.insert(9);
//     ht.printTable();
//     cout << endl;

//     ht.insert(4);
//     ht.printTable();
//     cout << endl;

//     ht.insert(90); 
//     ht.printTable();
//     cout << endl;

//     ht.insert(56); 
//     ht.printTable();
//     cout << endl;

//     ht.remove(56);
//     ht.printTable();
//     cout << endl;

//     ht.remove(5);
//     ht.printTable();
//     cout << endl;

//     cout << ht.search(4) << endl;
//     cout << ht.search(67);
// }