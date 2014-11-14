/**
 * Created by alvin777 on 07/11/14.
 */
public class Outcast {
    private WordNet wordNet;

    // constructor takes a WordNet object
    public Outcast(WordNet wordNet) {
        this.wordNet = wordNet;
    }

    // given an array of WordNet nouns, return an outcast
    public String outcast(String[] nouns) {
        int maxNounDistance = 0;
        int outcastIndex = -1;

        for (int i = 0; i < nouns.length; i++) {
            int nounDistance = 0;
            for (String noun : nouns) {
                nounDistance += wordNet.distance(nouns[i], noun);
            }

            if (nounDistance > maxNounDistance) {
                maxNounDistance = nounDistance;
                outcastIndex = i;
            }
        }

        if (outcastIndex < 0) {
            return "";
        }

        return nouns[outcastIndex];
    }

    // see test client below
    public static void main(String[] args) {
        WordNet wordnet = new WordNet(args[0], args[1]);
        Outcast outcast = new Outcast(wordnet);
        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();

            Stopwatch sw = new Stopwatch();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
            StdOut.println("Time: " + sw.elapsedTime());
        }
    }
}