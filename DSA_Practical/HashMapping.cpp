#include <iostream>
#define SIZE 10
using namespace std;

// Hash function
int Hash(int Roll) {
    return Roll % SIZE;
}

// Linear probing to find the next empty spot
int LinearProbe(int H[], int Roll) {
    int index = Hash(Roll);
    int i = 0;
    while (H[(index + i) % SIZE] != 0) {
        i++;
        if (i == SIZE) {  // Table full
            cout << "Hash table is full!" << endl;
            return -1;  // Indicate failure
        }
    }
    return (index + i) % SIZE;
}

// Insert a roll number into the hash table
void insert(int H[], int Roll) {
    int index = Hash(Roll);
    if (H[index] != 0) {  // Collision detected
        index = LinearProbe(H, Roll);
        if (index == -1) return;  // Stop if the table is full
    }
    H[index] = Roll;
}

// Display the hash table
void display(int H[]) {
    for (int i = 0; i < SIZE; i++) {
        if (H[i] != 0)
            cout << "Index " << i << ": " << H[i] << endl;
        else
            cout << "Index " << i << ": Empty" << endl;
    }
}

// Search for a roll number in the hash table
void search(int H[], int Roll) {
    int index = Hash(Roll);
    int i = 0;

    // Linear probing to search for the record
    while (H[(index + i) % SIZE] != 0) {
        if (H[(index + i) % SIZE] == Roll) {  // Found the roll number
            cout << "Roll number " << Roll << " found at index " << (index + i) % SIZE << endl;
            return;
        }
        i++;
        if (i == SIZE) {  // Full table checked
            break;
        }
    }

    // If the roll number is not found
    cout << "Roll number " << Roll << " not found in the hash table." << endl;
}

int main() {
    int HT[SIZE] = {0};  // Initialize hash table with 0

    // Insert roll numbers
    insert(HT, 12);
    insert(HT, 13);
    insert(HT, 14);
    insert(HT, 40);
    insert(HT, 44);
    insert(HT, 25);
    insert(HT, 35);
    insert(HT, 45);

    // Display the hash table
    cout << "Hash Table Contents:" << endl;
    display(HT);

    // Search for specific roll numbers
    cout << "\nSearch Results:" << endl;
    search(HT, 40);  // Roll number present
    search(HT, 99);  // Roll number absent

    return 0;
}
