// Student 1
// Name        : Ayush Bhakta
// Roll Number : 002411001072
// Year        : 3rd Year
// Section     : A3

// Student 2
// Name        : Dipram Biswas
// Roll Number : 002411001069
// Year        : 3rd Year
// Section     : A3

//Assignment Number : 4

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

const int FRAMES = 3;
const vector<int> mem_addr = {0, 1, 20, 2, 20, 21, 32, 31, 0, 60, 0, 0, 16, 1, 17, 18, 32, 31, 0, 61};
const int frame_lim = 3;

// Finds the page that will be needed farthest in the future
int furthest(unordered_map<int,int>& page_map, unordered_set<int>& frames, int current){
    int ans = -1;
    int max_dist = -1;
    for(int page : frames){
        int j = current + 1;
        while(j < mem_addr.size() && page_map[mem_addr[j]] != page){j++;}
        
        // If it is not used again, this is the best page to remove
        if(j == mem_addr.size()){return page;}
        if(j > max_dist){
            max_dist = j;
            ans = page;
        }
    }
    return ans;
}

struct node{
    int val;
    node* prev;
    node* next;

    node(int v, node* p, node* n) {
        val = v;
        prev = p;
        next = n;
    }
};

void fifo(unordered_map<int,int>& page_map){
    queue<int> f;
    int i = 0;
    unordered_set<int> frames;
    int page_fault = 0;
    // Queue keeps track of the order in which pages entered memory
    while(i < mem_addr.size()){
        if(frames.find(page_map[mem_addr[i]]) != frames.end()){
            i++;
            continue;
        }

        page_fault++;

        if(f.size() < frame_lim){
            f.push(page_map[mem_addr[i]]);
            frames.insert(page_map[mem_addr[i]]);
        }
        else{
            frames.erase(f.front());
            f.pop();
            f.push(page_map[mem_addr[i]]);
            frames.insert(page_map[mem_addr[i]]);
        }
        i++;
    }
    cout << "FIFO Page faults: " << page_fault << endl;
}

void lru(unordered_map<int,int>& page_map){
    int page_fault = 0;
    int i = 0;
    unordered_set<int> frames;
    node* head = new node(-1, nullptr, nullptr);
    node* tail = new node(-1, nullptr, nullptr);
    head->next = tail;
    tail->prev = head;
    while(i < mem_addr.size()){
        if(frames.find(page_map[mem_addr[i]]) != frames.end()){
            node* temp = head;

            // Move the recently used page to the front
            while(temp->val != page_map[mem_addr[i]]){
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            head->next->prev = temp;
            temp->next = head->next;
            head->next = temp;
            temp->prev = head;
            i++;
            continue;
        }

        page_fault++;

        if(frames.size() < frame_lim){
            node* nn = new node(page_map[mem_addr[i]], nullptr, nullptr);
            head->next->prev = nn;
            nn->next = head->next;
            head->next = nn;
            nn->prev = head;
            frames.insert(page_map[mem_addr[i]]);
        }
        else{
            // Last node is the least recently used page
            node* ln = tail->prev;
            frames.erase(ln->val);
            ln->prev->next = tail;
            tail->prev = ln->prev;
            delete(ln);

            node* nn = new node(page_map[mem_addr[i]], nullptr, nullptr);
            head->next->prev = nn;
            nn->next = head->next;
            head->next = nn;
            nn->prev = head;
            frames.insert(page_map[mem_addr[i]]);
        }
        i++;
    }
    cout << "LRU Page faults: " << page_fault << endl;
}

void optimal(unordered_map<int,int>& page_map){
    unordered_set<int> frames;
    int i = 0;
    int page_fault = 0;

    while(i < mem_addr.size()){
        if(frames.find(page_map[mem_addr[i]]) != frames.end()){
            i++;
            continue;
        }
        page_fault++;
        if(frames.size() < frame_lim){
            frames.insert(page_map[mem_addr[i]]);
        }
        else{
            // Replace the page whose next use is farthest away
            int ele = furthest(page_map, frames, i);
            frames.erase(ele);
            frames.insert(page_map[mem_addr[i]]);
        }
        i++;
    }

    cout << "Optimal Page faults: " << page_fault << endl;
}

int main(){
    unordered_map<int,int> page_map;
    string ref_s = "";

    // Convert each virtual address into page number and offset
    for(int i = 0; i < mem_addr.size(); i++){
        int page_num = mem_addr[i] / 16;
        page_map[mem_addr[i]] = page_num;
        int page_off = mem_addr[i] % 16;
        ref_s += to_string(page_num) + " ";
        cout << "MEM_ADDRESS - " << mem_addr[i] << " PAGE_NUM: " << page_num << " PAGE_OFFSET: " << page_off << endl;
    }

    cout << endl;
    cout << "Reference string: " << ref_s << endl;
    cout << endl;

    fifo(page_map);
    lru(page_map);
    optimal(page_map);
}