#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include "ArraySequence.h"
#include "ListSequence.h"
using namespace std;

void coutSequence(Sequence<int>* seq, ostream &out) {
    int length = seq->GetLength();
    for (int i = 0; i < length; i++) {
        out << seq->Get(i) << " ";
    }
    out << "\n";
}

void menu() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cerr << "ERROR OPENING INPUT.TXT" << endl;
        return;
    }
    if (!fout.is_open()) {
        cerr << "ERROR OPENING OUTPUT.TXT" << endl;
        return;
    }
    map<string, Sequence<int>*> sequences;
    string actName = "";
    Sequence<int>* actSeq = nullptr;

    string line;
    while (getline(fin, line)) {
        if (line == "END")
            break;
        if (line.empty())
            continue;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "CREATE") {
            string name, structType, dataType, mutability;
            iss >> name >> structType >> dataType >> mutability;
            if (dataType != "INT") {
                fout << "ONLY INT TYPE IS SUPPORTED" << name << "\n";
                continue;
            }
            vector<int> initial;
            int num;
            while (iss >> num)
                initial.push_back(num);
            Sequence<int>* seq = nullptr;
            if (structType == "ARRAY") {
                if (mutability == "MUTABLE") {
                    if (!initial.empty()) {
                        int* arr = new int[initial.size()];
                        for (int i = 0; i < initial.size(); i++)
                            arr[i] = initial[i];
                        seq = new MutableArraySequence<int>(arr, initial.size());
                        delete[] arr;
                    } else {
                        seq = new MutableArraySequence<int>();
                    }
                } else if (mutability == "IMMUTABLE") {
                    if (!initial.empty()) {
                        int* arr = new int[initial.size()];
                        for (int i = 0; i < initial.size(); i++)
                            arr[i] = initial[i];
                        seq = new ImmutableArraySequence<int>(arr, initial.size());
                        delete[] arr;
                    } else {
                        seq = new ImmutableArraySequence<int>();
                    }
                } else {
                    fout << "UNKNOWN MUTABILITY TYPE: " << mutability << "\n";
                    continue;
                }
            } else if (structType == "LIST") {
                if (mutability == "MUTABLE") {
                    if (!initial.empty()) {
                        int* arr = new int[initial.size()];
                        for (int i = 0; i < initial.size(); i++)
                            arr[i] = initial[i];
                        seq = new MutableListSequence<int>(arr, initial.size());
                        delete[] arr;
                    } else {
                        seq = new MutableListSequence<int>();
                    }
                } else if (mutability == "IMMUTABLE") {
                    if (!initial.empty()) {
                        int* arr = new int[initial.size()];
                        for (int i = 0; i < initial.size(); i++)
                            arr[i] = initial[i];
                        seq = new ImmutableListSequence<int>(arr, initial.size());
                        delete[] arr;
                    } else {
                        seq = new ImmutableListSequence<int>();
                    }
                } else {
                    fout << "UNKNOWN MUTABILITY TYPE: " << mutability << "\n";
                    continue;
                }
            } else {
                fout << "UNKNOWN struct TYPE: " << structType << "\n";
                continue;
            }
            sequences[name] = seq;
            actName = name;
            actSeq = seq;
            fout << "SEQUENCE " << name << " OF TYPE " << structType << " " << mutability << " CREATED\n";
        }
        else if (cmd == "SELECT") {
            string name;
            iss >> name;
            if (sequences.find(name) == sequences.end()) {
                fout << "SEQUENCE " << name << " NOT FOUND\n";
            } else {
                actName = name;
                actSeq = sequences[name];
                fout << "SEQUENCE " << name << " SELECTED\n";
            }
        }
        else if (cmd == "AVALIBLE_SEQ") {
            fout << "AVAILABLE SEQUENCES: ";
            for (auto &pair : sequences) {
                fout << pair.first;
                if (pair.first == actName)
                    fout << " (selected)";
                fout << "  ";
            }
            fout << "\n";
        }
        else {
            if (actSeq == nullptr) {
                fout << "NO ACTIVE SEQUENCE. USE CREATE OR SELECT.\n";
                continue;
            }
            if (cmd == "COUT") {
                coutSequence(actSeq, fout);
            } else if (cmd == "APPEND") {
                int val;
                iss >> val;
                actSeq->Append(val);
                fout << "APPENDED " << val << "\n";
            } else if (cmd == "PREPEND") {
                int val;
                iss >> val;
                actSeq->Prepend(val);
                fout << "PREPENDED " << val << "\n";
            } else if (cmd == "INSERT_AT") {
                int index, val;
                iss >> index >> val;
                actSeq->InsertAt(val, index);
                fout << "INSERTED " << val << " AT INDEX " << index << "\n";
            } else if (cmd == "GET") {
                int index;
                iss >> index;
                int res = actSeq->Get(index);
                fout << "ELEMENT AT INDEX " << index << ": " << res << "\n";
            } else if (cmd == "GET_FIRST") {
                int res = actSeq->GetFirst();
                fout << "FIRST ELEMENT: " << res << "\n";
            } else if (cmd == "GET_LAST") {
                int res = actSeq->GetLast();
                fout << "LAST ELEMENT: " << res << "\n";
            } else if (cmd == "LENGTH") {
                fout << "LENGTH: " << actSeq->GetLength() << "\n";
            } else if (cmd == "SUBSEQUENCE") {
                int start, end;
                iss >> start >> end;
                Sequence<int>* subSeq = actSeq->GetSubsequence(start, end);
                fout << "SUBSEQUENCE [" << start << ", " << end << "]: ";
                coutSequence(subSeq, fout);
                delete subSeq;
            } else if (cmd == "CONCAT") {
                vector<int> concatVec;
                int val;
                while (iss >> val) {
                    concatVec.push_back(val);
                }
                Sequence<int>* tmpSeq = nullptr;
                if (dynamic_cast<MutableArraySequence<int>*>(actSeq) != nullptr ||
                    dynamic_cast<ImmutableArraySequence<int>*>(actSeq) != nullptr) {
                    if (!concatVec.empty()) {
                        int* arr = new int[concatVec.size()];
                        for (int i = 0; i < concatVec.size(); i++)
                            arr[i] = concatVec[i];
                        tmpSeq = new MutableArraySequence<int>(arr, concatVec.size());
                        delete[] arr;
                    } else {
                        tmpSeq = new MutableArraySequence<int>();
                    }
                } else {
                    if (!concatVec.empty()) {
                        int* arr = new int[concatVec.size()];
                        for (int i = 0; i < concatVec.size(); i++)
                            arr[i] = concatVec[i];
                        tmpSeq = new MutableListSequence<int>(arr, concatVec.size());
                        delete[] arr;
                    } else {
                        tmpSeq = new MutableListSequence<int>();
                    }
                }
                Sequence<int>* newSeq = actSeq->Concat(tmpSeq);
                delete tmpSeq;
                delete actSeq;
                sequences[actName] = newSeq;
                actSeq = newSeq;
                fout << "SEQUENCES CONCATENATED\n";
            } else {
                fout << "UNKNOWN COMMAND: " << cmd << "\n";
            }
        }
    }
    
    for (auto &p : sequences)
        delete p.second;
}
