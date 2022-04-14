void solve_pyramid_scheme(int father_node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings) {
    vector<int> melhor_soma_filhos{1, scheme[father_node][(int)scheme[father_node].size()-1]};
    vector<int> sons = vector<int>(scheme[father_node].begin(), scheme[father_node].end()-1); // slice list to only have the children and not the cost of the node

    vector<int> sum_price_sons{0, 0};
    vector<vector<int>> temp_rating_son{{0, 0}, {0, 0}};

    for (int son: sons) {
        solve_pyramid_scheme(son, scheme, ratings);
        temp_rating_son = ratings[son];
        if (temp_rating_son[0][0] > temp_rating_son[1][0])
        {
            melhor_soma_filhos[0] += temp_rating_son[1][0];
            melhor_soma_filhos[1] += temp_rating_son[1][1];
        }
        else if (temp_rating_son[0][0] < temp_rating_son[1][0])
        {
            melhor_soma_filhos[0] += temp_rating_son[0][0];
            melhor_soma_filhos[1] += temp_rating_son[0][1];
        }
        else if (temp_rating_son[0][1] < temp_rating_son[1][1])
        {
            melhor_soma_filhos[0] += temp_rating_son[0][0];
            melhor_soma_filhos[1] += temp_rating_son[1][1];
        }
        else
        {
            melhor_soma_filhos[0] += temp_rating_son[0][0];
            melhor_soma_filhos[1] += temp_rating_son[0][1];
        }
        sum_price_sons[0] += temp_rating_son[0][0];
        sum_price_sons[1] += temp_rating_son[0][1];
    }
    ratings[father_node] = {melhor_soma_filhos, sum_price_sons};
}
