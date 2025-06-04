package calc;

import java.util.*;
import java.util.concurrent.locks.*;

public class mycalc {
    private final Map<String, Map<String, Integer>> adjacencyList = new HashMap<>();
    private final ReadWriteLock graphLock = new ReentrantReadWriteLock();

    // 构建图结构
    public mycalc() {
        String text = "The scientist carefully analyzed the data wrote a detailed report and shared the report with the team but the team requested more data so the scientist analyzed it again bus ";
        String[] words = text.toLowerCase().split("\\s+");
        for (int i = 0; i < words.length - 1; i++) {
            addEdge(words[i], words[i + 1]);
        }
    }

    public void addEdge(String from, String to) {
        graphLock.writeLock().lock();
        try {
            adjacencyList.computeIfAbsent(from, k -> new HashMap<>())
                       .merge(to, 1, Integer::sum);
        } finally {
            graphLock.writeLock().unlock();
        }
    }

    public String calcShortestPath(String word1, String word2) {
        if (word1 == null || word2 == null || word1.isEmpty() || word2.isEmpty()) {
            return "Input words cannot be empty!";
        }
        
        word1 = word1.toLowerCase();
        word2 = word2.toLowerCase();
        
        graphLock.readLock().lock();
        try {
            // 检查单词是否存在
            if (!adjacencyList.containsKey(word1)) {
                return "No \"" + word1 + "\" in the graph!";
            }
            if (!adjacencyList.containsKey(word2)) {
                return "No \"" + word2 + "\" in the graph!";
            }
            
            // 使用BFS算法计算最短路径（所有边权重为1）
            Map<String, String> previousNodes = new HashMap<>();
            Queue<String> queue = new LinkedList<>();
            Set<String> visited = new HashSet<>();
            
            queue.add(word1);
            visited.add(word1);
            boolean found = false;
            
            while (!queue.isEmpty() && !found) {
                String current = queue.poll();
                
                // 遍历所有邻居
                for (String neighbor : adjacencyList.getOrDefault(current, Collections.emptyMap()).keySet()) {
                    if (!visited.contains(neighbor)) {
                        previousNodes.put(neighbor, current);
                        visited.add(neighbor);
                        queue.add(neighbor);
                        
                        // 如果找到目标节点，提前结束
                        if (neighbor.equals(word2)) {
                            found = true;
                            break;
                        }
                    }
                }
            }
            
            // 构建路径
            if (!previousNodes.containsKey(word2)) {
                return "No path exists from \"" + word1 + "\" to \"" + word2 + "\"!";
            }
            
            List<String> path = new ArrayList<>();
            String current = word2;
            while (current != null) {
                path.add(current);
                current = previousNodes.get(current);
            }
            Collections.reverse(path);
            
            return "The shortest path from \"" + word1 + "\" to \"" + word2 + "\" is: " + 
                   String.join(" → ", path) + ".";
        } finally {
            graphLock.readLock().unlock();
        }
    }

    public static void main(String[] args) {
        mycalc graph = new mycalc();
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Word Graph Shortest Path Finder");
        System.out.println("Based on text: \"The scientist carefully analyzed the data...\"");
        System.out.println("Enter two words to find shortest path between them (or 'quit' to exit)");
        
        while (true) {
            System.out.print("\nEnter first word: ");
            String word1 = scanner.nextLine().trim();
            
            if (word1.equalsIgnoreCase("quit")) {
                break;
            }
            
            System.out.print("Enter second word: ");
            String word2 = scanner.nextLine().trim();
            
            if (word2.equalsIgnoreCase("quit")) {
                break;
            }
            
            String result = graph.calcShortestPath(word1, word2);
            System.out.println("\nResult: " + result);
            
            System.out.println("\nTry another pair or enter 'quit' to exit");
        }
        
        System.out.println("Goodbye!");
        scanner.close();
    }
}