#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <limits>
#include <thread>
#include <atomic>
<<<<<<< HEAD
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <functional>

using namespace std;

=======
#include <atomic
using namespace std;

// 有向图结构
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
class DirectedGraph {
private:
    unordered_map<string, unordered_map<string, int>> adjacencyList;
    unordered_map<string, double> pageRank;
    unordered_map<string, double> initialPR;
    atomic<bool> stopWalk;
<<<<<<< HEAD
    mutable shared_mutex graphMutex;

    struct StringPool {
        vector<unique_ptr<string>> pool;
        const string* intern(const string& s) {
            auto it = find_if(pool.begin(), pool.end(), 
                [&](const auto& ptr) { return *ptr == s; });
            if (it != pool.end()) return it->get();
            pool.push_back(make_unique<string>(s));
            return pool.back().get();
        }
    } stringPool;

    unordered_map<string, pair<int, string>> computeShortestPaths(const string& start) {
        shared_lock<shared_mutex> lock(graphMutex);
        unordered_map<string, pair<int, string>> distances;
        using QueueItem = pair<int, string>;
        priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> pq;
        
        for (const auto& node : adjacencyList) {
            distances[node.first] = {numeric_limits<int>::max(), ""};
        }
        
        if (!distances.count(start)) return distances;
        
        distances[start] = {0, ""};
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto [currentDist, current] = pq.top();
            pq.pop();
            
            if (currentDist > distances[current].first) continue;
            
            if (!adjacencyList.count(current)) continue;
            
            for (const auto& [neighbor, weight] : adjacencyList.at(current)) {
                int newDist = currentDist + weight;
                if (newDist < distances[neighbor].first) {
                    distances[neighbor] = {newDist, current};
                    pq.push({newDist, neighbor});
                }
            }
        }
        return distances;
    }
=======
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5

