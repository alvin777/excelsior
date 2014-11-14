/**
 * Created by alvin777 on 07/11/14.
 */
public class WordNet {

    private SeparateChainingHashST<String, Bag<Integer>> wordToIdMap = new SeparateChainingHashST<String, Bag<Integer>>();
    private SeparateChainingHashST<Integer, String> idToSynsetMap = new SeparateChainingHashST<Integer, String>();
    private SAP sap;
    private int maxVertex = 0;

    // constructor takes the name of the two input files
    public WordNet(String synsets, String hypernyms) {
        parseSynsets(synsets);
        parseHypernyms(hypernyms);
    }

    private void parseSynsets(String synsets) {
        In in = new In(synsets);
        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] strings = line.split(",");

            if (strings.length < 2) {
                continue;
            }

            int id = Integer.parseInt(strings[0]);
            String[] wordsArray = strings[1].split("\\s+");
//            String definition = strings[2];

            for (String word : wordsArray) {
                Bag<Integer> bag = wordToIdMap.get(word);
                if (bag == null) {
                    bag = new Bag<Integer>();
                    wordToIdMap.put(word, bag);
                }
                bag.add(id);
            }

            idToSynsetMap.put(id, strings[1]);

//            StdOut.printf("%6d %s\n", id, strings[1]);

//            idToDefinitionMap.put(id, definition);
            if (id > maxVertex) {
                maxVertex = id;
            }
        }
    }

    private void parseHypernyms(String hypernyms) {

        Digraph G = new Digraph(maxVertex + 1);

//        StdOut.printf("maxVertex: %d, G.V(): %d\n", maxVertex, G.V());

        In in = new In(hypernyms);
        while (in.hasNextLine()) {
            String line = in.readLine();
            String[] strings = line.split(",");

            if (strings.length < 2) {
                continue;
            }

            int u = Integer.parseInt(strings[0]);

            for (int i = 1; i < strings.length; i++) {
                int v = Integer.parseInt(strings[i]);
                G.addEdge(u, v);
            }
        }

        checkGraph(G);

        sap = new SAP(G);
    }

    private static int countIterable(Iterable it) {
        int count = 0;
        for (Object o : it) {
            count++;
        }
        return count;
    }

    private void checkGraph(Digraph g) {
        DirectedCycle cycle = new DirectedCycle(g);
        if (cycle.hasCycle()) throw new IllegalArgumentException();

        boolean foundRoot = false;
        for (int i = 0; i < g.V(); i++) {
            int count = countIterable(g.adj(i));

            if (count == 0) {
                if (!foundRoot) {
                    foundRoot = true;
                } else {
                    throw new IllegalArgumentException();
                }
            }
        }
    }

    // returns all WordNet nouns
    public Iterable<String> nouns() {
        return wordToIdMap.keys();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word) {
        return wordToIdMap.contains(word);
    }

    // distance between nounA and nounB (defined below)
    public int distance(String nounA, String nounB) {
        if (nounA == null || nounB == null) throw new java.lang.NullPointerException();
        if (!wordToIdMap.contains(nounA) || !wordToIdMap.contains(nounB)) throw new java.lang.IllegalArgumentException();

        return sap.length(wordToIdMap.get(nounA), wordToIdMap.get(nounB));
    }

    // a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB
    // in a shortest ancestral path (defined below)
    public String sap(String nounA, String nounB) {
        if (nounA == null || nounB == null) throw new java.lang.NullPointerException();
        if (!wordToIdMap.contains(nounA) || !wordToIdMap.contains(nounB)) throw new java.lang.IllegalArgumentException();


        String synset = "";
        int ancestor = sap.ancestor(wordToIdMap.get(nounA), wordToIdMap.get(nounB));
        if (ancestor >= 0) {
            synset = idToSynsetMap.get(ancestor);
        }

        return synset;
    }

    public static void main(String[] args) {
        WordNet wordNet = new WordNet("synsets.txt", "hypernyms.txt");
//        WordNet wordNet = new WordNet("synsets15.txt", "hypernymsPath15.txt");
//        WordNet wordNet = new WordNet(args[0], args[1]);
//        WordNet wordNet = new WordNet("synsets3.txt", "hypernymsInvalidTwoRoots.txt");
//        WordNet wordNet = new WordNet("synsets3.txt", "hypernymsInvalidCycle.txt");

        class WordsPair {
            private String first;
            private String second;
            public WordsPair(String first, String second) {
                this.first = first;
                this.second = second;
            }
        }

//        for (int key : wordNet.idToSynsetMap.keys()) {
//            StdOut.printf("%6d %s\n", key, wordNet.idToSynsetMap.get(key));
//        }

        WordsPair[] wordsPairs = {
//                new WordsPair("worm", "bird"),
//                new WordsPair("individual", "edible_fruit"),
//                new WordsPair("individual", "physical_entity"),
//                new WordsPair("edible_fruit", "physical_entity"),
//                new WordsPair("white_marlin", "mileage"),
//                new WordsPair("Black_Plague", "black_marlin"),
//                new WordsPair("American_water_spaniel", "histology"),
//                new WordsPair("Brown_Swiss", "barrel_roll"),
//                new WordsPair("a", "a"),
                new WordsPair("Taimyr_Peninsula", "opera_house"),
        };

        for (WordsPair pair : wordsPairs) {
            StdOut.printf("%-30s %-30s %-30s %d\n", pair.first, pair.second, wordNet.sap(pair.first, pair.second), wordNet.distance(pair.first, pair.second));
        }

        int nounsCount = countIterable(wordNet.nouns());

        StdOut.printf("wordNet.nouns() count: %d", nounsCount);
    }
}