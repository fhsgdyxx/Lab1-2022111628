package test;
import org.junit.Test;
import static org.junit.Assert.*;

import calc.*;
public class mytest {
	 mycalc graph = new mycalc();
	 @Test
	    public void testEmptyInput() {
	        String result = graph.calcShortestPath("" , "");
	        assertEquals("Input words cannot be empty!", result.trim());
	    }

	    // 测试用例2: 第一个单词不存在
	    @Test
	    public void testFirstWordNotExist() {
	        String result = graph.calcShortestPath("busda", "the");
	        assertEquals("No \"busda\" in the graph!", result);
	    }

	    // 测试用例3: 无路径存在
	    @Test
	    public void testNoPathExists() {
	        String result = graph.calcShortestPath("again", "the");
	        assertEquals("No path exists from \"again\" to \"the\"!", result);
	    }

	    // 测试用例4: 存在多跳路径
	    @Test
	    public void testMultiHopPath() {
	        String result = graph.calcShortestPath("and", "the");
	        // 验证输出格式和关键路径节点
	        assertTrue(result.startsWith("The shortest path from \"and\" to \"the\" is:"));
	        assertTrue(result.contains("and → shared → the"));
	        assertTrue(result.endsWith("."));
	    }
	}


