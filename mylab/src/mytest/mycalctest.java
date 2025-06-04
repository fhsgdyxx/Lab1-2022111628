package mytest;

import org.junit.Test;
import static org.junit.Assert.*;

import mycalc.*;

public class mycalctest {
    mylab graph = new mylab();
   

    @Test
    public void testExistingBridgeWords() {
        String result = graph.queryBridgeWords("and", "the");
        assertEquals("The bridge word from \"and\" to \"the\" is: shared.", result);
    }

    @Test
    public void testNoBridgeWords() {
        String result = graph.queryBridgeWords("but", "the");
        assertEquals("No bridge words from \"but\" to \"the\"!", result);
    }

    @Test
    public void testFirstWordNotInGraph() {
        String result = graph.queryBridgeWords("unknown", "scientist");
        assertEquals("No \"unknown\" in the graph!", result);
    }

    @Test
    public void testSecondWordNotInGraph() {
        String result = graph.queryBridgeWords("scientist", "unknown");
        assertEquals("No \"unknown\" in the graph!", result);
    }

    @Test
    public void testBothWordsNotInGraph() {
        String result = graph.queryBridgeWords("apple", "banana");
        assertTrue(result.startsWith("No \""));
    }

    @Test
    public void testEmptyFirstWord() {
        String result = graph.queryBridgeWords("", "data");
        assertEquals("Input words cannot be empty!", result);
    }

    @Test
    public void testEmptySecondWord() {
        String result = graph.queryBridgeWords("the", "");
        assertEquals("Input words cannot be empty!", result);
    }

    @Test
    public void testBothWordsEmpty() {
        String result = graph.queryBridgeWords("", "");
        assertEquals("Input words cannot be empty!", result);
    }

    @Test
    public void testSameWordInput() {
        String result = graph.queryBridgeWords("the", "the");
        assertEquals("No bridge words from \"the\" to \"the\"!", result);
    }

    @Test
    public void testMultipleBridgeWords() {
        // 添加额外边以创建多个桥接词的情况
 
        String result = graph.queryBridgeWords("the", "wrote");
        assertEquals("The bridge words from \"the\" to \"wrote\" are: a and data.", result);
    }
}