public:
    DirectedGraph() : stopWalk(false) {}

    void addEdge(const string& from, const string& to) {
<<<<<<< HEAD
        unique_lock<shared_mutex> lock(graphMutex);
        const string* f = stringPool.intern(from);
        const string* t = stringPool.intern(to);
        adjacencyList[*f][*t]++;
    }

    void display() const {
        shared_lock<shared_mutex> lock(graphMutex);
=======
        adjacencyList[from][to]++;
    }

    void display() const {
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        for (const auto& from : adjacencyList) {
            cout << from.first << " -> ";
            bool first = true;
            for (const auto& to : from.second) {
                if (!first) cout << ", ";
                cout << to.first << "(" << to.second << ")";
                first = false;
            }
            cout << endl;
        }
    }

    bool containsWord(const string& word) const {
<<<<<<< HEAD
        shared_lock<shared_mutex> lock(graphMutex);
        return adjacencyList.find(word) != adjacencyList.end();
    }

    vector<string> getBridgeWords(const string& word1, const string& word2, bool showWarning = true) {
        shared_lock<shared_mutex> lock(graphMutex);
        vector<string> bridgeWords;
        
        if (!containsWord(word1)) {
            if (showWarning) cout << "No " << word1 << " in the graph!" << endl;
            return bridgeWords;
        }
        if (!containsWord(word2)) {
            if (showWarning) cout << "No " << word2 << " in the graph!" << endl;
            return bridgeWords;
        }
        
        const auto& neighbors = adjacencyList.at(word1);
        for (const auto& neighbor : neighbors) {
            const string& word3 = neighbor.first;
            if (adjacencyList.count(word3) && adjacencyList.at(word3).count(word2)) {
                bridgeWords.push_back(word3);
            }
        }
=======
        return adjacencyList.find(word) != adjacencyList.end();
    }

   vector<string> getBridgeWords(const string& word1, const string& word2, bool showWarning = true) {
        vector<string> bridgeWords;
        
       if (!containsWord(word1)) {
        if (showWarning) cout << "No " << word1 << " in the graph!" << endl;
        return bridgeWords;
    }
    if (!containsWord(word2)) {
        if (showWarning) cout << "No " << word2 << " in the graph!" << endl;
        return bridgeWords;
    }
        
        for (const auto& neighbor : adjacencyList.at(word1)) {
            string word3 = neighbor.first;
            if (containsWord(word3) && adjacencyList.at(word3).find(word2) != adjacencyList.at(word3).end()) {
                bridgeWords.push_back(word3);
            }
        }
        
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        return bridgeWords;
    }

    string generateNewText(const string& inputText) {
<<<<<<< HEAD
        string cleanedInput = cleanString(inputText);
        istringstream iss(cleanedInput);
        vector<string> words;
        string word;
        
        while (iss >> word) {
            words.push_back(word);
        }
        
        if (words.size() < 2) {
            return inputText;
        }
        
        random_device rd;
        mt19937 gen(rd());
        string result = words[0];
        
        shared_lock<shared_mutex> lock(graphMutex);
        for (size_t i = 1; i < words.size(); ++i) {
            const string& word1 = words[i-1];
            const string& word2 = words[i];
            
            vector<string> bridges = getBridgeWords(word1, word2, false);
            
            if (!bridges.empty()) {
                uniform_int_distribution<> dis(0, bridges.size() - 1);
                string bridge = bridges[dis(gen)];
                result += " " + bridge;
            }
            result += " " + word2;
        }
        return result;
    }

    string getShortestPath(const string& word1, const string& word2) {
        auto distances = computeShortestPaths(word1);
=======
    string cleanedInput = cleanString(inputText);
    istringstream iss(cleanedInput);
    vector<string> words;
    string word;
    
    while (iss >> word) {
        words.push_back(word);
    }
    
    if (words.size() < 2) {
        return inputText;
    }
    
    string result = words[0];
    random_device rd;
    mt19937 gen(rd());
    
    for (size_t i = 1; i < words.size(); ++i) {
        const string& word1 = words[i-1];
        const string& word2 = words[i];
        
        // 不显示警告信息
        vector<string> bridges = getBridgeWords(word1, word2, false);
        
        if (!bridges.empty()) {
            uniform_int_distribution<> dis(0, bridges.size() - 1);
            string bridge = bridges[dis(gen)];
            result += " " + bridge;
        }
        result += " " + word2;
    }
    
    return result;
}

    unordered_map<string, pair<int, string>> shortestPath(const string& start) {
        unordered_map<string, pair<int, string>> distances;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        
        for (const auto& node : adjacencyList) {
            distances[node.first] = {numeric_limits<int>::max(), ""};
        }
        
        if (distances.find(start) == distances.end()) {
            return distances;
        }
        
        distances[start] = {0, ""};
        pq.push({0, start});
        
        while (!pq.empty()) {
            string current = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();
            
            if (currentDist > distances[current].first) {
                continue;
            }
            
            for (const auto& neighbor : adjacencyList[current]) {
                string next = neighbor.first;
                int weight = neighbor.second;
                int newDist = currentDist + weight;
                
                if (newDist < distances[next].first) {
                    distances[next] = {newDist, current};
                    pq.push({newDist, next});
                }
            }
        }
        
        return distances;
    }

    string getShortestPath(const string& word1, const string& word2) {
        auto distances = shortestPath(word1);
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        
        if (distances.find(word2) == distances.end() || 
            distances[word2].first == numeric_limits<int>::max()) {
            return "";
        }
        
        vector<string> path;
        string current = word2;
        
        while (current != "") {
            path.push_back(current);
            current = distances[current].second;
        }
        
        reverse(path.begin(), path.end());
        
        string result;
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) result += " -> ";
            result += path[i];
        }
<<<<<<< HEAD
        return result;
    }

    void calculatePageRank(double damping = 0.85, int iterations = 1000, double epsilon = 1e-8) {
        unique_lock<shared_mutex> lock(graphMutex);
        unordered_set<string> nodes;
        for (const auto& [from, neighbors] : adjacencyList) {
            nodes.insert(from);
            for (const auto& [to, _] : neighbors) {
                nodes.insert(to);
            }
        }
        
        const double N = nodes.size();
        const double initialValue = 1.0 / N;
        pageRank.clear();
        
        for (const string& node : nodes) {
            pageRank[node] = initialPR.count(node) ? initialPR[node] : initialValue;
        }
        
        for (int iter = 0; iter < iterations; ++iter) {
            unordered_map<string, double> newPR;
            double danglingSum = 0.0;
            
            for (const auto& node : nodes) {
                if (adjacencyList[node].empty()) {
                    danglingSum += pageRank[node];
                }
            }
            
            for (const auto& node : nodes) {
                double sum = 0.0;
                for (const auto& [from, neighbors] : adjacencyList) {
                    if (neighbors.count(node)) {
                        sum += pageRank[from] / neighbors.size();
                    }
                }
                newPR[node] = (1.0 - damping)/N + damping * (sum + danglingSum/N);
            }
            
            double diff = 0.0;
            for (const auto& [node, pr] : pageRank) {
                diff += abs(pr - newPR[node]);
            }
            
            pageRank = move(newPR);
            if (diff < epsilon) {
                cout << "PageRank converged after " << iter+1 << " iterations" << endl;
                break;
            }
        }
    }
