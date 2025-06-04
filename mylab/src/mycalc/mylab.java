package mycalc;
import java.util.*;
import java.util.concurrent.locks.*;
public class mylab {
	 private final Map<String, Map<String, Integer>> adjacencyList = new HashMap<>();
	    private final ReadWriteLock graphLock = new ReentrantReadWriteLock();

	    // 构建图结构
	    public mylab() {
	        String text = "The scientist carefully analyzed the data wrote a detailed report and shared the report with the team but the team requested more data so the scientist analyzed it again the a wrote";
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

	    public String queryBridgeWords(String word1, String word2) {
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
	            
	            // 查找桥接词
	            List<String> bridgeWords = new ArrayList<>();
	            Map<String, Integer> neighbors = adjacencyList.get(word1);
	            
	            for (String neighbor : neighbors.keySet()) {
	                if (adjacencyList.containsKey(neighbor) && 
	                    adjacencyList.get(neighbor).containsKey(word2)) {
	                    bridgeWords.add(neighbor);
	                }
	            }
	            
	            // 格式化输出
	            if (bridgeWords.isEmpty()) {
	                return "No bridge words from \"" + word1 + "\" to \"" + word2 + "\"!";
	            } else if (bridgeWords.size() == 1) {
	                return "The bridge word from \"" + word1 + "\" to \"" + word2 + "\" is: " + bridgeWords.get(0) + ".";
	            } else {
	                return "The bridge words from \"" + word1 + "\" to \"" + word2 + "\" are: " + 
	                       String.join(", ", bridgeWords.subList(0, bridgeWords.size()-1)) + 
	                       " and " + bridgeWords.get(bridgeWords.size()-1) + ".";
	            }
	        } finally {
	            graphLock.readLock().unlock();
	        }
	    }
	    public static void main(String[] args) {
	        mylab graph = new mylab();
	        Scanner scanner = new Scanner(System.in);
	        
	        System.out.println("Word Graph Bridge Words Finder");
	        System.out.println("Based on text: \"The scientist carefully analyzed the data...\"");
	        System.out.println("Enter two words to find bridge words between them (or 'quit' to exit)");
	        
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
	            
	            String result = graph.queryBridgeWords(word1, word2);
	            System.out.println("\nResult: " + result);
	            
	            System.out.println("\nTry another pair or enter 'quit' to exit");
	        }
	        
	        System.out.println("Goodbye!");
	        scanner.close();
	    }

}
