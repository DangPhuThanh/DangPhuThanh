#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define MAX 1000

// ================== CÁC HÀM ĐIỀU PHỐI TIẾN TRÌNH ====================
struct Process {
    int P, arrival_time, burst_time;
    int start_time = 0, completion_time = 0;
    int waiting_time = 0, turnaround_time = 0;
    bool is_completed = false;
    int remaining_time = 0;
};

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrival_time > p[j].arrival_time)
                swap(p[i], p[j]);
}

void printGanttChart(Process processes[], int n) {
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++) {
        cout << " P" << processes[i].P << " |";
    }
    cout << "\n" << processes[0].start_time;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << processes[i].completion_time;
    }
    cout << "\n";
}

void printResults(Process processes[], int n, string algoName) {
    double total_wait = 0, total_turn = 0;

    cout << "\nKet qua lap lich theo " << algoName << ":\n";
    cout << "TienTrinh\tDen\tThucHien\tBatDau\tHoanThanh\tCho\tXoayVong\n";

    for (int i = 0; i < n; i++) {
        total_wait += processes[i].waiting_time;
        total_turn += processes[i].turnaround_time;
        cout << "P" << processes[i].P << "\t\t"
             << processes[i].arrival_time << "\t"
             << processes[i].burst_time << "\t\t"
             << processes[i].start_time << "\t"
             << processes[i].completion_time << "\t\t"
             << processes[i].waiting_time << "\t"
             << processes[i].turnaround_time << "\n";
    }

    printGanttChart(processes, n);

    cout << fixed << setprecision(2);
    cout << "Thoi gian cho trung binh: " << total_wait / n << "\n";
    cout << "Thoi gian xoay vong trung binh: " << total_turn / n << "\n";
}

void FIFO(Process processes[], int n) {
    sortByArrival(processes, n);

    for (int i = 0; i < n; i++) {
        processes[i].start_time = (i == 0) ? processes[i].arrival_time :
            max(processes[i - 1].completion_time, processes[i].arrival_time);
        processes[i].completion_time = processes[i].start_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    printResults(processes, n, "FIFO (FCFS)");
}

void SJF(Process processes[], int n) {
    sortByArrival(processes, n);
    int completed = 0, current_time = 0;

    while (completed < n) {
        int idx = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed &&
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].start_time = current_time;
            processes[idx].completion_time = processes[idx].start_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            processes[idx].is_completed = true;
            current_time = processes[idx].completion_time;
            completed++;
        } else {
            current_time++;
        }
    }

    printResults(processes, n, "SJF");
}

void SRTF(Process processes[], int n) {
    sortByArrival(processes, n);
    int completed = 0, current_time = 0;

    while (completed < n) {
        int idx = -1, min_remaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed &&
                processes[i].remaining_time < min_remaining && processes[i].remaining_time > 0) {
                min_remaining = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx != -1) {
            if (processes[idx].remaining_time == processes[idx].burst_time)
                processes[idx].start_time = current_time;

            processes[idx].remaining_time--;
            current_time++;

            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].is_completed = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    printResults(processes, n, "SRTF");
}

void RR(Process processes[], int n, int quantum) {
    sortByArrival(processes, n);
    int completed = 0, current_time = 0;
    bool done;

    do {
        done = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                done = false;
                if (processes[i].remaining_time == processes[i].burst_time)
                    processes[i].start_time = max(current_time, processes[i].arrival_time);

                int exec_time = min(quantum, processes[i].remaining_time);
                current_time = max(current_time, processes[i].arrival_time) + exec_time;
                processes[i].remaining_time -= exec_time;

                if (processes[i].remaining_time == 0) {
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].is_completed = true;
                    completed++;
                }
            }
        }
        if (done == true) break;
    } while (completed < n);

    printResults(processes, n, "RR");
}

void runScheduling() {
    Process processes[MAX];
    int n, choice, quantum;

    cout << "=========== CHON THUAT TOAN ĐIEU PHOI TIEN TRINH ===========\n";
    cout << "1. FIFO (First Come First Serve)\n";
    cout << "2. SJF (Shortest Job First)\n";
    cout << "3. SRTF (Shortest Remaining Time First)\n";
    cout << "4. RR (Round Robin)\n";
    cout << "===============================================\n";
    cout << "Nhap lua chon (1-4): ";
    cin >> choice;

    if (choice < 1 || choice > 4) {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    cout << "Nhap so luong tien trinh: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        processes[i].P = i + 1;
        cout << "Tien trinh P" << i + 1 << ":\n";
        cout << " - Nhap thoi gian den: ";
        cin >> processes[i].arrival_time;
        cout << " - Nhap thoi gian thuc hien: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = false;
    }

    if (choice == 1)
        FIFO(processes, n);
    else if (choice == 2)
        SJF(processes, n);
    else if (choice == 3)
        SRTF(processes, n);
    else if (choice == 4) {
        cout << "Nhap quantum: ";
        cin >> quantum;
        RR(processes, n, quantum);
    }
}