=======
        
        return result;
    }

   void calculatePageRank(double damping = 0.85, int iterations = 1000, double epsilon = 1e-8) {
    unordered_set<string> nodes;
    // 收集所有节点（包括只有入边的节点）
    for (const auto& entry : adjacencyList) {
        nodes.insert(entry.first);
        for (const auto& neighbor : entry.second) {
            nodes.insert(neighbor.first);
        }
    }
    
    const double N = nodes.size();
    const double initialValue = 1.0 / N;
    
    // 初始化PR值
    for (const string& node : nodes) {
        pageRank[node] = (initialPR.find(node) != initialPR.end()) ? 
                         initialPR[node] : initialValue;
    }
    
    for (int iter = 0; iter < iterations; ++iter) {
        unordered_map<string, double> newPR;
        double danglingSum = 0.0;
        
        // 1. 计算悬挂节点的PR总和
        for (const string& node : nodes) {
            if (adjacencyList[node].empty()) {
                danglingSum += pageRank[node];
            }
        }
        
        // 2. 计算每个节点的新PR值
        for (const string& node : nodes) {
            double sum = 0.0;
            
            // 计算所有入链节点的贡献
            for (const auto& entry : adjacencyList) {
                if (entry.second.find(node) != entry.second.end()) {
                    int outDegree = entry.second.size();
                    sum += pageRank[entry.first] / outDegree;
                }
            }
            
            // 正确计算公式
            newPR[node] = (1.0 - damping)/N + damping * (sum + danglingSum/N);
        }
        
        // 3. 检查收敛条件
        double diff = 0.0;
        for (const auto& entry : pageRank) {
            diff += abs(entry.second - newPR[entry.first]);
            if (diff < epsilon) break;
        }
        
        pageRank = newPR;
        if (diff < epsilon) {
            cout << "PageRank在" << iter+1 << "次迭代后收敛" << endl;
            break;
        }
    }
}
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5

    void displayPageRank(int topN = 10) {
        vector<pair<string, double>> rankedNodes(pageRank.begin(), pageRank.end());
        sort(rankedNodes.begin(), rankedNodes.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });
        
        cout << "PageRank values (top " << topN << "):" << endl;
        for (int i = 0; i < min(topN, (int)rankedNodes.size()); ++i) {
            cout << rankedNodes[i].first << ": " << fixed << setprecision(6) << rankedNodes[i].second << endl;
        }
    }

    void stopRandomWalk() {
        stopWalk = true;
    }

    string randomWalk() {
        stopWalk = false;
        
        if (adjacencyList.empty()) {
            return "";
        }
        
        random_device rd;
        mt19937 gen(rd());
        vector<string> nodes;
        for (const auto& entry : adjacencyList) {
            nodes.push_back(entry.first);
        }
        uniform_int_distribution<> dis(0, nodes.size() - 1);
        
        string current = nodes[dis(gen)];
        unordered_set<string> visitedEdges;
        vector<string> walk;
        walk.push_back(current);
        
<<<<<<< HEAD
        cout << "Random walk started. Press Enter to stop..." << endl;
        
        while (!stopWalk) {
            if (adjacencyList[current].empty()) {
                cout << "Node '" << current << "' has no outgoing edges. Walk stopped." << endl;
=======
        cout << "随机游走开始，按回车键停止..." << endl;
        
        while (!stopWalk) {
            if (adjacencyList[current].empty()) {
                cout << "节点 '" << current << "' 没有出边，游走终止" << endl;
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
                break;
            }
            
            vector<string> neighbors;
            for (const auto& neighbor : adjacencyList[current]) {
                neighbors.push_back(neighbor.first);
            }
            
            uniform_int_distribution<> neighborDis(0, neighbors.size() - 1);
            string next = neighbors[neighborDis(gen)];
            string edge = current + "->" + next;
            
            if (visitedEdges.find(edge) != visitedEdges.end()) {
<<<<<<< HEAD
                cout << "Repeated edge '" << edge << "'. Walk stopped." << endl;
=======
                cout << "重复边 '" << edge << "'，游走终止" << endl;
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
                break;
            }
            
            visitedEdges.insert(edge);
            walk.push_back(next);
            current = next;
            
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        
        string result;
        for (size_t i = 0; i < walk.size(); ++i) {
            if (i != 0) result += " ";
            result += walk[i];
        }
<<<<<<< HEAD
=======
        
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        return result;
    }

    void setInitialPR(const string& word, double value) {
        initialPR[word] = value;
    }

    static string cleanString(const string& str) {
        string cleaned;
        for (char ch : str) {
            if (isalpha(ch) || isspace(ch)) {
                cleaned += tolower(ch);
            } else {
                cleaned += ' ';
            }
        }
        return cleaned;
    }
};

void processFile(const string& filename, DirectedGraph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
<<<<<<< HEAD
        cerr << "Cannot open file: " << filename << endl;
=======
        cerr << "无法打开文件: " << filename << endl;
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        return;
    }

    string line;
    vector<string> words;
<<<<<<< HEAD
    words.reserve(1000);
    
    while (getline(file, line)) {
        string cleaned = DirectedGraph::cleanString(line);
        istringstream lineStream(cleaned);
        string word;
        words.clear();
        
        while (lineStream >> word) {
            if (word.size() > 100) word = word.substr(0, 100);
            words.push_back(word);
        }
        
=======
    
    while (getline(file, line)) {
        string cleanedLine = DirectedGraph::cleanString(line);
        istringstream stream(cleanedLine);
        string word;
        words.clear();
        while (stream >> word) {
            words.push_back(word);
        }

>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        for (size_t i = 0; i < words.size() - 1; ++i) {
            graph.addEdge(words[i], words[i + 1]);
        }
    }
<<<<<<< HEAD
}

void displayMenu() {
    cout << "\n===== Menu =====" << endl;
    cout << "1. Show graph" << endl;
    cout << "2. Query bridge words" << endl;
    cout << "3. Generate new text" << endl;
    cout << "4. Find shortest path" << endl;
    cout << "5. Calculate PageRank" << endl;
    cout << "6. Random walk" << endl;
    cout << "7. Exit" << endl;
    cout << "================" << endl;
    cout << "Enter choice (1-7): ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string filename;
    cout << "Enter text file path: ";
    getline(cin, filename);

    DirectedGraph graph;
    
    atomic<bool> done(false);
    thread progress([&done]() {
        const char anim[] = {'|', '/', '-', '\\'};
        int i = 0;
        while (!done) {
            cout << "\rProcessing... " << anim[i++ % 4] << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        cout << "\rDone!                    " << endl;
    });
    
    processFile(filename, graph);
    done = true;
    progress.join();
=======

    file.close();
}

void displayMenu() {
    cout << "\n===== 功能菜单 =====" << endl;
    cout << "1. 展示生成的有向图" << endl;
    cout << "2. 查询桥接词" << endl;
    cout << "3. 根据bridge word生成新文本" << endl;
    cout << "4. 计算最短路径" << endl;
    cout << "5. 计算PageRank" << endl;
    cout << "6. 随机游走" << endl;
    cout << "7. 退出程序" << endl;
    cout << "====================" << endl;
    cout << "请选择功能 (1-7): ";
}

int main() {
    string filename;
    cout << "请输入文本文件的完整路径: ";
    getline(cin, filename);

    DirectedGraph graph;
    processFile(filename, graph);
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5

    int choice;
    do {
        displayMenu();
        cin >> choice;
<<<<<<< HEAD
        cin.ignore();

        switch (choice) {
            case 1: graph.display(); break;
            case 2: {
                string word1, word2;
                cout << "Enter two words: ";
                cin >> word1 >> word2;
                auto bridges = graph.getBridgeWords(word1, word2);
                if (bridges.empty()) {
                    cout << "No bridge words!" << endl;
                } else {
                    cout << "Bridge words: ";
                    for (const auto& w : bridges) cout << w << " ";
                    cout << endl;
=======
        cin.ignore(); // 清除输入缓冲区

        switch (choice) {
            case 1: {
                cout << "\n生成的有向图结构如下:" << endl;
                graph.display();
                break;
            }
            case 2: {
                string word1, word2;
                cout << "请输入第一个单词: ";
                cin >> word1;
                cout << "请输入第二个单词: ";
                cin >> word2;
                
                word1 = DirectedGraph::cleanString(word1);
                word2 = DirectedGraph::cleanString(word2);
                
                vector<string> bridges = graph.getBridgeWords(word1, word2);
                if (bridges.empty() && graph.containsWord(word1) && graph.containsWord(word2)) {
                    cout << "No bridge words from " << word1 << " to " << word2 << "!" << endl;
                } else if (!bridges.empty()) {
                    cout << "The bridge words from " << word1 << " to " << word2 << " are: ";
                    for (size_t i = 0; i < bridges.size(); ++i) {
                        if (i != 0) {
                            if (i == bridges.size() - 1) {
                                cout << " and ";
                            } else {
                                cout << ", ";
                            }
                        }
                        cout << bridges[i];
                    }
                    cout << "." << endl;
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
                }
                break;
            }
            case 3: {
<<<<<<< HEAD
                string text;
                cout << "Enter text: ";
                getline(cin, text);
                cout << "Generated text: " << graph.generateNewText(text) << endl;
                break;
            }
            case 4: {
                string from, to;
                cout << "Enter start and end: ";
                cin >> from >> to;
                string path = graph.getShortestPath(from, to);
                if (path.empty()) {
                    cout << "No path exists!" << endl;
                } else {
                    cout << "Shortest path: " << path << endl;
=======
                string inputText;
                cout << "请输入一行新文本: ";
                getline(cin, inputText);
                
                string newText = graph.generateNewText(inputText);
                cout << "生成的新文本: " << newText << endl;
                break;
            }
            case 4: {
                string word1, word2;
                cout << "请输入起始单词: ";
                cin >> word1;
                cout << "请输入目标单词 (留空则计算到所有单词的最短路径): ";
                cin.ignore();
                getline(cin, word2);
                
                if (word2.empty()) {
                    auto distances = graph.shortestPath(word1);
                    cout << "\n从 " << word1 << " 到其他单词的最短路径:" << endl;
                    for (const auto& entry : distances) {
                        if (entry.first != word1) {
                            if (entry.second.first == numeric_limits<int>::max()) {
                                cout << word1 << " -> " << entry.first << ": 不可达" << endl;
                            } else {
                                string path = graph.getShortestPath(word1, entry.first);
                                cout << path << " (长度: " << entry.second.first << ")" << endl;
                            }
                        }
                    }
                } else {
                    string path = graph.getShortestPath(word1, word2);
                    if (path.empty()) {
                        cout << word1 << " 和 " << word2 << " 之间不可达" << endl;
                    } else {
                        auto distances = graph.shortestPath(word1);
                        cout << "最短路径: " << path << endl;
                        cout << "路径长度: " << distances[word2].first << endl;
                    }
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
                }
                break;
            }
            case 5: {
                graph.calculatePageRank();
                graph.displayPageRank();
                break;
            }
            case 6: {
<<<<<<< HEAD
                cout << "Press Enter to stop random walk..." << endl;
                string walk = graph.randomWalk();
                cout << "Walk path: " << walk << endl;
                break;
            }
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
=======
                string walkResult;
                thread walkThread([&]() {
                    walkResult = graph.randomWalk();
                });
                
                cin.get();
                graph.stopRandomWalk();
                walkThread.join();
                
                cout << "随机游走结果: " << walkResult << endl;
                
                ofstream outFile("random_walk.txt");
                if (outFile.is_open()) {
                    outFile << walkResult;
                    outFile.close();
                    cout << "结果已写入 random_walk.txt 文件" << endl;
                } else {
                    cerr << "无法写入文件" << endl;
                }
                break;
            }
            case 7: {
                cout << "退出程序..." << endl;
                break;
            }
            default: {
                cout << "无效的选择，请重新输入!" << endl;
                break;
            }
>>>>>>> 18099d298ff3c6e540d2b81f4ddacfa7b5420bc5
        }
    } while (choice != 7);

    return 0;
}