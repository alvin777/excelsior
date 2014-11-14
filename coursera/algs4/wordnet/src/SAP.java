import java.util.Arrays;

/**
 * Created by alvin777 on 07/11/14.
 */
public class SAP {

    private Digraph G;

    // constructor takes a digraph (not necessarily a DAG)
    public SAP(Digraph G) {
        this.G = new Digraph(G);
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w) {
        return getAncestorDistance(v, w).distance;
    }

    // a common ancestor of v and w that participates in a shortest ancestral path; -1 if no such path
    public int ancestor(int v, int w) {
        return getAncestorDistance(v, w).ancestor;
    }

    // length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        return getAncestorDistance(v, w).distance;
    }

    // a common ancestor that participates in shortest ancestral path; -1 if no such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        return getAncestorDistance(v, w).ancestor;
    }


    // implementation

    private class AncestorDistance {
        private int distance = -1;
        private int ancestor = -1;
    }

    private AncestorDistance getAncestorDistance(int v, int w) {

        if (v == w) {
            AncestorDistance ancestorDistance = new AncestorDistance();
            ancestorDistance.distance = 0;
            ancestorDistance.ancestor = v;
            return ancestorDistance;
        }

        BreadthFirstDirectedPaths pathsV = new BreadthFirstDirectedPaths(G, v);
        BreadthFirstDirectedPaths pathsW = new BreadthFirstDirectedPaths(G, w);

        AncestorDistance ancestorDistance = new AncestorDistance();

        for (int i = 0; i < G.V(); i++) {
            if (!pathsV.hasPathTo(i) || !pathsW.hasPathTo(i)) continue;

            int distance = pathsV.distTo(i) + pathsW.distTo(i);
            if (distance < ancestorDistance.distance || ancestorDistance.ancestor == -1) {
                ancestorDistance.distance = distance;
                ancestorDistance.ancestor = i;
            }
        }

        return ancestorDistance;
    }

    private AncestorDistance getAncestorDistance(Iterable<Integer> v, Iterable<Integer> w) {

        int[] distancesArray = new int[G.V()];

        BreadthFirstDirectedPaths paths = new BreadthFirstDirectedPaths(G, v);
        for (int i = 0; i < distancesArray.length; i++) {
            if (paths.hasPathTo(i)) {
                distancesArray[i] = paths.distTo(i);
            } else {
                distancesArray[i] = -1;
            }
        }

        AncestorDistance ancestorDistance = new AncestorDistance();

        paths = new BreadthFirstDirectedPaths(G, w);
        for (int i = 0; i < distancesArray.length; i++) {
            if (distancesArray[i] >= 0 && paths.hasPathTo(i)) {
                int distance = distancesArray[i] + paths.distTo(i);
                if (distance < ancestorDistance.distance || ancestorDistance.ancestor == -1) {
                    ancestorDistance.distance = distance;
                    ancestorDistance.ancestor = i;
                }
            }
        }

//        BreadthFirstDirectedPaths pathsV = new BreadthFirstDirectedPaths(G, v);
//        BreadthFirstDirectedPaths pathsW = new BreadthFirstDirectedPaths(G, w);
//
//        for (int i = 0; i < G.V(); i++) {
//            if (!pathsV.hasPathTo(i) || !pathsW.hasPathTo(i)) continue;
//
//            int distance = pathsV.distTo(i) + pathsW.distTo(i);
//            if (distance < ancestorDistance.distance || ancestorDistance.ancestor == -1) {
//                ancestorDistance.distance = distance;
//                ancestorDistance.ancestor = i;
//            }
//        }

        return ancestorDistance;
    }

    //    // do unit testing of this class
//    public static void main(String[] args) {
//        In in = new In(args[0]);
//        Digraph G = new Digraph(in);
//        SAP sap = new SAP(G);
//        while (!StdIn.isEmpty()) {
//            int v = StdIn.readInt();
//            int w = StdIn.readInt();
//            int length   = sap.length(v, w);
//            int ancestor = sap.ancestor(v, w);
//            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
//        }
//    }

}