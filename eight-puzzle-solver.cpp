#include "eight-puzzle-solver.h"

using namespace std;

EightPuzzleSolver::EightPuzzleSolver(WINDOW *_window, const string &path):
    total(0),
    current(0),
    precentage(0.0d),
    printLine(3),
    range(pair<size_t,size_t>(3,20)),
    window(_window)
{
    outFile.open(path);
    if(!outFile.is_open()){
        throw new exception();
    }
}

EightPuzzleSolver::~EightPuzzleSolver()
{
    outFile.close();
}

bool EightPuzzleSolver::initialize(const size_t &start, const size_t &end)
{
    if(start < end && start > 0) {
        this->range.first = start;
        this->range.second = end;
        return true;
    }
    else {
        return false;
    }
}

void EightPuzzleSolver::start()
{
    for (size_t length = this->range.second; length> this->range.first; --length) {
        wmove(window, 0, 0);
        total = pow(5.0,length);
        current = 0;
        precentage = 0.0;
        wprintw(window, "Checking strings of length: %d",length);
        wmove(window, 1, 0);
        wprintw(window, "Total: %.0lf",pow(5.0,length));
        this->inputs = vector<char>(length,'0');
        auto begin = inputs.begin();
        permutation(begin);
    }
}

std::vector<string> EightPuzzleSolver::getResults()
{
    return this->getResults();
}

bool EightPuzzleSolver::check(const vector<char> &inputs)
{
    while(!evaluation.empty()) {
        evaluation.pop();
    }
    for(const auto& n: inputs) {
        int n1, n2;
        switch (n) {
        case '+': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2+n1);
            }
            break;
        case '-': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2-n1);
            }
            break;
        case '*': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2*n1);
            }
            break;
        case '/': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                if(n1==0) {
                    return false;
                }
                else {
                    evaluation.push(n2/n1);
                }
            }
            break;
        case '8':
            evaluation.push(8);
            break;
        default:
            return false;
            break;
        }
    }
    return (evaluation.size()==1 && evaluation.top()==1000);
}

void EightPuzzleSolver::permutation(vector<char>::iterator i)
{
    if(i==inputs.end()) {
        time_t rawtime;
        struct tm *timeinfo;
        char time_buffer[80];
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(time_buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
        wmove(window, 2, 0);
        ++current;
        precentage = 100.0*static_cast<double>(current)/total;
        wprintw(window, "Time: %s, Progress: %d of %.0lf (%.4f%%) sample: %.*s",
                time_buffer,current,total,precentage,inputs.size(),inputs.data());
        wrefresh(window);
        if(!check(inputs)) {
            sleep(1);
            wmove(window, printLine, 0);
            wprintw(window, "%d: %.*s",results.size()+1,inputs.size(),inputs.data());
            string PRN{inputs.begin(),inputs.end()};
            results.push_back(PRN);
            outFile << PRN << std::endl;
            wrefresh(window);
            ++printLine;
        }
        return;
    }
    else {
        *i='8';
        permutation(i+1);
        *i='+';
        permutation(i+1);
        *i='-';
        permutation(i+1);
        *i='*';
        permutation(i+1);
        *i='/';
        permutation(i+1);
    }
}