bool runBanker(const vector<vector<int>>& allocation, const vector<vector<int>>& need, const vector<int>& available, int P, int R, bool printResult = true);

void requestResource(vector<vector<int>>& allocation, vector<vector<int>>& need, vector<int>& available, int P, int R) {
    int pID;
    cout << "\nNhap tien trinh muon yeu cau cap phat them (P0 ~ P" << P - 1 << "): ";
    cin >> pID;

    vector<int> request(R);
    cout << "Nhap vector yeu cau (Request[" << pID << "]): ";
    for (int i = 0; i < R; i++) {
        cin >> request[i];
    }

    for (int i = 0; i < R; i++) {
        if (request[i] > need[pID][i]) {
            cout << "\nYeu cau vuot qua Need. Khong the cap phat.\n";
            return;
        }
        if (request[i] > available[i]) {
            cout << "\nYeu cau vuot qua Available. Khong the cap phat.\n";
            return;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[pID][i] += request[i];
        need[pID][i] -= request[i];
    }

    cout << "\nNeed sau cap phat:\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < R; j++)
            cout << setw(3) << need[i][j] << " ";
        cout << "\n";
    }

    cout << "\nAvailable sau cap phat: ";
    for (int i = 0; i < R; i++)
        cout << available[i] << " ";
    cout << "\n";

    if (runBanker(allocation, need, available, P, R)) {
        cout << "\nCap phat thanh cong. He thong van an toan.\n";
    } else {
        cout << "\nKhong an toan. Khoi phuc lai trang thai ban dau.\n";
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[pID][i] -= request[i];
            need[pID][i] += request[i];
        }
    }
}

void runBankerAlgorithm() {
    int P, R;
    cout << "Nhap so tien trinh P: ";
    cin >> P;
    cout << "Nhap so loai tai nguyen R: ";
    cin >> R;

    vector<vector<int>> max(P, vector<int>(R));
    vector<vector<int>> allocation(P, vector<int>(R));
    vector<vector<int>> need(P, vector<int>(R));
    vector<int> available(R);

    cout << "\nNhap Max matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "Tien trinh P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> max[i][j];
    }

    cout << "\nNhap Allocation matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "Tien trinh P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    }

    cout << "\nNhap Available vector:\n";
    for (int i = 0; i < R; i++) {
        cout << "R" << i+1 << ": ";
        cin >> available[i];
    }

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            cout << setw(3) << need[i][j] << " ";
        cout << "\n";
    }

    runBanker(allocation, need, available, P, R);

    char ask;
    cout << "\nBan co muon yeu cau cap phat them tai nguyen? (y/n): ";
    cin >> ask;
    if (ask == 'y' || ask == 'Y') {
        requestResource(allocation, need, available, P, R);
    }
}

bool runBanker(const vector<vector<int>>& allocation, const vector<vector<int>>& need, const vector<int>& available, int P, int R, bool printResult) {
    vector<bool> finish(P, false);
    vector<int> safeSeq;
    vector<int> work = available;
    vector<vector<int>> workTable;
    vector<int> processTable;

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    workTable.push_back(work);
                    processTable.push_back(i);
                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            if (printResult)
                cout << "\nHe thong KHONG an toan (co deadlock).\n";
            return false;
        }
    }

    if (printResult) {
        cout << "\nWork Table:\n";
        cout << setw(10) << "Process";
        for (int j = 0; j < R; j++)
            cout << setw(5) << "R" << j+1;
        cout << "\n";

        for (int i = 0; i < workTable.size(); i++) {
            cout << setw(10) << "P" << processTable[i];
            for (int val : workTable[i])
                cout << setw(5) << val;
            cout << "\n";
        }

        cout << "\nHe thong an toan (safe sequence): ";
        for (int i = 0; i < safeSeq.size(); i++)
            cout << "P" << safeSeq[i] << (i == safeSeq.size() - 1 ? "\n" : " -> ");
    }

    return true;
}

int main() {
    int choice;
    cout << "========= MENU CHINH =========\n";
    cout << "1. Thuat toan dieu phoi tien trinh\n";
    cout << "2. Thuat toan Banker\n";
    cout << "=============================\n";
    cout << "Nhap lua chon (1-2): ";
    cin >> choice;

       if (choice == 1) {
        runScheduling();
    } else if (choice == 2) {
        runBankerAlgorithm();
    } else {
        cout << "Lua chon khong hop le!\n";
    }

    return 0;
}

