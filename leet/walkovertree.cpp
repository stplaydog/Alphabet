int maxNodesVisited(vector<int> parent, int L)
{
    int ret = 1;
    vector<vector<int> > child;
    bool visited[parent.size()];
    for (int i=0; i< parent.size(); i++)
    {
        child[parent[i]].push_back(i+1);
    }

    /* DFS */
    int hop = 1;
    int root = 0;
    while(hop<L)
    {
        bool exhaulsted = true;
        for(int i=0; i<child[root].size(); i++)
        {
            if(!visited[child[i]])
            {
                root = child[i];
                visited[root] = true;
                ++hop;
                ++ret;
                exhaulsted = false;
                break;
            }
        }
        if(exhaulsted)
        {
            root = parent[root];
            ++hop;
        }
    }
    return ret;
}

