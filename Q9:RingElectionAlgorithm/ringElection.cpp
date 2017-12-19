#include <cstdlib>
#include <iostream>
using namespace std;

struct Process {
  int id;
  bool alive;
} processes[100];
int initiatorID = -1;
int coordinatorID = -1;
int numberOfProcesses;

void rebuildRing();
void dispProcess() {
  cout << "\nNumber Of Processes: " << numberOfProcesses << endl;
  for (int i = 0; i < numberOfProcesses; i++) {
    cout << processes[i].id << "->";
    if (processes[i].alive)
      cout << "Alive";
    else
      cout << "Dead";
    if (i == initiatorID)
      cout << "  -> INITIATOR";
    if (i == coordinatorID)
      cout << "  -> COORDINATOR";
    cout << endl;
  }
}
void initializeProcesses() {
  cout << "Enter the number of processes: ";
  cin >> numberOfProcesses;
  for (int i = 0; i < numberOfProcesses; i++) {
    processes[i].id = i;
    processes[i].alive = true;
  }
  cout << "\nEnter initiator ID";
  cin >> initiatorID;
  rebuildRing();
  dispProcess();
  cout << "Processes have been initialized";
}

int menu() {
  cout << "\nEnter Choice\n";
  cout << "1. Crash Process";
  cout << "\n2. Recover Process";
  cout << "\n3. Display Processes Status\n";
  cout << "4.Exit\n";
  int choice;
  cin >> choice;
  return choice;
}
void rebuildRing() {
  int aliveProcessID[100], numberOfAliveProcesses = 0;
  for (int i = 0; i < numberOfProcesses; i++) {
    if (processes[i].alive)
      aliveProcessID[numberOfAliveProcesses++] = i;
  }
  if (numberOfAliveProcesses == 0) {
    cout << "No Process Alive!";
    coordinatorID = -1;
  } else {
    int curProcess = 0;
    while (aliveProcessID[curProcess] != initiatorID) {
      curProcess++;
    }
    do {
      int nextID = (curProcess + 1) % numberOfAliveProcesses;
      cout << "\nMessage from " << aliveProcessID[curProcess] << " -> "
           << aliveProcessID[nextID];
      curProcess = nextID;
    } while (aliveProcessID[curProcess] != initiatorID);
    coordinatorID = aliveProcessID[numberOfAliveProcesses - 1];
    cout << "\nCoordinator: " << coordinatorID;
  }
}
void crashProcess() {
  cout << "Enter the ID of the process to Crash";
  int crashID;
  cin >> crashID;
  processes[crashID].alive = false;
  int tries = 100;
  if (crashID == initiatorID) {
    while (tries) {
      int newInitiator = rand() % numberOfProcesses;
      if (processes[newInitiator].alive) {
        initiatorID = newInitiator;
        break;
      }
      tries--;
    }
  }
  rebuildRing();
}

void recoverProcess() {
  cout << "\nEnter the process ID to recover: ";
  int recoverID;
  cin >> recoverID;
  if (!processes[recoverID].alive)
    processes[recoverID].alive = true;
  else
    cout << "\nProcess Already active";
  rebuildRing();
}

int main() {
  initializeProcesses();
  while (true) {
    switch (menu()) {
    case 1:
      crashProcess();
      break;
    case 2:
      recoverProcess();
      break;
    case 3:
      dispProcess();
      break;
    case 4:
      return 0;
    default:
      cout << "Wrong Choice";
    }
  }
}
