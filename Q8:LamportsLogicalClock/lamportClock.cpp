#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int numberOfEventsP1;
  int numberOfEventsP2;

  cout << "Enter number of events in Process 1: ";
  cin >> numberOfEventsP1;
  cout << "Enter number of events in Process 2: ";
  cin >> numberOfEventsP2;

  int timerP1[numberOfEventsP1], timerP2[numberOfEventsP2];
  int dependencyMatrix[numberOfEventsP1][numberOfEventsP2];
  // setting initial value of timestamps
  for (int i = 0; i < numberOfEventsP1; i++)
    timerP1[i] = i + 1;
  for (int i = 0; i < numberOfEventsP2; i++)
    timerP2[i] = i + 1;

  cout << "\n\nEnter Dependency matrix";
  cout << "\n1 \t-\t P1->P2\n-1 \t-\t P2->P1\n0 \t-\t otherwise\n";
  for (int i = 0; i < numberOfEventsP2; i++) {
    cout << "\tP2:" << i + 1;
  }
  for (int i = 0; i < numberOfEventsP1; i++) {
    cout << "\nP1:" << i + 1 << "\t";
    for (int j = 0; j < numberOfEventsP2; j++) {
      cin >> dependencyMatrix[i][j];
    }
  }

  // generating time stamps for each event
  for (int i = 0; i < numberOfEventsP1; i++) {
    for (int j = 0; j < numberOfEventsP2; j++) {
      switch (dependencyMatrix[i][j]) {
      case 1:
        timerP2[j] = max(timerP2[j], timerP1[i] + 1);
        for (int k = j; k < numberOfEventsP2 - 1; k++)
          timerP2[k + 1] = timerP2[k] + 1;
        break;
      case -1:
        timerP1[i] = max(timerP1[i], timerP2[j] + 1);
        for (int k = i; k < numberOfEventsP1 - 1; k++)
          timerP1[k + 1] = timerP1[k] + 1;
        break;
      case 0:
        break;
      default:
        cout << "Invalid Dependency Matrix";
        break;
      }
    }
  }

  cout << "Process P1 - ";
  for (int i = 0; i < numberOfEventsP1; i++)
    cout << "P1:" << i + 1 << " :" << timerP1[i] << "  ";
  cout << "\nProcess P2 - ";
  for (int i = 0; i < numberOfEventsP2; i++)
    cout << "P2:" << i + 1 << " :" << timerP2[i] << "  ";
  return 0;
}
