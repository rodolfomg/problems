#include <bits/stdc++.h>

using namespace std;
int letters[20], sub_letters[20];

// I saved the index for every letter => A:0 C:2 G:6 T:19
int acgt[4] = {0, 2, 6, 19};

int steadyGene(string gene, int n) {
    int i, check=0;

    // letter - 'A' just set a base 'A' = 0 for all alphabet
    for(i=0; i<n; i++) letters[gene[i]-'A']++;
    for(i=0; i<4; i++) letters[acgt[i]] -= n/4;

    // No changes are needed
    for(i=0; i<4; i++) if(letters[acgt[i]] == 0)check++;
    if(check==4)return 0;

    /*
     * start < n : is for check all posible one size substring
     * end == n && check != 4 : when you reach the end of substrings and you couldn't find the letters nedded
     *                          there's no need to move start because you woudn't find a valid substring
     */
    int start=0, end=0, min=n;
    while(start < n && !(end == n && check != 4)){
        // We need more letters
        if(end < n && check < 4){
            sub_letters[gene[end]-'A']++;
            end++;
        }

        check=0;
        for(i=0; i<4; i++) if(sub_letters[acgt[i]] >= letters[acgt[i]])check++;

        // Check must be 4 in order to assure all letters needed was finded, we can now remove a letter
        if(check==4){
            if(end - start < min) min = end - start;
            sub_letters[gene[start]-'A']--;
            start++;
        }
    }

    return min;
}

int main() {
    int n;
    cin >> n;
    string gene;
    cin >> gene;
    int result = steadyGene(gene, n);
    cout << result << endl;
    return 0;
}
