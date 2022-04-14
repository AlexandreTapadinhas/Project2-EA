void solve(int v)
{
    vector<int> nos = inputOrganized[v];
    vector<int> melhor_soma_filhos{1, nos.back()};
    vector<int> soma_filhos_colocados{0, 0};
    vector<vector<int>> temp{{0, 0}, {0, 0}};

    for (int i = 0; i < (int)nos.size() - 1; i++)
    {
        solve(nos[i]);
        temp = nodesSums[nos[i]];
        if (temp[0][0] > temp[1][0])
        {
            melhor_soma_filhos[0] += temp[1][0];
            melhor_soma_filhos[1] += temp[1][1];
        }
        else if (temp[0][0] < temp[1][0])
        {
            melhor_soma_filhos[0] += temp[0][0];
            melhor_soma_filhos[1] += temp[0][1];
        }
        else if (temp[0][1] < temp[1][1])
        {
            melhor_soma_filhos[0] += temp[0][0];
            melhor_soma_filhos[1] += temp[1][1];
        }
        else
        {
            melhor_soma_filhos[0] += temp[0][0];
            melhor_soma_filhos[1] += temp[0][1];
        }
        soma_filhos_colocados[0] += temp[0][0];
        soma_filhos_colocados[1] += temp[0][1];
    }
    nodesSums[v] = {melhor_soma_filhos, soma_filhos_colocados};
}